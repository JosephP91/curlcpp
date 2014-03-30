curlcpp
=======

An object-oriented C++ wrapper for cURL tool. I'm working for you. :P

There are a bunch of cURL C++ wrappers out there, but I personally don't like any of them. So, I was writing a framework for my university and I needed a curl wrapper in C++, so I wrote it.
I'm still working on it, so, if you find bugs or errors, please tell me! :)

If you want to know a bit more about cURL, you should go on the official website and read about the three interfaces that curl implements: http://curl.haxx.se/

Compile and link
================

I added the entire netbeans project so you can import and use it. Don't forget to link the libcurl library, with -lcurl option, and link curlcpp library and headers in your project settings.

I removed the CMake support added before, to simplify the process of compile/use.

Simple usage example
====================

Here's an example of a simple HTTP request to get google web page, using the curl_easy interface:

`````c++
#include "CurlEasy.h"

using curl::CurlEasy;

int main(int argc, char** argv) {
    CurlEasy easy;
    easy.addOption(CurlPair<CURLoption,string>(CURLOPT_URL,"http://www.google.it") );
    easy.addOption(CurlPair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L) );
    easy.perform();
    return 0;
}
`````

Here's instead, the creation of an HTTPS POST login form:

`````c++
#include "CurlEasy.h"
#include "CurlHttpPost.h"

using curl::CurlEasy;
using curl::CurlHttpPost;

int main(int argc, char** argv) {
    CurlEasy easy;
    CurlHttpPost post;
    post.formAdd(CurlPair<CURLformoption,string>(CURLFORM_COPYNAME,"user"),CurlPair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"username"));
    post.formAdd(CurlPair<CURLformoption,string>(CURLFORM_COPYNAME,"passw"),CurlPair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"password"));
    easy.addOption(CurlPair<CURLoption,string>(CURLOPT_URL,"https://xxx.xxxxx"));
    easy.addOption(CurlPair<CURLoption,CurlHttpPost>(CURLOPT_HTTPPOST,post));
    easy.perform();
    return 0;
}
`````
