//
//  curl_share.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 07/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curl_wrapper__curl_share__
#define __curl_wrapper__curl_share__

#include <vector>
#include "abstract_curl.h"

using std::vector;

namespace curl {
    class curl_share : public abstract_curl {
    public:
        template<class T> class option_pair {
        public:
            option_pair(const CURLSHoption option, const T value) : option(option), value(value) {};
            CURLSHoption first() const;
            T second() const;
        private:
            const CURLSHoption option;
            const T value;
        };
        curl_share();
        curl_share(const long);
        ~curl_share();
        template<typename T = CURLSHoption> curl_share &add_option(const curl_share::option_pair<T> &);
        template<typename T = CURLSHoption> curl_share &add_option(const vector<curl_share::option_pair<T>> &);
        int perform();
    protected:
        const string error_to_string(const CURLSHcode) const noexcept;
    private:
        CURLSH *curl;
    };
}

#endif /* defined(__curl_wrapper__curl_share__) */