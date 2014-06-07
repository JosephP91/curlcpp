/* 
 * File:   curl_easy.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:54 PM
 */

#include "curl_easy.h"

using curl::curl_easy;

// Default memory write callback.
namespace curl {
    size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        const size_t realsize = size * nmemb;
        ostream* const mem = static_cast<ostream*>(userp);
        mem->write(static_cast<const char*>(contents), realsize);
        return realsize;
    }
}

// Implementation of default constructor.
curl_easy::curl_easy() : curl_interface(curl_easy_init()) {
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void *)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void *>(CURLOPT_WRITEDATA, static_cast<void*>(&cout)));
}

// Implementation of default constructor.
curl_easy::curl_easy(ostream &outstream) : curl_interface(curl_easy_init()) {
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void*)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void*>(CURLOPT_WRITEDATA, static_cast<void*>(&outstream)));
}

// Implementation of overridden constructor.
curl_easy::curl_easy(const long flag) : curl_interface(curl_easy_init(),flag) {
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void *)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void *>(CURLOPT_WRITEDATA, static_cast<void*>(&cout)));
}

// Implementation of overridden constructor.
curl_easy::curl_easy(const long flag, ostream &outstream) : curl_interface(curl_easy_init(),flag) {
    this->add(curl_pair<CURLoption, size_t(*)(void*,size_t,size_t,void*)>(CURLOPT_WRITEFUNCTION, &write_memory_callback));
    this->add(curl_pair<CURLoption, void*>(CURLOPT_WRITEDATA, static_cast<void*>(&outstream)));
}
    
// Implementation of destructor.
curl_easy::~curl_easy() noexcept {
    curl_easy_cleanup(this->get_url());
}
  
// Implementation of errorto_string method.
const string curl_easy::to_string(const CURLcode code) const noexcept {
    return curl_easy_strerror(code);
}

// Implementation of abstract method perform.
void curl_easy::perform() {
    const CURLcode code = curl_easy_perform(this->get_url());
    if (code != CURLE_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of escape method.
void curl_easy::escape(string &url) {
    char *url_encoded = curl_easy_escape(this->get_url(),url.c_str(),(int)url.length());
    if (url_encoded == nullptr) {
        throw curl_error("*** null pointer intercepted  ***",__FUNCTION__);
    }
    url = string(url_encoded);
    curl_free(url_encoded);
    url_encoded = nullptr;
}

// Implementation of unescape method.
void curl_easy::unescape(string &url) {
    char *url_decoded = curl_easy_unescape(this->get_url(),url.c_str(),(int)url.length(),nullptr);
    if (url_decoded == nullptr) {
        throw curl_error("*** null pointer intercepted ***",__FUNCTION__);
    }
    url = string(url_decoded);
    curl_free(url_decoded);
    url_decoded = nullptr;
}

// Implementation of reset method
void curl_easy::reset() noexcept {
    curl_easy_reset(this->get_url());
}