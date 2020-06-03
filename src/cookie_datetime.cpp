/**
 * File:   cookie_datetime.cpp
 * Author: Giuseppe Persico
 */

#include "cookie_datetime.h"

// Implementation of constructor with parameters.
curl::cookie_datetime::cookie_datetime(const cookie_time &time, const cookie_date &date) NOEXCEPT {
    this->set_time(time)->set_date(date);
}

// Implementation of set_time method.
curl::cookie_datetime *curl::cookie_datetime::set_time(const cookie_time &cookieTime) NOEXCEPT {
    this->time = cookieTime;
    return this;
}

// Implementation of set_date method.
curl::cookie_datetime *curl::cookie_datetime::set_date(const cookie_date &cookieDate) NOEXCEPT {
    this->date = cookieDate;
    return this;
}

// Implementation of get_time method.
curl::cookie_time curl::cookie_datetime::get_time() const NOEXCEPT {
    return this->time;
}

// Implementation of get_date method.
curl::cookie_date curl::cookie_datetime::get_date() const NOEXCEPT {
    return this->date;
}

// Implementation of get method.
std::string curl::cookie_datetime::get_formatted() NOEXCEPT {
    return this->date.get_formatted()+" "+this->time.get_formatted();
}