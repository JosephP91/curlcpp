/* 
 * File:   curl_pair.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:39 PM
 */

#ifndef curl_pair_H
#define	curl_pair_H

#include <string>

// Forward reference to curl_form and curl_header
namespace curl {
    class curl_form;
    class curl_header;
}

using std::string;
using curl::curl_form;
using curl::curl_header;


namespace curl {
    /**
     * This is a class that wraps two objects: an option and the value for
     * that option. It's very useful when building forms or setting options
     * for easy/multi/share handlers. It let you specify the libcurl option
     * and its value.
     */
    template<class T, class K> class curl_pair {
    public:
        /**
         * The two parameters constructor gives users a fast way to
         * build an object of this type.
         */
        curl_pair(const T option, const K value) : option(option), value(value) {};
        /**
         * Simple method that returns the first field of the pair.
         */
        inline const T first() const noexcept {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair.
         */
        inline const K second() const noexcept {
            return this->value;
        }
    private:
        const T option;
        const K value;
    };
        
    /**
     * Template specialization for C++ strings. Why do we need this? Because
     * curl_pair must be passed to C functions that doesen't know how to
     * handle C++ string type, so we can specialize curl_pair class in a
     * manner that its methods returns a const char *.
     */
    template<class T> class curl_pair<T,string> {
    public:
        /**
         * The two parameters constructor gives users a fast way to 
         * build an object of this type.
         */
        curl_pair(const T option, const string value) : option(option), value(value) {};
        /**
         * Simple method that returns the first field of the pair.
         */
        inline const T first() const noexcept {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair as
         * a C string, so a const char *.
         */
        inline const char *second() const noexcept {
            return this->value.c_str();
        }
    private:
        const T option;
        const string value;
    };
    
    /**
     * Template specialization for curl_form type. Why do we need this? Because
     * curl_form wraps a struct curl_httppost list. libcurl functions can't handle
     * curl_form type, so we need to specialize curl_pair to return a struct
     * curl_httppost *.
     */
    template<class T> class curl_pair<T,curl_form> {
    public:
        /**
         * The two parameters constructor gives users a fast way to build an object of
         * this type.
         */
        curl_pair(const T option, const curl_form &value) : option(option), value(value) {}
        /**
         * Simple method that returns the first field of the pair.
         */
        inline const T first() const noexcept {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair as a 
         * C struct curl_httppost pointer.
         */
        inline const curl_httppost *second() const noexcept {
            return (this->value).get();
        }
    private:
        const T option;
        const curl_form &value;
    };
    
    /**
     * Template specialization for curl_header type. Why do we need this? Because
     * curl_header wraps a struct curl_slist list of headers. libcurl functions can't
     * handle a curl_header type, so we need to specialize curl_pair to return a 
     * struct curl_slist *.
     */
    template<class T> class curl_pair<T,curl_header> {
    public:
        /**
         * Thw two parameters constructor gives users a fast way to build an object
         * of this type.
         */
        curl_pair(const T option, const curl_header &value) : option(option), value(value) {}
        /**
         * Simple method that returns the first field of the pair.
         */
        inline const T first() const noexcept {
            return this->option;
        }
        /**
         * Simple method that returns the second field of the pair as a C struct 
         * curl_slist pointer.
         */
        inline const curl_slist *second() const noexcept {
            return (this->value).get();
        }
    private:
        const T option;
        const curl_header &value;    };
}

#endif	/* curl_pair_H */
