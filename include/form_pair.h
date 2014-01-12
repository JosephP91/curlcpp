//
//  form_pair.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 11/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curl_wrapper_form_pair_h
#define curl_wrapper_form_pair_h

#include "curl_http_post.h"

template<class T> class curl_http_post::form_pair {
public:
    form_pair(CURLformoption option, T value) : option(option), value(value) {}
    inline const CURLformoption first() const noexcept { return this->option; }
    inline const T second() const noexcept { return this->value; }
private:
    const CURLformoption option;
    const T value;
};


template<> class curl_http_post::form_pair<string> {
public:
    form_pair(CURLformoption option, string value) : option(option), value(value) {}
    inline const CURLformoption first() const noexcept { return this->option; }
    inline const char *second() const noexcept { return this->value.c_str(); }
private:
    const CURLformoption option;
    const string value;
};

#endif