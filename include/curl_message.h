//
//  curl_message.h
//  curlcpp
//
//  Created by Giuseppe Persico on 13/06/14.
//

#ifndef __curlcpp__curl_message__
#define __curlcpp__curl_message__

#include <iostream>
#include "curl_multi.h"
#include "curl_handle.h"

using curl::curl_multi;

// Wrap of the value returned by curl_multi_info_read
class curl_multi::curl_handle::curl_message {
public:
    curl_message(CURLMSG, curl_easy &, void *, CURLcode);
    curl_message(const curl_message &);
    curl_message &operator=(const curl_message &);
    const CURLMSG get_message() const;
    const CURLcode get_result() const;
    const curl_easy get_curl() const;
    const void *get_whatever() const;
private:
    CURLMSG message;
    curl_easy easy;
    void *whatever;
    CURLcode result;
};

#endif /* defined(__curlcpp__curl_message__) */
