//
//  curl_multi.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include <algorithm>
#include "curl_multi.h"
#include "curl_error.h"
#include "curl_message.h"

using std::for_each;
using std::move;
using curl::curl_multi;

namespace curl {
    curl_multi::curl_multi() : curl_interface() {
        this->curl = curl_multi_init();
        this->active_transfers = 0;
        this->message_queued = 0;
    }
    
    curl_multi::curl_multi(const long flag) : curl_interface(flag) {
        curl_multi();
    }
    
    curl_multi::~curl_multi() {
        for_each(this->handlers.begin(),this->handlers.end(),[this](curl_easy handler) { curl_multi_remove_handle(this->curl,handler.get_curl()); });
        curl_multi_cleanup(this->curl);
    }
    
    curl_multi &curl_multi::add_handle(const curl_easy &handler) noexcept {
        if (this->curl!=nullptr) {
            curl_multi_add_handle(this->curl,handler.get_curl());
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
        return *this;
    }
    
    curl_multi &curl_multi::add_handle(const vector<curl_easy> &handlers) noexcept {
        if (this->curl!=nullptr) {
            this->handlers = move(handlers);
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
        return *this;
    }
    
    curl_multi &curl_multi::remove_handle(const curl_easy &handler) noexcept {
        if (this->curl!=nullptr) {
            curl_multi_remove_handle(this->curl,handler.get_curl());
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
        return *this;
    }
    
    const int curl_multi::get_active_transfers() const noexcept {
        return this->active_transfers;
    }
    
    const int curl_multi::get_message_queued() const noexcept {
        return this->message_queued;
    }
	
    int curl_multi::perform() {
        if (this->curl!=nullptr) {
            return curl_multi_perform(this->curl,&this->active_transfers);
        } else {
            throw new curl_error<int>(" ** NULL pointe intercepted **",0);
        }
    }
    
    const vector<curl_multi::curl_message> curl_multi::get_transfers_info() {
        vector<curl_multi::curl_message> info;
        if (this->curl!=nullptr) {
            CURLMsg *msg = nullptr;
            while ((msg = curl_multi_info_read(this->curl,&this->message_queued))) {
                if (msg->msg == CURLMSG_DONE) {
                    for (auto handler : this->handlers) {
                        if (msg->easy_handle==handler.get_curl()) {
                            info.push_back(curl_message(msg->msg,handler,(msg->data).whatever,(msg->data).result));
                            break;
                        }
                    }
                }
            }
            return info;
        }
        throw new curl_error<int>(" ** NULL pointe intercepted ** ",0);
    }
    
    const string curl_multi::error_to_string(const CURLMcode code) const noexcept {
        return curl_multi_strerror(code);
    }
}