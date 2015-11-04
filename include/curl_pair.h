/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_pair.h
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

#ifndef __curlcpp__curl_pair__
#define __curlcpp__curl_pair__

#include <string>
#include "curl_config.h"

// Forward reference to curl_form and curl_header
namespace curl {
    class curl_form;
    class curl_header;
}

using std::string;
using curl::curl_form;
using curl::curl_header;

namespace curl {
    /**
     * This is a class that wraps two objects: an option and the value for
     * that option. It's very useful when building forms or setting options
     * for easy/multi/share handlers. It let you specify the libcurl option
     * and its value.
     */
    template<class T, class K> class curl_pair {
    public:
        /**
         * The two parameters constructor gives users a fast way to
         * build an object of this type.
         */
        curl_pair(const T option, const K &value) : option(option), value(value) {};
        /**
         * Simple method that returns the first field of the pair.
         */
        inline T first() const NOEXCEPT {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair.
         */
        inline K second() const NOEXCEPT {
            return this->value;
        }
    private:
        const T option;
        const K &value;
    };
    
    /**
     * Template specialization for C++ strings and CURLformoption.
     */
    template<> class curl_pair<CURLformoption,string> {
    public:
        /**
         * The two parameters constructor gives users a fast way to
         * build an object of this type.
         */
        curl_pair(const CURLformoption option, const string &value) : option(option), value(value) {}
        /**
         * Simple method that returns the first field of the pair.
         */
        inline CURLformoption first() const NOEXCEPT {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair as
         * a C string, so a const char *.
         */
        inline const char *second() const NOEXCEPT {
            return this->value.c_str();
        }
    private:
        const CURLformoption option;
        const string &value;
    };
        
    /**
     * Template specialization for C++ strings. Why do we need this? Because
     * curl_pair must be passed to C functions that doesen't know how to
     * handle C++ string type, so we can specialize curl_pair class in a
     * manner that its methods returns a const char *.
     */
    template<class T> class curl_pair<T,string> {
    public:
        /**
         * The two parameters constructor gives users a fast way to 
         * build an object of this type.
         */
        curl_pair(const T option, const string &value) : option(option == CURLOPT_POSTFIELDS ? CURLOPT_COPYPOSTFIELDS : option), value(value) {};
        /**
         * Simple method that returns the first field of the pair.
         */
        inline T first() const NOEXCEPT {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair as
         * a C string, so a const char *.
         */
        inline const char *second() const NOEXCEPT {
            return this->value.c_str();
        }
    private:
        const T option;
        const string &value;
    };
    
    /**
     * Template specialization for curl_form type. Why do we need this? Because
     * curl_form wraps a struct curl_httppost list. libcurl functions can't handle
     * curl_form type, so we need to specialize curl_pair to return a struct
     * curl_httppost *.
     */
    template<class T> class curl_pair<T,curl_form> {
    public:
        /**
         * The two parameters constructor gives users a fast way to build an object of
         * this type.
         */
        curl_pair(const T option, const curl_form &value) : option(option), value(value) {}
        /**
         * Simple method that returns the first field of the pair.
         */
        inline T first() const NOEXCEPT {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair as a 
         * C struct curl_httppost pointer.
         */
        inline const curl_httppost *second() const NOEXCEPT {
            return (this->value).get();
        }
    private:
        const T option;
        const curl_form &value;
    };
    
    /**
     * Template specialization for curl_header type. Why do we need this? Because
     * curl_header wraps a struct curl_slist list of headers. libcurl functions can't
     * handle a curl_header type, so we need to specialize curl_pair to return a 
     * struct curl_slist *.
     */
    template<class T> class curl_pair<T,curl_header> {
    public:
        /**
         * Thw two parameters constructor gives users a fast way to build an object
         * of this type.
         */
        curl_pair(const T option, const curl_header &value) : option(option), value(value) {}
        /**
         * Simple method that returns the first field of the pair.
         */
        inline T first() const NOEXCEPT {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair as a C struct 
         * curl_slist pointer.
         */
        inline const curl_slist *second() const NOEXCEPT {
            return (this->value).get();
        }
    private:
        const T option;
        const curl_header &value;
    };
}

#endif	/* defined(__curlcpp__curl_pair__) */
