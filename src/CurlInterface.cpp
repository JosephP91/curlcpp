/* 
 * File:   CurlInterface.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 10:17 PM
 */

#include "CurlInterface.h"
#include "CurlError.h"

using curl::CurlInterface;

// curl interface constructor implementation
CurlInterface::CurlInterface() {
    const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
    if (code!=0) {
        throw new CurlError<CURLcode>(" ** Error while initializing the curl environment **",code);
    }
}

// curl interface overloaded constructor implementation
CurlInterface::CurlInterface(const long flag) {
    const CURLcode code = curl_global_init(flag);
    if (code!=0) {
        throw new CurlError<CURLcode>(" ** Error while initializing the curl environment with the flag specified **",code);
    }    
}

// curl interface destructor implementation
CurlInterface::~CurlInterface() {
    curl_global_cleanup();
}

// curl interface free method implementation
void CurlInterface::free(char *ptr) noexcept {
    if (ptr != nullptr) {
        curl_free(ptr);
    }
}

// curl interface version method implementation
const string CurlInterface::version() const noexcept {
    return string(curl_version());
}