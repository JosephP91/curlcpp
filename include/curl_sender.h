//
//  curl_buffer.h
//  curlcpp
//
//  Created by Giuseppe Persico on 29/06/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_sender__
#define __curlcpp__curl_sender__

#include <iostream>
#include "curl_easy.h"

using curl::curl_easy;

namespace curl {
    /**
     * This class implements a sender that sends raw data on an established
     * connection on an easy handler.
     */
    template<class T> class curl_sender {
    public:
        /**
         * The constructor initializes the easy handler and the number of
         * sent bytes.
         */
        curl_sender(curl_easy &easy);
        /**
         * This method wraps the curl_easy_send function that sends raw data
         * on an established connection on an easy handler.
         */
        void send(const T, const size_t);
        /**
         * Simple getter method that returns the sents byte number.
         */
        size_t get_sent_bytes() const;
    private:
        curl_easy &_easy;
        size_t _sent_bytes;
    };
    
    // Implementatino of constructor.
    template<class T> curl_sender<T>::curl_sender(curl_easy &easy) : _easy(easy), _sent_bytes(0) {
        // ... nothing to do here ...
    }
    
    // Implementation of send method.
    template<class T> void curl_sender<T>::send(const T buffer, const size_t size) {
        const CURLcode code = curl_easy_send(_easy.get_curl(),buffer,size,&_sent_bytes);
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
    }
    
    // Implementation of get_sent_bytes method.
    template<class T> inline size_t curl_sender<T>::get_sent_bytes() const {
        return _sent_bytes;
    }
    
    /**
     * Template specialization for strings. C++ string type is not supported by libcurl C
     * functions, so we must treat it as a const char pointer. This is the purpose of
     * this class.
     */
    template<> class curl_sender<string> {
    public:
        /**
         * The constructor initializes the easy handler and the number of
         * sent bytes.
         */
        curl_sender(curl_easy &easy) : _easy(easy), _sent_bytes(0) {}
        /**
         * This method wraps the curl_easy_send function that sends raw data
         * on an established connection on an easy handler, treating strings
         * as const char pointers.
         */
        void send(const string buffer) {
            const CURLcode code = curl_easy_send(_easy.get_curl(),buffer.c_str(),buffer.length(),&_sent_bytes);
            if (code != CURLE_OK) {
                throw curl_easy_exception(code,__FUNCTION__);
            }
        }
        /**
         * Simple getter method that returns the sents byte number.
         */
        inline size_t get_sent_bytes() const {
            return _sent_bytes;
        }
    private:
        curl_easy &_easy;
        size_t _sent_bytes;
    };
}

#endif /* defined(__curlcpp__curl_sender__) */