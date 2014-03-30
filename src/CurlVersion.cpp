//
//  CurlVersion.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "CurlVersion.h"

using curl::CurlVersion;

// Implementation of constructor
CurlVersion::CurlVersion(const curl_version_info_data *version) {
    this->version = version;
}

// Implementation of getHost method
const string CurlVersion::getHost() const noexcept {
    return string(this->version->host);
}

// Implementation of getSSLVersion method
const string CurlVersion::getSSLVersion() const noexcept {
    return string(this->version->ssl_version);
}

// Implementation of getLibzVersion method
const string CurlVersion::getLibzVersion() const noexcept {
    return string(this->version->libz_version);
}

// Implementation of getAres method
const string CurlVersion::getAres() const noexcept {
    return string(this->version->ares);
}

// Implementation of getLibidn method
const string CurlVersion::getLibidn() const noexcept {
    return string(this->version->libidn);
}

// Implementation of getLibSSHVersion
const string CurlVersion::getLibSSHVersion() const noexcept {
    return string(this->version->libssh_version);
}

// Implementation of getVersionNumber
const unsigned int CurlVersion::getVersionNumber() const noexcept {
    return this->version->version_num;
}

// Implementation of getFeatures
const int CurlVersion::getFeatures() const noexcept {
    return this->version->features;
}

// Implementation of getAresNumber
const int CurlVersion::getAresNumber() const noexcept {
    return this->version->ares_num;
}

// Implementation getIconvVersionNumber
const int CurlVersion::getIconvVersionNumber() const noexcept {
    return this->version->iconv_ver_num;
}

// Implementation of getSSLVersionNumber
const long CurlVersion::getSSLVersionNumber() const noexcept {
    return this->version->ssl_version_num;
}

// Implementation of getProtocols
const list<string> CurlVersion::getProtocols() const noexcept {
    list<string> l;
    return l;
}

