/**
 * File:   curl_writer.cpp
 * Author: Giuseppe Persico
 */

#include "curl_writer.h"

using std::cout;
using curl::curl_writer;

// Default memory write callback.
namespace {
    size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        const size_t realsize = size * nmemb;
        ostream* const mem = static_cast<ostream*>(userp);
        mem->write(static_cast<const char*>(contents), realsize);
        return realsize;
    }
}

// Implementation of constructor.
curl_writer::curl_writer() {
    _stream_ptr = &cout;
    _writer_ptr = &write_memory_callback;
}

// Implementation of overloaded constructor.
curl_writer::curl_writer(ostream &stream) {
    _stream_ptr = &stream;
    _writer_ptr = &write_memory_callback;
}

// Implementation of another overloaded constructor.
curl_writer::curl_writer(curlcpp_writer_type writer_ptr) {
    _stream_ptr = &cout;
    this->set_writer_ptr(writer_ptr);
}

// Implementation of another overloaded constructor.
curl_writer::curl_writer(ostream &stream, curlcpp_writer_type writer_ptr) {
    _stream_ptr = &stream;
    this->set_writer_ptr(writer_ptr);
}

// Implementation of get_stream method.
ostream *curl_writer::get_stream() const {
    return _stream_ptr;
}

// Implementation of get_function method.
curlcpp_writer_type curl_writer::get_function() const {
    return _writer_ptr;
}

// Implementation of set_writer_ptr method.
void curl_writer::set_writer_ptr(curlcpp_writer_type writer_ptr) {
    _writer_ptr = (writer_ptr == nullptr) ? &write_memory_callback : writer_ptr;
}