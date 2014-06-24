//
//  curl_handle.h
//  curlcpp
//
//  Created by Giuseppe Persico on 12/06/14.
//

#ifndef __curlcpp__curl_handle__
#define __curlcpp__curl_handle__

#include "curl_multi.h"
#include <initializer_list>

using curl::curl_multi;
using std::initializer_list;

class curl_multi::curl_handle {
public:
    // This object wraps a curl message
    class curl_message;
    explicit curl_handle(curl_multi &);
    curl_handle(curl_multi &, initializer_list<curl_easy>);
    curl_handle(const curl_handle &);
    curl_handle &operator=(const curl_handle &);
    ~curl_handle() noexcept;
    void add(const curl_easy &);
    void remove(const curl_easy &);
    vector<curl_message> read_info();
private:
    vector<curl_easy> handlers;
    curl_multi &multi;
};

#endif /* defined(__curlcpp__curl_handle__) */