#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_form.h"
#include "curl_cookie.h"

using curl::curl_header;
using curl::curl_easy;
using curl::curl_exception;
using curl::curl_cookie;

/*
 * This example shows to how to set and get cookies in a
 * simple curl request.
 */

int main() {
    // Easy object to handle the connection.
    curl_easy easy;
    // Set the environment
    easy.add<CURLOPT_URL>("http://example.com");
    easy.add<CURLOPT_VERBOSE>(1L);
    // Create a cookie object.
    curl_cookie cookie(easy);
    // Let's set some cookies.
    cookie.set_cookie_list("Set-Cookie: OLD_PREF=3d141414bf4209321; "
                                   "expires=Sun, 17-Jan-2038 19:14:07 GMT; path=/; domain=.example.com");
    curlcpp_cookies cookies;
    try {
        easy.perform();
        // Retrieve all the cookies for the example.com
        cookies = cookie.get();
        // Delete all the memory helded cookies.
        easy.add<CURLOPT_COOKIEFILE>("ALL");
    } catch (curl_easy_exception error) {
        error.print_traceback();
    }
    // Now let's print them
    for (auto cook : cookies) {
        cout<<cook<<endl;
    }
    return 0;
}
