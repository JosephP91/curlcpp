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
        class curl_message {
        public:
            curl_message(CURLMSG message, curl_easy curl, void *whatever, CURLcode result) : message(message), curl(curl), whatever(whatever), result(result) {};
            const CURLMSG get_message() const noexcept;
            const CURLcode get_result() const noexcept;
            const curl_easy get_curl() const noexcept;
            const void *get_whatever() const noexcept;
        private:
            CURLMSG message;
            curl_easy curl;
            void *whatever;
            CURLcode result;
        };
        CURLM *curl;
        int message_queued;
        int active_transfers;
        vector<curl_easy> handlers;
    protected:
        const string error_to_string(const CURLMcode) const noexcept;
    public:
        template<class T> class option_pair {
        public:
            option_pair(const CURLMoption option, const T value) : option(option), value(value) {};
            CURLMoption first() const { return this->option; }
            T second() const { return this->value; }
        private:
            const CURLMoption option;
            const T value;
        };
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
        const vector<curl_message> get_transfers_info();
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
            for_each(pairs.begin(),pairs.end(),[this](curl_multi::option_pair<T> option) { curl_multi_setopt(this->curl,option.first(),option.second()); } );
        } else {
            throw new null_pointer_exception("add_option(...) : NULL pointer intercepted");
        }
    }
}

#endif /* defined(__curl_wrapper__curl_multi__) */