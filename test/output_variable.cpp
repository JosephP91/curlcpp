#include <iostream>
#include <ostream>

#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_form.h"
#include "curlcpp/curl_ios.h"
#include "curlcpp/curl_exception.h"

using std::cout;
using std::endl;
using std::ostringstream;

using curl::curl_easy;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;


/**
 * This example shows how to put curl output inside a stream (a variable, for
 * example)
 */
int main() {
    // Create a stringstream object
    ostringstream str;
    // Create a curl_ios object, passing the stream object.
    curl_ios<ostringstream> writer(str);
    
    // Pass the writer to the easy constructor and watch the content returned in that variable!
    curl_easy easy(writer);
    easy.add<CURLOPT_URL>("https://google.com");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();
        
        // Print the content of ostringstream.
        cout<<str.str()<<endl;
    
    } catch (curl_easy_exception &error) {
		    // If you want to print the last error.
		    std::cerr<<error.what()<<std::endl;

		    // If you want to print the entire error stack you can do
		    error.print_traceback();
    }
    return 0;
}
