//
//  curl_easy.h
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_easy__
#define __curlcpp__curl_easy__

#include <vector>
#include <list>
#include <memory>
#include <algorithm>

#include "curl_interface.h"
#include "curl_error.h"
#include "curl_pair.h"

using std::vector;
using std::list;
using std::unique_ptr;
using std::for_each;
using curl::curl_pair;

namespace curl  {
    class curl_easy : public curl_interface {
    public:
        curl_easy();
        curl_easy(const long);
        ~curl_easy();
        template<typename T> curl_easy &add_option(const curl_pair<CURLoption,T> &);
        template<typename T> curl_easy &add_option(const vector<curl_pair<CURLoption,T>> &);
        template<typename T> curl_easy &add_option(const list<curl_pair<CURLoption,T>> &);
        template<typename T> unique_ptr<T> get_session_info(const CURLINFO, T *) const;
        void escape(string &);
        void unescape(string &);
        virtual int perform();
        void reset() noexcept;
        CURL *get_curl() const noexcept;
    protected:
        const string error_to_string(const CURLcode) const noexcept;
    private:
        CURL *curl;
    };
    
    
    template<typename T> curl_easy &curl_easy::add_option(const curl_pair<CURLoption,T> &pair) {
        if (this->curl!=nullptr) {
            curl_easy_setopt(this->curl,pair.first(),pair.second());
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted **",0);
        }
        return *this;
    }
    
    template<typename T> curl_easy &curl_easy::add_option(const vector<curl_pair<CURLoption,T>> &pairs) {
        if (this->curl!=nullptr) {
            for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLoption,T> option) { this->add_option(option); } );
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted **",0);
        }
        return *this;
    }
    
    template<typename T> curl_easy &curl_easy::add_option(const list<curl_pair<CURLoption,T> > &pairs) {
        if (this->curl!=nullptr) {
            for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLoption,T> option) { this->add_option(option); });
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted",0);
        }
        return *this;
    }
    
    template<typename T> unique_ptr<T> curl_easy::get_session_info(const CURLINFO info, T *ptr_info) const {
        if (this->curl!=nullptr) {
            const CURLcode code = curl_easy_getinfo(this->curl,info,ptr_info);
            if (code!=CURLE_OK && ptr_info) {
                throw new curl_error<CURLcode>(this->error_to_string(code),code);
            }
            return unique_ptr<T>{ptr_info};
        }
        throw new curl_error<int>(" ** NULL pointer intercepted **",0);
    }
}

#endif /* defined(__curlcpp__curl_easy__) */