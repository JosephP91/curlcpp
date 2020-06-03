/**
 * File:   curl_cookie.cpp
 * Author: Giuseppe Persico
 */

#include <vector>

#include "curl_cookie.h"

using std::vector;
using std::string;
using std::ostringstream;

namespace curl {
    // Implementation of the get method.
    curlcpp_cookies curl_cookie::get() const NOEXCEPT {
        auto info = this->easy.get_info<CURLINFO_COOKIELIST>();
        return info.get();
    }
    
    // Implementation of set_cookie_file method.
    void curl_cookie::set_file(const string& file = "") {
        this->easy.add<CURLOPT_COOKIEFILE>(file.c_str());
    }
    
    // Implementation of set_cookie_list method.
    void curl_cookie::set(curl::cookie &cookie) {
        this->easy.add<CURLOPT_COOKIELIST>(cookie.get_formatted().c_str());
    }
    
    // Implementation of overloaded set_cookie_list method.
    void curl_cookie::set(const vector<curl::cookie> &cookies) {
        for (auto c : cookies) {
            this->set(c);
        }
    }
    
    // Implementation of erase method.
    void curl_cookie::erase() {
        this->easy.add<CURLOPT_COOKIELIST>("ALL");
    }
    
    // Implementation of flush method.
    void curl_cookie::flush() {
        this->easy.add<CURLOPT_COOKIELIST>("FLUSH");
    }
    
    // Implementation of erase_session method.
    void curl_cookie::erase_session() {
        this->easy.add<CURLOPT_COOKIELIST>("SESS");
    }
    
    // Implementation of reload method.
    void curl_cookie::reload() {
        this->easy.add<CURLOPT_COOKIELIST>("RELOAD");
    }
}
