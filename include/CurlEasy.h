/* 
 * File:   CurlEasy.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:54 PM
 */

#ifndef CURLEASY_H
#define	CURLEASY_H

#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <curl/curl.h>

#include "CurlInterface.h"
#include "CurlPair.h"

using std::vector;
using std::list;
using std::unique_ptr;
using std::for_each;
using curl::CurlPair;
using curl::CurlInterface;

namespace curl  {
    class CurlEasy : public CurlInterface<CURL,CURLcode> {
    public:
        CurlEasy() : CurlInterface(curl_easy_init()) {}
        CurlEasy(const long flag) : CurlInterface(curl_easy_init(),flag) {}
        ~CurlEasy();
        template<typename T> void add(const CurlPair<CURLoption,T> &);
        template<typename T> void add(const vector<CurlPair<CURLoption,T>> &);
        template<typename T> void add(const list<CurlPair<CURLoption,T>> &);
        template<typename T> unique_ptr<T> getSessionInfo(const CURLINFO, T *) const;
        void escape(string &);
        void unescape(string &);
        CURLcode perform();
        void reset() noexcept;
    protected:
        const string toString(const CURLcode) const noexcept;
    };
    
    // Implementation of addOption method
    template<typename T> void CurlEasy::add(const CurlPair<CURLoption,T> &pair) {
        const CURLcode code = curl_easy_setopt(this->getCurl(),pair.first(),pair.second());
        if (code != CURLE_OK) {
            throw CurlError(this->toString(code));
        }
    }
    // Implementation of overloaded method addOption
    template<typename T> void CurlEasy::add(const vector<CurlPair<CURLoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](CurlPair<CURLoption,T> option) { this->add(option); } );
    }
    // Implementation of overloaded method addOption
    template<typename T> void CurlEasy::add(const list<CurlPair<CURLoption,T> > &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](CurlPair<CURLoption,T> option) { this->add(option); });
    }
    // Implementation of getSessionInfo method
    template<typename T> unique_ptr<T> CurlEasy::getSessionInfo(const CURLINFO info, T *ptr_info) const {
        const CURLcode code = curl_easy_getinfo(this->getCurl(),info,ptr_info);
        if (code != CURLE_OK && ptr_info) {
            throw CurlError(this->toString(code));
        }
        return unique_ptr<T>{ptr_info};
    }
}

#endif	/* CURLEASY_H */