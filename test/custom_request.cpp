#include "curl_easy.h"
#include "curl_form.h"
#include "curl_header.h"

using curl::curl_header;
using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

int main() {
    // Let's create an object which will contain a list of headers.
    curl_header header;
    // Easy object to handle the connection.
    curl_easy easy;

    // Add custom headers.
    std::string jsonInfo = "{\"username\":\"abc\",\"password\":\"abc\"}";
    header.add(jsonInfo);
    header.add("Content-type: application/json");

    // Add the headers to the easy object.
    easy.add<CURLOPT_HTTPHEADER>(header.get());
    // Your URL.
    easy.add<CURLOPT_URL>("http://yoururl");
    // Custom request.
    easy.add<CURLOPT_CUSTOMREQUEST>("PUT");
    // You can choose between 1L and 0L (enable verbose video log or disable)
    easy.add<CURLOPT_VERBOSE>(0L);

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
