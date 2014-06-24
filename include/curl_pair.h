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
    // Generic pair of objects.
    template<class T, class K> class curl_pair {
    public:
        curl_pair(const T option, const K value) : option(option), value(value) {};
        inline const T first() const noexcept {
            return this->option;
        }
        inline const K second() const noexcept {
            return this->value;
        }
    private:
        const T option;
        const K value;
    };
        
    // Template specialization for strings.
    template<class T> class curl_pair<T,string> {
    public:
        curl_pair(const T option, const string value) : option(option), value(value) {};
        inline const T first() const noexcept {
            return this->option;
        }
        inline const char *second() const noexcept {
            return this->value.c_str();
        }
    private:
        const T option;
        const string value;
    };
    
    // Template specialization for curl_form type
    template<class T> class curl_pair<T,curl_form> {
    public:
        curl_pair(const T option, const curl_form &value) : option(option), value(value) {}
        inline const T first() const noexcept {
            return this->option;
        }
        inline const curl_httppost *second() const noexcept {
            return (this->value).get();
        }
    private:
        const T option;
        const curl_form &value;
    };
    
    // Template specialization for curl_header type
    template<class T> class curl_pair<T,curl_header> {
    public:
        curl_pair(const T option, const curl_header &value) : option(option), value(value) {}
        inline const T first() const noexcept {
            return this->option;
        }
        inline const curl_slist *second() const noexcept {
            return (this->value).get();
        }
    private:
        const T option;
        const curl_header &value;
    };
}

#endif	/* curl_pair_H */