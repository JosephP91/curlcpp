//
//  curl_message.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 13/06/14.
//

#include "curl_message.h"

// That's too deep. Let's typedef somthing.
typedef curl_multi::curl_handle::curl_message c_message;

// Implementation of constructor.
c_message::curl_message(CURLMSG message, curl_easy &easy, void *whatever, CURLcode result) : message(message), easy(easy), whatever(whatever), result(result) {
    // ... nothing to do here ...
}

// Implementation of copy constructor.
c_message::curl_message(const c_message &message) : message(message.message), easy(message.easy), whatever(message.whatever), result(message.result) {
    // ... nothing to do here ...
}

// Implementation of get_message method.
const CURLMSG c_message::get_message() const {
    return this->message;
}

// Implementation of get_result method.
const CURLcode c_message::get_result() const {
    return this->result;
}

// Implementation of get_curl method.
const curl_easy c_message::get_curl() const {
    return this->easy;
}

// Implementation of get_whatever method.
const void *c_message::get_whatever() const {
    return this->whatever;
}