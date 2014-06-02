/* 
 * File:   curl_http_post.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:38 PM
 */

#ifndef curl_http_post_H
#define	curl_http_post_H

#include <curl/curl.h>
#include "curl_error.h"

using curl::curl_error;

// Forward declaration because of circular reference
namespace curl {
    template<class T, class K> class curl_pair;
}

namespace curl {
    class curl_http_post {
    public:
        curl_http_post() : form_post(nullptr), last_ptr(nullptr) {}
        ~curl_http_post();
        template<typename T> void add(const curl_pair<CURLformoption,T> &, const curl_pair<CURLformoption,T> &);
        struct curl_httppost *get() const noexcept;
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };

    // Implementation of formAdd method
    template<typename T> void curl_http_post::add(const curl_pair<CURLformoption,T> &pair, const curl_pair<CURLformoption,T> &pair_2) {
        CURLFORMcode code = curl_formadd(&this->form_post,&this->last_ptr,pair.first(),pair.second(),pair_2.first(),pair_2.second(),CURLFORM_END);
        if (code != 0) {
            throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
        }
    }
}

#endif	/* curl_http_post_H */