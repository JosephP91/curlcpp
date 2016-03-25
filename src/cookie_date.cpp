/**
 * File:   cookie_date.cpp
 * Author: Giuseppe Persico
 */

#include "cookie_date.h"

// Implementation of constructor with parameters.
curl::cookie_date::cookie_date(const unsigned int day, const unsigned int month, const unsigned int year) NOEXCEPT {
    this->set_day(day)->set_month(month)->set_year(year);
}

// Implementation of set_day method.
curl::cookie_date *curl::cookie_date::set_day(const unsigned int day) NOEXCEPT {
    this->day = (day < 1 or day > 31) ? 1 : day;
    return this;
}

// Implementation of set_month method.
curl::cookie_date *curl::cookie_date::set_month(const unsigned int month) {
    try {
        this->month = details::months_names.at(month);
    } catch (const std::out_of_range &exception) {
        this->month = "Jan";
    }
    return this;
}

// Implementation of set_year method.
curl::cookie_date *curl::cookie_date::set_year(const unsigned int year) NOEXCEPT {
    this->year = (year < 1970 ) ? 1970 : year;
    return this;
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
    std::ostringstream stream;
    stream<<this->get_day()<<"-"<<this->get_month()<<"-"<<this->get_year();
    return stream.str();
}