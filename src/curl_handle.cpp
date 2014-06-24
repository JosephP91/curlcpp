//
//  curl_handle.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 12/06/14.
//

#include "curl_handle.h"
#include "curl_message.h"

using std::find;

// That's too deep. Let's typedef something
typedef curl_multi::curl_handle c_handle;
typedef curl_multi::curl_handle::curl_message c_message;

// Implementation of constructor.
c_handle::curl_handle(curl_multi &multi) : multi(multi) {
    // ... nothing to do here ...
}

// Implementation of copy constructor.
c_handle::curl_handle(const curl_handle &handle) : handlers(handle.handlers), multi(handle.multi) {
    // ... nothing to do here ...
}

// Implementation of constructor with an initializer list.
c_handle::curl_handle(curl_multi &multi, initializer_list<curl_easy> handlers_list) : multi(multi) {
    for_each(handlers_list.begin(),handlers_list.end(),[this](curl_easy handle) {
        this->add(handle);
    });
}

// Implementation of assignment operator.
c_handle &c_handle::operator=(const curl_handle &handle) {
    if (this == &handle) {
        return *this;
    }
    this->multi = handle.multi;
    this->handlers = handle.handlers;
    return *this;
}

// Implementation of destructor.
c_handle::~curl_handle() noexcept {
    for_each(this->handlers.begin(),this->handlers.end(),[this](curl_easy handler) {
        curl_multi_remove_handle(this->multi.curl,handler.get_curl());
    });
}

// Implementation of add method.
void c_handle::add(const curl_easy &handler) {
    const CURLMcode code = curl_multi_add_handle((this->multi).curl,handler.get_curl());
    if (code != CURLM_OK) {
        throw curl_error((this->multi).to_string(code),__FUNCTION__);
    }
    this->handlers.push_back(handler);
}

// Implementation of remove method.
void c_handle::remove(const curl_easy &handler) {
    const CURLMcode code = curl_multi_remove_handle((this->multi).curl,handler.get_curl());
    if (code != CURLM_OK) {
        throw curl_error((this->multi).to_string(code),__FUNCTION__);
    }
    this->handlers.erase(find(this->handlers.begin(),this->handlers.end(),handler));
}

// Implementation of read_info method.
vector<c_message> c_handle::read_info() {
    vector<curl_message> info;
    CURLMsg *msg = nullptr;
    while ((msg = curl_multi_info_read((this->multi).curl,&(this->multi).message_queued))) {
        if (msg->msg == CURLMSG_DONE) {
            for_each(this->handlers.begin(),this->handlers.end(),[msg,&info](curl_easy handler) {
                if (msg->easy_handle == handler.get_curl()) {
                    info.push_back(curl_message(msg->msg,handler,(msg->data).whatever,(msg->data).result));
                }
            });
        }
    }
    return info;
}
