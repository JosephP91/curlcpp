#include "curl_easy.h"
#include "curl_ios.h"
#include "curl_exception.h"

using std::ostringstream;

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_ios;

int main(int argc, const char **argv) {
    // Let's declare a stream
    ostringstream str;
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(str);
    // Declaration of an easy object
    curl_easy easy(ios);
    // Add some option to the curl_easy object.
    easy.add<CURLOPT_URL>("http://www.google.it");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    try {
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
    }
    // Retrieve information about curl current session.
    auto x = easy.get_info<char>(CURLINFO_CONTENT_TYPE);
    /**
     * get_info returns a curl_easy_info object. With the get method we retrieve
     * the std::pair object associated with it: the first item is the return code of the
     * request. The second is the element requested by the specified libcurl macro.
     */
    std::cout<<x.get().second<<std::endl;
    return 0;
}
