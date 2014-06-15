//
//  curl_form.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 09/06/14.
//

#include "curl_form.h"

using curl::curl_form;

// Use some typedefs to code readability
typedef curl_form::name name;
typedef curl_form::content content;
typedef curl_form::name_pointer name_pointer;
typedef curl_form::content_pointer content_pointer;
typedef curl_form::content_type content_type;
typedef curl_form::file file;
typedef curl_form::multi_file multi_file;

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
void curl_form::add(name name, content content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.first(),name.second(),
                     content.first(),content.second(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}



// Implementation of overloaded add method.
void curl_form::add(name name, content content, content_type content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.first(),name.second(),
                     content.first(),content.second(),
                     content_type.first(),content_type.second(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(name name, content_pointer content_pointer) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.first(),name.second(),
                     content_pointer.first(),content_pointer.second(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(name_pointer name_pointer, content_pointer content_pointer) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name_pointer.first(),name_pointer.second(),
                     content_pointer.first(),content_pointer.second(),
                     name_pointer.length_option(), name_pointer.length(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(name name, content_pointer content_pointer, content_type content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.first(),name.second(),
                     content_pointer.first(),content_pointer.second(),
                     content_pointer.length_option(),content_pointer.length(),
                     content_type.first(),content_type.second(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(name name, file file) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.first(),name.second(),
                     file.first(),file.second(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(name name, file file, content_type content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     name.first(),name.second(),
                     file.first(),file.second(),
                     content_type.first(),content_type.second(),
                     CURLFORM_END) != 0) {
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    }
}

// Implementation of add overloaded method.
void curl_form::add(multi_file files) {
    const vector<string> tmp_files =  files.second();
    const size_t size = tmp_files.size();
    struct curl_forms *x = new struct curl_forms[size];
    for (int i = 0; i < size; ++i) {
        x[i].option = CURLFORM_FILE;
        x[i].value = tmp_files[i].c_str();
    }
    if (curl_formadd(&this->form_post,&this->last_ptr,
                     files.first().first(),files.first().second(),
                     CURLFORM_ARRAY,x,
                     CURLFORM_END) != 0) {
        delete []x;
        throw curl_error(" *** Error while adding the form ***",__FUNCTION__);
    } else {
        delete []x;
    }
}