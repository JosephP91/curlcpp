/* 
 * File:   CurlHttpPost.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:38 PM
 */

#include "CurlHttpPost.h"

using curl::CurlHttpPost;

// Implementation of destructor
CurlHttpPost::~CurlHttpPost() {
    if (this->form_post!=nullptr) {
        this->form_post = nullptr;
        this->last_ptr = nullptr;
    }
}

// Implementation of getFormPost
struct curl_httppost *CurlHttpPost::getFormPost() const noexcept {
    return this->form_post; 
}
