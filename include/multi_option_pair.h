//
//  curl_multi_option.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 09/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curl_wrapper_curl_multi_option_h
#define curl_wrapper_curl_multi_option_h

#include "curl_multi.h"
#include <string>

using curl::curl_multi;
using std::string;

namespace curl {
    template<class T> class curl_multi::option_pair {
    public:
        option_pair(const CURLMoption option, const T value) : option(option), value(value) {};
        inline const CURLMoption first() const { return this->option; }
        inline const T second() const { return this->value; }
    private:
        const CURLMoption option;
        const T value;
    };

    template<> class curl_multi::option_pair<string> {
    public:
        option_pair(const CURLMoption option, const string value) : option(option), value(value) {};
        inline const CURLMoption first() const noexcept { return this->option; }
        inline const char *second() const noexcept { return this->value.c_str(); }
    private:
        const CURLMoption option;
        const string value;
    };
}

#endif