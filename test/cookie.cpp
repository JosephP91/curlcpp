#include <iostream>

#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_form.h"
#include "curl_cookie.h"
#include "curl_ios.h"

using std::ostringstream;

using curl::cookie;
using curl::curl_header;
using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curl_cookie;
using curl::curlcpp_cookies;
using curl::curl_ios;


/**
 * This example shows to how to set and get cookies in a
 * simple curl request.
 */

int main() {
    // Let's declare a stream
    ostringstream str;
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(str);

    // Easy object to handle the connection, url and verbosity level.
    curl_easy easy(ios);
    easy.add<CURLOPT_URL>("http://example.com");

    // Let's create a cooie
    cookie ck;
    ck.set_name("nome cookie");
    ck.set_value("valore cookie");
    ck.set_path("/");
    ck.set_domain(".example.com");

    // Create a cookie object and add the previously created cookie.
    curl_cookie c_obj(easy);
    c_obj.set(ck);

    // This rapresents a vector of cookies.
    curlcpp_cookies cookies;
    try {
        easy.perform();
        // Retrieve all the cookies for the example.com
        cookies = c_obj.get();
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
