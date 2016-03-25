#include <iostream>

#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_form.h"
#include "curl_cookie.h"

using curl::cookie;
using curl::curl_header;
using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curl_cookie;
using curl::curlcpp_cookies;


/**
 * This example shows to how to set and get cookies in a
 * simple curl request.
 */

int main() {
    // Easy object to handle the connection, url and verbosity level.
    curl_easy easy;
    easy.add<CURLOPT_URL>("http://example.com");
    easy.add<CURLOPT_VERBOSE>(1L);

    // Let's create a cooie
    cookie ck("test","/",".example.com",null);

    // Create a cookie object and add the previously created cookie.
    curl_cookie cookie_object(easy);
    cookie_object.set(ck);

    // This rapresents a vector of cookies.
    curlcpp_cookies cookies;
    try {
        easy.perform();
        // Retrieve all the cookies for the example.com
        cookies = cookie_object.get();
        // Delete all the memory helded cookies.
        easy.add<CURLOPT_COOKIEFILE>("ALL");
    } catch (curl_easy_exception error) {
        error.print_traceback();
    }
    // Print them all!
    for (auto cook : cookies) {
        std::cout<<cook<<std::endl;
    }
    return 0;
}
