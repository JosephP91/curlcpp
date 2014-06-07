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
curl_multi::curl_multi() : curl_interface(curl_multi_init()) {
    this->active_transfers = 0;
    this->message_queued = 0;
}

// Implementation of overloaded constructor.
curl_multi::curl_multi(const long flag) : curl_interface(curl_multi_init(),flag) {
    curl_multi();
}

// Implementation of destructor.
curl_multi::~curl_multi() noexcept{
    for_each(this->handlers.begin(),this->handlers.end(),[this](curl_easy handler) {
        curl_multi_remove_handle(this->get_url(),handler.get_url());
    });
    curl_multi_cleanup(this->get_url());
}

// Implementation of addHandle method.
curl_multi &curl_multi::addHandle(const curl_easy &handler) noexcept {
    CURLMcode code = curl_multi_add_handle(this->get_url(),handler.get_url());
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
    return *this;
}

// Implementation of addHandle overloaded method.
curl_multi &curl_multi::addHandle(const vector<curl_easy> &handlers) noexcept {
    this->handlers = move(handlers);
    return *this;
}

// Implementation of removeHandle overloaded method.
curl_multi &curl_multi::removeHandle(const curl_easy &handler) noexcept {
    CURLMcode code = curl_multi_remove_handle(this->get_url(),handler.get_url());
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
    return *this;
}

// Implementation of getActiveTransfers method.
const int curl_multi::getActiveTransfers() const noexcept {
    return this->active_transfers;
}

// Implementation of getMessageQueued method.
const int curl_multi::getMessageQueued() const noexcept {
    return this->message_queued;
}

// Implementation of perform method.
bool curl_multi::perform() {
    CURLMcode code = curl_multi_perform(this->get_url(),&this->active_transfers);
    if (code == CURLM_CALL_MULTI_PERFORM) {
        return false;
    }
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
    return true;
}

// Implementation of getTransfersInfo method
const vector<curl_multi::CurlMessage> curl_multi::infoRead() {
    vector<curl_multi::CurlMessage> info;
    CURLMsg *msg = nullptr;
    while ((msg = curl_multi_info_read(this->get_url(),&this->message_queued))) {
        if (msg->msg == CURLMSG_DONE) {
            for (auto handler : this->handlers) {
                if (msg->easy_handle == handler.get_url()) {
                    info.push_back(CurlMessage(msg->msg,handler,(msg->data).whatever,(msg->data).result));
                }
            }
        }
    }
    return info;
}

// Implementation of fdSet
void curl_multi::fdSet(fd_set *readFdSet, fd_set *writeFdSet, fd_set *executeFdSet, int *maxFd) {
    CURLMcode code = curl_multi_fdset(this->get_url(),readFdSet,writeFdSet,executeFdSet,maxFd);
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of timeout
void curl_multi::timeout(long *milliseconds) {
    CURLMcode code = curl_multi_timeout(this->get_url(),milliseconds);
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of assign
void curl_multi::assign(curl_socket_t sockFd, void *socketPtr) {
    CURLMcode code = curl_multi_assign(this->get_url(),sockFd,socketPtr);
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of wait
void curl_multi::wait(curl_waitfd extraFds[], unsigned int numberExtraFds, int timeoutMilliseconds, int *numberFds) {
    CURLMcode code = curl_multi_wait(this->get_url(),extraFds,numberExtraFds,timeoutMilliseconds,numberFds);
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of socket action
bool curl_multi::socketAction(curl_socket_t sockFd, int bitMask, int *runningHandles) {
    CURLMcode code = curl_multi_socket_action(this->get_url(),sockFd,bitMask,runningHandles);
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