//
//  curl_http_post.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "../include/curl_http_post.h"

using curl::curl_http_post;

curl_http_post::~curl_http_post() {
    if (this->form_post!=nullptr) {
        this->form_post = nullptr;
        this->last_ptr = nullptr;
    }
}
