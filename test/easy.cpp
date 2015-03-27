#include "curl_easy.h"
#include "curl_option.h"

using curl::curl_easy;
using curl::make_option;

int main(int argc, const char **argv) {
    curl_easy easy;
    
    easy.add(make_option(CURLOPT_URL, "http://www.google.it"));
    easy.add(make_option(CURLOPT_FOLLOWLOCATION,1L));
    
    try {
        easy.perform();
    } 
    catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        vector<pair<string,string>> errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    
    return 0;
}