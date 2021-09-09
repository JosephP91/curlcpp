/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_header.h
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

#ifndef __curlcpp__curl_header__
#define __curlcpp__curl_header__

#include <string>
#include <initializer_list>
#include <curl/curl.h>

#include "curl_config.h"

namespace curl {

    /**
     * This class represents a generic header. It allows a user to add
     * headers without caring about deallocation of resources.
     */
    class curl_header {
    public:
        /**
         * The default constructor will initialize the headers list
         * with nullptr.
         */
        curl_header();
        /**
         * Overloaded constructor that allows users to initialize the
         * headers list with a list of values.
         */
        curl_header(std::initializer_list<std::string>);
        /**
         * Copy constructor. Performs a deep copy of the headers list.
         */
        curl_header(const curl_header &);
        /**
         * Assignment operator to perform assignment between object of
         * this class type.
         */
        curl_header &operator=(const curl_header &);
        /**
         * The destructor will deallocate the resources used to handle
         * the headers list.
         */
        ~curl_header() NOEXCEPT;
        /**
         * This method allows users to add a header as string.
         */
        void add(const std::string&);
        /**
         * This method allows users to add headers specifying an iterable
         * data structure containing the headers to add.
         */
        template<typename Iterator> void add(Iterator, Iterator);
        /**
         * Simple getter method that returns the pointer to the headers
         * list.
         */
        const struct curl_slist *get() const;
    private:
        int size;
        struct curl_slist *headers;
    };

    // Implementation of get method.
    inline const struct curl_slist *curl_header::get() const {
        return this->headers;
    }

    // Implementation of copy constructor.
    inline curl_header::curl_header(const curl_header &header) : headers(nullptr), size(0) {
        *this = header;
    }

    // Implementation of overloaded add method.
    template<typename Iterator> void curl_header::add(Iterator begin, const Iterator end) {
        for (; begin != end; ++begin) {
            this->add(*begin);
        }
    }
    
    /**
     * Re-declaring template curl_pair, in case this is not in include path
     */
    template<class T, class K> class curl_pair;
    
    /**
     * Template specialization of curl_pair for curl_header type.
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

#endif	/* defined(__curlcpp__curl_header__) */
