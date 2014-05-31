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
        CurlHeader &add(const string);
        CurlHeader &add(const vector<string> &);
        CurlHeader &add(const list<string> &);
        CurlHeader &remove(const string);
        void confirm();
        const struct curl_slist *get() const;
    protected:
        void set(const string);
        void setSize(const size_t);
    private:
        vector<string> tmpHeaders;
        struct curl_slist *headers;
    };
}

#endif	/* CURLHEADER_H */