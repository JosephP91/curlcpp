//
//  curl_version.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "curl_version.h"

using curl::curl_version;

// Implementation of constructor
curl_version::curl_version(const curl_version_info_data *version) {
    this->version = version;
}

// Implementation of getHost method
const string curl_version::getHost() const noexcept {
    return string(this->version->host);
}

// Implementation of getSSLVersion method
const string curl_version::getSSLVersion() const noexcept {
    return string(this->version->ssl_version);
}

// Implementation of getLibzVersion method
const string curl_version::getLibzVersion() const noexcept {
    return string(this->version->libz_version);
}

// Implementation of getAres method
const string curl_version::getAres() const noexcept {
    return string(this->version->ares);
}

// Implementation of getLibidn method
const string curl_version::getLibidn() const noexcept {
    return string(this->version->libidn);
}

// Implementation of getLibSSHVersion
const string curl_version::getLibSSHVersion() const noexcept {
    return string(this->version->libssh_version);
}

// Implementation of getVersionNumber
const unsigned int curl_version::getVersionNumber() const noexcept {
    return this->version->version_num;
}

// Implementation of getFeatures
const int curl_version::getFeatures() const noexcept {
    return this->version->features;
}

// Implementation of getAresNumber
const int curl_version::getAresNumber() const noexcept {
    return this->version->ares_num;
}

// Implementation getIconvVersionNumber
const int curl_version::getIconvVersionNumber() const noexcept {
    return this->version->iconv_ver_num;
}

// Implementation of getSSLVersionNumber
const long curl_version::getSSLVersionNumber() const noexcept {
    return this->version->ssl_version_num;
}

// Implementation of getProtocols
const list<string> curl_version::getProtocols() const noexcept {
    list<string> l;
    return l;
}

