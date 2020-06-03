/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_receiver.h
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

#ifndef __curlcpp__curl_receiver__
#define __curlcpp__curl_receiver__

#include <array>
#include "curl_easy.h"

namespace curl {

    /**
     * This class implements a receiver that allow users to receive raw
     * data on an established connection on an easy handler.
     */
    template<class T, const size_t SIZE> class curl_receiver {
    public:
        /**
         * The default constructor simply initializes the attributes. In this
         * case just the received bytes number is initialized to zero.
         */
        curl_receiver();
        /**
         * In this case the destructor does not have to release any resource.
         */
        ~curl_receiver() = default;
        /**
         * The receive method wraps curl_easy_recv function and receives raw
         * data from the established connection on an easy handler.
         */
        bool receive(curl_easy &);
        /**
         * Simple getter method that returns the buffer with the received
         * data.
         */
        std::array<T,SIZE> get_buffer() const;
        /**
         * Simple getter method that returns the number of received bytes.
         * Real applications should check this number to ensure that the
         * communication ended without errors.
         */
        size_t get_received_bytes() const;
    private:
        std::array<T,SIZE> _buffer;
        size_t _recv_bytes;
    };
    
    // Implementation of constructor.
    template<typename T, const size_t SIZE> curl_receiver<T,SIZE>::curl_receiver() : _recv_bytes(0) {
        if (SIZE <= 0) {
            throw curl_exception("Buffer size can not be less or equal to zero",__FUNCTION__);
        }
    }
    
    // Implementation of receive method.
    template<typename T, const size_t SIZE> bool curl_receiver<T,SIZE>::receive(curl_easy &easy) {
        const CURLcode code = curl_easy_recv(easy.get_curl(),&_buffer,SIZE,&_recv_bytes);
        if (code == CURLE_AGAIN) {
            return false;
        }
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
        return true;
    }
    
    // Implementation of get_buffer method.
    template<typename T, const size_t SIZE> inline std::array<T,SIZE> curl_receiver<T,SIZE>::get_buffer() const {
        return _buffer;
    }
    
    // Implementation of get_received_buffer method.
    template<typename T, const size_t SIZE> inline size_t curl_receiver<T,SIZE>::get_received_bytes() const {
        return _recv_bytes;
    }
}

#endif /* defined(__curlcpp__curl_receiver__) */
