/**
 * File:   cookie_time.cpp
 * Author: Giuseppe Persico
 */

#include "cookie_time.h"

using std::ostringstream;

// Implementation of constructor with parameters.
curl::cookie_time::cookie_time(const unsigned int hour, const unsigned int minutes, const unsigned int seconds) {
    this->set_hour(hour)->set_minutes(minutes)->set_seconds(seconds);
}

// Implementation of set_hour method.
curl::cookie_time *curl::cookie_time::set_hour(const unsigned int hour) NOEXCEPT {
    this->hour = hour > 23 ? 0 : hour;
    return this;
}

// Implementation of set_minutes method.
curl::cookie_time *curl::cookie_time::set_minutes(const unsigned int minutes) NOEXCEPT {
    this->minutes =  minutes > 59 ? 0 : minutes;
    return this;
}

// Implementation of set_seconds method.
curl::cookie_time *curl::cookie_time::set_seconds(const unsigned int seconds) NOEXCEPT {
    this->seconds = seconds > 59 ? 0 : seconds;
    return this;
}

// Implementation of get_hour method.
const unsigned int curl::cookie_time::get_hour() const NOEXCEPT {
    return this->hour;
}

// Implementation of get_minutes method.
const unsigned int curl::cookie_time::get_minutes() const NOEXCEPT {
    return this->minutes;
}

// Implementation of get_seconds method.
const unsigned int curl::cookie_time::get_seconds() const NOEXCEPT {
    return this->seconds;
}

// Implementation of get_formatted method.
std::string curl::cookie_time::get_formatted() NOEXCEPT {
    ostringstream stream;
    stream<<this->get_hour()<<":"<<this->get_minutes()<<":"<<this->get_seconds()<<" GMT";
    return stream.str();
}