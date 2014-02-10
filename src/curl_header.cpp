//
//  curl_header.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "curl_header.h"
#include "curl_error.h"

using curl::curl_header;

curl_header::curl_header(const size_t header_num) {
    curl_header();
    this->set_headers_size(header_num);
}

curl_header::~curl_header() {
    curl_slist_free_all(this->headers);
    this->headers = nullptr;
}

void curl_header::set_header(const string header) {
    this->headers = curl_slist_append(this->headers,header.c_str());
    if (this->headers == nullptr) {
        throw curl_error<int>(" ** An error occurred while inserting last header ** ",0);
    }
}

void curl_header::set_headers_size(const size_t headers_num) {
    if (headers_num>0) {
        if (headers_num!=this->tmp_headers.size()) {
            this->tmp_headers.resize(headers_num);
        }
    } else {
        throw new curl_error<int>(" ** Headers vector size cannot be less or equal to zero ** ",0);
    }
}

curl_header &curl_header::add_header(const vector<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmp_headers.push_back(header); } );
    return *this;
}

curl_header &curl_header::add_header(const list<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmp_headers.push_back(header); } );
    return *this;
}

curl_header &curl_header::add_header(const string header) {
    this->tmp_headers.push_back(header);
    return *this;
}

curl_header &curl_header::remove_header(const string remove) {
    for (vector<string>::iterator it=this->tmp_headers.begin(); it!=this->tmp_headers.end(); ++it) {
        if ((*it)==remove) {
            this->tmp_headers.erase(it);
            return *this;
        }
    }
    return *this;
}

void curl_header::confirm_headers() {
    for_each(this->tmp_headers.begin(),this->tmp_headers.end(),[this](const string header) { this->set_header(header); } );
}

curl_header::DEFAULT_HEADERS_TYPE curl_header::get_headers() const {
    return this->headers;
}