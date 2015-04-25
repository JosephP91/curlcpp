/*
 * File:    curl_utility.h
 * Author:  Giuseppe
 *
 * Created on March 26, 2014, 21:17 PM
 */

#ifndef __curlcpp__curl_utility__
#define __curlcpp__curl_utility__

#include <string>
#include "curl_exception.h"

using std::string;
using curl::curl_exception;

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
        static time_t get_date(const string);
    private:
        /**
         * Build an object of this type have no sense. So let's hide
         * the constructor.
         */
        curl_utility() {};
    };

    // Implementation of get_date method.
    time_t curl_utility::get_date(const string format) {
        const time_t value = curl_getdate(format.c_str(),nullptr);
        if (value == -1) {
            throw curl_exception("*** Error while parsing the date ***",__FUNCTION__);
        }
        return value;
    }
}

#endif /* defined(__curlcpp__curl_utility__) */
