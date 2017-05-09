curlcpp
=======

An object-oriented C++ wrapper for cURL tool

If you want to know a bit more about cURL and libcurl, you should go on the official website http://curl.haxx.se/

Please note: this requires C++11. For Mac users, you will probably need to update your compiler, since xCode provides a dated version.

Compile and link
================

Standalone
----------

```bash
cd build
cmake ..
make # -j2
```

**Note:** cURL >= 7.34 is required.

Then add `<curlcpp root>/build/src/` to your library path and `<curlcpp root>/include/` to your include path.

When linking, link against `curlcpp` (e.g.: g++ -std=c++11 example.cpp -o example -lcurlcpp -lcurl).
Or if you want run from terminal,

g++ -std=c++11 example.cpp -L/home/arun/path/to/build/src/ -I/home/arun/path/to/include/ -lcurlcpp -lcurl 


Submodule
---------

When using a git submodule and CMake-buildsystem, add the following lines to your `CMakeLists.txt`:

```
ADD_SUBDIRECTORY(ext/curlcpp) # Change `ext/curlcpp` to a directory according to your setup
INCLUDE_DIRECTORIES(${CURLCPP_SOURCE_DIR}/include)
```

Biicode support
===============

Yes, it's avaiable thanks to @qqiangwu! :)

Simple usage example
====================

Here are some usage examples. You will find more examples in the test folder!

Here's an example of a simple HTTP request to get google web page, using the curl_easy interface:

`````c++
#include "curl_easy.h"
#include "curl_exception.h"

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

int main(int argc, const char **argv) {
    curl_easy easy;
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
    return 0;
}
`````

If you want to get information about the current curl session, you could do:

`````c++
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
    auto x = easy.get_info<CURL_CONTENT_TYPE>();
    // Print out content type
    std::cout << x.get() << std::endl;
    return 0;
}
`````

Here's instead, the creation of an HTTPS POST login form:

`````c++
#include <string>

#include "curl_easy.h"
#include "curl_pair.h"
#include "curl_form.h"
#include "curl_exception.h"

using std::string;

using curl::curl_form;
using curl::curl_easy;
using curl::curl_pair;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

int main(int argc, const char * argv[]) {
    curl_form form;
    curl_easy easy;
    // Forms creation
    curl_pair<CURLformoption,string> name_form(CURLFORM_COPYNAME,"user");
    curl_pair<CURLformoption,string> name_cont(CURLFORM_COPYCONTENTS,"you username here");
    curl_pair<CURLformoption,string> pass_form(CURLFORM_COPYNAME,"passw");
    curl_pair<CURLformoption,string> pass_cont(CURLFORM_COPYCONTENTS,"your password here");
    
    try {
        // Form adding
        form.add(name_form,name_cont);
        form.add(pass_form,pass_cont);
        
        // Add some options to our request
        easy.add<CURLOPT_URL>("your url here");
        easy.add<CURLOPT_SSL_VERIFYPEER>(false);
        easy.add<CURLOPT_HTTPPOST>(form.get());
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
    }
    return 0;
}
`````

And if we would like to put the returned content in a file? Nothing easier than:

`````c++
#include <iostream>
#include <ostream>
#include <fstream>

#include "curl_easy.h"
#include "curl_ios.h"
#include "curl_exception.h"

using std::cout;
using std::endl;
using std::ostream;
using std::ofstream;

using curl::curl_easy;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

int main(int argc, const char * argv[]) {
    // Create a file
    ofstream myfile;
    myfile.open ("Path to your file");
    
    // Create a curl_ios object to handle the stream
    curl_ios<ostream> writer(myfile);
    // Pass it to the easy constructor and watch the content returned in that file!
    curl_easy easy(writer);
    
    // Add some option to the easy handle
    easy.add<CURLOPT_URL>("http://www.google.it");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    try {
        // Execute the request
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
    }
    myfile.close();
    return 0;
}
`````

Not interested in files? So let's put the request's output in a variable!

`````c++
#include <iostream>
#include <ostream>

#include "curl_easy.h"
#include "curl_form.h"
#include "curl_ios.h"
#include "curl_exception.h"

using std::cout;
using std::endl;
using std::ostringstream;

using curl::curl_easy;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

int main() {
    // Create a stringstream object
    ostringstream str;
    // Create a curl_ios object, passing the stream object.
    curl_ios<ostringstream> writer(str);
    
    // Pass the writer to the easy constructor and watch the content returned in that variable!
    curl_easy easy(writer);
    // Add some option to the easy handle
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
    // Let's print the stream content.
    cout<<str.str()<<endl;
    return 0;
}
`````

I have implemented a sender and a receiver to make it easy to use send/receive without handling
buffers. For example, a very simple send/receiver would be:

`````c++
#include <iostream>
#include <string>

#include "curl_easy.h"
#include "curl_form.h"
#include "curl_pair.h"
#include "curl_receiver.h"
#include "curl_exception.h"
#include "curl_sender.h"

using std::cout;
using std::endl;
using std::string;

using curl::curl_form;
using curl::curl_easy;
using curl::curl_sender;
using curl::curl_receiver;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

int main(int argc, const char * argv[]) {
    // Simple request
    string request = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";
    // Creation of easy object.
    curl_easy easy;
    try {
        easy.add<CURLOPT_URL>("http://example.com");
        // Just connect
        easy.add<CURLOPT_CONNECT_ONLY>(true);
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
    }
    
    // Creation of a sender. You should wait here using select to check if socket is ready to send.
    curl_sender<string> sender(easy);
    sender.send(request);
    // Prints che sent bytes number.
    cout<<"Sent bytes: "<<sender.get_sent_bytes()<<endl;
    for(;;) {
        // You should wait here to check if socket is ready to receive
        try {
            // Create a receiver
            curl_receiver<char,1024> receiver;
            // Receive the content on the easy handler
            receiver.receive(easy);
            // Prints the received bytes number.
            cout<<"Receiver bytes: "<<receiver.get_received_bytes()<<endl;
        } catch (curl_easy_exception error) {
            // If any errors occurs, exit from the loop
            break;
        }
    }
    return 0;
}
`````
