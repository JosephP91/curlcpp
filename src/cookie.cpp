/**
 * File:   cookie.cpp
 * Author: Giuseppe Persico
 */

#include "cookie.h"

using std::string;

// Implementation of constructor.
curl::cookie::cookie(const string& name, const string& value,
		const cookie_datetime &datetime, const string& path, const string& domain, const bool secure) {

    set_name(name)->set_value(value)->set_path(path)->set_domain(domain)->set_secure(secure)->set_datetime(datetime);
}

// Implementation of overloaded constructor.
curl::cookie::cookie(const char *name, const char * value, const cookie_datetime &datetime,
		const char *path, const char *domain, const bool secure) {

	set_name(name)->set_value(value)->set_path(path)->set_domain(domain)->set_secure(secure)->set_datetime(datetime);
}

// Implementation of set_name method.
curl::cookie *curl::cookie::set_name(const string& _name) {
    if (_name.empty()) {
        throw curl_easy_exception("Cookie must have a name",__FUNCTION__);
    }
    this->name = _name;
    return this;
}

// Implementation of set_name overloaded method.
curl::cookie *curl::cookie::set_name(const char *_name) {
    if (_name == nullptr) {
        throw curl_easy_exception("Cookie must have a name",__FUNCTION__);
    }
    this->name = string(_name);
    return this;
}

// Implementation of set_name method.
curl::cookie *curl::cookie::set_value(const string& _value) {
    this->value = _value;
    return this;
}

// Implementation of set_value method.
curl::cookie *curl::cookie::set_value(const char *_value) {
    if (_value == nullptr) {
        this->value = "";
    } else {
        this->value = string(_value);
    }
    return this;
}

// Implementation of set_path method.
curl::cookie *curl::cookie::set_path(const string& _path) NOEXCEPT {
    this->path = _path.empty() ? "/" : _path;
    return this;
}

// Implementation of set_path overloaded method.
curl::cookie *curl::cookie::set_path(const char *_path) NOEXCEPT {
    if (_path == nullptr) {
        this->path = "/";
    } else {
        this->path = string(path);
    }
    return this;
}

// Implelementation of set_domain method.
curl::cookie *curl::cookie::set_domain(const string& _domain) NOEXCEPT {
    this->domain = _domain;
    return this;
}

// Implementation of set_domain overloaded method.
curl::cookie *curl::cookie::set_domain(const char *_domain) NOEXCEPT {
    if (_domain == nullptr) {
        this->domain = "";
    } else {
        this->domain = string(domain);
    }
    return this;
}

// Implementation of set_secure method.
curl::cookie *curl::cookie::set_secure(const bool _secure) NOEXCEPT {
    this->secure = _secure;
    return this;
}

// Implementation of set_secure overloaded method.
curl::cookie *curl::cookie::set_secure(const string& _secure) NOEXCEPT {
	set_secure(_secure == "secure");
    return this;
}

// Implementation of set_secure overloaded method.
curl::cookie *curl::cookie::set_secure(const char *_secure) NOEXCEPT {
	if (_secure == nullptr) {
		set_secure(false);
	} else {
		set_secure(string(_secure));
	}
	return this;
}

// Implementation of set_secure method.
curl::cookie *curl::cookie::set_secure(const unsigned int _secure) {
    if (_secure == 0) {
    	set_secure(false);
    } else if (_secure == 1) {
    	set_secure(true);
    } else {
        throw curl_easy_exception("The security can be 0 (false) or 1 (true)",__FUNCTION__);
    }
    return this;
}

// Implementation of set_datetime method.
curl::cookie *curl::cookie::set_datetime(const cookie_datetime & _datetime) NOEXCEPT {
    this->datetime = _datetime;
    return this;
}

// Implementation of get_name method.
string curl::cookie::get_name() const NOEXCEPT {
    return this->name;
}

// Implmentation of get_value method.
string curl::cookie::get_value() const NOEXCEPT {
    return this->value;
}

// Implementation of get_path method.
string curl::cookie::get_path() const NOEXCEPT {
    return this->path;
}

// Implementation of get_domain method.
string curl::cookie::get_domain() const NOEXCEPT {
    return this->domain;
}

// Implementation of is_secure method.
bool curl::cookie::is_secure() const NOEXCEPT {
    return this->secure;
}

// Implementation of get_datetime method.
curl::cookie_datetime curl::cookie::get_datetime() const NOEXCEPT {
    return this->datetime;
}

// Implementation of get_formatted method.
string curl::cookie::get_formatted() NOEXCEPT {
    string _secure = this->is_secure() == 1 ? "secure" : "";

    return "Set-Cookie: "+this->name+"="+this->value+"; expires="+this->datetime.get_formatted()
    	+"; path="+this->path+"; domain="+this->domain+" "+_secure;
}
