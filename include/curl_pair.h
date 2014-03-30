//
//  option_pair.h
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curlcpp_option_pair_h
#define curlcpp_option_pair_h

#include "curl_http_post.h"

using curl::curl_http_post;

namespace curl {
    template<class T, class K> class curl_pair {
    public:
        curl_pair(const T option, const K value) : option(option), value(value) {};
        inline const T first() const noexcept { return this->option; }
        inline const K second() const noexcept { return this->value; }
    private:
        const T option;
        const K value;
    };
    
    template<class T> class curl_pair<T,string> {
    public:
        curl_pair(const T option, const string value) : option(option), value(value) {};
        inline const T first() const noexcept { return this->option; }
        inline const char *second() const noexcept { return this->value.c_str(); }
    private:
        const T option;
        const string value;
    };
    
    template<class T> class curl_pair<T,curl_http_post> {
    public:
        curl_pair(const T option, const curl_http_post value) : option(option), value(value) {}
        inline const T first() const noexcept { return this->option; }
        inline const curl_httppost *second() const noexcept { return this->value.get_form_post(); }
    private:
        const T option;
        const curl_http_post value;
    };
}

#endif