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
	urls.emplace_back("https://<website1>.com");
	urls.emplace_back("https://<website2>.com");
	urls.emplace_back("https://<website3>.com");
	urls.emplace_back("https://<website4>.com");
	urls.emplace_back("https://<website5>.com");
	urls.emplace_back("https://<website6>.com");
	urls.emplace_back("https://<website7>.com");

	// Create a vector of ostringstreams. In this way the request output is not printed on stdout
	std::vector<curl_ios<std::ostringstream >> streams;
	for (int i = 0; i < urls.size(); ++i) {
		std::ostringstream stream;
		streams.emplace_back(curl_ios<std::ostringstream>(stream));
	}

	// Create a vector of easy handlers.
	std::vector<curl_easy> handlers;
	for (int i = 0; i < urls.size(); ++i) {
		curl_easy easy(streams.at(i));
		easy.add<CURLOPT_URL>(urls.at(i).c_str());
		easy.add<CURLOPT_FOLLOWLOCATION>(1L);

		handlers.emplace_back(easy);
	}

	// Add easy handlers to curl_multi object.
	curl::curl_multi multi;
	for (int i = 0; i < urls.size(); ++i) {
		multi.add(handlers.at(i));
	}

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
				auto response_code = handler->get_info<CURLINFO_RESPONSE_CODE>();
				auto content_type = handler->get_info<CURLINFO_CONTENT_TYPE>();
				auto http_code = handler->get_info<CURLINFO_HTTP_CODE>();

				std::cout << "CODE: " << response_code.get()
						<< ", TYPE: " << content_type.get()
						<< ", HTTP_CODE: " << http_code.get() << std::endl;
			}
		}

	} catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;
	}
	return 0;
}