/* 
 * File:   curl_easy.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:54 PM
 */

#include "curl_easy.h"

using curl::curl_easy;

// Default memory write callback.
namespace {
    size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        const size_t realsize = size * nmemb;
        ostream* const mem = static_cast<ostream*>(userp);
        mem->write(static_cast<const char*>(contents), realsize);
        return realsize;
    }
}

// Implementation of default constructor.
curl_easy::curl_easy() : curl_interface() {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_error("*** Error during curl easy pointer initialization ***",__FUNCTION__);
    }
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void *)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void *>(CURLOPT_WRITEDATA, static_cast<void*>(&cout)));
}

// Implementation of default constructor.
curl_easy::curl_easy(ostream &outstream) : curl_interface() {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_error("*** Error during curl easy pointer initialization ***",__FUNCTION__);
    }
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void*)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void*>(CURLOPT_WRITEDATA, static_cast<void*>(&outstream)));
}

// Implementation of overridden constructor.
curl_easy::curl_easy(const long flag) : curl_interface(flag) {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_error("*** Error during curl easy pointer initialization ***",__FUNCTION__);
    }
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void *)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void *>(CURLOPT_WRITEDATA, static_cast<void*>(&cout)));
}

// Implementation of overridden constructor.
curl_easy::curl_easy(const long flag, ostream &outstream) : curl_interface(flag) {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_error("*** Error during curl easy pointer initialization ***",__FUNCTION__);
    }
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void*)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void*>(CURLOPT_WRITEDATA, static_cast<void*>(&outstream)));
}

// Implementation of copy constructor to respect the rule of three.
curl_easy::curl_easy(const curl_easy &easy) {
    // add ostream as attribute!!
    this->curl = curl_easy_init();
}

// Impementation of assignment operator to perform a deep copy.
curl_easy &curl_easy::operator=(const curl_easy &easy) {
    // add ostream as attribute!!
    if (this == &easy) {
        return *this;
    }
    this->curl = curl_easy_init();
    return *this;
}

// Implementation of destructor.
curl_easy::~curl_easy() noexcept {
    if (this->curl != nullptr) {
        curl_easy_cleanup(this->curl);
        this->curl = nullptr;
    }
}

// Implementation of get method. It simply returns the curl pointer.
CURL *curl_easy::get_curl() const {
    return this->curl;
}
  
// Implementation of error to_string method.
const string curl_easy::to_string(const CURLcode code) const noexcept {
    return curl_easy_strerror(code);
}

// Implementation of abstract method perform.
void curl_easy::perform() {
    const CURLcode code = curl_easy_perform(this->curl);
    if (code != CURLE_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of escape method.
void curl_easy::escape(string &url) {
    char *url_encoded = curl_easy_escape(this->curl,url.c_str(),(int)url.length());
    if (url_encoded == nullptr) {
        throw curl_error("*** null pointer intercepted  ***",__FUNCTION__);
    }
    url = string(url_encoded);
    curl_free(url_encoded);
    url_encoded = nullptr;
}

// Implementation of unescape method.
void curl_easy::unescape(string &url) {
    char *url_decoded = curl_easy_unescape(this->curl,url.c_str(),(int)url.length(),nullptr);
    if (url_decoded == nullptr) {
        throw curl_error("*** null pointer intercepted ***",__FUNCTION__);
    }
    url = string(url_decoded);
    curl_free(url_decoded);
    url_decoded = nullptr;
}

// Implementation of reset method
void curl_easy::reset() noexcept {
    curl_easy_reset(this->curl);
}