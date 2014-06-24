//
//  curl_info.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//

#include "curl_info.h"

using curl::curl_info;

// Implementation of default constructor.
curl_info::curl_info() {
    this->version = curl_version_info(CURLVERSION_NOW);
}

// Implementation of overloaded constructor.
curl_info::curl_info(const CURLversion version) {
    this->version = curl_version_info(version);
}

// Implementation of getHost method
const string curl_info::get_host() const noexcept {
    return string(this->version->host);
}

// Implementation of getSSLVersion method
const string curl_info::get_ssl_version() const noexcept {
    return string(this->version->ssl_version);
}

// Implementation of getLibzVersion method
const string curl_info::get_libz_version() const noexcept {
    return string(this->version->libz_version);
}

// Implementation of getAres method
const string curl_info::get_ares() const noexcept {
    return string(this->version->ares);
}

// Implementation of getLibidn method
const string curl_info::get_libidn() const noexcept {
    return string(this->version->libidn);
}

// Implementation of getLibSSHVersion
const string curl_info::get_libssh_version() const noexcept {
    return string(this->version->libssh_version);
}

// Implementation of getVersionNumber
const unsigned int curl_info::get_version_number() const noexcept {
    return this->version->version_num;
}

// Implementation of get_features
const int curl_info::get_features() const noexcept {
    return this->version->features;
}

// Implementation of getAresNumber
const int curl_info::get_ares_number() const noexcept {
    return this->version->ares_num;
}

// Implementation getIconvVersionNumber
const int curl_info::get_iconv_version_number() const noexcept {
    return this->version->iconv_ver_num;
}

// Implementation of getSSLVersionNumber
const long curl_info::get_ssl_version_number() const noexcept {
    return this->version->ssl_version_num;
}

// Implementation of getProtocols
const list<string> curl_info::get_protocols() const noexcept {
    list<string> protocols;
    const char *const *const prot = this->version->protocols;
    int i = 0;
    while (*(prot+i) != NULL) {
        protocols.push_back(string(*(prot+i)));
        i++;
    }
    return protocols;
}