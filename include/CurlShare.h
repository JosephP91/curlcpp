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
    class CurlShare : public CurlInterface<CURLSHcode> {
    public:
        CurlShare();
        CurlShare(const long);
        ~CurlShare();
        template<typename T> CurlShare &addOption(const CurlPair<CURLSHoption,T> &);
        template<typename T> CurlShare &addOption(const vector<CurlPair<CURLSHoption,T>> &);
        template<typename T> CurlShare &addOption(const list<CurlPair<CURLSHoption,T>> &);
    protected:
        const string toString(const CURLSHcode) const noexcept;
    private:
        CURLSH *curl;
    };
}

#endif /* defined(__curlcpp__CurlShare__) */