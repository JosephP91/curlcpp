/**
 * File:   curl_share.cpp
 * Author: Giuseppe Persico
 */

#include "curl_share.h"

using curl::curl_share;

// Implementation of default constructor.
curl_share::curl_share() : curl_interface() {
    this->curl = curl_share_init();
    if (this->curl == nullptr) {
        throw curl_share_exception("Null pointer intercepted",__FUNCTION__);
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
curl_share::~curl_share() NOEXCEPT {
    if (this->curl != nullptr) {
        curl_share_cleanup(this->curl);
        this->curl = nullptr;
    }
}