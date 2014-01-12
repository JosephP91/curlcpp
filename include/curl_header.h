//
//  curl_header.h
//  meteo
//
//  Created by Giuseppe Persico on 04/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __meteo__header__
#define __meteo__header__

#include <vector>
#include <string>
#include <list>
#include <curl/curl.h>

using std::string;
using std::vector;
using std::list;

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

#endif /* defined(__meteo__header__) */