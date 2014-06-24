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

namespace curl {
    class curl_share : public curl_interface<CURLSHcode> {
    public:
        curl_share();
        explicit curl_share(const long);
        curl_share(const curl_share &);
        curl_share &operator=(const curl_share &);
        ~curl_share() noexcept;
        template<typename T> void add(const curl_pair<CURLSHoption,T> &);
        template<typename T> void add(const vector<curl_pair<CURLSHoption,T>> &);
        template<typename T> void add(const list<curl_pair<CURLSHoption,T>> &);
        const string to_string(const CURLSHcode) const noexcept;
    private:
        CURLSH *curl;
    };
    
    // Implementation of add method
    template<typename T> void curl_share::add(const curl_pair<CURLSHoption,T> &pair) {
        const CURLSHcode code = curl_share_setopt(this->curl,pair.first(),pair.second());
        if (code != CURLSHE_OK) {
            throw curl_error(this->to_string(code),__FUNCTION__);
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