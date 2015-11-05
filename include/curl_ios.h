
/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_header.h
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

#ifndef curl_ios_h
#define curl_ios_h

#include <iostream>
#include <string>
#include <sstream>

using std::ostream;
using std::istream;
using std::string;
using std::cout;
using std::cin;
using std::ostringstream;

// Let's typedef this big boy to enhance code readability.
using curlcpp_callback_type = size_t(*)(void *,size_t,size_t,void *);

namespace {
    // Default in-memory write callback.
    size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        const size_t realsize = size * nmemb;
        ostream* const mem = static_cast<ostream*>(userp);
        mem->write(static_cast<const char*>(contents), realsize);
        return realsize;
    }
    // Default in-variable write callback.
    size_t write_variable_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        const size_t realsize = size * nmemb;
        std::ostringstream *stream = static_cast<ostringstream*>(userp);
        stream->write(static_cast<const char *>(contents), realsize);
        return realsize;
    }
    // Default in-memory read callback.
    size_t read_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        const size_t realsize = size * nmemb;
        istream* const mem = static_cast<istream*>(userp);
        mem->read(static_cast<char*>(contents), realsize);
        return mem->gcount();
    }
}

namespace curl {
    template<class T> class curl_ios {
    public:
        // This constructor allows to specifiy a custom stream and a custom callback pointer.
        curl_ios(T &stream, curlcpp_callback_type callback_ptr) : _stream(stream) {
            this->set_callback(callback_ptr);
        }
        // This method allow to specify a custom callback pointer.
        void set_callback(curlcpp_callback_type callback_ptr) {
            _callback_ptr = callback_ptr == nullptr ? write_variable_callback : callback_ptr;
        }
        // This method returns the stream pointer.
        T *get_stream() const {
            return _stream;
        }
        // This method return the callback function pointer.
        curlcpp_callback_type get_function() const {
            return _callback_ptr;
        }
    private:
        // Callback pointer.
        curlcpp_callback_type _callback_ptr;
        // Generic stream pointer.
        T* _stream;
    };
    
    // Template specialization for ostream class.
    template<> class curl_ios<ostream> {
    public:
        // This constructor will initialize the stream with cout and the callback with a default in-memory write callback.
        curl_ios() : _callback_ptr(write_memory_callback), _io_stream(&cout) {}
        // This constructor will initialize the stream with a customized stream and a default in-memory write callback.
        curl_ios(ostream &io_stream) : _callback_ptr(write_memory_callback), _io_stream(&io_stream) {}
        // This constructor will initialize the stream with cout and a customized write callback.
        curl_ios(curlcpp_callback_type callback_ptr) : _io_stream(&cout) {
            this->set_callback(callback_ptr);
        }
        // This constructor will initialize the the stream with a custom stream and the callback with a customized one.
        curl_ios(ostream &io_stream, curlcpp_callback_type callback_ptr) : _io_stream(&io_stream) {
            this->set_callback(callback_ptr);
        }
        // This method allow to specify a custom callback pointer.
        void set_callback(curlcpp_callback_type callback_ptr) {
            _callback_ptr = callback_ptr == nullptr ? write_variable_callback : callback_ptr;
        }
        // This method returns the stream pointer.
        ostream *get_stream() const {
            return this->_io_stream;
        }
        // This method returns the callback for this curl_ios.
        curlcpp_callback_type get_function() const {
            return this->_callback_ptr;
        }
    private:
        // The callback pointer.
        curlcpp_callback_type _callback_ptr;
        // A stream pointer.
        ostream *_io_stream;
    };
    
    // Template specialization for ostringstream class.
    template<> class curl_ios<ostringstream> {
    public:
        //This constructor allows to specify a custom ostringstream stream.
        curl_ios(ostringstream &o_stream) : _callback_ptr(write_variable_callback), _o_stream(&o_stream) {}
        //This constructor allows to specify a custom stream and a custom callback pointer.
        curl_ios(ostringstream &o_stream, curlcpp_callback_type callback_ptr) {
            _o_stream = &o_stream;
            this->set_callback(callback_ptr);
        }
        // This method allows to specify a custom callback pointer.
        void set_callback(curlcpp_callback_type callback_ptr) {
            _callback_ptr = callback_ptr == nullptr ? write_variable_callback : callback_ptr;
        }
        // This method returns the stream pointer.
        ostringstream *get_stream() const {
            return this->_o_stream;
        }
        // This method returns the callback pointer.
        curlcpp_callback_type get_function() const {
            return this->_callback_ptr;
        }
    private:
        // The callback pointer.
        curlcpp_callback_type _callback_ptr;
        // The ostringstream pointer.
        ostringstream *_o_stream;
    };
    
    
    // Template specialization for istream class.
    template<> class curl_ios<istream> {
    public:
        // The default constructor will initialize the callback pointer and the stream with default values.
        curl_ios() : _callback_ptr(read_memory_callback), _i_stream(&cin) {}
        //This constructor allows to specify an input stream while the a default callback pointer will be used.
        curl_ios(istream &i_stream) : _callback_ptr(read_memory_callback) {
            _i_stream = &i_stream;
        }
        // This overloaded constructor allows to specify a custom callback pointer while the stream will be cin.
        curl_ios(curlcpp_callback_type callback_ptr) : _i_stream(&cin) {
            this->set_callback(callback_ptr);
        }
        // This method allows to specify a custom stream and a custom callback pointer.
        curl_ios(istream &i_stream, curlcpp_callback_type callback_ptr) : _i_stream(&i_stream) {
            this->set_callback(callback_ptr);
        }
        // This method allows to specify a custom callback pointer.
        void set_callback(curlcpp_callback_type callback_ptr) {
            _callback_ptr = callback_ptr == nullptr ? write_variable_callback : callback_ptr;
        }
        // This method returns the stream pointer.
        istream *get_stream() const {
            return _i_stream;
        }
        // This method returns the callback pointer.
        curlcpp_callback_type get_function() const {
            return _callback_ptr;
        }
    private:
        // The callback pointer.
        curlcpp_callback_type _callback_ptr;
        // The stream pointer.
        istream *_i_stream;
    };
}

#endif /* curl_ios_h */
