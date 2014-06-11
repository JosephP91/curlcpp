//
//  curl_form.h
//  curlcpp
//
//  Created by Giuseppe Persico on 09/06/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_form__
#define __curlcpp__curl_form__

#include <curl/curl.h>
#include <map>
#include <memory>
#include <string>
#include "curl_error.h"

using std::map;
using std::unique_ptr;
using std::string;
using curl::curl_error;

// Simple class used to handle curl forms.
namespace curl {
    class curl_form {
        // Base class for every form content
        template<class T> class abstract_content {
        public:
            abstract_content(const CURLformoption option, const T value) : option(option), value(value) {}
            virtual CURLformoption get_option() const {
                return this->option;
            }
            virtual T get_value() const {
                return this->value;
            }
        private:
            const CURLformoption option;
            const T value;
        };
        // Base class for every form content pointer which extends the previous one.
        template<class T> class abstract_content_ptr : public abstract_content<T> {
        public:
            abstract_content_ptr(const CURLformoption option, const T value, const CURLformoption len_opt, const int len) : abstract_content<T>(option,value), len_opt(len_opt), len(len) {}
            virtual CURLformoption get_len_option() {
                return this->len_opt;
            }
            virtual int get_length() const {
                return this->len;
            }
        private:
            const CURLformoption len_opt;
            const int len;
        };
    public:
        // This nested subclass rapresent the form name
        class name : public abstract_content<const char *> {
        public:
            name(const CURLformoption option, string value) : abstract_content(option,value.c_str()) {}
        };
        
        // This nested class rapresent a pointer to a name
        class ptr_name : public abstract_content_ptr<char *> {
        public:
            ptr_name(const CURLformoption option, char *value, const CURLformoption len_opt, const int length) : abstract_content_ptr(option,value,len_opt,length) {}
        };
        
        // This nested class rapresent the form content
        class content : public abstract_content<const char *> {
        public:
            content(CURLformoption option, string value) : abstract_content(option,value.c_str()) {}
        };
        
        // This nested class rapresent a pointer to a form content
        class ptr_content : public abstract_content_ptr<char *> {
        public:
            ptr_content(const CURLformoption option, char *value, const CURLformoption len_opt, const int length) : abstract_content_ptr(option,value,len_opt,length) {}
        };
        
        // This nested class rapresent a form content type
        class content_type : public abstract_content<const char *> {
        public:
            content_type(CURLformoption option, string value) : abstract_content(option,value.c_str()) {}
        };
        
        // This nested class rapresent a file to upload
        class file : public abstract_content<const char *> {
        public:
            file(CURLformoption option, const char *value) : abstract_content(option,value) {}
        };
        // This nested class allows to upload multiple files
        class multi_file : public abstract_content<map<CURLformoption,string>> {
        public:
            multi_file(CURLformoption option, map<CURLformoption,string> value) : abstract_content(option,value) {}
        };
        explicit curl_form();
        ~curl_form() noexcept;
        void add(curl_form::name, curl_form::content);
        void add(curl_form::name, curl_form::content, curl_form::content_type);
        void add(curl_form::name, curl_form::ptr_content);
        void add(curl_form::ptr_name, curl_form::ptr_content);
        void add(curl_form::name, curl_form::ptr_content, curl_form::content_type);
        void add(curl_form::name, curl_form::file);
        void add(curl_form::name, curl_form::file, curl_form::content_type);
        struct curl_httppost *get() const;
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };
}

#endif /* defined(__curlcpp__curl_form__) */
