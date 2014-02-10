//
//  curl_interface.h
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_interface__
#define __curlcpp__curl_interface__

#include <curl/curl.h>
#include <string>

using std::string;

namespace curl {
    class curl_interface {
    public:
        curl_interface();
        curl_interface(const long);
        virtual ~curl_interface();
        virtual int perform()=0;
        inline const string version() const noexcept;
        inline string escape(const string) const;
        inline string unescape(const string) const;
    protected:
        void free(char *) noexcept;
    };
}
#endif /* defined(__curlcpp__curl_interface__) */
