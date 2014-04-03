curlcpp
=======

An object-oriented C++ wrapper for cURL tool. I'm working for you. :P

There are a bunch of cURL C++ wrappers out there, but I personally don't like any of them. So, I was writing a framework for my university and I needed a curl wrapper in C++, so I wrote it.
I'm still working on it, so, if you find bugs or errors, please tell me! :)

If you want to know a bit more about cURL, you should go on the official website and read about the three interfaces that curl implements: http://curl.haxx.se/

Compile and link
================

Standalone
----------

```bash
cd build
cmake ..
make # -j2
```

Then add `<curlcpp root>/build/src/` to your library path and `<curlcpp root>/include/` to your include path.

When linking, link against `curlcpp` (e.g.: gcc example.cpp -o example -lcurlcpp).

Submodule
---------

When using a git submodule and CMake-buildsystem, add the following lines to your `CMakeLists.txt`:

```
ADD_SUBDIRECTORY(ext/curlcpp) # Change `ext/curlcpp` to a directory according to your setup
INCLUDE_DIRECTORIES(${CURLCPP_SOURCE_DIR}/include)
```

Simple usage example
====================

Here's an example of a simple HTTP request to get google web page, using the curl_easy interface:

`````c++
#include "../include/CurlEasy.h"
// only "CurlEasy.h" if you use above submodule-way of compilation and linking

using curl::CurlEasy;

int main(int argc, const char **argv) {
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
// only "CurlEasy.h" and "CurlHttpPost.h" if you use above submodule-way of compilation and linking

using curl::CurlEasy;
using curl::CurlHttpPost;

int main(int argc, const char * argv[]) {
    CurlEasy easy;
    CurlHttpPost post;
    post.formAdd(CurlPair<CURLformoption,string>(CURLFORM_COPYNAME,"user"),CurlPair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"username"));
    post.formAdd(CurlPair<CURLformoption,string>(CURLFORM_COPYNAME,"passw"),CurlPair<CURLformoption,string>(CURLFORM_COPYCONTENTS,"password"));
    easy.addOption(CurlPair<CURLoption,string>(CURLOPT_URL,"https://xxxxx/"));
    easy.addOption(CurlPair<CURLoption,CurlHttpPost>(CURLOPT_HTTPPOST,post));
    easy.perform();
    return 0;
}
`````

That's it! :)
