/* 
 * File:   curl_interface.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:17 PM
 */

#ifndef curl_interface_H
#define	curl_interface_H

#include <curl/curl.h>
#include <string>
#include "curl_error.h"
#include "curl_version.h"

using std::string;
using curl::curl_error;
using curl::curl_version;

namespace curl {
    template<class T> class curl_interface {
    public:
        curl_interface();
        curl_interface(const long);
        virtual ~curl_interface();
        const curl_version version_info(const CURLversion) noexcept;
    protected:
        virtual const string to_string(const T) const noexcept = 0;
    };
    
    // Implementation of constructor.
    template<class T> curl_interface<T>::curl_interface() {
        CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code != CURLE_OK) {
            throw curl_error(curl_easy_strerror(code),__FUNCTION__);
        }
    }
    
    // Implementation of overloaded constructor.
    template<class T> curl_interface<T>::curl_interface(const long flag) {
        CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code != CURLE_OK) {
            throw curl_error(curl_easy_strerror(code),__FUNCTION__);
        }
    }
    
    // Implementation of the virtual destructor.
    template<class T> curl_interface<T>::~curl_interface() {
        curl_global_cleanup();
    }
}

#endif	/* curl_interface_H */