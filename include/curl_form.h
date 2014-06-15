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
        // This class extends curl_pair to add another attribute: the length of the content.
        template<class T> class curl_double_pair : public curl_pair<CURLformoption,T> {
        public:
            curl_double_pair(const CURLformoption option, const T value, const CURLformoption len_option, const int len) : curl_pair<CURLformoption,T>(option,value), len_option(len_option), len(len) {}
            int length() const {
                return len;
            }
            CURLformoption length_option() const {
                return this->len_option;
            }
        private:
            CURLformoption len_option;
            const int len;
        };
    public:
        // This nested subclass rapresent the form name
        class name : public curl_pair<CURLformoption,const char *> {
        public:
            name(const CURLformoption option, const string value) : curl_pair(option,value.c_str()) {}
        };
        
        // This nested class rapresent a pointer to a name
        class name_pointer : public curl_double_pair<const char *> {
        public:
            name_pointer(const CURLformoption option, const char *value, const CURLformoption len_opt, const int length) : curl_double_pair(option,value,len_opt,length) {}
        };
        
        // This nested class rapresent the form content
        class content : public curl_pair<CURLformoption,const char *>  {
        public:
            content(CURLformoption option, string value) : curl_pair(option,value.c_str()) {}
        };
        
        // This nested class rapresent a pointer to a form content
        class content_pointer : public curl_double_pair<const char *> {
        public:
            content_pointer(const CURLformoption option, const char *value, const CURLformoption len_opt, const int length) : curl_double_pair(option,value,len_opt,length) {}
        };
        
        // This nested class rapresent a form content type
        class content_type : public curl_pair<CURLformoption,const char *> {
        public:
            content_type(CURLformoption option, string value) : curl_pair(option,value.c_str()) {}
        };
        
        // This nested class rapresent a file to upload
        class file : public curl_pair<CURLformoption,const char *> {
        public:
            file(CURLformoption option, const char *value) : curl_pair(option,value) {}
        };
        
        // This nested class allows to upload multiple files
        class multi_file : public curl_pair<curl_form::name,vector<string>> {
            multi_file(curl_form::name name, vector<string> value) : curl_pair(name,value) {}
        };
        explicit curl_form();
        ~curl_form() noexcept;
        void add(curl_form::name, curl_form::content);
        void add(curl_form::name, curl_form::content, curl_form::content_type);
        void add(curl_form::name, curl_form::content_pointer);
        void add(curl_form::name_pointer, curl_form::content_pointer);
        void add(curl_form::name, curl_form::content_pointer, curl_form::content_type);
        void add(curl_form::name, curl_form::file);
        void add(curl_form::name, curl_form::file, curl_form::content_type);
        void add(curl_form::multi_file);
        struct curl_httppost *get() const;
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };
}

#endif /* defined(__curlcpp__curl_form__) */
