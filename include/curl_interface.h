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
#include "curl_info.h"

using std::string;
using curl::curl_error;
using curl::curl_info;

namespace curl {
    template<class T> class curl_interface {
    public:
        curl_interface();
        curl_interface(const long);
        virtual ~curl_interface();
        static time_t get_date(const char *, const time_t *);
    protected:
        virtual const string to_string(const T) const noexcept = 0;
    };
    
    // Implementation of constructor.
    template<class T> curl_interface<T>::curl_interface() {
        const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code != CURLE_OK) {
            throw curl_error(curl_easy_strerror(code),__FUNCTION__);
        }
    }
    
    // Implementation of overloaded constructor.
    template<class T> curl_interface<T>::curl_interface(const long flag) {
        const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code != CURLE_OK) {
            throw curl_error(curl_easy_strerror(code),__FUNCTION__);
        }
    }
    
    // Implementation of the virtual destructor.
    template<class T> curl_interface<T>::~curl_interface() {
        curl_global_cleanup();
    }
    
    // Implementation of get_date.
    template<class T> time_t curl_interface<T>::get_date(const char *datetime, const time_t *now) {
        time_t value = curl_getdate(datetime,now);
        if (value == -1) {
            throw curl_error("Error while parsing the date",__FUNCTION__);
        }
        return value;
    }
}

#endif	/* curl_interface_H */