curlcpp
=======

An object-oriented C++ wrapper for cURL tool

If you want to know a bit more about cURL and libcurl, you should go on the official website http://curl.haxx.se/

Donate
======

Help me to improve this project!

<a href="https://www.bitcoinqrcodemaker.com/pay/?type=2&amp;style=bitcoin&amp;color=1&amp;border=4&amp;address=bc1qn99uh5a7h7mezd9j3grrc2hrr376n25z5dk8er" target="_blank"><img src="https://www.bitcoinqrcodemaker.com/donate_button.png" border="0" width="150" height="36" alt="Donate button" title="Donate" /></a>



Compile and link manually
=========================

Standalone (static library)
----------

```bash
cd build
cmake ..
make
```

Standalone (dynamic/shared library)
----------

```bash
cd build
cmake .. -DBUILD_SHARED_LIBS=SHARED
make
```

**Note:** cURL >= 7.34.0 is required.

When linking curlcpp to your application don't forget to also link `curl`. Example:

```bash
g++ -std=c++11 example.cpp -I/usr/local/include/curlcpp/ -lcurlcpp -lcurl 
```

Submodule
---------

When using a git submodule and CMake-buildsystem, add the following lines to your `CMakeLists.txt`:

```
ADD_SUBDIRECTORY(ext/curlcpp) # Change `ext/curlcpp` to a directory according to your setup
INCLUDE_DIRECTORIES(${CURLCPP_SOURCE_DIR}/include)
```


Install via Homebrew
====================

curlcpp is now available also via homebrew package manager:

```bash
brew install curlcpp
```


Examples
========

Here are some usage examples. You will find more examples in the test folder!

Here's an example of a simple HTTP request to get google web page, using the curl_easy interface:

* ### Simple request

`````c++
#include "curlcpp/curl_easy.h"

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

/**
 * This example shows how to make a simple request with curl.
 */
int main() {
    // Easy object to handle the connection.
    curl_easy easy;

    // Add some options.
    easy.add<CURLOPT_URL>("http://<your_url_here>");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();
    } catch (curl_easy_exception &error) {
    	// If you want to print the last error.
        std::cerr<<error.what()<<std::endl;
    }
    return 0;
}
`````

* ### Extract session information

If you want to get information about the current curl session, you could do:

`````c++
#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_ios.h"
#include "curlcpp/curl_exception.h"

using std::ostringstream;

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_ios;

/**
 * This example shows how to use the easy interface and obtain 
 * information about the current session.
 */
int main(int argc, const char **argv) {
    // Let's declare a stream
    ostringstream stream;

    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(stream);

    // Declaration of an easy object
    curl_easy easy(ios);

    // Add some option to the curl_easy object.
    easy.add<CURLOPT_URL>("http://<your_url_here>");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();

		// Retrieve information about curl current session.
		auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();

		/**
		 * get_info returns a curl_easy_info object. With the get method we retrieve
		 * the std::pair object associated with it: the first item is the return code of the
		 * request. The second is the element requested by the specified libcurl macro.
		 */
		std::cout<<x.get()<<std::endl;

    } catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;

		// If you want to print the entire error stack you can do
		error.print_traceback();
    }
    return 0;
}
`````

* ### HTTP Post

Here's instead, the creation of an HTTPS POST login form:

`````c++
#include <string>

#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_pair.h"
#include "curlcpp/curl_form.h"
#include "curlcpp/curl_exception.h"

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
        easy.add<CURLOPT_URL>("http://<your_url_here>");
        easy.add<CURLOPT_SSL_VERIFYPEER>(false);
        easy.add<CURLOPT_HTTPPOST>(form.get());
        // Execute the request.
        easy.perform();

    } catch (curl_easy_exception &error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
    }
    return 0;
}
`````

* ### Store response in a file

And if we would like to put the returned content in a file? Nothing easier than:

`````c++
#include <iostream>
#include <ostream>
#include <fstream>

#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_ios.h"
#include "curlcpp/curl_exception.h"

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
    myfile.open ("/path/to/your/file");
    
    // Create a curl_ios object to handle the stream
    curl_ios<ostream> writer(myfile);
    // Pass it to the easy constructor and watch the content returned in that file!
    curl_easy easy(writer);
    
    // Add some option to the easy handle
    easy.add<CURLOPT_URL>("http://<your_url_here>");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    try {
        // Execute the request
        easy.perform();

    } catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;

		// If you want to print the entire error stack you can do
		error.print_traceback();
    }
    myfile.close();
    return 0;
}
`````

* ### Store response in a variable

Not interested in files? So let's put the request's output in a variable!

