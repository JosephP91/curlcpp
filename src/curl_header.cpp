/* 
 * File:   curl_header.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:45 PM
 */

#include "curl_header.h"
#include <algorithm>

using std::for_each;
using std::find;
using curl::curl_header;

// Implementation of constructor
curl_header::curl_header(const size_t size) {
    curl_header();
    if (size > 0) {
        this->headers_vector.resize(size);
    } else {
        throw curl_error(" *** Headers vector size cannot be less or equal to zero ***",__FUNCTION__);
    }
}

// Implementation of destructor
curl_header::~curl_header() {
    curl_slist_free_all(this->headers);
    this->headers = nullptr;
}

// Implementation of copy constructor.
curl_header::curl_header(const curl_header &header) {
    this->headers = header.headers;
    for_each(header.headers_vector.begin(),header.headers_vector.end(),[this](const string header) {
        this->headers_vector.push_back(header);
    });
}

// Implementation of assignment operator.
curl_header &curl_header::operator=(const curl_header &header) {
    if (this == &header) {
        return *this;
    }
    this->headers = header.headers;
    for_each(header.headers_vector.begin(),header.headers_vector.end(),[this](const string header) {
        this->headers_vector.push_back(header);
    });
    return *this;
}

// Implementation of add method.
void curl_header::add(const vector<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) {
        this->add(header);
    });
}

// Implementation of add overloaded method.
void curl_header::add(const list<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) {
        this->add(header);
    });
}

// Implementation of add overloaded method.
void curl_header::add(const string header) {
    this->headers_vector.push_back(header);
}

// Implementation of remove method.
void curl_header::remove(const string remove) {
    this->headers_vector.erase(find(headers_vector.begin(),headers_vector.end(),remove));
}

// Implementation of confirm method
void curl_header::confirm() {
    for_each(this->headers_vector.begin(),this->headers_vector.end(),[this](const string header) {
        this->headers = curl_slist_append(this->headers,header.c_str());
        if (this->headers == nullptr) {
            throw curl_error(" *** An error occurred while inserting header: "+header+"***",__FUNCTION__);
        }
    });
}

// Implementation of getHeader method
const vector<string> curl_header::get() const {
    return this->headers_vector;
}