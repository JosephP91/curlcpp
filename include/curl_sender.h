/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_sender.h
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

#ifndef __curlcpp__curl_sender__
#define __curlcpp__curl_sender__

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
         * Simple getter method that returns sent's current byte number.
         */
        size_t get_sent_bytes() const;
    private:
        curl_easy &_easy;
        size_t _sent_bytes;
    };
    
    // Implementation of constructor.
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
         * Simple getter method that returns sent's current byte number.
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
