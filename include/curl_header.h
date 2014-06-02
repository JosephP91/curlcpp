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
#include <curl/curl.h>
#include "curl_error.h"

using std::string;
using std::vector;
using std::list;
using curl::curl_error;

namespace curl {
    class curl_header {
    public:
        curl_header() : headers(nullptr) {};
        curl_header(const size_t);
        ~curl_header();
        void add(const string);
        void add(const vector<string> &);
        void add(const list<string> &);
        void remove(const string);
        void confirm();
        const vector<string> get() const;
    protected:
        void set(const string);
        void setSize(const size_t);
    private:
        vector<string> tmpHeaders;
        struct curl_slist *headers;
    };
}

#endif	/* curl_header_H */