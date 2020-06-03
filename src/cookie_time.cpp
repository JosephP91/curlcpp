/**
 * File:   cookie_time.cpp
 * Author: Giuseppe Persico
 */

#include "cookie_time.h"

using std::ostringstream;

// Implementation of constructor with parameters.
curl::cookie_time::cookie_time(const unsigned int hour, const unsigned int minutes,
		const unsigned int seconds) {

    this->set_hour(hour)->set_minutes(minutes)->set_seconds(seconds);
}

// Implementation of set_hour method.
curl::cookie_time *curl::cookie_time::set_hour(unsigned int _hour) NOEXCEPT {
    this->hour = _hour > 23 ? 0 : _hour;
    return this;
}

// Implementation of set_minutes method.
curl::cookie_time *curl::cookie_time::set_minutes(unsigned int _minutes) NOEXCEPT {
    this->minutes =  _minutes > 59 ? 0 : _minutes;
    return this;
}

// Implementation of set_seconds method.
curl::cookie_time *curl::cookie_time::set_seconds(unsigned int _seconds) NOEXCEPT {
    this->seconds = _seconds > 59 ? 0 : _seconds;
    return this;
}

// Implementation of get_hour method.
unsigned int curl::cookie_time::get_hour() const NOEXCEPT {
    return this->hour;
}

// Implementation of get_minutes method.
unsigned int curl::cookie_time::get_minutes() const NOEXCEPT {
    return this->minutes;
}

// Implementation of get_seconds method.
unsigned int curl::cookie_time::get_seconds() const NOEXCEPT {
    return this->seconds;
}

// Implementation of get_formatted method.
std::string curl::cookie_time::get_formatted() const NOEXCEPT {
    ostringstream stream;
    stream<<this->get_hour()<<":"<<this->get_minutes()<<":"<<this->get_seconds()<<" GMT";
    return stream.str();
}