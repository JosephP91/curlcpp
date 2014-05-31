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
using curl::CurlError;
using curl::CurlVersion;

namespace curl {
    template<class CURLTYPE,class CODETYPE> class CurlInterface {
    public:
        CurlInterface(CURLTYPE *);
        CurlInterface(CURLTYPE *, const long);
        virtual ~CurlInterface();
        static const string version() noexcept;
        static const CurlVersion versionInfo(const CURLversion) noexcept;
        CURLTYPE *getCurl() const;
    protected:
        virtual const string toString(const CODETYPE) const noexcept = 0;
    private:
        void setCurl(CURLTYPE *);
        CURLTYPE *curl;
    };
    
    // Implementation of constructor.
    template<class CURLTYPE, class CODETYPE> CurlInterface<CURLTYPE,CODETYPE>::CurlInterface(CURLTYPE *curl) {
        if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
            throw CurlError(" *** Error while initializing the curl environment ***");
        }
        this->setCurl(curl);
    }
    // Implementation of overloaded constructor
    template<class CURLTYPE, class CODETYPE> CurlInterface<CURLTYPE,CODETYPE>::CurlInterface(CURLTYPE *curl, const long flag) {
        if (curl_global_init(flag) != 0) {
            throw CurlError(" *** Error while initializing the curl environment with the flag specified ***");
        }
        this->setCurl(curl);
    }
    // Implementation of the virtual destructor
    template<class CURLTYPE, class CODETYPE> CurlInterface<CURLTYPE,CODETYPE>::~CurlInterface() {
        curl_global_cleanup();
    }
    // Returns the version of curl
    template<class CURLTYPE, class CODETYPE> const string CurlInterface<CURLTYPE,CODETYPE>::version() noexcept {
        return string(curl_version());
    }
    // Returns an object containing information about a version of curl
    template<class CURLTYPE, class CODETYPE> const CurlVersion CurlInterface<CURLTYPE,CODETYPE>::versionInfo(const CURLversion version) noexcept {
        return CurlVersion(curl_version_info(version));
    }
    // Returns the curl pointer
    template<class CURLTYPE, class CODETYPE> CURLTYPE *CurlInterface<CURLTYPE,CODETYPE>::getCurl() const {
        return this->curl;
    }
    // Implementation of setter method used to validate curl pointer.
    template<class CURLTYPE, class CODETYPE> void CurlInterface<CURLTYPE,CODETYPE>::setCurl(CURLTYPE *curl) {
        this->curl = curl;
        if (this->curl == nullptr) {
            throw CurlError(" *** null pointer intercepted ***");
        }
    }
}

#endif	/* CURLINTERFACE_H */