#include "curl_easy.h"

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

/**
 * This example shows how to make a simple request with curl.
 */
int main() {
    // Easy object to handle the connection.
    curl_easy easy;

    // Add some options.
    easy.add<CURLOPT_URL>("http://www.google.it");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();
    } catch (curl_easy_exception &error) {
    	// If you want to print the last error.
        std::cerr<<error.what()<<std::endl;
    }
    return 0;
}
