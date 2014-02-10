//
//  curl_interface.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "curl_interface.h"
#include "curl_error.h"

using curl::curl_interface;

namespace curl {
    curl_interface::curl_interface() {
        const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code!=0) {
            throw new curl_error<CURLcode>(" ** Error while initializing the curl environment **",code);
        }
    }
    
    curl_interface::curl_interface(const long flag) {
        const CURLcode code = curl_global_init(flag);
        if (code!=0) {
            throw new curl_error<CURLcode>(" ** Error while initializing the curl environment with the flag specified **",code);
        }
        
    }
    
    curl_interface::~curl_interface() {
        curl_global_cleanup();
    }
    
    void curl_interface::free(char *ptr) noexcept {
        if (ptr!=nullptr) {
            curl_free(ptr);
        }
    }
    
    const string curl_interface::version() const noexcept {
        return string(curl_version());
    }
}