/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_interface.h
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

#ifndef __curlcpp__curl_interface__
#define __curlcpp__curl_interface__

#include <curl/curl.h>
#include "curl_exception.h"

using curl::curl_exception;

namespace curl {
    /**
     * This class is a common interface for all the libcurl interfaces:
     * easy, multi and share. It provides methods that these three interfaces
     * have in common with each other.
     */
    template<class T> class curl_interface {
    protected:
        /**
         * The default constructor will initialize the curl
         * environment with the default flag.
         */
        curl_interface();
        /**
         * Overloaded constructor that initializes curl environment
         * with user specified flag.
         */
        explicit curl_interface(const long);
        /**
         * The virtual destructor will provide an easy and clean
         * way to deallocate resources, closing curl environment
         * correctly.
         */
        virtual ~curl_interface();
    };
    
    // Implementation of constructor.
    template<class T> curl_interface<T>::curl_interface() {
        const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
    }
    
    // Implementation of overloaded constructor.
    template<class T> curl_interface<T>::curl_interface(const long flag) {
        const CURLcode code = curl_global_init(flag);
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
    }
    
    // Implementation of the virtual destructor.
    template<class T> curl_interface<T>::~curl_interface() {
        curl_global_cleanup();
    }
}

#endif	/* defined(__curlcpp__curl_interface__) */
