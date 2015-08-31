/**
 * File:   curl_reader.cpp
 * Author: Giuseppe Persico
 */

#include "curl_reader.h"

using std::cin;
using curl::curl_reader;

// Default memory read callback.
namespace {
    size_t read_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        const size_t realsize = size * nmemb;
        istream* const mem = static_cast<istream*>(userp);
        mem->read(static_cast<char*>(contents), realsize);
        return mem->gcount();
    }
}

// Implementation of constructor.
curl_reader::curl_reader() {
    _stream_ptr = &cin;
    _reader_ptr = &read_memory_callback;
}

// Implementation of overloaded constructor.
curl_reader::curl_reader(istream &stream) {
    _stream_ptr = &stream;
    _reader_ptr = &read_memory_callback;
}

// Implementation of another overloaded constructor.
curl_reader::curl_reader(curlcpp_reader_type reader_ptr) {
    _stream_ptr = &cin;
    this->set_reader_ptr(reader_ptr);
}

// Implementation of another overloaded constructor.
curl_reader::curl_reader(istream &stream, curlcpp_reader_type reader_ptr) {
    _stream_ptr = &stream;
    this->set_reader_ptr(reader_ptr);
}

// Implementation of get_stream method.
istream *curl_reader::get_stream() const {
    return _stream_ptr;
}

// Implementation of get_function method.
curlcpp_reader_type curl_reader::get_function() const {
    return _reader_ptr;
}

// Implementation of set_reader_ptr method.
void curl_reader::set_reader_ptr(curlcpp_reader_type reader_ptr) {
    _reader_ptr = (reader_ptr == nullptr) ? &read_memory_callback : reader_ptr;
}
