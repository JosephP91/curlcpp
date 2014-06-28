//
//  curl_error.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 02/06/14.
//

#include "curl_error.h"

using curl::curl_error;

// Need to define the traceback here to separate declaration from definition, or we'll get a linker error.
vector<pair<string,string>> curl::curl_error::traceback;

// Constuctor implementation. Every call will push into the calls stack the function name and the error occurred.
curl_error::curl_error(const string error, const string fun_name) {
    curl_error::traceback.insert(curl_error::traceback.begin(),pair<string,string>(error,fun_name));
}

// Implementation of destructor.
curl_error::~curl_error() throw() {
    // ... nothing to do here ...
}
