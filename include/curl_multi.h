//
//  curl_multi.h
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_multi__
#define __curlcpp__curl_multi__

#include <vector>
#include <algorithm>
#include "curl_easy.h"

using std::vector;
using std::for_each;
using curl::curl_easy;

namespace curl {
    class curl_multi : public curl_interface {
    private:
        class curl_message;
        CURLM *curl;
        int message_queued;
        int active_transfers;
        vector<curl_easy> handlers;
    protected:
        const string error_to_string(const CURLMcode) const noexcept;
    public:
        curl_multi();
        curl_multi(const long);
        ~curl_multi();
        template<typename T> curl_multi &add_option(const curl_pair<CURLMoption,T> &);
        template<typename T> curl_multi &add_option(const vector<curl_pair<CURLMoption,T>> &);
        curl_multi &add_handle(const curl_easy &) noexcept;
        curl_multi &add_handle(const vector<curl_easy> &) noexcept;
        curl_multi &remove_handle(const curl_easy &) noexcept;
        int perform();
        const int get_active_transfers() const noexcept;
        const int get_message_queued() const noexcept;
        const vector<curl_multi::curl_message> get_transfers_info();
    };
    
    
    template<typename T> curl_multi &curl_multi::add_option(const curl_pair<CURLMoption,T> &pair) {
        if (this->curl!=nullptr) {
            curl_multi_setopt(this->curl,pair.first(),pair.second());
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
        return *this;
    }
 	
    template<typename T> curl_multi &curl_multi::add_option(const vector<curl_pair<CURLMoption,T>> &pairs) {
    	if (this->curl!=nullptr) {
            for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLMoption,T> option) { this->add_option(option); } );
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
    }
}

#endif /* defined(__curlcpp__curl_multi__) */