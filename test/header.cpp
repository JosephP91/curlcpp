#include "curl_easy.h"
#include "curl_form.h"
#include "curl_header.h"

using curl::curl_header;
using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

/**
 * This example shows how to add custom headers to a simple
 * curl request.
 */
int main() {
    // Easy object to handle the connection.
    curl_easy easy;

	// Let's create an object which will contain a list of headers.
	curl_header header;
    header.add("Accept:");
    header.add("Another:yes");
    header.add("Host: example.com");
    
    // Add the headers to the easy object.
    easy.add<CURLOPT_HTTPHEADER>(header.get());
    
    easy.add<CURLOPT_URL>("http://example.com");
    easy.add<CURLOPT_VERBOSE>(1L);

    try {
        easy.perform();
    } catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;

		// If you want to print the entire error stack you can do
		error.print_traceback();
    }
    return 0;
}
