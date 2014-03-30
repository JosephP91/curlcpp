//
//  CurlVersion.h
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__CurlVersion__
#define __curlcpp__CurlVersion__

#include <curl/curl.h>
#include <string>
#include <list>

using std::string;
using std::list;

namespace curl {
    class CurlVersion {
    public:
        CurlVersion(const curl_version_info_data *);
        const string getHost() const noexcept;
        const string getSSLVersion() const noexcept;
        const string getLibzVersion() const noexcept;
        const string getAres() const noexcept;
        const string getLibidn() const noexcept;
        const string getLibSSHVersion() const noexcept;
        const unsigned int getVersionNumber() const noexcept;
        const int getFeatures() const noexcept;
        const int getAresNumber() const noexcept;
        const int getIconvVersionNumber() const noexcept;
        const long getSSLVersionNumber() const noexcept;
        const list<string> getProtocols() const noexcept;
    private:
        const curl_version_info_data *version;
    };
}

#endif /* defined(__curlcpp__CurlVersion__) */