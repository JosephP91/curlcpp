/* 
 * File:   curl_easy.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:54 PM
 */

#include "curl_easy.h"

using curl::curl_easy;
    
// Implementation of destructor
curl_easy::~curl_easy() {
    curl_easy_cleanup(this->get_url());
}
  
// Implementation of errorto_string method
const string curl_easy::to_string(const CURLcode code) const noexcept {
    return curl_easy_strerror(code);
}

// Implementation of abstract method perform
void curl_easy::perform() {
    const CURLcode code = curl_easy_perform(this->get_url());
    if (code != CURLE_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of escape method
void curl_easy::escape(string &url) {
    char *url_encoded = curl_easy_escape(this->get_url(),url.c_str(),(int)url.length());
    if (url_encoded == nullptr) {
        throw curl_error("*** null pointer intercepted  ***",__FUNCTION__);
    }
    url = string(url_encoded);
    curl_free(url_encoded);
    url_encoded = nullptr;
}

// Implementation of unescape method
void curl_easy::unescape(string &url) {
    char *url_decoded = curl_easy_unescape(this->get_url(),url.c_str(),(int)url.length(),nullptr);
    if (url_decoded == nullptr) {
        throw curl_error("*** null pointer intercepted ***",__FUNCTION__);
    }
    url = string(url_decoded);
    curl_free(url_decoded);
    url_decoded = nullptr;
}

// Implementation of reset method
void curl_easy::reset() noexcept {
    curl_easy_reset(this->get_url());
}