/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_cookie.h
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

#ifndef curl_cookie_h
#define curl_cookie_h

#include <string>
#include <vector>
#include <ostream>

#include "curl_easy.h"
#include "cookie.h"

namespace curl {
    // Typedef to enhance readability.
	using curlcpp_cookies = std::vector<std::string>;
    /**
     * This class represents a generic cookie handler. It allows a user to get
     * and set cookie for a domain, in an easy way and without caring about resources
     * allocation and deallocation.
     */
    class curl_cookie {
    public:
   		/**
   		 * This constructor allow you to specify a curl_easy object.
   		 */
        explicit curl_cookie(curl_easy &easy) : easy(easy) {}
        /**
         * This method allow you to set the cookie file from where to read initial cookies.
         * If you pass an empty string or a string containing a non existing file's path, 
         * the cookie engine will be initialized, but without reading initial cookies.
         */
        void set_file(const std::string&);
        /**
         * This method allow you to specify a string that represents a cookie. Such a cookie 
         * can be either a single line in Netscape / Mozilla format or just regular HTTP-style
         * header (Set-Cookie: ...) format. This will also enable the cookie engine. This adds
         * that single cookie to the internal cookie store.
         */
        void set(curl::cookie &);
        /**
         * This method overloads the one previously declared allowing to specify a vector of cookies.
         */
        void set(const std::vector<curl::cookie> &);
        /**
         * This method allow you to get all known cookies for a specific domain.
         */
        curlcpp_cookies get() const NOEXCEPT;
        /**
         * This method erases all cookies held in memory.
         */
        void erase();
        /**
         * This method writes all the cookies held in memory to the file specifiied with
         * set_cookiejar_file method.
         */
        void flush();
        /**
         * This method erases all the session cookies held in memory.
         */
        void erase_session();
        /**
         * This method loads all the cookies from the file specified with set_cookie_file method.
         */
        void reload();
    private:
        /**
         * Istance on curl_easy class.
         */
        curl_easy &easy;
    };
}

#endif /* curl_cookie_h */