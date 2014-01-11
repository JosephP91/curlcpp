//
//  http_post.cpp
//  curl_wrapper
//
//  Created by Giuseppe Persico on 11/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "http_post.h"

http_post::~http_post() {
    curl_formfree(this->form_post);
    this->form_post = nullptr;
    this->last_ptr = nullptr;
}
