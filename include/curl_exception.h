/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_exception.h
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __curlcpp__curl_exception__
#define __curlcpp__curl_exception__

#include <iostream>
#include <string>
#include <exception>
#include <utility>
#include <vector>
#include <algorithm>
#include <curl/curl.h>

#include "curl_config.h"

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::pair;
using std::vector;
using std::for_each;

// We like it short.
using curlcpp_traceback_object = pair<string,string>;
using curlcpp_traceback = vector<curlcpp_traceback_object>;

namespace curl {
    /**
     * This class represents a custom exception for libcurl errors. 
     * If a function throws an error, its name will be added to a
     * vector (treated like a stack, because if I had used a stack,
     * to print it, I should have to remove all the elements), so
     * users can keep track of which method threw which exception.
     */
    class curl_exception : public exception {
    public:
        /**
         * This constructor is used to build the error.
         */
        curl_exception(const string, const string);
        /**
         * The destructor, in this case, doesn't do anything.
         */
        ~curl_exception() NOEXCEPT;
        using exception::what;
        /**
         * Returns the vector of errors.
         */
        curlcpp_traceback get_traceback() const;
        /**
         * Simple method which prints the entire error stack.
         */
        void print_traceback() const;
    private:
        /**
         * The error container must be static or will be cleared
         * when an exception is thrown.
         */
        static curlcpp_traceback traceback;
    };

    // Implementation of print_traceback
    inline void curl_exception::print_traceback() const {
        for_each(curl_exception::traceback.begin(),curl_exception::traceback.end(),[](const curlcpp_traceback_object &value) {
            cout<<"ERROR: "<<value.first<<" ::::: FUNCTION: "<<value.second<<endl;
        });
    }
    
    // Implementation of get_traceback.
    inline curlcpp_traceback curl_exception::get_traceback() const {
        return curl_exception::traceback;
    }
    
    /**
     * Derived class represents an error condition returned by the easy
     * interface functions.
     */
    class curl_easy_exception : public curl_exception {
    public:
        /**
         * This constructor allows to specify a custom error message and the method name where
         * the exception has been thrown.
         */
        curl_easy_exception(const string error, const string method) : curl_exception(error,method) {}
        /**
         * The constructor will transform a CURLcode error in a proper error message.
         */
        curl_easy_exception(const CURLcode code, const string method) : curl_exception(curl_easy_strerror(code),method) {}
    };
    
    /**
     * Derived class represents an error condition returned by the multi
     * interface functions.
     */
    class curl_multi_exception : public curl_exception {
    public:
        /**
         * This constructor enables setting a custom error message and the method name where
         * the exception has been thrown.
         */
        curl_multi_exception(const string error, const string method) : curl_exception(error,method) {}
        /**
         * The constructor will transform a CURLMcode error to a proper error message.
         */
        curl_multi_exception(const CURLMcode code, const string method) : curl_exception(curl_multi_strerror(code),method) {}
    };
    
    /**
     * Derived class used to represent an error condition returned by the share
     * interface functions.
     */
    class curl_share_exception : public curl_exception {
    public:
        /**
         * This constructor enables setting a custom error message and the method name where
         * the exception has been thrown.
         */
        curl_share_exception(const string error, const string method) : curl_exception(error,method) {}
        /**
         * The constructor will transform a CURLSHcode error in a proper error message.
         */
        curl_share_exception(const  CURLSHcode code, const string method) : curl_exception(curl_share_strerror(code),method) {}
    };
}

#endif /* defined(__curlcpp__curl_exception__) */
