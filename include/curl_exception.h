//
//  curl_exception.h
//  curlcpp
//
//  Created by Giuseppe Persico on 02/06/14.
//

#ifndef __curlcpp__curl_exception__
#define __curlcpp__curl_exception__

#include <iostream>
#include <string>
#include <exception>
#include <utility>
#include <vector>
#include <curl/curl.h>

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::pair;
using std::vector;

namespace curl {
    /**
     * This class rapresent a custom exception for libcurl errors. 
     * If a function throws an error, its name will be added to a
     * vector (treated like a stack, because if I had used a stack,
     * to print it, I should have to remove all the elements), so
     * users can keep track of which method threw which exception.
     */
    class curl_exception : public exception {
    public:
        /**
         * This constructor is used to build the error.
         */
        curl_exception(const string, const string);
        /**
         * The destructor, in this case, doesen't do anything.
         */
        ~curl_exception() throw();
        using exception::what;
        /**
         * Override of exception's what method, used to returns
         * the vector of errors.
         */
        const vector<pair<string,string>> what();
        /**
         * Simple method which prints the entire error stack.
         */
        void print_traceback() const;
    private:
        /**
         * The error container must be static or will be cleared
         * when an exceptions is thrown.
         */
        static vector<pair<string,string>> traceback;
    };

    // Implementation of print_traceback
    inline void curl_exception::print_traceback() const {
        for_each(curl_exception::traceback.begin(),curl_exception::traceback.end(),[](const pair<string,string> &value) {
            cout<<"ERROR: "<<value.first<<" ::::: FUNCTION: "<<value.second<<endl;
        });
    }
    
    // Implementation of what method.
    inline const vector<pair<string,string>> curl_exception::what() {
        return curl_exception::traceback;
    }
    
    /**
     * Derived class used to rapresent a condition of error returned by the easy
     * interface functions.
     */
    class curl_easy_exception : public curl_exception {
    public:
        /**
         * This constructor allows to specify a custom error message and the method name where
         * the exeption has been thrown.
         */
        curl_easy_exception(const string error, const string method) : curl_exception(error,method) {}
        /**
         * The constructor will transfrom a CURLcode error in a proper error message.
         */
        curl_easy_exception(const CURLcode code, const string method) : curl_exception(curl_easy_strerror(code),method) {}
    };
    
    /**
     * Derived class used to rapresent a condition of error returned by the multi
     * interface functions.
     */
    class curl_multi_exception : public curl_exception {
    public:
        /**
         * This constructor allows to specify a custom error message and the method name where
         * the exeption has been thrown.
         */
        curl_multi_exception(const string error, const string method) : curl_exception(error,method) {}
        /**
         * The constructor will transform a CURLMcode error in a proper error message.
         */
        curl_multi_exception(const CURLMcode code, const string method) : curl_exception(curl_multi_strerror(code),method) {}
    };
    
    /**
     * Derived class used to rapresent a condition of error returned by the share
     * interface functions.
     */
    class curl_share_exception : public curl_exception {
    public:
        /**
         * This constructor allows to specify a custom error message and the method name where
         * the exeption has been thrown.
         */
        curl_share_exception(const string error, const string method) : curl_exception(error,method) {}
        /**
         * The constructor will transform a CURLSHcode error in a proper error message.
         */
        curl_share_exception(const  CURLSHcode code, const string method) : curl_exception(curl_share_strerror(code),method) {}
    };
}

#endif /* defined(__curlcpp__curl_exception__) */