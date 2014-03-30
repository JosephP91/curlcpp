/* 
 * File:   CurlMulti.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 11:02 PM
 */

#ifndef CURLMULTI_H
#define	CURLMULTI_H

#include "CurlEasy.h"

using curl::CurlEasy;

namespace curl {
    class CurlMulti : public CurlInterface<CURLMcode> {
    private:
        class CurlMessage;
        CURLM *curl;
        int message_queued;
        int active_transfers;
        vector<CurlEasy> handlers;
    protected:
        const string toString(const CURLMcode) const noexcept;
    public:
        CurlMulti();
        CurlMulti(const long);
        ~CurlMulti();
        template<typename T> CurlMulti &addOption(const CurlPair<CURLMoption,T> &);
        template<typename T> CurlMulti &addOption(const vector<CurlPair<CURLMoption,T>> &);
        CurlMulti &addHandle(const CurlEasy &) noexcept;
        CurlMulti &addHandle(const vector<CurlEasy> &) noexcept;
        CurlMulti &removeHandle(const CurlEasy &) noexcept;
        int perform();
        const int getActiveTransfers() const noexcept;
        const int getMessageQueued() const noexcept;
        const vector<CurlMulti::CurlMessage> getTransfersInfo();
    };
    
    // Implementation of addOption method
    template<typename T> CurlMulti &CurlMulti::addOption(const CurlPair<CURLMoption,T> &pair) {
        if (this->curl!=nullptr) {
            curl_multi_setopt(this->curl,pair.first(),pair.second());
        } else {
            throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
        }
        return *this;
    }
    
    // Implementation of addOption overloaded method
    template<typename T> CurlMulti &CurlMulti::addOption(const vector<CurlPair<CURLMoption,T>> &pairs) {
    	if (this->curl!=nullptr) {
            for_each(pairs.begin(),pairs.end(),[this](CurlPair<CURLMoption,T> option) { this->addOption(option); } );
        } else {
            throw new CurlError<int>(" ** NULL pointer intercepted ** ",0);
        }
    }
}

#endif	/* CURLMULTI_H */