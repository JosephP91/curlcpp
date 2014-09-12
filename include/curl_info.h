/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_info.h
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __curlcpp__curl_version__
#define __curlcpp__curl_version__

#include <curl/curl.h>
#include <string>
#include <list>

using std::string;
using std::list;

namespace curl {
    /**
     * This class represents a structure that provides information about various
     * features in the running version of libcurl.
     */
    class curl_info {
    public:
        /**
         * The default constructor uses the current version of libcurl
         * as referral.
         */
        curl_info();
        /**
         * Overloaded constructor that allows users to specify the 
         * libcurl version.
         */
        explicit curl_info(const CURLversion);
        /**
         * Returns a string that shows what host information that this
         * libcurl was built for.
         */
        const string get_host() const noexcept;
        /**
         * Returns a string for the OpenSSL version used. If libcurl has no
         * SSL support, the method returns null.
         */
        const string get_ssl_version() const noexcept;
        /**
         * Returns a string for libz compression library version. If libcurl
         * has no libz support, the method returns null.
         */
        const string get_libz_version() const noexcept;
        /**
         * No description supplied for this method.
         */
        const string get_ares() const noexcept;
        /**
         * No description supplied for this method.
         */
        const string get_libidn() const noexcept;
        /**
         * Returns a string for libssh library version. If libcurl
         * has no libssh support, the method returns null.
         */
        const string get_libssh_version() const noexcept;
        /**
         * Returns the version number.
         */
        const unsigned int get_version_number() const noexcept;
        /**
         * Check online documentation for the possible return values.
         */
        const int get_features() const noexcept;
        /**
         * No description supplied for this method.
         */
        const int get_ares_number() const noexcept;
        /**
         * No description supplied for this method.
         */
        const int get_iconv_version_number() const noexcept;
        /**
         * Returns the libssl version number.
         */
        const long get_ssl_version_number() const noexcept;
        /**
         * Returns a list of all the protocols supported in the
         * running version of libcurl library.
         */
        const list<string> get_protocols() const noexcept;
    private:
        const curl_version_info_data *version;
    };

    // Implementation of get_host method.
    inline const string curl_info::get_host() const noexcept {
        return string(this->version->host);
    }

    // Implementation of get_ssl_version.
    inline const string curl_info::get_ssl_version() const noexcept {
        return string(this->version->ssl_version);
    }

    // Implementation of get_libz_version.
    inline const string curl_info::get_libz_version() const noexcept {
        return string(this->version->libz_version);
    }

    // Implementation of get_ares method.
    inline const string curl_info::get_ares() const noexcept {
        return string(this->version->ares);
    }

    // Implementation of get_libidin method.
    inline const string curl_info::get_libidn() const noexcept {
        return string(this->version->libidn);
    }

    // Implementation of get_libssh_version method.
    inline const string curl_info::get_libssh_version() const noexcept {
        return string(this->version->libssh_version);
    }

    // Implementation of get_version_number method.
    inline const unsigned int curl_info::get_version_number() const noexcept {
        return this->version->version_num;
    }

    // Implementation of get_features method.
    inline const int curl_info::get_features() const noexcept {
        return this->version->features;
    }

    // Implementation of get_ares_number method.
    inline const int curl_info::get_ares_number() const noexcept {
        return this->version->ares_num;
    }

    // Implementation of get_iconv_version_number method.
    inline const int curl_info::get_iconv_version_number() const noexcept {
        return this->version->iconv_ver_num;
    }

    // Implementation of get_ssl_version_number method.
    inline const long curl_info::get_ssl_version_number() const noexcept {
        return this->version->ssl_version_num;
    }
}

#endif /* defined(__curlcpp__curl_version__) */
