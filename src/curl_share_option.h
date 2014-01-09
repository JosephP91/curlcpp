//
//  curl_share_option.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 09/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curl_wrapper_curl_share_option_h
#define curl_wrapper_curl_share_option_h

#include "curl_share.h"
#include <string>

using curl::curl_share;
using std::string;

template<> class curl_share::option_pair<string> {
public:
    option_pair(const CURLSHoption option, const string value) : option(option), value(value) {};
    CURLSHoption first() const;
    const char *second() const;
private:
    const CURLSHoption option;
    const string value;
};

inline CURLSHoption curl_share::option_pair<string>::first() const {
    return this->option;
}

inline const char *curl_share::option_pair<string>::second() const {
    return this->value.c_str();
}

#endif