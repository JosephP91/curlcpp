//
//  exceptions.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 06/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curl_wrapper_exceptions_h
#define curl_wrapper_exceptions_h

#include <curl/curl.h>
#include <exception>
#include <string>

using std::exception;
using std::string;
using std::make_pair;
using std::pair;

template<class T> class curl_error : public exception {
public:
    curl_error(const string error, const T code) : error(error), code(code) {};
    using exception::what;
    pair<string,T> what() { return make_pair(error,code); };
private:
    string error;
    T code;
};


class null_pointer_exception : public exception {
public:
    null_pointer_exception() : error("NULL pointer intercepted!") {};
    null_pointer_exception(const string error) : error(error) {};
    using exception::what;
    string what() { return this->error; };
private:
    string error;
};

#endif