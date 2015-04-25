/**
 * File:   curl_multi.cpp
 * Author: Giuseppe Persico
 */

#include "curl_multi.h"

using curl::curl_multi;

// Implementation of constructor.
curl_multi::curl_multi() : curl_interface() {
    this->curl = curl_multi_init();
    if (this->curl == nullptr) {
        throw curl_multi_exception("Null pointer intercepted",__FUNCTION__);
    }
    this->active_transfers = 0;
    this->message_queued = 0;
}

// Implementation of overloaded constructor.
curl_multi::curl_multi(const long flag) : curl_interface(flag) {
    curl_multi();
}

// Implementation of copy constructor to respect the rule of three.
curl_multi::curl_multi(const curl_multi &multi)
	: curl_interface(),
	  message_queued(multi.message_queued),
	  active_transfers(multi.active_transfers) {
    this->curl = curl_multi_init();
    if (this->curl == nullptr) {
        throw curl_multi_exception("Null pointer intercepted",__FUNCTION__);
    }
}

// Implementation of assignment operator to perform deep copy.
curl_multi &curl_multi::operator=(const curl_multi &multi) {
    if (this == &multi) {
        return *this;
    }
    curl_multi();
    return *this;
}

// Implementation of destructor.
curl_multi::~curl_multi() NOEXCEPT{
    curl_multi_cleanup(this->curl);
}

// Implementation of add method for easy handlers.
void curl_multi::add(const curl_easy &easy) {
    const CURLMcode code = curl_multi_add_handle(this->curl,easy.get_curl());
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of remove for easy handlers.
void curl_multi::remove(const curl_easy &easy) {
    const CURLMcode code = curl_multi_remove_handle(this->curl,easy.get_curl());
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of get_info method.
vector<unique_ptr<curl_multi::curl_message>> curl_multi::get_info() {
    vector<unique_ptr<curl_multi::curl_message>> infos;
    CURLMsg *message = nullptr;
    while ((message = curl_multi_info_read(this->curl,&this->message_queued))) {
        infos.push_back(unique_ptr<curl_multi::curl_message>(new curl_multi::curl_message(message)));
    }
    return infos;
}

// Implementation of overloaded get_info method.
unique_ptr<curl_multi::curl_message> curl_multi::get_info(const curl_easy &easy) {
    CURLMsg *message = nullptr;
    while ((message = curl_multi_info_read(this->curl,&this->message_queued))) {
        if (message->easy_handle == easy.get_curl()) {
            unique_ptr<curl_multi::curl_message> ptr{new curl_multi::curl_message(message)};
            return ptr;
        }
    }
    return nullptr;
}

// Implementation of is_finished method.
bool curl_multi::is_finished(const curl_easy &easy) {
    CURLMsg *message = nullptr;
    while ((message = curl_multi_info_read(this->curl,&this->message_queued))) {
        if (message->easy_handle == easy.get_curl() and message->msg == CURLMSG_DONE) {
            return true;
        }
    }
    return false;
}

// Implementation of perform method.
bool curl_multi::perform() {
    const CURLMcode code = curl_multi_perform(this->curl,&this->active_transfers);
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
    const CURLMcode code = curl_multi_socket_action(this->curl,sockfd,ev_bitmask,&this->active_transfers);
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
    const CURLMcode code = curl_multi_fdset(this->curl,read,write,exec,max_fd);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of wait method.
void curl_multi::wait(struct curl_waitfd extra_fds[], const unsigned int extra_nfds, const int timeout_ms, int *numfds) {
    const CURLMcode code = curl_multi_wait(this->curl,extra_fds,extra_nfds,timeout_ms,numfds);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of assign method.
void curl_multi::assign(const curl_socket_t sockfd, void *sockptr) {
    const CURLMcode code = curl_multi_assign(this->curl,sockfd,sockptr);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of timeout method.
void curl_multi::timeout(long *timeout) {
    const CURLMcode code = curl_multi_timeout(this->curl,timeout);
    if (code != CURLM_OK) {
        throw curl_multi_exception(code,__FUNCTION__);
    }
}

// Implementation of curl_message constructor.
curl_multi::curl_message::curl_message(const CURLMsg *msg) :
    message(msg->msg), whatever(msg->data.whatever), code(msg->data.result) {
    // ... nothing to do here ...
}
