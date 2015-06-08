/**
 * File:   curl_exception.cpp
 * Author: Giuseppe Persico
 */

#include "curl_exception.h"

using curl::curl_exception;

// Constructor implementation. Every call will push into the calls stack the function name and the error occurred.
curl_exception::curl_exception(const string &error, const string &method) {
    traceback.insert(
        traceback.begin(),
        pair<string, string>(error, method));
}

// Implementation of destructor.
curl_exception::~curl_exception() NOEXCEPT {
    // ... nothing to do here ...
}
