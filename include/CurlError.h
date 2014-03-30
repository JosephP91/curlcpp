/* 
 * File:   CurlError.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:25 PM
 */

#ifndef CURLERROR_H
#define	CURLERROR_H

#include <curl/curl.h>
#include <exception>
#include <string>
#include <utility>

using std::exception;
using std::string;
using std::make_pair;
using std::pair;

template<class T> class CurlError : public exception {
public:
    CurlError(const string error, const T code) : error(error), code(code) {}
    ~CurlError() throw() {};
    pair<string,T> what() noexcept;
private:
    string error;
    T code;
};

// Template specialization for CurlError class
template<class T> pair<string,T> CurlError<T>::what() noexcept {
    return make_pair(this->error,this->code);
}


#endif	/* CURLERROR_H */