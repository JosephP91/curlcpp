//
//  curl_easy.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "../include/curl_easy.h"

using curl::curl_easy;

namespace curl {
    curl_easy::curl_easy() : curl_interface() {
	    this->curl = curl_easy_init();
    }
    
    curl_easy::curl_easy(const long flag) : curl_interface(flag) {
	    curl_easy();
    }
    
    curl_easy::~curl_easy() {
        if (this->curl!=nullptr) {
            curl_easy_cleanup(this->curl);
            this->curl = nullptr;
        }
    }
    
    const string curl_easy::error_to_string(const CURLcode code) const noexcept {
        return curl_easy_strerror(code);
    }
    
    CURL *curl_easy::get_curl() const noexcept {
        return this->curl;
    }
    
    int curl_easy::perform() {
        if (this->curl!=nullptr) {
            return curl_easy_perform(this->curl);
        } else {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
    }
    
    void curl_easy::escape(string &url) {
        char *url_encoded = curl_easy_escape(this->curl,url.c_str(),(int)url.length());
        if (url_encoded==nullptr) {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
        url = string(url_encoded);
        this->free(url_encoded);
    }
    
    void curl_easy::unescape(string &url) {
        char *url_decoded = curl_easy_unescape(this->curl,url.c_str(),(int)url.length(),nullptr);
        if (url_decoded==nullptr) {
            throw new curl_error<int>(" ** NULL pointer intercepted ** ",0);
        }
        url = string(url_decoded);
        this->free(url_decoded);
    }
    
    void curl_easy::reset() noexcept {
        if (this->curl!=nullptr) {
            curl_easy_reset(this->curl);
        }
    }
}
