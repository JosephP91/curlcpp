//
//  curl_error.h
//  curlcpp
//
//  Created by Giuseppe Persico on 02/06/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_error__
#define __curlcpp__curl_error__


#include <iostream>
#include <string>
#include <exception>
#include <utility>
#include <stack>

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::pair;
using std::make_pair;
using std::stack;

namespace curl {
    class curl_error : public exception {
    public:
        curl_error(const string, const string);
        ~curl_error() throw() { /* ... nothing to delete */ }
        const stack<pair<string,string>> what();
        const void print_traceback();
    private:
        static stack<pair<string,string>> traceback;
    };
}
#endif /* defined(__curlcpp__curl_error__) */
