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
    /**
     * This is class is a common interface for all the libcurl interfaces:
     * easy, multi and share. It provides methods that these three interfaces
     * has in common with each other.
     */
    template<class T> class curl_interface {
    public:
        /**
         * The default constructor will initializes the curl
         * environment with the default flag.
         */
        curl_interface();
        /**
         * Overloaded constuctor that initializes curl environment
         * with user specified flag.
         */
        explicit curl_interface(const long);
        /**
         * The virtual destructor will provide an easy and clean
         * way to deallocate resources, closing curl environment
         * correctly.
         */
        virtual ~curl_interface();
    protected:
        virtual string to_string(const T) const noexcept = 0;
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
}

#endif	/* curl_interface_H */
