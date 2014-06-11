/* 
 * File:   curl_multi.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 11:02 PM
 */

#include <algorithm>
#include "curl_multi.h"

using std::for_each;
using std::move;
using curl::curl_multi;

// Implementation of constructor.
curl_multi::curl_multi() : curl_interface() {
    this->curl = curl_multi_init();
    this->active_transfers = 0;
    this->message_queued = 0;
}

// Implementation of overloaded constructor.
curl_multi::curl_multi(const long flag) : curl_interface(flag) {
    curl_multi();
}

// Implementation of copy constructor to respect the rule of three.
curl_multi::curl_multi(const curl_multi &multi) : message_queued(multi.message_queued), active_transfers(multi.active_transfers) {
    this->curl = curl_multi_init();
    this->handlers = multi.handlers;
}

// Implementation of assignment operator to perform deep copy.
curl_multi &curl_multi::operator=(const curl_multi &multi) {
    if (this == &multi) {
        return *this;
    }
    this->curl = curl_multi_init();
    this->message_queued = multi.message_queued;
    this->active_transfers = multi.active_transfers;
    this->handlers = multi.handlers;
    return *this;
}

// Implementation of destructor.
curl_multi::~curl_multi() noexcept{
    for_each(this->handlers.begin(),this->handlers.end(),[this](curl_easy handler) {
        curl_multi_remove_handle(this->curl,handler.get_curl());
    });
    curl_multi_cleanup(this->curl);
}

// Implementation of addHandle method.
void curl_multi::add(const curl_easy &handler) {
    CURLMcode code = curl_multi_add_handle(this->curl,handler.get_curl());
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of removeHandle overloaded method.
void curl_multi::remove(const curl_easy &handler) {
    auto code = curl_multi_remove_handle(this->curl,handler.get_curl());
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of get_active_transfers method.
const int curl_multi::get_active_transfers() const noexcept {
    return this->active_transfers;
}

// Implementation of get_message_queued method.
const int curl_multi::get_message_queued() const noexcept {
    return this->message_queued;
}

// Implementation of read_info method
const vector<curl::curl_multi::curl_message> curl_multi::read_info() {
    vector<curl_message> info;
    CURLMsg *msg = nullptr;
    while ((msg = curl_multi_info_read(this->curl,&this->message_queued))) {
        if (msg->msg == CURLMSG_DONE) {
            for (auto handler : this->handlers) {
                if (msg->easy_handle == handler.get_curl()) {
                    info.push_back(curl_message(msg->msg,handler,(msg->data).whatever,(msg->data).result));
                }
            }
        }
    }
    return info;
}

// Implementation of perform method.
bool curl_multi::perform() {
    CURLMcode code = curl_multi_perform(this->curl,&this->active_transfers);
    if (code == CURLM_CALL_MULTI_PERFORM) {
        return false;
    }
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
    return true;
}

// Implementation of errorto_string method
const string curl_multi::to_string(const CURLMcode code) const noexcept {
    return string(curl_multi_strerror(code));
}