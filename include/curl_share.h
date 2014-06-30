//
//  curl_share.h
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//

#ifndef __curlcpp__curl_share__
#define __curlcpp__curl_share__

#include <vector>
#include <list>
#include "curl_interface.h"
#include "curl_pair.h"

using std::vector;
using std::list;
using curl::curl_interface;
using curl::curl_pair;
using curl::curl_share_exception;

namespace curl {
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
        explicit curl_share(const long);
        /**
         * Copy constructor to perform the copy of the share handle.
         */ 
        curl_share(const curl_share &);
        /**
         * Assignment operator to perform assignment between two or
         * more objects of this class.
         */
        curl_share &operator=(const curl_share &);
        ~curl_share() noexcept;
        /**
         * Add method used to add options to the share handle.
         */
        template<typename T> void add(const curl_pair<CURLSHoption,T> &);
        /**
         * Overloaded add method used to add a vector of options to
         * the share handle.
         */
        template<typename T> void add(const vector<curl_pair<CURLSHoption,T>> &);
        /**
         * Overloaded add method used to add a list of options to share
         * handle.
         */
        template<typename T> void add(const list<curl_pair<CURLSHoption,T>> &);
    private:
        CURLSH *curl;
    };

    // Implementation of overloaded constructor.
    inline curl_share::curl_share(const long flag) : curl_interface(flag) {
        curl_share();
    }

    // Implementation of copy constructor.
    inline curl_share::curl_share(const curl_share &share) {
        curl_share();
    }
    
    // Implementation of add method
    template<typename T> void curl_share::add(const curl_pair<CURLSHoption,T> &pair) {
        const CURLSHcode code = curl_share_setopt(this->curl,pair.first(),pair.second());
        if (code != CURLSHE_OK) {
            throw curl_share_exception(code,__FUNCTION__);
        }
    }
    // Implementation of overloaded method add
    template<typename T> void curl_share::add(const vector<curl_pair<CURLSHoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](const curl_pair<CURLSHoption,T> option) {
            this->add(option);
        });
    }
    // Implementation of overloaded method add
    template<typename T> void curl_share::add(const list<curl_pair<CURLSHoption,T> > &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](const curl_pair<CURLSHoption,T> option) {
            this->add(option);
        });
    }
}

#endif /* defined(__curlcpp__curl_share__) */
