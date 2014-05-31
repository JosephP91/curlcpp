/* 
 * File:   CurlHeader.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:45 PM
 */

#include "CurlHeader.h"
#include <algorithm>

using std::for_each;
using curl::CurlHeader;

// Implementation of constructor
CurlHeader::CurlHeader(const size_t header_num) {
    CurlHeader();
    this->setSize(header_num);
}

// Implementation of destructor
CurlHeader::~CurlHeader() {
    curl_slist_free_all(this->headers);
    this->headers = nullptr;
}

// Implementation of setHeader method
void CurlHeader::set(const string header) {
    this->headers = curl_slist_append(this->headers,header.c_str());
    if (this->headers == nullptr) {
        throw CurlError(" *** An error occurred while inserting last header ***");
    }
}

// Implementation of setHeadersSize method
void CurlHeader::setSize(const size_t headers_num) {
    if (headers_num > 0) {
        if (headers_num != this->tmpHeaders.size()) {
            this->tmpHeaders.resize(headers_num);
        }
    } else {
        throw CurlError(" *** Headers vector size cannot be less or equal to zero ***");
    }
}

// Implementation of add method
void CurlHeader::add(const vector<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmpHeaders.push_back(header); } );
}

// Implementation of add overloaded method
void CurlHeader::add(const list<string> &headers) {
    for_each(headers.begin(),headers.end(),[this](const string header) { this->tmpHeaders.push_back(header); } );
}

// Implementation of add overloaded method
void CurlHeader::add(const string header) {
    this->tmpHeaders.push_back(header);
}

// Implementation of remve method
void CurlHeader::remove(const string remove) {
    for (vector<string>::iterator it = this->tmpHeaders.begin(); it != this->tmpHeaders.end(); ++it) {
        if ((*it) == remove) {
            this->tmpHeaders.erase(it);
            break;
        }
    }
}

// Implementation of confirm method
void CurlHeader::confirm() {
    for_each(this->tmpHeaders.begin(),this->tmpHeaders.end(),[this](const string header) { this->set(header); } );
}

// Implementation of getHeader method
const vector<string> CurlHeader::get() const {
    return this->tmpHeaders;
}