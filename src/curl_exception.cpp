/**
 * File:   curl_exception.cpp
 * Author: Giuseppe Persico
 */

#include "curl_exception.h"

using curl::curl_exception;
using curl::curlcpp_traceback;

// Need to define the traceback here to separate declaration from definition, or we'll get a linker error...
curlcpp_traceback curl::curl_exception::traceback;
// .. same for the traceback mutex.
std::mutex curl::curl_exception::tracebackLocker;

// Constructor implementation. Every call will push into the calls stack the function name and the error occurred.
curl_exception::curl_exception(const std::string &error, const std::string &fun_name) NOEXCEPT
    : std::runtime_error(error) {

    curl_exception::tracebackLocker.lock();

    curl_exception::traceback.insert(
    		curl_exception::traceback.begin(),curlcpp_traceback_object(error,fun_name));

    curl_exception::tracebackLocker.unlock();
}

// Copy constructor implementation. It makes a copy of the traceback in a thread safe way.
curl_exception::curl_exception(const curl_exception &object) NOEXCEPT : std::runtime_error(object.what()) {
    curl_exception::traceback = object.get_traceback();
}

// Assignment operator implementation. Implement the assignment operation in a thread safe way avoiding self assignment.
curl_exception& curl_exception::operator=(curl_exception const &object) {
    if (&object != this) {
        curl_exception::traceback = object.get_traceback();
    }
    return *this;
}
