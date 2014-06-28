//
//  curl_share.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//

#include "curl_share.h"

using curl::curl_share;

// Implementation of default constructor.
curl_share::curl_share() : curl_interface() {
    this->curl = curl_share_init();
    if (this->curl == nullptr) {
        throw curl_error("*** Error during curl share pointer initialization ***",__FUNCTION__);
    }
}

// Implementation of assignment operator to perform a deep copy.
curl_share &curl_share::operator=(const curl::curl_share &share) {
    if (this != &share) {
        return *this;
    }
    curl_share();
    return *this;
}

// Implementation of destructor
curl_share::~curl_share() noexcept {
    if (this->curl != nullptr) {
        curl_share_cleanup(this->curl);
        this->curl = nullptr;
    }
}
