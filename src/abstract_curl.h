//
//  abstract_curl.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 06/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curl_wrapper__abstract_curl__
#define __curl_wrapper__abstract_curl__

#include <curl/curl.h>
#include <string>

using std::string;

namespace curl {
    class abstract_curl {
    public:
        abstract_curl();
        abstract_curl(const long);
        virtual ~abstract_curl();
        virtual int perform()=0;
        const string version() const noexcept;
        string escape(const string) const;
        string unescape(const string) const;
        void free(char *) noexcept;
    };
}

#endif /* defined(__curl_wrapper__abstract_curl__) */