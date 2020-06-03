/**
 * File:   cookie_date.cpp
 * Author: Giuseppe Persico
 */

#include "cookie_date.h"

using std::out_of_range;
using std::ostringstream;

// Implementation of constructor with parameters.
curl::cookie_date::cookie_date(const unsigned int week_day, const unsigned int day,
		const unsigned int month, const unsigned int year) NOEXCEPT {

    this->set_week_day(week_day)->set_day(day)->set_month(month)->set_year(year);
}

// Implementation of set_week_day method.
curl::cookie_date *curl::cookie_date::set_week_day(const unsigned int weekDay) NOEXCEPT {
    try {
        this->week_day = details::weekdayNames.at(weekDay);
    } catch (const out_of_range &exception) {
        this->week_day = "Mon";
    }
    return this;
}

// Implementation of set_day method.
curl::cookie_date *curl::cookie_date::set_day(const unsigned int cookieDay) NOEXCEPT {
    this->day = (cookieDay < 1 or cookieDay > 31) ? 1 : cookieDay;
    return this;
}

// Implementation of set_month method.
curl::cookie_date *curl::cookie_date::set_month(const unsigned int cookieMonth) {
    try {
        this->month = details::monthsNames.at(cookieMonth);
    } catch (const out_of_range &exception) {
        this->month = "Jan";
    }
    return this;
}

// Implementation of set_year method.
curl::cookie_date *curl::cookie_date::set_year(const unsigned int cookieYear) NOEXCEPT {
    this->year = (cookieYear < 1970 ) ? 1970 : cookieYear;
    return this;
}

std::string curl::cookie_date::get_week_day() const NOEXCEPT {
    return this->week_day;
}

// Implementation of get_day method.
unsigned int curl::cookie_date::get_day() const NOEXCEPT {
    return this->day;
}

// Implementation of get_month method.
std::string curl::cookie_date::get_month() const NOEXCEPT {
    return this->month;
}

// Implementation of get_year method.
unsigned int curl::cookie_date::get_year() const NOEXCEPT {
    return this->year;
}

// Implementation of get_formatted method.
std::string curl::cookie_date::get_formatted() NOEXCEPT {
    ostringstream stream;
    stream<<this->week_day<<", "<<this->day<<"-"<<this->month<<"-"<<this->year;
    return stream.str();
}