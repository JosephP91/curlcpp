/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - cookie_date.h
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

#ifndef CURLCPP_COOKIE_TIME_H
#define CURLCPP_COOKIE_TIME_H

#include "curl_config.h"

#include <string>
#include <iostream>
#include <sstream>

namespace curl {
    /**
     * This class provides a fast way to build a time object formed by hour, minutes and seconds.
     */
    class cookie_time {
    public:
        /**
         * The default constructor will initialize every attribute with zero.
         */
        cookie_time() : hour(0), minutes(0), seconds(0) {};
        /**
         * The constructor with parameters allows to initialize attributes with custom values.
         */
        cookie_time(unsigned int, unsigned int, unsigned int);
        /**
         * This method allows to specify the hours.
         */
        cookie_time *set_hour(unsigned int) NOEXCEPT;
        /**
         * This method allows to specify the minutes.
         */
        cookie_time *set_minutes(unsigned int) NOEXCEPT;
        /**
         * This method allows to specify the seconds.
         */
        cookie_time *set_seconds(unsigned int) NOEXCEPT;
        /**
         * This method returns the hours.
         */
        unsigned int get_hour() const NOEXCEPT;
        /**
         * This method returns the minutes.
         */
        unsigned int get_minutes() const NOEXCEPT;
        /**
         * This method returns the seconds.
         */
        unsigned int get_seconds() const NOEXCEPT;
        /**
         * This method returns the time formatted as h:m:s
         */
        std::string get_formatted() const NOEXCEPT;
    private:
        /**
         * The hours.
         */
        unsigned int hour;
        /**
         * The minutes.
         */
        unsigned int minutes;
        /**
         * The seconds.
         */
        unsigned int seconds;
    };
}

#endif //CURLCPP_COOKIE_TIME_H