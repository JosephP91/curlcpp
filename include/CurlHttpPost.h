/* 
 * File:   CurlHttpPost.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:38 PM
 */

#ifndef CURLHTTPPOST_H
#define	CURLHTTPPOST_H

#include <curl/curl.h>

// Forward declaration because of circular reference
namespace curl {
    template<class T, class K> class CurlPair;
}

namespace curl {
    class CurlHttpPost {
    public:
        CurlHttpPost() : form_post(nullptr), last_ptr(nullptr) {}
        ~CurlHttpPost();
        template<typename T> CurlHttpPost &formAdd(const CurlPair<CURLformoption,T> &, const CurlPair<CURLformoption,T> &);
        struct curl_httppost *getFormPost() const noexcept;
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };

    // Implementation of formAdd method
    template<typename T> CurlHttpPost &CurlHttpPost::formAdd(const CurlPair<CURLformoption,T> &pair, const CurlPair<CURLformoption,T> &pair_2) {
        curl_formadd(&this->form_post,&this->last_ptr,pair.first(),pair.second(),pair_2.first(),pair_2.second(),CURLFORM_END);
        return *this;
    }
}

#endif	/* CURLHTTPPOST_H */