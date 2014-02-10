//
//  curl_header.h
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_header__
#define __curlcpp__curl_header__

#include <vector>
#include <string>
#include <list>
#include <curl/curl.h>

using std::string;
using std::vector;
using std::list;

namespace curl {
    class curl_header {
    public:
        using DEFAULT_HEADERS_TYPE = struct curl_slist *;
        curl_header() : headers(nullptr) {};
        curl_header(const size_t);
        ~curl_header();
        void set_headers_size(const size_t);
        curl_header &add_header(const string);
        curl_header &add_header(const vector<string> &);
        curl_header &add_header(const list<string> &);
        curl_header &remove_header(const string);
        void confirm_headers();
        DEFAULT_HEADERS_TYPE get_headers() const;
    protected:
        void set_header(const string);
    private:
        vector<string> tmp_headers;
        DEFAULT_HEADERS_TYPE headers;
    };
}

#endif /* defined(__curlcpp__curl_header__) */
