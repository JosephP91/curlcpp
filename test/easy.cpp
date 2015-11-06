#include "curl_easy.h"

using curl::curl_easy;

/*
 * This example shows how to make a simple request with
 * curl.
 */

int main() {
    // Easy object to handle the connection.
    curl_easy easy;
    // Add some options.
    easy.add<CURLOPT_URL>("http://www.google.it");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    try {
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        auto errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    return 0;
}