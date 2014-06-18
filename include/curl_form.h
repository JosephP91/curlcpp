//
//  curl_form.h
//  curlcpp
//
//  Created by Giuseppe Persico on 09/06/14.
//

#ifndef __curlcpp__curl_form__
#define __curlcpp__curl_form__

#include <curl/curl.h>
#include <vector>
#include <string>
#include "curl_error.h"
#include "curl_pair.h"

using std::string;
using std::vector;
using curl::curl_pair;
using curl::curl_error;

// Simple class used to handle curl forms.
namespace curl {
    class curl_form {
    public:
        explicit curl_form();
        ~curl_form() noexcept;
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &);
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &); 
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &); 
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &, const curl_pair<CURLformoption,string> &);
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &, const curl_pair<CURLformoption,string> &); 
        void add(const curl_pair<CURLformoption,string> &, const vector<string> &);
        struct curl_httppost *get() const;
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };
}

#endif /* defined(__curlcpp__curl_form__) */
