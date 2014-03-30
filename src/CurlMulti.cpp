/* 
 * File:   CurlMulti.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 11:02 PM
 */

#include <algorithm>
#include "CurlError.h"
#include "CurlMessage.h"
#include "CurlMulti.h"

using std::for_each;
using std::move;
using curl::CurlMulti;

// Implementation of constructor
CurlMulti::CurlMulti() : CurlInterface() {
    this->curl = curl_multi_init();
    this->active_transfers = 0;
    this->message_queued = 0;
}

// Implementation of overloaded constructor
CurlMulti::CurlMulti(const long flag) : CurlInterface(flag) {
    CurlMulti();
}
    
// Implementation of destructor
CurlMulti::~CurlMulti() {
    for_each(this->handlers.begin(),this->handlers.end(),[this](CurlEasy handler) { curl_multi_remove_handle(this->curl,handler.getCurl());});
    curl_multi_cleanup(this->curl);
}
    
// Implementation of addHandle method
CurlMulti &CurlMulti::addHandle(const CurlEasy &handler) noexcept {
    if (this->curl!=nullptr) {
        curl_multi_add_handle(this->curl,handler.getCurl());
    } else {
        throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
    }
    return *this;
}
    
// Implementation of addHandle overloaded method
CurlMulti &CurlMulti::addHandle(const vector<CurlEasy> &handlers) noexcept {
    if (this->curl!=nullptr) {
        this->handlers = move(handlers);
    } else {
        throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
    }
    return *this;
}
    
// Implementation of removeHandle overloaded method
CurlMulti &CurlMulti::removeHandle(const CurlEasy &handler) noexcept {
    if (this->curl!=nullptr) {
        curl_multi_remove_handle(this->curl,handler.getCurl());
    } else {
        throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
    }
    return *this;
}
    
// Implementation of getActiveTransfers method
const int CurlMulti::getActiveTransfers() const noexcept {
    return this->active_transfers;
}
    
// Implementation of getMessageQueued method
const int CurlMulti::getMessageQueued() const noexcept {
    return this->message_queued;
}

// Implementation of perform abstract method
int CurlMulti::perform() {
    if (this->curl!=nullptr) {
        return curl_multi_perform(this->curl,&this->active_transfers);
    }
    throw new CurlError<int>(" ** NULL pointer intercepted **",0);
}
    
// Implementation of getTransfersInfo method
const vector<CurlMulti::CurlMessage> CurlMulti::getTransfersInfo() {
    vector<CurlMulti::CurlMessage> info;
    if (this->curl!=nullptr) {
        CURLMsg *msg = nullptr;
        while ((msg = curl_multi_info_read(this->curl,&this->message_queued))) {
            if (msg->msg == CURLMSG_DONE) {
                for (auto handler : this->handlers) {
                    if (msg->easy_handle==handler.getCurl()) {
                        info.push_back(CurlMessage(msg->msg,handler,(msg->data).whatever,(msg->data).result));
                        break;
                    }
                }
            }
        }
        return info;
    }
    throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
}
    
// Implementation of errorToString method
const string CurlMulti::toString(const CURLMcode code) const noexcept {
    return curl_multi_strerror(code);
}