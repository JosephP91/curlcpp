//
//  CurlShare.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "CurlShare.h"

using curl::CurlShare;

// Implementation of destructor
CurlShare::~CurlShare() {
    curl_share_cleanup(this->getCurl());
}

// Implementation of toString method
const string CurlShare::toString(const CURLSHcode code) const noexcept {
    return string(curl_share_strerror(code));
}