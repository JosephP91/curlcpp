/**
 * File:   curl_form.cpp
 * Author: Giuseppe Persico
 */

#include <cstring>
#include "curl_form.h"

using curl::curl_form;

// Implementation of constructor.
curl_form::curl_form() : form_post(nullptr), last_ptr(nullptr) {
    // ... nothing to do here ...
}

// Implementation of destructor.
curl_form::~curl_form() NOEXCEPT {
    if (this->form_post != nullptr) {
        curl_formfree(this->form_post);
        this->form_post = nullptr;
        this->last_ptr = nullptr;
    }
}

// Implementation of assignment operator. Also here, we must perform a deep copy of the entire list.
curl_form &curl_form::operator=(const curl_form &form) {
    if (this == &form) {
        return *this;
    }
    curl_formfree(this->form_post);
    struct curl_httppost *old_head = form.form_post;
    while (old_head != nullptr) {
        if (this->form_post == nullptr) {
            this->is_null(this->last_ptr = this->form_post = (struct curl_httppost *)malloc(sizeof(struct curl_httppost)));
            this->copy_ptr(&this->last_ptr,old_head);
        } else {
            this->is_null(this->last_ptr->next = (struct curl_httppost *)malloc(sizeof(struct curl_httppost)));
            this->copy_ptr(&this->last_ptr->next,old_head);
            this->last_ptr = this->last_ptr->next;
        }
        old_head = old_head->next;
    }
    return *this;
}

// Implementation of add method.
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,string> &form_content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    CURLFORM_END) != 0) {
        throw curl_exception("Error while adding the form",__FUNCTION__);
    }
}

// Implementation of overloaded add method.
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,string> &form_content, const curl_pair<CURLformoption,string> &content_type) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    content_type.first(),content_type.second(),
                    CURLFORM_END) != 0) {
        throw curl_exception("Error while adding the form",__FUNCTION__);
    }
}

void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,string> &form_content, const curl_pair<CURLformoption,int> &content_length) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    content_length.first(),content_length.second(),
                    CURLFORM_END) != 0) {
        throw curl_exception("Error while adding the form",__FUNCTION__);
    }
}

// Implementation of add overloaded method.
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const curl_pair<CURLformoption,int> &name_length, const curl_pair<CURLformoption,string> &form_content) {
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    form_content.first(),form_content.second(),
                    name_length.first(),name_length.second(),
                    CURLFORM_END) != 0) {
        throw curl_exception("Error while adding the form",__FUNCTION__);
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
        throw curl_exception("Error while adding the form",__FUNCTION__);
    }
}

/**
 * If you want to upload more than one file, you can pass the form name and a 
 * vector of filenames.
 */
void curl_form::add(const curl_pair<CURLformoption,string> &form_name, const vector<string> &files) {
    const size_t size = files.size();
    struct curl_forms *new_files;
    this->is_null(new_files = (struct curl_forms *)calloc(size,sizeof(struct curl_forms)));
    if (new_files == nullptr) {
        throw bad_alloc();
    }
    for (size_t i = 0; i < size; ++i) {
        new_files[i].option = CURLFORM_FILE;
        new_files[i].value = files[i].c_str();
    }
    if (curl_formadd(&this->form_post,&this->last_ptr,
                    form_name.first(),form_name.second(),
                    CURLFORM_ARRAY,new_files,
                    CURLFORM_END) != 0) {
        delete []new_files;
        throw curl_exception("Error while adding the form",__FUNCTION__);
    } 
    delete []new_files;
}

/**
 * Helper function used to copy the curl_httppost list in the copy constructor, to reduce code verbosity.
 * We must allocate a pointer for every single pointer data in the old list to perform a complete deep 
 * copy.
 */
void curl_form::copy_ptr(struct curl_httppost **ptr, const struct curl_httppost *old_ptr) {
    if (old_ptr->name) {
        this->is_null((*ptr)->name = (char *)malloc(old_ptr->namelength*sizeof(char)));
        strcpy((*ptr)->name,old_ptr->name);
        // Copy the namelength
        (*ptr)->namelength = old_ptr->namelength;
    }
    if (old_ptr->buffer) {
        // Copy the buffers
        this->is_null((*ptr)->buffer = (char *)malloc(old_ptr->bufferlength*sizeof(char)));
        strcpy((*ptr)->buffer,old_ptr->buffer);
        // Copy the buffer length
        (*ptr)->bufferlength = old_ptr->bufferlength;
    }
    if (old_ptr->contents) {
        // Copy the contents
        this->is_null((*ptr)->contents = (char *)malloc(old_ptr->contentslength*sizeof(char)));
        strcpy((*ptr)->contents,old_ptr->contents);
        // Copy contents length
        (*ptr)->contentslength = old_ptr->contentslength;
    }
    if (old_ptr->contenttype) {
        // Copy content type
        this->is_null((*ptr)->contenttype = (char *)malloc(strlen(old_ptr->contenttype)*sizeof(char)));
        strcpy((*ptr)->contenttype,old_ptr->contenttype);
    }
    if (old_ptr->showfilename) {
        // Copy file name
        this->is_null((*ptr)->showfilename = (char *)malloc(strlen(old_ptr->showfilename)*sizeof(char)));
        strcpy((*ptr)->showfilename,old_ptr->showfilename);
    }
    // Copy flags
    (*ptr)->flags = old_ptr->flags;
}
