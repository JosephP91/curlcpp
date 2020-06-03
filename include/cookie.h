/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - cookie.h
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

#ifndef CURLCPP_COOKIE_H
#define CURLCPP_COOKIE_H

#include <string>

#include "curl_exception.h"
#include "cookie_datetime.h"

namespace curl {
    /**
     * This class allows to specify every single field of an http-style cookie.
     */
    class cookie {
    public:
        /**
         * Default constructor.
         */
        cookie() = default;
        /**
         * The overloaded constructor allow a fast way to build a cookie.
         */
        cookie(const std::string&, const std::string&, const cookie_datetime &,
        		const std::string& = "", const std::string& = "", bool = false);
        /**
         * This constructor overloades the previous one.
         */
        cookie(const char *, const char *, const cookie_datetime &, const char * = "",
        		const char * = "", bool = false);
        /**
         * This method allows to specify the cookie name.
         */
        cookie *set_name(const std::string&);
        /**
         * This method overloads the previous one allowing to specify a const char *
         * instead of a string.
         */
        cookie *set_name(const char *);
        /**
         * This method allows to specify the cookie value.
         */
        cookie *set_value(const std::string&);
        /**
         * This method allows to specify the cookie value,
         */
        cookie *set_value(const char *);
        /**
         * This method allows to specify the cookie path.
         */
        cookie *set_path(const std::string&) NOEXCEPT;
        /**
         * This method overloads the previous one allowing to specify a const char *
         * instead of a string.
         */
        cookie *set_path(const char *) NOEXCEPT;
        /**
         * This method allows to specify the cookie domain.
         */
        cookie *set_domain(const std::string&) NOEXCEPT;
        /**
         * This method overloads the previous one allowing to specify a const char *
         * instead of a string.
         */
        cookie *set_domain(const char *) NOEXCEPT;
        /**
         * This method allows to specify the cookie security.
         */
        cookie *set_secure(bool) NOEXCEPT;
        /**
         * This method overloads the previous one allowing to specify an integer instead
         * of a bool.
         */
        cookie *set_secure(unsigned int);
        /**
         * This method overloads the previous one allowing to specify a string to indicate
         * whether the cookie is secure (with "secure" keyword) or not (empty string).
         */
        cookie *set_secure(const std::string&) NOEXCEPT;
        /**
         * This method overloads the previous one allowing to specify a string to indicate
         * whether the cookie is secure (with "secure" keyword) or not (empty string).
         */
        cookie *set_secure(const char *) NOEXCEPT;
        /**
         * This method allows to specify a datetime expiration to this cookie.
         */
        cookie *set_datetime(const cookie_datetime &) NOEXCEPT;
        /**
         * This method returns the cookie name.
         */
        std::string get_name() const NOEXCEPT;
        /**
         * This method returns the cookie value.
         */
        std::string get_value() const NOEXCEPT;
        /**
         * This method returns the cookie path.
         */
        std::string get_path() const NOEXCEPT;
        /**
         * This method returns the cookie domain.
         */
        std::string get_domain() const NOEXCEPT;
        /**
         * This method returns the datetime expire object for this cookie.
         */
        cookie_datetime get_datetime() const NOEXCEPT;
        /**
         * This method returns the cookie security.
         */
        bool is_secure() const NOEXCEPT;
        /**
         * This method allows to get a string representing the entire cookie. Example:
         * 'Set-cookie: name=xxx; path=/; domain=/ expires=date'
         */
        std::string get_formatted() NOEXCEPT;
    private:
        /**
         * The cookie name.
         */
        std::string name;
        /**
         * Il valore del cookie.
         */
        std::string value;
        /**
         * The cookie path.
         */
        std::string path;
        /**
         * The cookie domain.
         */
        std::string domain;
        /**
         * The cookie expire date and time.
         */
        cookie_datetime datetime;
        /**
         * The cookie security.
         */
        bool secure;
    };
}

#endif //CURLCPP_COOKIE_H