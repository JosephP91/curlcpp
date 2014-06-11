curlcpp
=======

An object-oriented C++ wrapper for cURL tool

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

When linking, link against `curlcpp` (e.g.: gcc -std=c++11 example.cpp -o example -lcurlcpp).

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
#include <iostream>
#include "../include/curl_easy.h"
// only "curl_easy.h" if you use above submodule-way of compilation and linking

using std::cout;
using std::endl;
using curl::curl_easy;

int main(int argc, const char **argv) {
    curl_easy easy;
    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"http://www.google.it") );
    easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
    try {
        easy.perform();
    } catch (curl_error error) {
        // If you want to get the entire error stack we can do:
        stack<pair<string,string>> errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    return 0;
}
`````

Here's instead, the creation of an HTTPS POST login form:

`````c++
#include <iostream>
#include "curl_easy.h"
#include "curl_form.h"
// only "curl_easy.h" and "curl_form.h" if you use above submodule-way of compilation and linking

using std::cout;
using std::endl;
using curl::curl_easy;
using curl::curl_form;

int main(int argc, const char * argv[]) {
    curl_easy easy;
    curl_form form;
    
    // Create form name and content for username
    curl_form::name name(CURLFORM_COPYNAME,"user");
    curl_form::content content(CURLFORM_COPYCONTENTS,"your username");
    
    // Create form name and content for password
    curl_form::name passw(CURLFORM_COPYNAME,"passw");
    curl_form::content content_p(CURLFORM_COPYCONTENTS,"your password");
    
    try {
        // Add the two forms
        form.add(name,content);
        form.add(passw,content_p);
        easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"https://xxxxxx"));
        easy.add(curl_pair<CURLoption,bool>(CURLOPT_SSL_VERIFYPEER,false));
        easy.add(curl_pair<CURLoption,curl_form>(CURLOPT_HTTPPOST,form));
        easy.perform();
    } catch (curl_error error) {
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    return 0;
}
`````

And if we would like to put the returned content in a file? Nothing easier than:

`````c++
#include <iostream>
#include "curl_easy.h"
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;
using curl::curl_easy;

int main(int argc, const char * argv[]) {
    
    ofstream myfile;
    // Create a file
    myfile.open ("/Users/Giuseppe/Desktop/test.txt");
    // Pass it to the easy constructor and watch the content returned in that file!
    curl_easy easy(myfile);
    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"http://www.google.it") );
    easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
    try {
        easy.perform();
    } catch (curl_error error) {
        // If you want to get the entire error stack we can do:
        stack<pair<string,string>> errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    myfile.close();
    return 0;
}
`````

That's it! :)
