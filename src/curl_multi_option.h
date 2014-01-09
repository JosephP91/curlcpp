//
//  curl_multi_option.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 09/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curl_wrapper_curl_multi_option_h
#define curl_wrapper_curl_multi_option_h

#include "curl_easy.h"
#include <string>

using curl::curl_multi;
using std::string;

template<> class curl_multi::option_pair<string> {
public:
    option_pair(const CURLMoption option, const string value) : option(option), value(value) {};
    CURLMoption first() const;
    const char *second() const;
private:
    const CURLMoption option;
    const string value;
};

inline CURLMoption curl_multi::option_pair<string>::first() const {
    return this->option;
}

inline const char *curl_multi::option_pair<string>::second() const {
    return this->value.c_str();
}

#endif
