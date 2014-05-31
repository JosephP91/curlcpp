/* 
 * File:   CurlHeader.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:45 PM
 */

#ifndef CURLHEADER_H
#define	CURLHEADER_H

#include <vector>
#include <string>
#include <list>
#include <curl/curl.h>
#include "CurlError.h"

using std::string;
using std::vector;
using std::list;
using curl::CurlError;

namespace curl {
    class CurlHeader {
    public:
        CurlHeader() : headers(nullptr) {};
        CurlHeader(const size_t);
        ~CurlHeader();
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

#endif	/* CURLHEADER_H */