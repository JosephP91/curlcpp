/* 
 * File:   CurlEasy.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:54 PM
 */

#include "CurlEasy.h"

using curl::CurlEasy;
    
// Implementation of destructor
CurlEasy::~CurlEasy() {
    curl_easy_cleanup(this->getCurl());
}
  
// Implementation of errorToString method
const string CurlEasy::toString(const CURLcode code) const noexcept {
    return curl_easy_strerror(code);
}

// Implementation of abstract method perform
CURLcode CurlEasy::perform() {
    const CURLcode code = curl_easy_perform(this->getCurl());
    if (code != CURLE_OK) {
        throw CurlError(this->toString(code));
    }
    return code;
}

// Implementation of escape method
void CurlEasy::escape(string &url) {
    char *url_encoded = curl_easy_escape(this->getCurl(),url.c_str(),(int)url.length());
    if (url_encoded == nullptr) {
        throw CurlError("*** null pointer intercepted  ***");
    }
    url = string(url_encoded);
    curl_free(url_encoded);
    url_encoded = nullptr;
}

// Implementation of unescape method
void CurlEasy::unescape(string &url) {
    char *url_decoded = curl_easy_unescape(this->getCurl(),url.c_str(),(int)url.length(),nullptr);
    if (url_decoded == nullptr) {
        throw CurlError("*** null pointer intercepted ***");
    }
    url = string(url_decoded);
    curl_free(url_decoded);
    url_decoded = nullptr;
}

// Implementation of reset method
void CurlEasy::reset() noexcept {
    curl_easy_reset(this->getCurl());
}