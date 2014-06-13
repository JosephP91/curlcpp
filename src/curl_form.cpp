//
//  curl_form.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 09/06/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "curl_form.h"

using curl::curl_form;

// Implementation of constructor.
curl_form::curl_form() : form_post(nullptr), last_ptr(nullptr) {
    // ... nothing to do here ...
}

// Implementation of destructor. The form post will be deallocated.
curl_form::~curl_form() noexcept {
    if (this->form_post != nullptr) {
        curl_formfree(this->form_post);
        this->form_post = nullptr;
        this->last_ptr = nullptr;
    }
}

// Implementation of get method.
struct curl_httppost *curl_form::get() const {
    return this->form_post;
}

// Implementation of add method.
void curl_form::add(curl_form::name name, curl_form::content content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.get_option(),name.get_value(),
                     content.get_option(),content.get_value(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(curl_form::name name, curl_form::content content, curl_form::content_type content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.get_option(),name.get_value(),
                     content.get_option(),content.get_value(),
                     content_type.get_option(),content_type.get_value(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(curl_form::name name, curl_form::ptr_content ptr_content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.get_option(),name.get_value(),
                     ptr_content.get_option(),ptr_content.get_value(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(curl_form::ptr_name ptr_name, curl_form::ptr_content ptr_content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     ptr_name.get_option(),ptr_name.get_value(),
                     ptr_content.get_option(),ptr_content.get_value(),
                     ptr_name.get_length(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(curl_form::name name, curl_form::ptr_content ptr_content, curl_form::content_type content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.get_option(),name.get_value(),
                     ptr_content.get_option(),ptr_content.get_value(),ptr_content.get_length(),
                     content_type.get_option(),content_type.get_value(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(curl_form::name name, curl_form::file file) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.get_option(),name.get_value(),
                     file.get_option(),file.get_value(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(curl_form::name name, curl_form::file file, curl_form::content_type content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.get_option(),name.get_value(),
                     file.get_option(),file.get_value(),
                     content_type.get_option(),content_type.get_value(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}