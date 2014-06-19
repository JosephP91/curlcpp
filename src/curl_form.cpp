//
//  curl_form.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 09/06/14.
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

struct curl_httppost *curl_form::get() const {
    return this->form_post;
}

// Implementation of add method.
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,string> &form_content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    CURLFORM_END) != 0) {
        throw curl_error("*** Error while adding the form *** ",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,string> &form_content, const curl_pair<CURLformoption,string> &content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    content_type.first(),content_type.second(),
                    CURLFORM_END) != 0) {
        throw curl_error("*** Error while adding the form ***",__FUNCTION__);
    }
}

void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,string> &form_content, const curl_pair<CURLformoption,int> &content_length) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    content_length.first(),content_length.second(),
                    CURLFORM_END) != 0) {
        throw curl_error("*** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of add overloaded method.
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,int> &name_length, const curl_pair<CURLformoption,string> &form_content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    name_length.first(),name_length.second(),
                    CURLFORM_END) != 0) {
        throw curl_error("*** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of add overloaded method.
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,string> &form_content, const curl_pair<CURLformoption,int> &content_length, const curl_pair<CURLformoption,string> &content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    content_length.first(),content_length.second(),
                    content_type.first(),content_type.second(),
                    CURLFORM_END) != 0) {
        throw curl_error("*** Error while adding the form ***",__FUNCTION__);
    }
}

/**
 * If you want to upload more than one file, you can pass the form name and a 
 * vector of filenames
 */
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const vector<string> &files) {
    const size_t size = files.size();
    struct curl_forms *new_files = new struct curl_forms[size];
    for (int i = 0; i < size; ++i) {
        new_files[i].option = CURLFORM_FILE;
        new_files[i].value = files[i].c_str();
    }
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    CURLFORM_ARRAY,new_files,
                    CURLFORM_END) != 0) {
        delete []new_files;
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    } else {
        delete []new_files;
    }
}
