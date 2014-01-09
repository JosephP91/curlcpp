//
//  curl_multi_message.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 09/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curl_wrapper__curl_multi_message__
#define __curl_wrapper__curl_multi_message__

#include <iostream>
#include "curl_multi.h"

using curl::curl_multi;

class curl_multi::curl_message {
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

#endif /* defined(__curl_wrapper__curl_multi_message__) */
