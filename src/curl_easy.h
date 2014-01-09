//
//  curl_easy.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 06/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curl_wrapper__curl_easy__
#define __curl_wrapper__curl_easy__

#include <vector>
#include <memory>
#include "abstract_curl.h"
#include "exceptions.h"

using std::vector;
using std::unique_ptr;

namespace curl  {
    class curl_easy : public abstract_curl {
    public:
        template<class T> class option_pair {
        public:
            option_pair(const CURLoption option, const T value) : option(option), value(value) {};
            CURLoption first() const { return this->option; }
            T second() const { return this->value; }
        private:
            const CURLoption option;
            const T value;
        };
        
        curl_easy();
        curl_easy(const long);
        ~curl_easy();
        template<typename T = CURLoption> curl_easy &add_option(const curl_easy::option_pair<T> &);
        template<typename T = CURLoption> curl_easy &add_option(const vector<option_pair<T>> &);
        template<typename T> unique_ptr<T> get_session_info(const CURLINFO, T *) const;
        void escape(string &);
        void unescape(string &);
        int perform();
        void reset() noexcept;
        CURL *get_curl() const noexcept;
    protected:
        const string error_to_string(const CURLcode) const noexcept;
    private:
        CURL *curl;
    };
    
    template<typename T> curl_easy &curl_easy::add_option(const curl_easy::option_pair<T> &pair) {
        if (this->curl!=nullptr) {
            curl_easy_setopt(this->curl,pair.first(),pair.second());
        } else {
            throw new null_pointer_exception("add_option(...) : NULL pointer intercepted");
        }
        return *this;
    }
    
    template<typename T> curl_easy &curl_easy::add_option(const vector<curl_easy::option_pair<T>> &pairs) {
        if (this->curl!=nullptr) {
            for_each(pairs.begin(),pairs.end(),[this](curl_easy::option_pair<T> option) { curl_easy_setopt(this->curl,option.first(),option.second()); } );
        } else {
            throw new null_pointer_exception("add_option(...) : NULL pointer intercepted");
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
        } else {
            throw new null_pointer_exception("get_session_info(...) : NULL pointer intercepted");
        }
    }
}

#endif /* defined(__curl_wrapper__curl_easy__) */
