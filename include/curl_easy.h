/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_easy.h
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

#ifndef curl_easy_H
#define	curl_easy_H

#include <algorithm>
#include <curl/curl.h>
#include <memory>

#include "curl_interface.h"
#include "curl_pair.h"
#include "curl_writer.h"

using std::for_each;
using std::unique_ptr;

using curl::curl_pair;
using curl::curl_writer;
using curl::curl_interface;
using curl::curl_easy_exception;

namespace curl  {
    /**
     * Easy interface is used to make requests and transfers. 
     * You don't have to worry about freeing data or things like
     * that. The class will do it for you.
     */
    class curl_easy : public curl_interface<CURLcode> {
    public:
        /**
         * The default constructor will initialize the easy handler
         * using libcurl functions.
         */
        curl_easy();
        /**
         * This overloaded constructor allows users to specify a
         * stream where they want to put the output of the libcurl
         * operations.
         */
        explicit curl_easy(curl_writer &);
        /**
         * This overloaded constructor allows users to specify a flag
         * used to initialize libcurl environment.
         */
        explicit curl_easy(const long);
        /**
         * This overloaded constructor specifies the environment
         * initialization flags and an output stream for the libcurl output.
         */
        curl_easy(const long, curl_writer &);
        /**
         * Copy constructor to handle pointer copy. Internally, it uses
         * a function which duplicates the easy handler.
         */
        curl_easy(const curl_easy &);
        /**
         * Assignment operator used to perform assignment between objects
         * of this class.
         */
        curl_easy &operator=(const curl_easy &);
        /**
         * Override of equality operator. It has been overridden to check
         * whether two curl_easy objects are equal.
         */
        bool operator==(const curl_easy &) const;
        /**
         * The destructor will perform cleanup operations.
         */
        ~curl_easy() noexcept;
        /**
         * Allows users to specify an option for the current easy handler,
         * using a curl_pair object.
         */
        template<typename T> void add(const curl_pair<CURLoption,T>);
        /**
         * Allows users to specify a list of options for the current
         * easy handler. In this way, you can specify any iterable data
         * structure.
         */
        template<typename Iterator> void add(Iterator, const Iterator);
        /**
         * This method allows users to request internal information from
         * the curl session. I recommend reading online documentation for
         * further information.
         */
        template<typename T> unique_ptr<T> get_info(const CURLINFO) const;
        /**
         * get_info overloaded method. It it used when the second argument is
         * of type struct_slist*.
         */
        unique_ptr<vector<string>> get_info(const CURLINFO) const;
        /**
         * Using this function, you can explicitly pause a running connection, 
         * and you can resume a previously paused connection.
         */
        void pause(const int);
        /**
         * This function converts the given input string to an URL encoded
         * string and returns a newly allocated string.
         */
        void escape(string &);
        /**
         * This function converts the given URL encoded input string to a
         * "plain string" and returns a newly allocated string.
         */
        void unescape(string &);
        /**
         * This function performs all the operations a user has specified
         * with the add methods. If the performing operation has finished
         * the method returns true otherwise false.
         */
        void perform();
        /**
         * Re-initializes all options previously set on a specified CURL handle
         * to the default values. This puts the handle back to the initial state.
         */
        void reset() noexcept;
        /**
         * Simple getter method used to return the easy handle.
         */
        CURL *get_curl() const;
    private:
        CURL *curl;
    };
    
    // Implementation of overloaded add method.
    template<typename Iterator> void curl_easy::add(Iterator begin, const Iterator end) {
        for (; begin != end; ++begin) {
            this->add(*begin);
        }
    }
    
    // Implementation of add method.
    template<typename T> void curl_easy::add(const curl_pair<CURLoption,T> pair) {
        const CURLcode code = curl_easy_setopt(this->curl,pair.first(),pair.second());
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
    }

    // Implementation of get_session_info method.
    template<typename T> unique_ptr<T> curl_easy::get_info(const CURLINFO info) const {
        unique_ptr<T> ptr(new T);
        const CURLcode code = curl_easy_getinfo(this->curl,info,ptr.get());
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
        return ptr;
    }

    // Implementation of get_curl method.
    inline CURL *curl_easy::get_curl() const {
        return this->curl;
    }
}

#endif	/* curl_easy_H */
