/* 
 * File:   CurlInterface.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:17 PM
 */

#ifndef CURLINTERFACE_H
#define	CURLINTERFACE_H

#include <curl/curl.h>
#include <string>
#include "CurlError.h"
#include "CurlVersion.h"

using std::string;
using curl::CurlVersion;

namespace curl {
    template<class CODETYPE> class CurlInterface {
    public:
        CurlInterface();
        CurlInterface(const long);
        virtual ~CurlInterface();
        const string version() const noexcept;
        const CurlVersion versionInfo(const CURLversion) const noexcept;
    protected:
        virtual const string toString(const CODETYPE) const noexcept = 0;
        void free(char *) noexcept;
    };
    
    // Implementation of constructor
    template<class CODETYPE> CurlInterface<CODETYPE>::CurlInterface() {
        const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
        if (code!=0) {
            throw new CurlError<CURLcode>(" ** Error while initializing the curl environment **",code);
        }
    }
    
    // Implementation of overloaded constructor
    template<class CODETYPE> CurlInterface<CODETYPE>::CurlInterface(const long flag) {
        const CURLcode code = curl_global_init(flag);
        if (code!=0) {
            throw new CurlError<CURLcode>(" ** Error while initializing the curl environment with the flag specified **",code);
        }
    }
    
    // Implementation of destructor
    template<class CODETYPE> CurlInterface<CODETYPE>::~CurlInterface() {
        curl_global_cleanup();
    }
    
    // Implementation of free method
    template<class CODETYPE> void CurlInterface<CODETYPE>::free(char *ptr) noexcept {
        if (ptr != nullptr) {
            curl_free(ptr);
        }
    }
    
    // Implementation of version method
    template<class CODETYPE> const string CurlInterface<CODETYPE>::version() const noexcept {
        return string(curl_version());
    }
    
    // Implementation of versionInfo method
    template<class CODETYPE> const CurlVersion CurlInterface<CODETYPE>::versionInfo(const CURLversion version) const noexcept {
        return CurlVersion(curl_version_info(version));
    }
}

#endif	/* CURLINTERFACE_H */