`````c++
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

int main() {
    // Create a stringstream object
    ostringstream str;
    // Create a curl_ios object, passing the stream object.
    curl_ios<ostringstream> writer(str);
    
    // Pass the writer to the easy constructor and watch the content returned in that variable!
    curl_easy easy(writer);
    // Add some option to the easy handle
    easy.add<CURLOPT_URL>("http://<your_url_here>");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();

        // Let's print the stream content
        cout<<str.str()<<endl;

    } catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;

		// If you want to print the entire error stack you can do
		error.print_traceback();
    }
    return 0;
}
`````

* ### Sender/Receiver

I have implemented a sender and a receiver to make it easy to use send/receive without handling
buffers. For example, a very simple send/receiver would be:

`````c++
#include <iostream>
#include <string>

#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_form.h"
#include "curlcpp/curl_pair.h"
#include "curlcpp/curl_receiver.h"
#include "curlcpp/curl_exception.h"
#include "curlcpp/curl_sender.h"

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
        easy.add<CURLOPT_URL>("http://<your_url_here>");
        // Just connect
        easy.add<CURLOPT_CONNECT_ONLY>(true);
        // Execute the request.
        easy.perform();

    } catch (curl_easy_exception &error) {
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
            curl_receiver<char, 1024> receiver;
            // Receive the content on the easy handler
            receiver.receive(easy);
            // Prints the received bytes number.
            cout<<"Receiver bytes: "<<receiver.get_received_bytes()<<endl;

        } catch (curl_easy_exception &error) {
            // If any errors occur, exit from the loop
            break;
        }
    }
    return 0;
}
`````

* ### Multi interface example

The following example shows ho to use the curl MULTI interface.

I have implemented a sender and a receiver to make it easy to use send/receive without handling
buffers. For example, a very simple send/receiver would be:

`````c++
#include <iostream>
#include <ostream>

#include "curlcpp/curl_easy.h"
#include "curlcpp/curl_multi.h"
#include "curlcpp/curl_ios.h"

using curl::curl_easy;
using curl::curl_multi;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

/**
 * This example shows how to make multiple requests
 * using curl_multi interface.
 */
int main() {
    std::vector<std::string> urls;
    urls.emplace_back("https://google.com");
    urls.emplace_back("https://facebook.com");
    urls.emplace_back("https://linkedin.com");

    // Create a vector of curl easy handlers.
    std::vector<curl_easy> handlers;

    // Create a vector of curl streams.
    std::vector<curl_ios<std::ostringstream>> streams;

    // Create the curl easy handler and associated the streams with it.
    for (const auto & url : urls) {
        auto *output_stream = new std::ostringstream;
        curl_ios<std::ostringstream> curl_stream(*output_stream);

        curl_easy easy(curl_stream);
        easy.add<CURLOPT_URL>(url.c_str());
        easy.add<CURLOPT_FOLLOWLOCATION>(1L);

        streams.emplace_back(curl_stream);
        handlers.emplace_back(easy);
    }

    // Create a map of curl pointers to output streams.
    std::unordered_map<CURL*, curl_ios<std::ostringstream>*> easy_streams;
    for (int i = 0; i < handlers.size(); ++i) {
        easy_streams[handlers.at(i).get_curl()] = (curl_ios<std::ostringstream>*)&streams.at(i);
    }

    // Add all the handlers to the curl multi object.
    curl_multi multi;
    multi.add(handlers);

    try {
        // Start the transfers.
        multi.perform();

        // Until there are active transfers, call the perform() API.
        while (multi.get_active_transfers()) {
            multi.perform();

            // Extracts the first finished request.
            std::unique_ptr<curl_multi::curl_message> message = multi.get_next_finished();
            if (message != nullptr) {
                const curl_easy *handler = message->get_handler();

                // Get the stream associated with the curl easy handler.
                curl_ios<std::ostringstream> stream_handler = *easy_streams[handler->get_curl()];

                auto content = stream_handler.get_stream()->str();
                auto url = handler->get_info<CURLINFO_EFFECTIVE_URL>();
                auto response_code = handler->get_info<CURLINFO_RESPONSE_CODE>();
                auto content_type = handler->get_info<CURLINFO_CONTENT_TYPE>();
                auto http_code = handler->get_info<CURLINFO_HTTP_CODE>();

                std::cout << "CODE: " << response_code.get()
                          << ", TYPE: " << content_type.get()
                          << ", HTTP_CODE: " << http_code.get()
                          << ", URL: " << url.get()
                          << ", CONTENT: " << content.substr(0, 10) + " ... "
                          << std::endl;
            }
        }

        // Free the memory allocated for easy streams.
        for (auto stream : streams) {
            delete stream.get_stream();
        }

    } catch (curl_easy_exception &error) {
        // If you want to print the last error.
        std::cerr<<error.what()<<std::endl;
    }
    return 0;
}
`````
