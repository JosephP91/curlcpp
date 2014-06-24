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
#include <new>
#include "curl_error.h"
#include "curl_pair.h"

using std::string;
using std::vector;
using std::bad_alloc;
using curl::curl_pair;
using curl::curl_error;

// Simple class used to handle curl forms.
namespace curl {
    class curl_form {
    public:
        curl_form();
        ~curl_form() noexcept;
        curl_form(const curl_form &);
        curl_form &operator=(const curl_form &);
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &);
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &); 
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &); 
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &, const curl_pair<CURLformoption,string> &);
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &, const curl_pair<CURLformoption,string> &); 
        void add(const curl_pair<CURLformoption,string> &, const vector<string> &);
        const struct curl_httppost *get() const;
    protected:
        template<typename T> inline void is_null(const T *ptr) const;
        void copy_ptr(struct curl_httppost **, const struct curl_httppost *);
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };
    
    // Implementation of utility function to check if a pointer points to null.
    template<typename T> void curl_form::is_null(const T *ptr) const {
        if (ptr == nullptr) {
            throw bad_alloc();
        }
    }
}

#endif /* defined(__curlcpp__curl_form__) */
