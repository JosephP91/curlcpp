//
//  curl_multi_message.cpp
//  curl_wrapper
//
//  Created by Giuseppe Persico on 09/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "multi_message.h"

using curl::curl_multi;

const CURLMSG curl_multi::curl_message::get_message() const noexcept {
    return this->message;
}

const curl_easy curl_multi::curl_message::get_curl() const noexcept {
    return this->curl;
}

const void *curl_multi::curl_message::get_whatever() const noexcept {
    return this->whatever;
}

const CURLcode curl_multi::curl_message::get_result() const noexcept {
    return this->result;
}