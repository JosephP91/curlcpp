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
#include <ostream>

#include "curl_interface.h"
#include "curl_pair.h"

using std::vector;
using std::list;
using std::unique_ptr;
using std::for_each;
using std::ostream;
using curl::curl_pair;
using curl::curl_interface;

namespace curl  {
    class curl_easy : public curl_interface<CURLcode> {
    public:
        curl_easy();
        explicit curl_easy(ostream &);
        explicit curl_easy(const long);
        explicit curl_easy(const long, ostream &);
        curl_easy(const curl_easy &);
        curl_easy &operator=(const curl_easy &);
        ~curl_easy() noexcept;
        template<typename T> void add(const curl_pair<CURLoption,T>);
        template<typename T> void add(const vector<curl_pair<CURLoption,T>> &);
        template<typename T> void add(const list<curl_pair<CURLoption,T>> &);
        template<typename T> T *get_session_info(const CURLINFO, T *) const;
        //vector<string> get_session_info(const CURLINFO, struct curl_slist **) const;
        void escape(string &);
        void unescape(string &);
        void perform();
        void reset() noexcept;
        CURL *get_curl() const;
    protected:
        const string to_string(const CURLcode) const noexcept;
    private:
        CURL *curl;
    };
    
    // Implementation of addOption method
    template<typename T> void curl_easy::add(const curl_pair<CURLoption,T> pair) {
        const CURLcode code = curl_easy_setopt(this->curl,pair.first(),pair.second());
        if (code != CURLE_OK) {
            throw curl_error(this->to_string(code),__FUNCTION__);
        }
    }
    
    // Implementation of overloaded method addOption
    template<typename T> void curl_easy::add(const vector<curl_pair<CURLoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLoption,T> option) {
            this->add(option);
        });
    }
    
    // Implementation of overloaded method addOption
    template<typename T> void curl_easy::add(const list<curl_pair<CURLoption,T> > &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLoption,T> option) {
            this->add(option);
        });
    }
    
    // Implementation of get_session_info method
    template<typename T> T *curl_easy::get_session_info(const CURLINFO info, T *ptr_info) const {
        const CURLcode code = curl_easy_getinfo(this->curl,info,ptr_info);
        if (code != CURLE_OK && ptr_info) {
            throw curl_error(this->to_string(code),__FUNCTION__);
        }
        return ptr_info;
    }
}

#endif	/* curl_easy_H */