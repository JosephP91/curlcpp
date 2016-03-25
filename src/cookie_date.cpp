/**
 * File:   curl_date.cpp
 * Author: Giuseppe Persico
 */

#include "cookie_date.h"

curl::cookie_date::cookie_date(const unsigned int day, const unsigned int month, const unsigned int year) {
    this->set_day(day)->set_month(month)->set_year(year);
}

curl::cookie_date *curl::cookie_date::set_day(const unsigned int day) {
    this->day = (day < 1 or day > 31) ? 1 : day;
    return this;
}

curl::cookie_date *curl::cookie_date::set_month(const unsigned int month) {
    try {
        this->month = details::months_names.at(month);
    } catch (const std::out_of_range &exception) {
        this->month = "Jan";
    }
    return this;
}

curl::cookie_date *curl::cookie_date::set_year(const unsigned int year) {
    this->year = (year < 1970 ) ? 1970 : year;
    return this;
}

unsigned int curl::cookie_date::get_day() const {
    return this->day;
}

std::string curl::cookie_date::get_month() const {
    return this->month;
}

unsigned int curl::cookie_date::get_year() const {
    return this->year;
}