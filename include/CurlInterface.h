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
    template<class CURLTYPE,class CODETYPE> class CurlInterface {
    public:
        // Implementation of constructor.
        CurlInterface(CURLTYPE *curl) {
            if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
                throw CurlError(" *** Error while initializing the curl environment ***");
            }
            this->setCurl(curl);
        }
        // Implementation of overloaded constructor
        CurlInterface(CURLTYPE *curl , const long flag) {
            if (curl_global_init(flag) != 0) {
                throw CurlError(" *** Error while initializing the curl environment with the flag specified ***");
            }
            this->setCurl(curl);
        }
        // Implementation of the virtual destructor
        virtual ~CurlInterface() {
            curl_global_cleanup();
        }
        // Returns the version of curl
        static const string version() noexcept {
            return string(curl_version());
        }
        // Returns an object containing information about a version of curl
        static const CurlVersion versionInfo(const CURLversion version) noexcept {
            return CurlVersion(curl_version_info(version));
        }
        // Returns the curl pointer
        CURLTYPE *getCurl() const {
            return this->curl;
        }
    protected:
        virtual const string toString(const CODETYPE) const noexcept = 0;
    private:
        // Implementation of setter method used to validate curl pointer.
        void setCurl(CURLTYPE *curl) {
            this->curl = curl;
            if (this->curl == nullptr) {
                throw CurlError(" *** null pointer intercepted ***");
            }
        }
        CURLTYPE *curl;
    };
}

#endif	/* CURLINTERFACE_H */