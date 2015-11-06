/**
 * File:   curl_easy.cpp
 * Author: Giuseppe Persico
 */

#include "curl_easy.h"

using curl::curl_easy;

// Implementation of default constructor.
curl_easy::curl_easy() : curl_interface() {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
    }
}

// Implementation of overridden constructor.
curl_easy::curl_easy(const long flag) : curl_interface(flag) {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
    }
}

// Implementation of copy constructor to respect the rule of three.
curl_easy::curl_easy(const curl_easy &easy) : curl_interface(), curl(nullptr) {
    *this = easy;
    // Let's use a duplication handle function provided by libcurl.
    this->curl = curl_easy_duphandle(easy.curl);
}

// Implementation of assignment operator to perform a deep copy.
curl_easy &curl_easy::operator=(const curl_easy &easy) {
    if (this == &easy) {
        return *this;
    }
    curl_easy_cleanup(this->curl);
    // We use the duplication handle function also here.
    this->curl = curl_easy_duphandle(easy.curl);
    return *this;
}

// Implementation of equality operator overload.
bool curl_easy::operator==(const curl_easy &easy) const {
    return this->curl == easy.curl;
}

// Implementation of destructor.
curl_easy::~curl_easy() NOEXCEPT {
    if (this->curl != nullptr) {
        curl_easy_cleanup(this->curl);
        this->curl = nullptr;
    }
}

// Implementation of abstract method perform.
void curl_easy::perform() {
    const CURLcode code = curl_easy_perform(this->curl);
    if (code != CURLE_OK) {
        throw curl_easy_exception(code,__FUNCTION__);
    }
}

// Implementation of escape method.
void curl_easy::escape(string &url) {
    char *url_encoded = curl_easy_escape(this->curl,url.c_str(),(int)url.length());
    if (url_encoded == nullptr) {
        throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
    }
    url = string(url_encoded);
    curl_free(url_encoded);
}

// Implementation of unescape method.
void curl_easy::unescape(string &url) {
    char *url_decoded = curl_easy_unescape(this->curl,url.c_str(),(int)url.length(),nullptr);
    if (url_decoded == nullptr) {
        throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
    }
    url = string(url_decoded);
    curl_free(url_decoded);
}

// Implementation of reset method.
void curl_easy::reset() NOEXCEPT {
    curl_easy_reset(this->curl);
}

// Implementation of pause method.
void curl_easy::pause(const int bitmask) {
    const CURLcode code = curl_easy_pause(this->curl,bitmask);
    if (code != CURLE_OK) {
        throw curl_easy_exception(code,__FUNCTION__);
    }
}
