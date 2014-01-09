//
//  curl_easy_option.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 09/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curl_wrapper_curl_easy_option_h
#define curl_wrapper_curl_easy_option_h

#include "curl_easy.h"
#include <string>

using curl::curl_easy;
using std::string;

template<> class curl_easy::option_pair<string> {
public:
    option_pair(const CURLoption option, const string value) : option(option), value(value) {};
    CURLoption first() const;
    const char *second() const;
private:
    const CURLoption option;
    const string value;
};

inline CURLoption curl_easy::option_pair<string>::first() const {
    return this->option;
}

inline const char *curl_easy::option_pair<string>::second() const {
    return this->value.c_str();
}

#endif