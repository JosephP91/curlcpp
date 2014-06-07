//
//  curl_share.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "curl_share.h"

using curl::curl_share;

// Implementation of destructor
curl_share::~curl_share() noexcept {
    curl_share_cleanup(this->get_url());
}

// Implementation of to_string method
const string curl_share::to_string(const CURLSHcode code) const noexcept {
    return string(curl_share_strerror(code));
}