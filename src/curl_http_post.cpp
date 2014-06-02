/* 
 * File:   curl_http_post.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:38 PM
 */

#include "curl_http_post.h"

using curl::curl_http_post;

// Implementation of destructor
curl_http_post::~curl_http_post() {
    if (this->form_post!=nullptr) {
        this->form_post = nullptr;
        this->last_ptr = nullptr;
    }
}

// Implementation of getFormPost
struct curl_httppost *curl_http_post::get() const noexcept {
    return this->form_post; 
}
