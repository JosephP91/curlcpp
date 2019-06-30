/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_share.h
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

#ifndef __curlcpp__curl_share__
#define __curlcpp__curl_share__

#include "curl_interface.h"
#include "curl_pair.h"

#define CURLCPP_DEFINE_OPTION(opt, value_type)\
    template <> struct shoption_t<opt> {\
        using type = value_type;\
    }

namespace curl {
    namespace detail {
        template <CURLSHoption>
        struct shoption_t;

        template <CURLSHoption opt>
        using SHOption_type = typename shoption_t<opt>::type;

        /*
         * The parameter must be a pointer to a function matching the following prototype:
         * void lock_function(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr);
         * data defines what data libcurl wants to lock, and you must make sure that only one lock is given
         * at any time for each kind of data. access defines what access type libcurl wants, shared or single.
         * userptr is the pointer you set with CURLSHOPT_USERDATA.
         */
        CURLCPP_DEFINE_OPTION(CURLSHOPT_LOCKFUNC,
                              void(*)(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr));
        /*
         * The parameter must be a pointer to a function matching the following prototype:
         * void unlock_function(CURL *handle, curl_lock_data data, void *userptr);
         * data defines what data libcurl wants to unlock, and you must make sure that only one lock is given
         * at any time for each kind of data.
         * userptr is the pointer you set with CURLSHOPT_USERDATA.
         */
        CURLCPP_DEFINE_OPTION(CURLSHOPT_UNLOCKFUNC, void(*)(CURL *handle, curl_lock_data data, void *userptr));

        /*
         * The parameter specifies a type of data that should be shared. This may be set to one of the values described below.
         * CURL_LOCK_DATA_COOKIE: Cookie data will be shared across the easy handles using this shared object.
         * CURL_LOCK_DATA_DNS: Cached DNS hosts will be shared across the easy handles using this shared object.
         * Note that when you use the multi interface, all easy handles added to the same multi handle will share
         * DNS cache by default without this having to be used!
         * CURL_LOCK_DATA_SSL_SESSION: SSL session IDs will be shared across the easy handles using this shared
         * object. This will reduce the time spent in the SSL handshake when reconnecting to the same server.
         * Note SSL session IDs are reused within the same easy handle by default. Note this symbol was added
         * in 7.10.3 but was not implemented until 7.23.0.
         */
        CURLCPP_DEFINE_OPTION(CURLSHOPT_SHARE, int);

        /*
         * This option does the opposite of CURLSHOPT_SHARE. It specifies that the specified parameter will no longer
         * be shared. Valid values are the same as those for CURLSHOPT_SHARE.
         */
        CURLCPP_DEFINE_OPTION(CURLSHOPT_UNSHARE, int);

        /*
         * The parameter allows you to specify a pointer to data that will be passed to the lock_function and
         * unlock_function each time it is called.
         */
        CURLCPP_DEFINE_OPTION(CURLSHOPT_USERDATA, void *);
    }

    /**
     * Definition of share interface. The purpose of this interface is to
     * enable data sharing between curl handlers.
     */
    class curl_share : public curl_interface<CURLSHcode> {
    public:
        /**
         * The default constructor will initialize the share
         * handle to its default value.
         */
        curl_share();
        /**
         * The overloaded constructor allows users to initialize
         * the share handle and initialize the libcurl environment
         * using customs flags.
         */
        explicit curl_share(long);
        /**
         * Copy constructor to perform the copy of the share handle.
         */ 
        curl_share(const curl_share &);
        /**
         * Assignment operator to perform assignment between two or
         * more objects of this class.
         */
        curl_share &operator=(const curl_share &);
        /**
         * The destructor will free the share handler previously 
         * allocated.
         */
        ~curl_share() NOEXCEPT override;
        /**
         * Add method used to add options to the share handle.
         */
        template <CURLSHoption Opt> void add(detail::SHOption_type<Opt>);
        /**
         * Allows users to specify a list of options for the current
         * easy handler. In this way, you can specify any iterable data
         * structure.
         */
        template<typename Iterator> void add(Iterator, Iterator);
    protected:
    	void initialize_curl_share();
    private:
        CURLSH *curl;
    };

    // Implementation of overloaded constructor.
    inline curl_share::curl_share(const long flag) : curl_interface(flag) {
        initialize_curl_share();
    }

    // Implementation of copy constructor.
    inline curl_share::curl_share(const curl_share &share) : curl_interface() {
    	(void)share; // unused
    	initialize_curl_share();
    }
    
    // Implementation of add method
    template<CURLSHoption Opt> void curl_share::add(const detail::SHOption_type<Opt> val) {
        const auto code = curl_share_setopt(this->curl, Opt, val);
        if (code != CURLSHE_OK) {
            throw curl_share_exception(code, __FUNCTION__);
        }
    }
    
    // Implementation of overloaded add method.
    template<typename Iterator> void curl_share::add(Iterator begin, const Iterator end) {
        for (; begin != end; ++begin) {
            this->add(*begin);
        }
    }
}

#endif /* defined(__curlcpp__curl_share__) */
