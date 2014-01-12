//
//  curl_multi.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 07/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curl_wrapper__curl_multi__
#define __curl_wrapper__curl_multi__

#include <vector>
#include <algorithm>
#include "curl_easy.h"

using std::vector;
using std::for_each;
using curl::curl_easy;

namespace curl {
    class curl_multi : public abstract_curl {
    private:
        class curl_message;
        CURLM *curl;
        int message_queued;
        int active_transfers;
        vector<curl_easy> handlers;
    protected:
        const string error_to_string(const CURLMcode) const noexcept;
    public:
        template<class T> class option_pair;
        curl_multi();
        curl_multi(const long);
        ~curl_multi();
        template<typename T = CURLMoption> curl_multi &add_option(const curl_multi::option_pair<T> &);
        template<typename T = CURLMoption> curl_multi &add_option(const vector<curl_multi::option_pair<T>> &);
        curl_multi &add_handle(const curl_easy &) noexcept;
        curl_multi &add_handle(const vector<curl_easy> &) noexcept;
        curl_multi &remove_handle(const curl_easy &) noexcept;
        int perform();
        const int get_active_transfers() const noexcept;
        const int get_message_queued() const noexcept;
        const vector<curl_multi::curl_message> get_transfers_info();
    };
    
    
    template<typename T> curl_multi &curl_multi::add_option(const curl_multi::option_pair<T> &pair) {
        if (this->curl!=nullptr) {
            curl_multi_setopt(this->curl,pair.first(),pair.second());
        } else {
            throw new null_pointer_exception("add_option(...) : NULL pointer intercepted");
        }
        return *this;
    }
 	
    template<typename T> curl_multi &curl_multi::add_option(const vector<curl_multi::option_pair<T>> &pairs) {
    	if (this->curl!=nullptr) {
            for_each(pairs.begin(),pairs.end(),[this](curl_multi::option_pair<T> option) { this->add_option(option); } );
        } else {
            throw new null_pointer_exception("add_option(...) : NULL pointer intercepted");
        }
    }
}

#endif /* defined(__curl_wrapper__curl_multi__) */