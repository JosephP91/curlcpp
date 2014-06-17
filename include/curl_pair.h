/* 
 * File:   curl_pair.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:39 PM
 */

#ifndef curl_pair_H
#define	curl_pair_H

#include <string>

// Forward reference to curl_form
namespace curl {
    class curl_form;
}

using std::string;
using curl::curl_form;

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
            return (this->value).form_post;
        }
    private:
        const T option;
        const curl_form &value;
    };
}

#endif	/* curl_pair_H */