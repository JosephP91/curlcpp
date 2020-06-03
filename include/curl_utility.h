/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_utility.h
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

#ifndef __curlcpp__curl_utility__
#define __curlcpp__curl_utility__

#include <string>
#include "curl_exception.h"

namespace curl {
    /**
     * This class provides some utilities that are unrelated to
     * the libcurl interfaces, so they are enclosed in this class.
     */
    class curl_utility {
    public:
        /**
         * This method returns the number of seconds since the Epoch, 
         * January 1st 1970 00:00:00 in the UTC time zone, for the date
         * and time that the datestring parameter specifies. Check the
         * online documentation for more information about the datetime
         * parameter.
         */
        static time_t get_date(const std::string&);
    private:
        /**
         * Build an object of this type have no sense. So let's hide
         * the constructor.
         */
        curl_utility() = default;
    };

    // Implementation of get_date method.
    time_t curl_utility::get_date(const std::string& format) {
        const time_t value = curl_getdate(format.c_str(),nullptr);
        if (value == -1) {
            throw curl_exception("*** Error while parsing the date ***",__FUNCTION__);
        }
        return value;
    }
}

#endif /* defined(__curlcpp__curl_utility__) */
