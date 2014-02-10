//
//  curl_http_post.h
//  curlcpp
//
//  Created by Giuseppe Persico on 10/02/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curlcpp_curl_http_post_h
#define curlcpp_curl_http_post_h

#include <curl/curl.h>

// Forward declaration because of circular reference
namespace curl {
    template<class T, class K> class curl_pair;
}

namespace curl {
    class curl_http_post {
    public:
        curl_http_post() : form_post(nullptr), last_ptr(nullptr) {}
        ~curl_http_post();
        template<typename T> curl_http_post &form_add(const curl_pair<CURLformoption,T> &, const curl_pair<CURLformoption,T> &);
        struct curl_httppost *get_form_post() const noexcept { return this->form_post; }
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };

    template<typename T> curl_http_post &curl_http_post::form_add(const curl_pair<CURLformoption,T> &pair, const curl_pair<CURLformoption,T> &pair_2) {
        curl_formadd(&this->form_post,&this->last_ptr,pair.first(),pair.second(),pair_2.first(),pair_2.second(),CURLFORM_END);
        return *this;
    }
}

#endif
