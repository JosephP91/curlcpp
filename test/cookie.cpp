#include <iostream>

#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_cookie.h"
#include "curl_ios.h"
#include "cookie_datetime.h"

using std::ostringstream;

using curl::cookie;
using curl::curl_header;
using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curl_cookie;
using curl::curlcpp_cookies;
using curl::curl_ios;
using curl::cookie_date;
using curl::cookie_time;
using curl::cookie_datetime;

/**
 * This example shows to how to set and get cookies in a
 * simple curl request.
 */

int main() {
    // Let's declare a stream
    ostringstream stream;
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(stream);

    // Easy object to handle the connection, url and verbosity level.
    curl_easy easy(ios);
    easy.add<CURLOPT_URL>("http://example.com");

    // Let's create a cookie which expires at Mon, 27-03-2016 20:30:30 GMT
    cookie ck;
    cookie_date date(curl::weekdays::MONDAY,27,curl::months::MARCH,2016);
    cookie_time time(20,30,30);
    cookie_datetime datetime(time,date);

    ck.set_name("nomecookie");
    ck.set_value("valorecookie");
    ck.set_path("/");
    ck.set_domain(".example.com");
    ck.set_datetime(datetime);

    // Create a cookie object and add the previously created cookie.
    curl_cookie cookie_object(easy);
    cookie_object.set(ck);

    try {
        easy.perform();

        // Retrieve all the cookies for the example.com (as a vector)
        curlcpp_cookies cookies = cookie_object.get();
        // Delete all the memory helded cookies.
        cookie_object.erase();

		// Print them all!
		for (const auto& cook : cookies) {
			std::cout<<cook<<std::endl;
		}

    } catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;

		// If you want to print the entire error stack you can do.
		error.print_traceback();
    }
    return 0;
}
