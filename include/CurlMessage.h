/* 
 * File:   CurlMessage.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 11:08 PM
 */

#ifndef CURLMESSAGE_H
#define	CURLMESSAGE_H

#include "CurlMulti.h"

using curl::CurlMulti;

namespace curl {
    class CurlMulti::CurlMessage {
    public:
        CurlMessage(CURLMSG message, CurlEasy curl, void *whatever, CURLcode result) : message(message), curl(curl), whatever(whatever), result(result) {};
        const CURLMSG getMessage() const noexcept;
        const CURLcode getResult() const noexcept;
        const CurlEasy getCurl() const noexcept;
        const void *getWhatever() const noexcept;
    private:
        CURLMSG message;
        CurlEasy curl;
        void *whatever;
        CURLcode result;
    };
}

#endif	/* CURLMESSAGE_H */