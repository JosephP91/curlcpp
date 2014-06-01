/* 
 * File:   CurlMulti.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 11:02 PM
 */

#include <algorithm>
#include "CurlMulti.h"

using std::for_each;
using std::move;
using curl::CurlMulti;

// Implementation of constructor.
CurlMulti::CurlMulti() : CurlInterface(curl_multi_init()) {
    this->active_transfers = 0;
    this->message_queued = 0;
}

// Implementation of overloaded constructor.
CurlMulti::CurlMulti(const long flag) : CurlInterface(curl_multi_init(),flag) {
    CurlMulti();
}

// Implementation of destructor.
CurlMulti::~CurlMulti() {
    for_each(this->handlers.begin(),this->handlers.end(),[this](CurlEasy handler) {
        curl_multi_remove_handle(this->getCurl(),handler.getCurl());
    });
    curl_multi_cleanup(this->getCurl());
}

// Implementation of addHandle method.
CurlMulti &CurlMulti::addHandle(const CurlEasy &handler) noexcept {
    CURLMcode code = curl_multi_add_handle(this->getCurl(),handler.getCurl());
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
    return *this;
}

// Implementation of addHandle overloaded method.
CurlMulti &CurlMulti::addHandle(const vector<CurlEasy> &handlers) noexcept {
    this->handlers = move(handlers);
    return *this;
}

// Implementation of removeHandle overloaded method.
CurlMulti &CurlMulti::removeHandle(const CurlEasy &handler) noexcept {
    CURLMcode code = curl_multi_remove_handle(this->getCurl(),handler.getCurl());
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
    return *this;
}

// Implementation of getActiveTransfers method.
const int CurlMulti::getActiveTransfers() const noexcept {
    return this->active_transfers;
}

// Implementation of getMessageQueued method.
const int CurlMulti::getMessageQueued() const noexcept {
    return this->message_queued;
}

// Implementation of perform method.
bool CurlMulti::perform() {
    CURLMcode code = curl_multi_perform(this->getCurl(),&this->active_transfers);
    if (code == CURLM_CALL_MULTI_PERFORM) {
        return false;
    }
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
    return true;
}

// Implementation of getTransfersInfo method
const vector<CurlMulti::CurlMessage> CurlMulti::infoRead() {
    vector<CurlMulti::CurlMessage> info;
    CURLMsg *msg = nullptr;
    while ((msg = curl_multi_info_read(this->getCurl(),&this->message_queued))) {
        if (msg->msg == CURLMSG_DONE) {
            for (auto handler : this->handlers) {
                if (msg->easy_handle == handler.getCurl()) {
                    info.push_back(CurlMessage(msg->msg,handler,(msg->data).whatever,(msg->data).result));
                }
            }
        }
    }
    return info;
}

// Implementation of fdSet
void CurlMulti::fdSet(fd_set *readFdSet, fd_set *writeFdSet, fd_set *executeFdSet, int *maxFd) {
    CURLMcode code = curl_multi_fdset(this->getCurl(),readFdSet,writeFdSet,executeFdSet,maxFd);
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
}

// Implementation of timeout
void CurlMulti::timeout(long *milliseconds) {
    CURLMcode code = curl_multi_timeout(this->getCurl(),milliseconds);
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
}

// Implementation of assign
void CurlMulti::assign(curl_socket_t sockFd, void *socketPtr) {
    CURLMcode code = curl_multi_assign(this->getCurl(),sockFd,socketPtr);
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
}

// Implementation of wait
void CurlMulti::wait(curl_waitfd extraFds[], unsigned int numberExtraFds, int timeoutMilliseconds, int *numberFds) {
    CURLMcode code = curl_multi_wait(this->getCurl(),extraFds,numberExtraFds,timeoutMilliseconds,numberFds);
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
}

// Implementation of socket action
bool CurlMulti::socketAction(curl_socket_t sockFd, int bitMask, int *runningHandles) {
    CURLMcode code = curl_multi_socket_action(this->getCurl(),sockFd,bitMask,runningHandles);
    if (code == CURLM_CALL_MULTI_PERFORM) {
        return false;
    }
    if (code != CURLM_OK) {
        throw CurlError(this->toString(code));
    }
    return true;
}

// Implementation of errorToString method
const string CurlMulti::toString(const CURLMcode code) const noexcept {
    return curl_multi_strerror(code);
}