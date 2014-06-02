//
//  curl_share.h
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
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

namespace curl {
    class curl_share : public curl_interface<CURLSH,CURLSHcode> {
    public:
        curl_share() : curl_interface(curl_share_init()) {}
        curl_share(const long flag) : curl_interface(curl_share_init(),flag) {}
        ~curl_share();
        template<typename T> void add(const curl_pair<CURLSHoption,T> &);
        template<typename T> void add(const vector<curl_pair<CURLSHoption,T>> &);
        template<typename T> void add(const list<curl_pair<CURLSHoption,T>> &);
    protected:
        const string to_string(const CURLSHcode) const noexcept;
    };
    
    // Implementation of add method
    template<typename T> void curl_share::add(const curl_pair<CURLSHoption,T> &pair) {
        CURLSHcode code = curl_share_setopt(this->get_url(),pair.first(),pair.second());
        if (code != CURLSHE_OK) {
            throw curl_error(this->to_string(code),__FUNCTION__);
        }
    }
    // Implementation of overloaded method add
    template<typename T> void curl_share::add(const vector<curl_pair<CURLSHoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](const curl_pair<CURLSHoption,T> option) { this->add(option); } );
    }
    // Implementation of overloaded method add
    template<typename T> void curl_share::add(const list<curl_pair<CURLSHoption,T> > &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](const curl_pair<CURLSHoption,T> option) { this->add(option); });
    }
}

#endif /* defined(__curlcpp__curl_share__) */