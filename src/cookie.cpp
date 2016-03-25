/**
 * File:   cookie.cpp
 * Author: Giuseppe Persico
 */

#include "cookie.h"

using std::string;

// Implementation of constructor.
curl::cookie::cookie(const string name, const string path, const string domain, const bool secure) {
    this->set_name(name)->set_path(path)->set_domain(domain)->set_secure(secure);
}

// Implementation of overloaded constructor.
curl::cookie::cookie(const char *name, const char *path, const char *domain, const bool secure) {
    this->set_name(name)->set_path(path)->set_domain(domain)->set_secure(secure);
}

// Implementation of set_name method.
curl::cookie *curl::cookie::set_name(const string name) {
    if (name.empty()) {
        throw new curl_easy_exception("Cookie must have a name",__FUNCTION__);
    }
    this->name = name;
    return this;
}

// Implementation of set_name overloaded method.
curl::cookie *curl::cookie::set_name(const char *name) {
    if (name == nullptr) {
        throw new curl_easy_exception("Cookie must have a name",__FUNCTION__);
    }
    this->name = string(name);
    return this;
}

// Implementation of set_path method.
curl::cookie *curl::cookie::set_path(const string path) NOEXCEPT {
    this->path = path.empty() ? "/" : path;
    return this;
}

// Implementation of set_path overloaded method.
curl::cookie *curl::cookie::set_path(const char *path) NOEXCEPT {
    if (path == nullptr) {
        this->path = "/";
    } else {
        this->path = string(path);
    }
    return this;
}

// Implelementation of set_domain method.
curl::cookie *curl::cookie::set_domain(const string domain) NOEXCEPT {
    this->domain = domain;
    return this;
}

// Implementation of set_domain overloaded method.
curl::cookie *curl::cookie::set_domain(const char *domain) NOEXCEPT {
    if (domain == nullptr) {
        this->domain = "";
    } else {
        this->domain = string(domain);
    }
    return this;
}

// Implementation of set_secure method.
curl::cookie *curl::cookie::set_secure(const bool secure) NOEXCEPT {
    this->secure = secure;
    return this;
}

//
curl::cookie *curl::cookie::set_secure(const unsigned int secure) {
    if (secure == 0) {
        this->secure = false;
    } else if (secure == 1) {
        this->secure = true;
    } else {
        throw new curl_easy_exception("The security can be 0 (false) or 1 (true)",__FUNCTION__);
    }
    return this;
}

// Implementation of get_name method.
string curl::cookie::get_name() const NOEXCEPT {
    return this->name;
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

// Implementation of get_formatted method.
string curl::cookie::get_formatted() const NOEXCEPT {
    return "Set-cookie: name="+this->name+"; path="+this->path+"; domain="+this->domain;
}

/*
 *
 *time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (buffer,80,"%d-%b-%Y %X GMT",timeinfo);
 */