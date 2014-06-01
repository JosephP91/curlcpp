/* 
 * File:   CurlError.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:25 PM
 */

#ifndef CURLERROR_H
#define	CURLERROR_H

#include <string>
#include <exception>

using std::exception;
using std::string;

namespace curl {
    class CurlError : public exception {
    public:
        CurlError(const string error) : error(error) {}
        ~CurlError() throw() {};
        // Override of exception's what() method.
        string what() {
            return this->error;
        }
    private:
        string error;
    };
   
}

#endif	/* CURLERROR_H */