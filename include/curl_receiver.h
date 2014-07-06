//
//  curl_receiver.h
//  curlcpp
//
//  Created by Giuseppe Persico on 29/06/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_receiver__
#define __curlcpp__curl_receiver__

#include <array>
#include "curl_easy.h"

using std::array;
using curl::curl_easy;

namespace curl {
    /**
     * This class implement a receiver that allows users to receives raw
     * data on an established connection on an easy handler.
     */
    template<class T, const size_t SIZE> class curl_receiver {
    public:
        /**
         * The default constructor simply initialize the attributes. In this
         * case just the recieved bytes number is initialized to zero.
         */
        curl_receiver();
        /**
         * In this case the destuctor does not have to release any resource.
         */
        ~curl_receiver() {}
        /**
         * The recieve method wraps curl_easy_recv function and receives raw
         * data from the established connection on an easy handler.
         */
        bool receive(curl_easy &);
        /**
         * Simple getter method that returns the buffer with the recieved
         * data.
         */
        const array<T,SIZE> get_buffer() const;
        /**
         * Simple getter method that returns the number of received bytes.
         * Real applications should check this number to ensure that the
         * communication ended without errors.
         */
        size_t get_received_bytes() const;
    private:
        array<T,SIZE> _buffer;
        size_t _recv_bytes;
    };
    
    // Impementation of constructor.
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
    
    // Implementation of get_buffeer method.
    template<typename T, const size_t SIZE> inline const array<T,SIZE> curl_receiver<T,SIZE>::get_buffer() const {
        return _buffer;
    }
    
    // Implementation of get_received_buffer method.
    template<typename T, const size_t SIZE> inline size_t curl_receiver<T,SIZE>::get_received_bytes() const {
        return _recv_bytes;
    }
}

#endif /* defined(__curlcpp__curl_receiver__) */