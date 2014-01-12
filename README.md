curlcpp
=======

An object oriented C++ wrapper for cURL tool. I'm working for you :P

There a bunch of cURL C++ wrappers out there, but I personally don't like any of them. So, I was writing a framework for my university and I needed a curl wrap in C++, so I wrote it.
I'm still working on it, so, if you find bugs or errors, please tell me! :)

If you want to know a bit more about cURL, you should go on the official website and read about the three interfaces that curl implements: http://curl.haxx.se/

Simple usage example
====================

After including the library provided and the header files, you can start to use the classes and the methods provided with this wrapper.

Here's an example of a simple HTTP request to get google web page, using the curl_easy interface:

`````c++
#include "curl_easy.h"
#include "curl_easy_option.h"

using curl::curl_easy;

int main(int argc, const char **argv) {
    curl_easy easy;
    easy.add_option( curl_easy::option_pair<string>(CURLOPT_URL,"http://www.google.it") );
    easy.add_option( curl_easy::option_pair<long>(CURL_FOLLOWLOCATION,1L) );
    easy.perform();
    return 0;
}
`````

Here's instead, the creation of an HTTP POST form for file uploading:

`````c++
#include "curl_easy.h"
#include "curl_easy_option.h"
#include "curl_multi_option.h"
#include "curl_http_post.h"
#include "form_pair.h"
#include "header.h"

using curl::curl_easy;

int main(int argc, const char * argv[]) {
    string buf="Expect: ";
    curl_easy easy;
    curl_http_post post;
    post.form_add(curl_http_post::form_pair<string>(CURLFORM_COPYNAME,"sendfile"));
    post.form_add(curl_http_post::form_pair<string>(CURLFORM_FILE,"main.cpp"));
    
    post.form_add(curl_http_post::form_pair<string>(CURLFORM_COPYNAME,"filename"));
    post.form_add(curl_http_post::form_pair<string>(CURLFORM_COPYCONTENTS,"main.cpp"));
    
    post.form_add(curl_http_post::form_pair<string>(CURLFORM_COPYNAME,"submit"));
    post.form_add(curl_http_post::form_pair<string>(CURLFORM_COPYCONTENTS,"send"));
    
    Header headers;
    headers.add_header(buf);
    
    easy.add_option(curl_easy::option_pair<string>(CURLOPT_URL,"http://example.com/examplepost.cgi"));
    easy.add_option(curl_easy::option_pair<curl_http_post>(CURLOPT_HTTPPOST,post));
    
    easy.perform();
    return 0;
}
`````

That's it! :)
