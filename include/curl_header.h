/* 
 * File:   curl_header.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:45 PM
 */

#ifndef curl_header_H
#define	curl_header_H

#include <vector>
#include <string>
#include <list>
#include <initializer_list>
#include <curl/curl.h>

using std::string;
using std::vector;
using std::list;
using std::initializer_list;

// Definition of a header object.
namespace curl {
    class curl_header {
    public:
        curl_header();
        curl_header(initializer_list<string>);
        curl_header(const curl_header &);
        curl_header &operator=(const curl_header &);
        ~curl_header() noexcept;
        void add(const string);
        void add(const vector<string> &);
        void add(const list<string> &);
        const struct curl_slist *get() const;
    private:
        int size;
        struct curl_slist *headers;
    };
}

#endif	/* curl_header_H */