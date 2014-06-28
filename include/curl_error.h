//
//  curl_error.h
//  curlcpp
//
//  Created by Giuseppe Persico on 02/06/14.
//

#ifndef __curlcpp__curl_error__
#define __curlcpp__curl_error__

#include <iostream>
#include <string>
#include <exception>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::pair;
using std::vector;

namespace curl {
    /**
     * This class rapresent a custom exception for libcurl errors. 
     * If a function throws an error, its name will be added to a
     * vector (treated like a stack, because if I had used a stack,
     * to print it, I should have to remove all the elements), so
     * users can keep track of which method threw which exception.
     */
    class curl_error : public exception {
    public:
        /**
         * This constructor is used to build the error.
         */
        curl_error(const string, const string);
        /**
         * The destructor, in this case, doesen't do anything.
         */
        ~curl_error() throw();
        using exception::what;
        /**
         * Override of exception's what method, used to returns
         * the vector of errors.
         */
        const vector<pair<string,string>> what();
        /**
         * Simple method which prints the entire error stack.
         */
        void print_traceback() const;
    private:
        /**
         * The error container must be static or will be cleared
         * when an exceptions is thrown.
         */
        static vector<pair<string,string>> traceback;
    };

    // Implementation of print_traceback
    inline void curl_error::print_traceback() const {
        for (vector<pair<string,string>>::const_iterator it = curl_error::traceback.begin(); it != curl_error::traceback.end(); ++it) {
            cout<<"*** ERROR: "<<it->first<<" === FUNCTION: "<<it->second<<endl;
        }
    }
    
    // Implementation of what method.
    inline const vector<pair<string,string>> curl_error::what() {
        return curl_error::traceback;
    }
}

#endif /* defined(__curlcpp__curl_error__) */
