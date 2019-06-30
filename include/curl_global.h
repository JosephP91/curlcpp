/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_global.h
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

#ifndef __curlcpp__curl_global__
#define __curlcpp__curl_global__

#include <curl/curl.h>
#include "curl_exception.h"

namespace curl {
    /**
     * This class provides global initialization of curl so that use of all curl
     * interfaces is thread safe.
     */
    class curl_global {
    public:
        /**
         * The default constructor will initialize the curl
         * environment with the default flag.
         */
        curl_global();
        /**
         * Overloaded constructor that initializes curl environment
         * with user specified flag.
         */
        explicit curl_global(long);

        /**
          * Copying disabled to follow RAII idiom.
          */
        curl_global(const curl_global&) = delete;
        curl_global& operator=(const curl_global&) = delete;

        /**
         * The virtual destructor will provide an easy and clean
         * way to deallocate resources, closing curl environment
         * correctly.
         */
        virtual ~curl_global();
    };
}

#endif	/* defined(__curlcpp__curl_global__) */
