/**
 * File:   curl_easy.cpp
 * Author: Giuseppe Persico
 */

#include "curl_easy.h"

using curl::curl_easy;
using std::ostream;
using std::string;

// Implementation of default constructor.
curl_easy::curl_easy() : curl_interface() {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
    }
    curl_ios<ostream> writer;
    this->add<CURLOPT_WRITEFUNCTION>(writer.get_function());
    this->add<CURLOPT_WRITEDATA>(static_cast<void*>(writer.get_stream()));
    this->add<CURLOPT_HEADERFUNCTION>(writer.get_function());
    this->add<CURLOPT_HEADERDATA>(static_cast<void *>(writer.get_stream()));
}

// Implementation of overridden constructor.
curl_easy::curl_easy(const long flag) : curl_interface(flag) {
    this->curl = curl_easy_init();
    if (this->curl == nullptr) {
        throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
    }
    curl_ios<ostream> writer;
    this->add<CURLOPT_WRITEFUNCTION>(writer.get_function());
    this->add<CURLOPT_WRITEDATA>(static_cast<void*>(writer.get_stream()));
}

// Implementation of copy constructor to respect the rule of three.
curl_easy::curl_easy(const curl_easy &easy) : curl_interface(), curl(nullptr) {
    *this = easy;
    // Let's use a duplication handle function provided by libcurl.
    this->curl = curl_easy_duphandle(easy.curl);
}

// Implementation of move constructor
curl_easy::curl_easy(curl_easy &&other) NOEXCEPT : curl_interface(), curl(nullptr) {
    this->curl = other.curl;
    // Other's pointer is set to nullptr so that destructor doesn't call the
    // cleanup function.
    other.curl = nullptr;
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
    std::unique_ptr<char, void(*)(char*)> url_encoded(curl_easy_escape(this->curl, url.c_str(), (int)url.length()),
    		[](char *ptr) { curl_free(ptr); });

    if (!url_encoded) {
        throw curl_easy_exception("Null pointer intercepted", __FUNCTION__);
    }
    url = string(url_encoded.get());
}

// Implementation of unescape method.
void curl_easy::unescape(string &url) {
    std::unique_ptr<char,void(*)(char*)> url_decoded(curl_easy_unescape(this->curl,url.c_str(),(int)url.length(),
    		nullptr),[](char *ptr) { curl_free(ptr); });

    if (url_decoded == nullptr) {
        throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
    }
    url = string(url_decoded.get());
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