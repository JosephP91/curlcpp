curlcpp
=======

An object oriented C++ wrapper for cURL tool. I'm working for you :P

There a bunch of cURL C++ wrappers out there, but I personally don't like any of them. So, I was writing a framework for my university and I needed a curl wrap in C++, so I wrote it.
I'm still working on it, so, if you find bugs or errors, please tell me! :)

If you want to know a bit more about cURL, you should go on the official website and read about the three interfaces that curl implements: http://curl.haxx.se/

Compile and link
================

After including the header files, you can start to use the library.

I used the most recent C++ standard, C++11, to compile this project. So when you will compile it, don't forget to put the -std=c++11 option. Make sure that your compiler supports it!

Make sure you have installed libcurl. If not, you can download and compile it from official website. After doing that, create a simple main.cpp file and then type:

g++ -std=c++11 *.cpp -lcurl

This command assumes that you have libcurl installed in the standard directory.

Simple usage example
====================

Here's an example of a simple HTTP request to get google web page, using the curl_easy interface:

`````c++
#include "../include/curl_easy.h"

using curl::curl_easy;

int main(int argc, const char **argv) {
    curl_easy easy;
    easy.add_option(curl_pair<CURLoption,string>(CURLOPT_URL,"http://www.google.it") );
    easy.add_option(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L) );
    easy.perform();
    return 0;
}
`````

Here's instead, the creation of an HTTPS POST login form:

`````c++
#include <iostream>
#include "../include/curl_easy.h"
#include "../include/curl_http_post.h"

using curl::curl_easy;
using curl::curl_http_post;

int main(int argc, const char * argv[]) {
    curl_easy easy;
    curl_http_post post;
    post.form_add(curl_pair<CURLformoption,string>(CURLFORM_COPYNAME,"user"),curl_pair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"username"));
    post.form_add(curl_pair<CURLformoption,string>(CURLFORM_COPYNAME,"passw"),curl_pair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"password"));
    easy.add_option(curl_pair<CURLoption,string>(CURLOPT_URL,"https://xxxxx/"));
    easy.add_option(curl_pair<CURLoption,curl_http_post>(CURLOPT_HTTPPOST,post));
    easy.perform();
    return 0;
}
`````

That's it! :)
