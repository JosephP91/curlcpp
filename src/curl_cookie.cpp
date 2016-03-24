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
    const curlcpp_cookies curl_cookie::get() const NOEXCEPT {
        auto info = this->easy.get_info<struct curl_slist>(CURLINFO_COOKIELIST);
        return info.get().second;
    }
    
    // Implementation of set_cookie_file method.
    void curl_cookie::set_cookie_file(const string file = "") NOEXCEPT {
        this->easy.add<CURLOPT_COOKIEFILE>(file.c_str());
    }
    
    // Implementation of set_cookie_list method.
    void curl_cookie::set_cookie_list(const string list) NOEXCEPT {
        this->easy.add<CURLOPT_COOKIELIST>(list.c_str());
    }

    // Implementation of overloaded set_cookie_list method.
    void curl_cookie::set_cookie_list(const char *list) NOEXCEPT {
        this->easy.add<CURLOPT_COOKIELIST>(list);
    }
    
    // Implementation of overloaded set_cookie_list method.
    void curl_cookie::set_cookie_list(const vector<string> &list) NOEXCEPT {
        string cookies;
        for (auto cookie : list) {
            cookies+=cookie;
        }
        this->set_cookie_list(cookies);
    }
    
    // Implementation of overloaded set_cookie_list method.
    void curl_cookie::set_cookie_list(const ostringstream list) NOEXCEPT {
        this->set_cookie_list(list.str());
    }
    
    // Implementation of erase method.
    void curl_cookie::erase() NOEXCEPT {
        this->set_cookie_list("ALL");
    }
    
    // Implementation of flush method.
    void curl_cookie::flush() NOEXCEPT {
        this->set_cookie_list("FLUSH");
    }
    
    // Implementation of erase_session method.
    void curl_cookie::erase_session() NOEXCEPT {
        this->set_cookie_list("SESS");
    }
    
    // Implementation of reload method.
    void curl_cookie::reload() NOEXCEPT {
        this->set_cookie_list("RELOAD");
    }
}
