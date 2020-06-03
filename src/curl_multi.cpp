/**
 * File:   curl_multi.cpp
 * Author: Giuseppe Persico
 */

#include "curl_multi.h"

using curl::curl_multi;
using curl::curl_easy;

using std::vector;
using std::unique_ptr;

void curl_multi::multi_deleter::operator()(CURLM* ptr) const {
    curl_multi_cleanup(ptr);
}

curl_multi::curl_multi() : curl_multi(CURL_GLOBAL_ALL) {}

curl_multi::curl_multi(const long flag) : curl_interface(flag), curl(curl_multi_init()) {
    if (this->curl == nullptr) {
        throw curl_multi_exception("Null pointer intercepted", __FUNCTION__);
    }
    this->active_transfers = 0;
    this->message_queued = 0;
}

curl_multi::curl_multi(curl_multi&& other) NOEXCEPT : curl_interface(std::forward<curl_interface>(other)),
	  curl(std::move(other.curl)),
	  active_transfers(other.active_transfers),
	  message_queued(other.message_queued) {
}

curl_multi &curl_multi::operator=(curl_multi&& other) NOEXCEPT {
    if (this != &other) {
        curl = std::move(other.curl);
        active_transfers = other.active_transfers;
        message_queued = other.message_queued;
    }
    return *this;
}

curl_multi::~curl_multi() NOEXCEPT = default;

// Implementation of add method for easy handlers.
void curl_multi::add(const curl_easy &easy) {
    const CURLMcode code = curl_multi_add_handle(this->curl.get(),easy.get_curl());
    if (code == CURLM_OK) {
        handles[easy.get_curl()] = (curl_easy*)&easy;
    } else {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of remove for easy handlers.
void curl_multi::remove(const curl_easy &easy) {
    const CURLMcode code = curl_multi_remove_handle(this->curl.get(),easy.get_curl());
    if (code == CURLM_OK) {
        handles.erase(easy.get_curl());
    } else {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of get_info method.
vector<unique_ptr<curl_multi::curl_message>> curl_multi::get_info() {
    vector<unique_ptr<curl_multi::curl_message>> infos;
    CURLMsg *message;
    while ((message = curl_multi_info_read(this->curl.get(),&this->message_queued))) {
        infos.push_back(unique_ptr<curl_multi::curl_message>(new curl_multi::curl_message(message)));
    }
    return infos;
}

// Implementation of overloaded get_info method.
unique_ptr<curl_multi::curl_message> curl_multi::get_info(const curl_easy &easy) {
    CURLMsg *message;
    while ((message = curl_multi_info_read(this->curl.get(),&this->message_queued))) {
        if (message->easy_handle == easy.get_curl()) {
            unique_ptr<curl_multi::curl_message> ptr{new curl_multi::curl_message(message)};
            return ptr;
        }
    }
    return nullptr;
}

// Implementation of get_next_finished method.
curl_easy* curl_multi::get_next_finished() {
    CURLMsg *message = curl_multi_info_read(this->curl.get(),&this->message_queued);
    if (!message) {
		return nullptr;
	}
    if (message->msg == CURLMSG_DONE) {
        std::unordered_map<CURL*, curl_easy*>::const_iterator it = handles.find(message->easy_handle);
        if (it != handles.end()) {
            return it->second;
        }
    }
    return nullptr;
}

// Implementation of is_finished method.
bool curl_multi::is_finished(const curl_easy &easy) {
    CURLMsg *message;
    while ((message = curl_multi_info_read(this->curl.get(),&this->message_queued))) {
        if (message->easy_handle == easy.get_curl() and message->msg == CURLMSG_DONE) {
            return true;
        }
    }
    return false;
}

// Implementation of perform method.
bool curl_multi::perform() {
    const CURLMcode code = curl_multi_perform(this->curl.get(),&this->active_transfers);
    if (code == CURLM_CALL_MULTI_PERFORM) {
        return false;
    }
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
    return true;
}

// Implementation of socket_action method.
bool curl_multi::socket_action(const curl_socket_t sockfd, const int ev_bitmask) {
    const CURLMcode code = curl_multi_socket_action(this->curl.get(),sockfd,ev_bitmask,&this->active_transfers);
    if (code == CURLM_CALL_MULTI_PERFORM) {
        return false;
    } 
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
    return true;
}

// Implementation of set_fd method.
void curl_multi::set_descriptors(fd_set *read, fd_set *write, fd_set *exec, int *max_fd) {
    const CURLMcode code = curl_multi_fdset(this->curl.get(),read,write,exec,max_fd);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of wait method.
void curl_multi::wait(struct curl_waitfd extra_fds[], const unsigned int extra_nfds, const int timeout_ms, int *numfds) {
    const CURLMcode code = curl_multi_wait(this->curl.get(),extra_fds,extra_nfds,timeout_ms,numfds);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of assign method.
void curl_multi::assign(const curl_socket_t sockfd, void *sockptr) {
    const CURLMcode code = curl_multi_assign(this->curl.get(),sockfd,sockptr);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of timeout method.
void curl_multi::timeout(long *timeout) {
    const CURLMcode code = curl_multi_timeout(this->curl.get(),timeout);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of curl_message constructor.
curl_multi::curl_message::curl_message(const CURLMsg *msg) :
    message(msg->msg), whatever(msg->data.whatever), code(msg->data.result) {

    // ... nothing to do here ...
}

// Implementation of get_curl method.
CURLM *curl_multi::get_curl() const {
    return this->curl.get();
}
