#include "curl_easy.h"
#include "curl_form.h"
#include "curl_header.h"

using curl::curl_header;
using curl::curl_easy;

/*
 * This example shows how to add custom headers to a simple
 * curl request.
 */

int main() {
    // Let's create an object which will contain a list of headers.
    curl_header header;
    // Easy object to handle the connection.
    curl_easy easy;

    // Add custom headers.
    header.add("Accept:");
    header.add("Another:yes");
    header.add("Host: example.com");
    
    // Add the headers to the easy object.
    easy.add<CURLOPT_HTTPHEADER>(header.get());
    
    easy.add<CURLOPT_URL>("localhost");
    easy.add<CURLOPT_VERBOSE>(1L);
    try {
        // Request execution
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
    }
    return 0;
}
