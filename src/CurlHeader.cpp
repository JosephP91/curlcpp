/* 
 * File:   CurlHeader.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:45 PM
 */

#include "CurlHeader.h"
#include "CurlError.h"
#include <algorithm>

using curl::CurlHeader;
using std::for_each;

// Implementation of constructor
CurlHeader::CurlHeader(const size_t header_num) {
    CurlHeader();
    this->setHeadersSize(header_num);
}

// Implementation of destructor
CurlHeader::~CurlHeader() {
    curl_slist_free_all(this->headers);
    this->headers = nullptr;
}

// Implementation of setHeader method
void CurlHeader::setHeader(const string header) {
    this->headers = curl_slist_append(this->headers,header.c_str());
    if (this->headers == nullptr) {
        throw CurlError<int>(" ** An error occurred while inserting last header ** ",0);
    }
}

// Implementation of setHeadersSize method
void CurlHeader::setHeadersSize(const size_t headers_num) {
    if (headers_num > 0) {
        if (headers_num != this->tmpHeaders.size()) {
            this->tmpHeaders.resize(headers_num);
        }
    } else {
        throw new CurlError<int>(" ** Headers vector size cannot be less or equal to zero ** ",0);
    }
}

// Implementation of addHeader method
CurlHeader &CurlHeader::addHeader(const vector<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmpHeaders.push_back(header); } );
    return *this;
}

// Implementation of addHeader overloaded method
CurlHeader &CurlHeader::addHeader(const list<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmpHeaders.push_back(header); } );
    return *this;
}

// Implementation of addHeader overloaded method
CurlHeader &CurlHeader::addHeader(const string header) {
    this->tmpHeaders.push_back(header);
    return *this;
}

// Implementation of remveHeader method
CurlHeader &CurlHeader::removeHeader(const string remove) {
    for (vector<string>::iterator it=this->tmpHeaders.begin(); it!=this->tmpHeaders.end(); ++it) {
        if ((*it)==remove) {
            this->tmpHeaders.erase(it);
            return *this;
        }
    }
    return *this;
}

// Implementation of confirmHeaders method
void CurlHeader::confirmHeaders() {
    for_each(this->tmpHeaders.begin(),this->tmpHeaders.end(),[this](const string header) { this->setHeader(header); } );
}

const // Implementation of getHeader method
struct curl_slist *CurlHeader::getHeaders() const {
    return this->headers;
}