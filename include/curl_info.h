//
//  curl_version.h
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//

#ifndef __curlcpp__curl_version__
#define __curlcpp__curl_version__

#include <curl/curl.h>
#include <string>
#include <list>

using std::string;
using std::list;

// Curl version wrapper. You can use this class to obtain information about curl library
namespace curl {
    class curl_info {
    public:
        curl_info();
        explicit curl_info(const CURLversion);
        const string get_host() const noexcept;
        const string get_ssl_version() const noexcept;
        const string get_libz_version() const noexcept;
        const string get_ares() const noexcept;
        const string get_libidn() const noexcept;
        const string get_libssh_version() const noexcept;
        const unsigned int get_version_number() const noexcept;
        const int get_features() const noexcept;
        const int get_ares_number() const noexcept;
        const int get_iconv_version_number() const noexcept;
        const long get_ssl_version_number() const noexcept;
        const list<string> get_protocols() const noexcept;
    private:
        const curl_version_info_data *version;
    };
}

#endif /* defined(__curlcpp__curl_version__) */