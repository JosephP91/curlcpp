/* 
 * File:   CurlError.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:25 PM
 */

#ifndef CURLERROR_H
#define	CURLERROR_H

#include <iostream>
#include <curl/curl.h>
#include <exception>

using std::exception;
using std::string;

class CurlError : public exception {
public:
    CurlError(const string error) : error(error) {}
    ~CurlError() throw() {};
    string what() { return this->error; }
private:
    string error;
};

#endif	/* CURLERROR_H */