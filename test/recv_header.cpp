#include "curl_easy.h"
#include "curl_form.h"

using curl::curl_easy;
using curl::curl_ios;
using curl::curl_easy_exception;
using std::ostringstream;

/**
 * This example shows how to split the received headers and body content
 * into two different streams
 */
int main() {
    // Create two different ostringstream objects
    ostringstream body_var;
    ostringstream header_var;

    // The "body" stream will put the body content into "body_var"
    curl_ios<ostringstream> body(body_var);
    // The "header" stream will put the headers into "header_var"
    curl_ios<ostringstream> header(header_var);

    // Easy object to handle the connection.
    curl_easy easy;

    // We will use the default write function
    easy.add<CURLOPT_WRITEFUNCTION>(header.get_function());

    // Specify the stream for headers content.
    easy.add<CURLOPT_HEADERDATA>(header.get_stream());

    // Specify the stream for body content.
    easy.add<CURLOPT_WRITEDATA>(body.get_stream());
    easy.add<CURLOPT_URL>("http://www.example.com");

    try {
        easy.perform();

		// Let's print ONLY the headers.
		std::cout<<header_var.str()<<std::endl;

    } catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;

		// If you want to print the entire error stack you can do
		error.print_traceback();
    }
    return 0;
}
