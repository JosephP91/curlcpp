/* 
 * File:   curl_easy.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:54 PM
 */

#ifndef curl_easy_H
#define	curl_easy_H

#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <curl/curl.h>

#include "curl_interface.h"
#include "curl_pair.h"

using std::vector;
using std::list;
using std::unique_ptr;
using std::for_each;
using curl::curl_pair;
using curl::curl_interface;

namespace curl  {
    class curl_easy : public curl_interface<CURL,CURLcode> {
    public:
        curl_easy() : curl_interface(curl_easy_init()) {}
        curl_easy(const long flag) : curl_interface(curl_easy_init(),flag) {}
        ~curl_easy();
        template<typename T> void add(const curl_pair<CURLoption,T> &);
        template<typename T> void add(const vector<curl_pair<CURLoption,T>> &);
        template<typename T> void add(const list<curl_pair<CURLoption,T>> &);
        template<typename T> unique_ptr<T> getSessionInfo(const CURLINFO, T *) const;
        void escape(string &);
        void unescape(string &);
        void perform();
        void reset() noexcept;
    protected:
        const string to_string(const CURLcode) const noexcept;
    };
    
    // Implementation of addOption method
    template<typename T> void curl_easy::add(const curl_pair<CURLoption,T> &pair) {
        const CURLcode code = curl_easy_setopt(this->get_url(),pair.first(),pair.second());
        if (code != CURLE_OK) {
            throw curl_error(this->to_string(code),__FUNCTION__);
        }
    }
    // Implementation of overloaded method addOption
    template<typename T> void curl_easy::add(const vector<curl_pair<CURLoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLoption,T> option) { this->add(option); } );
    }
    // Implementation of overloaded method addOption
    template<typename T> void curl_easy::add(const list<curl_pair<CURLoption,T> > &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLoption,T> option) { this->add(option); });
    }
    // Implementation of getSessionInfo method
    template<typename T> unique_ptr<T> curl_easy::getSessionInfo(const CURLINFO info, T *ptr_info) const {
        const CURLcode code = curl_easy_getinfo(this->get_url(),info,ptr_info);
        if (code != CURLE_OK && ptr_info) {
            throw curl_error(this->to_string(code),__FUNCTION__);
        }
        return unique_ptr<T>{ptr_info};
    }
}

#endif	/* curl_easy_H */