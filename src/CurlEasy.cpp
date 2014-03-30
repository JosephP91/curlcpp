/* 
 * File:   CurlEasy.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:54 PM
 */

#include "CurlEasy.h"

using curl::CurlEasy;

 // Implementation of constructor
 CurlEasy::CurlEasy() : CurlInterface() {
     this->curl = curl_easy_init();
}

 // Implementation of overloaded constructor
CurlEasy::CurlEasy(const long flag) : CurlInterface(flag) {
    CurlEasy();
}
    
// Implementation of destructor
CurlEasy::~CurlEasy() {
    if (this->curl!=nullptr) {
        curl_easy_cleanup(this->curl);
        this->curl = nullptr;
    }
}
  
// Implementation of errorToString method
const string CurlEasy::toString(const CURLcode code) const noexcept {
    return curl_easy_strerror(code);
}

// Implementation of getCurl method
CURL *CurlEasy::getCurl() const noexcept {
    return this->curl;
}

// Implementation of abstract method perform
int CurlEasy::perform() {
    if (this->curl!=nullptr) {
        return curl_easy_perform(this->curl);
    } else {
        throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
    }
}
   
// Implementation of escape method
void CurlEasy::escape(string &url) {
    char *url_encoded = curl_easy_escape(this->curl,url.c_str(),(int)url.length());
    if (url_encoded==nullptr) {
        throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
    }
    url = string(url_encoded);
    this->free(url_encoded);
}

// Implementation of unescape method
void CurlEasy::unescape(string &url) {
    char *url_decoded = curl_easy_unescape(this->curl,url.c_str(),(int)url.length(),nullptr);
    if (url_decoded==nullptr) {
        throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
    }
    url = string(url_decoded);
    this->free(url_decoded);
}

// Implementation of reset method
void CurlEasy::reset() noexcept {
    if (this->curl!=nullptr) {
        curl_easy_reset(this->curl);
    }
}