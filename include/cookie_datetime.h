/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - cookie_datetime.h
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

#ifndef CURLCPP_COOKIE_DATETIME_H
#define CURLCPP_COOKIE_DATETIME_H

#include "cookie_date.h"
#include "cookie_time.h"

namespace curl {
    /**
     * This class provide an easy way to specify the date and the time of cooking expiration.
     */
    class cookie_datetime {
    public:
        /**
         * Default constructor.
         */
        cookie_datetime() = default;
        /**
         * The constructor with parameters allows to specify a time and a date for cookie expiration.
         */
        cookie_datetime(const cookie_time &, const cookie_date &) NOEXCEPT;
        /**
         * This method allows to set the expiration time.
         */
        cookie_datetime *set_time(const cookie_time &) NOEXCEPT;
        /**
         * This method allows to set the expiration date.
         */
        cookie_datetime *set_date(const cookie_date &) NOEXCEPT;
        /**
         * This method returns the time object.
         */
        cookie_time get_time() const NOEXCEPT;
        /**
         * This method returns the date object.
         */
        cookie_date get_date() const NOEXCEPT;
        /**
         * This method returns the cookie_datetime as a string.
         */
        std::string get_formatted() NOEXCEPT;
    private:
        /**
         * Time object.
         */
        cookie_time time;
        /**
         * Date object.
         */
        cookie_date date;
    };
}

#endif //CURLCPP_COOKIE_DATETIME_H