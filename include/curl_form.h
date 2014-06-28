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

namespace curl {
    /**
     * This class simplify the creation of a form. It wraps all the libcurl
     * functions used to add content to a form and to destroy it.
     */   
    class curl_form {
    public:
        /**
         * The default constructor will simply initialize the pointers to the
         * list of form contents.
         */
        curl_form();
        /**
         * The destructor will free the space allocated for the form content
         * list.
         */
        ~curl_form() noexcept;
        /**
         * Copy constructor used to perform a deep copy of the form content
         * list. Without it we would be not able to perform copy. 
         */
        curl_form(const curl_form &);
        /**
         * Assignment operator to implement assignment between two object
         * of this class.
         */
        curl_form &operator=(const curl_form &);
        /**
         * This method allows users to add content to a form, using the 
         * curl_pair class.
         */
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &);
        /**
         * Overloaded add method.
         */
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &); 
        /**
         * Overloaded add method. It adds another curl_pair object to add more
         * contents to the form contents list.
         */
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &); 
        /**
         * Overloaded add method. It adds another curl_pair object to add more
         * contents to the form contents list.
         */
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &, const curl_pair<CURLformoption,string> &);
        /**
         * Overloaded add method. It adds another curl_pair object to add more
         * contents to the form contents list.
         */
        void add(const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,string> &, const curl_pair<CURLformoption,int> &, const curl_pair<CURLformoption,string> &); 
        /**
         * Overloaded add method. This version is primarly used to upload multiple files. 
         * You can pass a vector of filenames to upload them.
         */
        void add(const curl_pair<CURLformoption,string> &, const vector<string> &);
        /**
         * Simple getter method used to return the head of the list.
         */
        const struct curl_httppost *get() const;
    protected:
        /**
         * This utility function is used to check if a given pointer, is null.
         */
        template<typename T> void is_null(const T *ptr) const;
        /**
         * This utility function is used to perform a deep copy of 
         * the form contents list. We must traverse the new list to
         * copy all the field in the left-object's list. This method
         * puts the node in the tail. Indeed, libcurl keeps two 
         * pointers to implement this list: a tail and a head.
         */
        void copy_ptr(struct curl_httppost **, const struct curl_httppost *);
    private:
        struct curl_httppost *form_post;
        struct curl_httppost *last_ptr;
    };

    // Implementation of copy constructor.
    inline curl_form::curl_form(const curl_form &form) : form_post(nullptr), last_ptr(nullptr) {
        *this = form;
    }
    
    // Implementation of utility function to check if a pointer points to null.
    template<typename T> inline void curl_form::is_null(const T *ptr) const {
        if (ptr == nullptr) {
            throw bad_alloc();
        }
    }
    
    // Implementation of getter method that returns the list head.
    inline const struct curl_httppost *curl_form::get() const {
        return this->form_post;
    }
}

#endif /* defined(__curlcpp__curl_form__) */
