/* 
 * File:   curl_header.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:45 PM
 */

#ifndef curl_header_H
#define	curl_header_H

#include <string>
#include <initializer_list>
#include <curl/curl.h>

using std::string;
using std::initializer_list;

namespace curl {
    /**
     * This class rapresent a generic header. It allows user to add
     * headers without caring about deallocation of resources.
     */
    class curl_header {
    public:
        /**
         * The default constructor will initialize the headers list
         * with nullptr.
         */
        curl_header();
        /**
         * Overloaded constructor that allows users to initialize the
         * headers list with a list of values.
         */
        curl_header(initializer_list<string>);
        /**
         * Copy constructor. Performs a deep copy of the headers list.
         */
        curl_header(const curl_header &);
        /**
         * Assignment operator to perform assignment between object of
         * this class type.
         */
        curl_header &operator=(const curl_header &);
        /**
         * The destructor will deallocate the resources used to handle
         * the headers list.
         */
        ~curl_header() noexcept;
        /**
         * This method allows users to add a header as string.
         */
        void add(const string);
        /**
         * This method allows users to add headers specifying an iterable
         * data structure containing the headers to add.
         */
        template<typename Iterator> void add(Iterator, const Iterator);
        /**
         * Simple getter method that returns the pointer to the headers
         * list.
         */
        const struct curl_slist *get() const;
    private:
        int size;
        struct curl_slist *headers;
    };

    // Implementation of get method.
    inline const struct curl_slist *curl_header::get() const {
        return this->headers;
    }

    // Implementation of copy constructor.
    inline curl_header::curl_header(const curl_header &header) : headers(nullptr) {
        *this = header;
    }
    
    // Implementation of overloaded add method.
    template<typename Iterator> void curl_header::add(Iterator begin, const Iterator end) {
        for (; begin != end; ++begin) {
            this->add(*begin);
        }
    }
}

#endif	/* curl_header_H */