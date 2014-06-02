//
//  curl_error.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 02/06/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "curl_error.h"

using curl::curl_error;

// Need to define the traceback here to separate declaration from definition, or we'll get a linker error.
stack<pair<string,string>> curl::curl_error::traceback;

// Constuctor implementation. Every call will push into the calls stack the function name and the error occurred.
curl_error::curl_error(const string error, const string fun_name) {
    curl_error::traceback.push(pair<string,string>(error,fun_name));
}

// Returns the traceback stack
const stack<pair<string,string>> curl_error::what() {
    return curl_error::traceback;
}

// Simply prints the stack. Check that this method clears the stack to print it.
const void curl_error::print_traceback() {
    while (!curl_error::traceback.empty()) {
        cout<<"ERROR: "<<curl_error::traceback.top().first<<" == FUNCTION: "<<curl_error::traceback.top().second<<endl;
        curl_error::traceback.pop();
    }
}