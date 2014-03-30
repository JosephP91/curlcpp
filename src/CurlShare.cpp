//
//  CurlShare.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "CurlShare.h"

using curl::CurlShare;

// Implementation of constructor
CurlShare::CurlShare() : CurlInterface() {
    this->curl = curl_share_init();
}

// Implementation of overloaded constructor
CurlShare::CurlShare(const long flag) : CurlInterface(flag) {
    CurlShare();
}

// Implementation of destructor
CurlShare::~CurlShare() {
    curl_share_cleanup(this->curl);
}

// Implementation of toString method
const string CurlShare::toString(const CURLSHcode code) const noexcept {
    return string(curl_share_strerror(code));
}

// Implementation of addOption method
template<typename T> CurlShare &CurlShare::addOption(const CurlPair<CURLSHoption,T> &pair) {
    if (this->curl!=nullptr) {
        curl_share_setopt(this->curl,pair.first(),pair.second());
    } else {
        throw new CurlError<int>(" ** NULL pointer intercepted **",0);
    }
    return *this;
}

// Implementation of overloaded method addOption
template<typename T> CurlShare &CurlShare::addOption(const vector<CurlPair<CURLSHoption,T>> &pairs) {
    if (this->curl!=nullptr) {
        for_each(pairs.begin(),pairs.end(),[this](CurlPair<CURLSHoption,T> option) { this->addOption(option); } );
    } else {
        throw new CurlError<int>(" ** NULL pointer intercepted **",0);
    }
    return *this;
}

// Implementation of overloaded method addOption
template<typename T> CurlShare &CurlShare::addOption(const list<CurlPair<CURLSHoption,T> > &pairs) {
    if (this->curl!=nullptr) {
        for_each(pairs.begin(),pairs.end(),[this](CurlPair<CURLSHoption,T> option) { this->addOption(option); });
    } else {
        throw new CurlError<int>(" ** NULL pointer intercepted",0);
    }
    return *this;
}