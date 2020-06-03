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

#ifndef CURLCPP_COOKIE_DATE_H
#define CURLCPP_COOKIE_DATE_H

#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "curl_config.h"

namespace curl {
    // Enumeration to better define months.
    enum months { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
    // Enumeration to better define week days.
    enum weekdays {MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};

    // Leave this alone :)
    namespace details {
        // Map months numbers with months short names (cookies likes it short XD)
        static const std::map<int,std::string> monthsNames = {
                {JANUARY,"Jan"}, {FEBRUARY,"Feb"}, {MARCH,"Mar"}, {APRIL,"Apr"}, {MAY,"May"}, {JUNE,"Jun"},
                {JULY,"Jul"},{AUGUST,"Aug"},{SEPTEMBER,"Sep"},{OCTOBER,"Oct"},{NOVEMBER,"Nov"},{DECEMBER,"Dec"}
        };
        // Map week days numbers with days short names (cookies likes it, still, short XD)
        static const std::map<int,std::string> weekdayNames = {
                {MONDAY,"Mon"}, {TUESDAY,"Tue"}, {WEDNESDAY,"Wed"}, {THURSDAY,"Thu"}, {FRIDAY,"Fri"}, {SATURDAY,"Sat"},
                {SUNDAY,"Sun"}
        };
    }

    /**
     * This class provide an easy way to build a date formed by day, month and year
     */
    class cookie_date {
    public:
        /**
         * Default constructor. Inizialize the attributes with default values.
         */
        cookie_date() : day(1), month("Jan"), week_day("Mon"), year(1970) {}
        /**
         * Constructor with parameters, which gives a fast way to build a cookie_date object.
         */
        cookie_date(unsigned int, unsigned int, unsigned int, unsigned int) NOEXCEPT;
        /**
         * This method allows to specify the week dayname for the date. If the day is less or equal
         * than zero or greater than 7, 1 will be choosen
         */
        cookie_date *set_week_day(unsigned int) NOEXCEPT;
        /**
         * This method allows to specify a day for the date. If the day is less than zero or
         * greater than 31, 1 will be choosen.
         */
        cookie_date *set_day(unsigned int) NOEXCEPT;
        /**
         * This method allows to specify a month for the date. If the month is not supported,
         * January will be choosen.
         */
        cookie_date *set_month(unsigned int);
        /**
         * This method allows to specify a year for the date. If year is less than 1970, 1970 will
         * be choosen.
         */
        cookie_date *set_year(unsigned int) NOEXCEPT;
        /**
         * This method returns the week day name
         */
        std::string get_week_day() const NOEXCEPT;
        /**
         * This method returns the day number.
         */
        unsigned int get_day() const NOEXCEPT;
        /**
         * This method returns the month name.
         */
        std::string get_month() const NOEXCEPT;
        /**
         * This method returns the year number.
         */
        unsigned int get_year() const NOEXCEPT;
        /**
         * This method returns the date formatted as day-month-year
         */
        std::string get_formatted() NOEXCEPT;
    private:
        /**
         * The day for this date.
         */
        unsigned int day;
        /**
         * The month name.
         */
        std::string month;
        /**
         * The week dayname.
         */
        std::string week_day;
        /**
         * The month year.
         */
        unsigned int year;
    };
}

#endif //CURLCPP_COOKIE_DATE_H
