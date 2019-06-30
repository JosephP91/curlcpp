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
        explicit curl_interface(long);
        /**
         * The virtual destructor will provide an easy and clean
         * way to deallocate resources, closing curl environment
         * correctly.
         */
        virtual ~curl_interface();

    private:
        /**
         * This struct is used for initializing curl only once
         * it is implemented as a singleton pattern
         */
        struct global_initializer {
            explicit global_initializer(long);
            ~global_initializer();
        };

        /**
         * the singleton initialization, constructing a global_initializer.
         */
        static void init(long flag);
    };
    
    // Implementation of constructor.
    template<class T> curl_interface<T>::curl_interface() {
        init(CURL_GLOBAL_ALL);
    }
    
    // Implementation of overloaded constructor.
    template<class T> curl_interface<T>::curl_interface(const long flag) {
        init(flag);
    }
    
    // Implementation of the virtual destructor.
    template<class T> curl_interface<T>::~curl_interface() = default;

    // Implementation of the static initialization function
    template<class T> void curl_interface<T>::init(const long flag) {
        static global_initializer _instance {flag};
    }

    // Implementation of the singleton initializer
    template<class T> curl_interface<T>::global_initializer::global_initializer(const long flag) {
        const CURLcode code = curl_global_init(flag);
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
    }

    // Implementation of the singleton destructor
    template<class T> curl_interface<T>::global_initializer::~global_initializer() {
        curl_global_cleanup();
    }
}

#endif	/* defined(__curlcpp__curl_interface__) */
