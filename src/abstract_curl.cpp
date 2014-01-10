//
//  abstract_curl.cpp
//  curl_wrapper
//
//  Created by Giuseppe Persico on 06/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include <curl/curl.h>
#include "../include/abstract_curl.h"
#include "../include/exceptions.h"

using curl::abstract_curl;

namespace curl {
    abstract_curl::abstract_curl() {
        const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code!=0) {
            throw new curl_error<CURLcode>("curl_global_init(): Error while initializing the curl environment",code);
        }
    }
    
    abstract_curl::abstract_curl(const long flag) {
        const CURLcode code = curl_global_init(flag);
        if (code!=0) {
            throw new curl_error<CURLcode>("curl_global_init(): Error while initializing the curl environment with the flag specified",code);
        }
        
    }
    
    abstract_curl::~abstract_curl() {
        curl_global_cleanup();
    }
    
    void abstract_curl::free(char *ptr) noexcept {
        if (ptr!=nullptr) {
            curl_free(ptr);
        }
    }
    
    const string abstract_curl::version() const noexcept {
        return string(curl_version());
    }
}
