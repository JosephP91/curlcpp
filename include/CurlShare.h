//
//  CurlShare.h
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__CurlShare__
#define __curlcpp__CurlShare__

#include "CurlEasy.h"

using curl::CurlEasy;

namespace curl {
    class CurlShare : public CurlInterface<CURLSH,CURLSHcode> {
    public:
        CurlShare() : CurlInterface(curl_share_init()) {}
        CurlShare(const long flag) : CurlInterface(curl_share_init(),flag) {}
        ~CurlShare();
        template<typename T> void add(const CurlPair<CURLSHoption,T> &);
        template<typename T> void add(const vector<CurlPair<CURLSHoption,T>> &);
        template<typename T> void add(const list<CurlPair<CURLSHoption,T>> &);
    protected:
        const string toString(const CURLSHcode) const noexcept;
    };
    
    // Implementation of addOption method
    template<typename T> void CurlShare::add(const CurlPair<CURLSHoption,T> &pair) {
        CURLSHcode code = curl_share_setopt(this->getCurl(),pair.first(),pair.second());
        if (code != CURLSHE_OK) {
            throw CurlError(this->toString(code));
        }
    }
    
    // Implementation of overloaded method addOption
    template<typename T> void CurlShare::add(const vector<CurlPair<CURLSHoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](const CurlPair<CURLSHoption,T> option) { this->add(option); } );
    }
    
    // Implementation of overloaded method addOption
    template<typename T> void CurlShare::add(const list<CurlPair<CURLSHoption,T> > &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](const CurlPair<CURLSHoption,T> option) { this->add(option); });
    }
}

#endif /* defined(__curlcpp__CurlShare__) */