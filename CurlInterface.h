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

using std::string;

namespace curl {
    class CurlInterface {
    public:
        CurlInterface();
        CurlInterface(const long);
        virtual ~CurlInterface();
        virtual int perform() = 0;
        const string version() const noexcept;
    protected:
        void free(char *) noexcept;
    };
}

#endif	/* CURLINTERFACE_H */