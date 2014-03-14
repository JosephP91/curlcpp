//
//  exceptions.h
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__exceptions__
#define __curlcpp__exceptions__

#include <curl/curl.h>
#include <exception>
#include <string>

using std::exception;
using std::string;
using std::make_pair;
using std::pair;

template<class T> class curl_error : public exception {
public:
    curl_error(const string error, const T code) : error(error), code(code) {}
    ~curl_error() throw() {};
    pair<string,T> what() noexcept;
private:
    string error;
    T code;
};

template<class T> pair<string,T> curl_error<T>::what() noexcept {
    return make_pair(this->error,this->code);
}

#endif /* defined(__curlcpp__exceptions__) */