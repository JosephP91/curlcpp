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

using std::string;
using std::vector;
using std::list;

namespace curl {
    class CurlHeader {
    public:
        CurlHeader() : headers(nullptr) {};
        CurlHeader(const size_t);
        ~CurlHeader();
        void setHeadersSize(const size_t);
        CurlHeader &addHeader(const string);
        CurlHeader &addHeader(const vector<string> &);
        CurlHeader &addHeader(const list<string> &);
        CurlHeader &removeHeader(const string);
        void confirmHeaders();
        const struct curl_slist * getHeaders() const;
    protected:
        void setHeader(const string);
    private:
        vector<string> tmpHeaders;
        struct curl_slist *headers;
    };
}

#endif	/* CURLHEADER_H */