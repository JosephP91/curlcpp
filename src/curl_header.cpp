/**
 * File:   curl_header.cpp
 * Author: Giuseppe Persico
 */

#include "curl_header.h"
#include "curl_exception.h"
#include <algorithm>

using std::for_each;
using curl::curl_header;
using curl::curl_exception;

// Implementation of constructor.
curl_header::curl_header() : size(0), headers(nullptr) {
    // ... nothing to do here ...
}

// Implementation of the list constructor's initialize method.
curl_header::curl_header(initializer_list<string> headers) : size(0), headers(nullptr) {
    for_each(headers.begin(),headers.end(),[this](const string header) {
        this->add(header);
    });
}

/**
 * Implementation of assignment operator. The object has just been created, so its members have just
 * been loaded in memory, so we need to give a valid value to them (in this case just to "headers").
 */
curl_header &curl_header::operator=(const curl_header &header) {
    if (this == &header) {
        return *this;
    }
    curl_slist_free_all(this->headers);
    struct curl_slist *tmp_ptr = header.headers;
    while (tmp_ptr != nullptr) {
        this->add(tmp_ptr->data);
        tmp_ptr = tmp_ptr->next;
    }
    return *this;
}

// Implementation of destructor.
curl_header::~curl_header() NOEXCEPT {
    if (this->headers != nullptr) {
        curl_slist_free_all(this->headers);
        this->headers = nullptr;
    }
}

// Implementation of add overloaded method.
void curl_header::add(const string header) {
    this->headers = curl_slist_append(this->headers,header.c_str());
    if (this->headers == nullptr) {
        throw curl_exception("Null pointer exception",__FUNCTION__);
    }
    ++this->size;
}
