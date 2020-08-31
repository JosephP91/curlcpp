/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_exception.h
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __curlcpp__curl_exception__
#define __curlcpp__curl_exception__

#include <iostream>
#include <string>
#include <exception>
#include <utility>
#include <vector>
#include <algorithm>
#include <mutex>
#include <curl/curl.h>

#include "curl_config.h"

namespace curl {
	// We like it short.
	using curlcpp_traceback_object = std::pair<std::string,std::string>;
	using curlcpp_traceback = std::vector<curlcpp_traceback_object>;

	/**
     * This class represents a custom exception for libcurl errors. 
     * If a function throws an error, its name will be added to a
     * vector (treated like a stack, because if I had used a stack,
     * to print it, I should have to remove all the elements), so
     * users can keep track of which method threw which exception.
     */
    class curl_exception : public std::runtime_error {
    public:
        /**
         * This constructor is used to build the error.
         */
        curl_exception(const std::string&, const std::string&) NOEXCEPT;
        /**
         * The copy constructor allows to copy the object in a thread safe way.
         */
        curl_exception(const curl_exception &) NOEXCEPT;
        /**
         * The assignment operator allows to assign the object to another object in
         * a thread safe way.
         */
        curl_exception & operator=(curl_exception const&);
        /**
         * The destructor, in this case, doesn't do anything.
         */
        ~curl_exception() NOEXCEPT override = default;

        using std::exception::what;
        /**
         * Returns the vector of errors.
         */
        static curlcpp_traceback get_traceback() ;
        /**
         * Simple method which prints the entire error stack.
         */
        static void print_traceback() ;
        /**
         * Simple method which clears the entire error stack.
         */
        static void clear_traceback() ;
        /**
         * Simple method which clears the error stack saving it (before cleaning) in a
         * traceback specified in input.
         */
        static void clear_traceback(curlcpp_traceback &) ;
    private:
        /**
         * The error container must be static or will be cleared
         * when an exception is thrown.
         */
        static curlcpp_traceback traceback;
        
        /**
         * Locker for inserting traceback.
         */
         static std::mutex tracebackLocker;
    };

    // Implementation of print_traceback
    inline void curl_exception::print_traceback() {
	    curl_exception::tracebackLocker.lock();
        std::for_each(curl_exception::traceback.begin(),curl_exception::traceback.end(),
        		[](const curlcpp_traceback_object &value) {

            std::cout<<"ERROR: "<<value.first<<" ::::: FUNCTION: "<<value.second<<std::endl;
        });
	    curl_exception::tracebackLocker.unlock();
    }

    // Implementation of clear method.
    inline void curl_exception::clear_traceback() {
        curl_exception::tracebackLocker.lock();
        curl_exception::traceback.clear();
        curl_exception::tracebackLocker.unlock();
    }

    // Implementation of overloaded clear method.
    inline void curl_exception::clear_traceback(curlcpp_traceback& traceback_ref) {
        curl_exception::tracebackLocker.lock();
        traceback_ref = curl_exception::traceback;
        curl_exception::traceback.clear();
        curl_exception::tracebackLocker.unlock();
    }
    
    // Implementation of get_traceback.
    inline curlcpp_traceback curl_exception::get_traceback() {
        curl_exception::tracebackLocker.lock();
        curlcpp_traceback tmp = curl_exception::traceback;
        curl_exception::tracebackLocker.unlock();
        return tmp;
    }
    
    /**
     * Derived class represents an error condition returned by the easy
     * interface functions.
     */
    class curl_easy_exception : public curl_exception {
    public:
        /**
         * This constructor allows to specify a custom error message and the method name where
         * the exception has been thrown.
         */
        curl_easy_exception(const std::string &error, const std::string &method) :
        	curl_exception(error,method), code(CURLE_OK) {}

        /**
         * The constructor will transform a CURLcode error in a proper error message.
         */
        curl_easy_exception(const CURLcode &code, const std::string &method) :
        	curl_exception(curl_easy_strerror(code),method), code(code) {}
        
        /**
         * Returns the error code if there is one. Returns CURLE_OK if none has been set.
         */
        inline CURLcode get_code() const {
            return code;
        }
      private:
        CURLcode code;
    };
    
    /**
     * Derived class represents an error condition returned by the multi
     * interface functions.
     */
    class curl_multi_exception : public curl_exception {
    public:
        /**
         * This constructor enables setting a custom error message and the method name where
         * the exception has been thrown.
         */
        curl_multi_exception(const std::string &error, const std::string &method) :
        	curl_exception(error,method), code(CURLM_OK) {}
        /**
         * The constructor will transform a CURLMcode error to a proper error message.
         */
        curl_multi_exception(const CURLMcode code, const std::string &method) :
        	curl_exception(curl_multi_strerror(code),method), code(code) {}
        
        /**
         * Returns the error code if there is one. Returns CURLM_OK if none has been set.
         */
        inline CURLMcode get_code() const {
            return code;
        }
      private:
        CURLMcode code;
    };
    
    /**
     * Derived class used to represent an error condition returned by the share
     * interface functions.
     */
    class curl_share_exception : public curl_exception {
    public:
        /**
         * This constructor enables setting a custom error message and the method name where
         * the exception has been thrown.
         */
        curl_share_exception(const std::string &error, const std::string &method) :
        	curl_exception(error,method), code(CURLSHE_OK) {}
        /**
         * The constructor will transform a CURLSHcode error in a proper error message.
         */
        curl_share_exception(const  CURLSHcode code, const std::string &method) :
        	curl_exception(curl_share_strerror(code),method), code(code) {}
        
        /**
         * Returns the error code if there is one. Returns CURLE_OK if none has been set.
         */
        inline CURLSHcode get_code() const {
            return code;
        }
      private:
          CURLSHcode code;
    };
}

#endif /* defined(__curlcpp__curl_exception__) */
