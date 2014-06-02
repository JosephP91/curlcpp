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
    template<class CURLTYPE,class CODETYPE> class curl_interface {
    public:
        curl_interface(CURLTYPE *);
        curl_interface(CURLTYPE *, const long);
        virtual ~curl_interface();
        static const curl_version version_info(const CURLversion) noexcept;
        CURLTYPE *get_url() const;
    protected:
        virtual const string to_string(const CODETYPE) const noexcept = 0;
    private:
        void set_curl(CURLTYPE *);
        CURLTYPE *curl;
    };
    
    // Implementation of constructor.
    template<class CURLTYPE, class CODETYPE> curl_interface<CURLTYPE,CODETYPE>::curl_interface(CURLTYPE *curl) {
        CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code != CURLE_OK) {
            throw curl_error(curl_easy_strerror(code),__FUNCTION__);
        }
        this->set_curl(curl);
    }
    // Implementation of overloaded constructor.
    template<class CURLTYPE, class CODETYPE> curl_interface<CURLTYPE,CODETYPE>::curl_interface(CURLTYPE *curl, const long flag) {
        CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code != CURLE_OK) {
            throw curl_error(curl_easy_strerror(code),__FUNCTION__);
        }
        this->set_curl(curl);
    }
    // Implementation of the virtual destructor.
    template<class CURLTYPE, class CODETYPE> curl_interface<CURLTYPE,CODETYPE>::~curl_interface() {
        curl_global_cleanup();
    }
    // Returns an object containing information about a version of curl.
    template<class CURLTYPE, class CODETYPE> const curl_version curl_interface<CURLTYPE,CODETYPE>::version_info(const CURLversion version) noexcept {
        return curl_version(curl_version_info(version));
    }
    // Returns the curl pointer
    template<class CURLTYPE, class CODETYPE> CURLTYPE *curl_interface<CURLTYPE,CODETYPE>::get_url() const {
        return this->curl;
    }
    // Implementation of setter method used to validate curl pointer.
    template<class CURLTYPE, class CODETYPE> void curl_interface<CURLTYPE,CODETYPE>::set_curl(CURLTYPE *curl) {
        this->curl = curl;
        if (this->curl == nullptr) {
            throw curl_error(" *** null pointer intercepted ***",__FUNCTION__);
        }
    }
}

#endif	/* curl_interface_H */