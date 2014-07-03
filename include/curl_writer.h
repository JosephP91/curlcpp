//
//  curl_writer.h
//  curlcpp
//
//  Created by Giuseppe Persico on 03/07/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__curl_writer__
#define __curlcpp__curl_writer__

#include <iostream>

using std::ostream;

// Let's typedef this big boy to enheance code readability.
typedef size_t (*curlcpp_writer_type)(void *, size_t, size_t, void *);

namespace curl {
    /**
     * This class allows users to specify a stream where to put the
     * output returned by libcurl functions. curl_easy class
     * will set all the necessary options to make it easy. You just have
     * to specify your stream and your writer function.
     */
    class curl_writer {
    public:
        /**
         * The default constructor will use a default stream and a default
         * writer callback to perform the operations.
         */
        curl_writer();
        /**
         * This overloaded constructor allows users to specify a stream
         * where to write, using the default writer callback.
         */
        curl_writer(ostream &);
        /**
         * This overloaed constructor allows users to specify a writer
         * callback function used specify how to write something on the
         * the default stream which is std::cout;
         */
        curl_writer(curlcpp_writer_type);
        /**
         * This overloaded constructor allows users to specify a custom
         * stream and a custom writer callback function.
         */
        curl_writer(ostream &, curlcpp_writer_type);
        /**
         * Simple getter method that returns the stream specifyed in the
         * constructor.
         */
        ostream *get_stream() const;
        /**
         * Simple getter method that returns the function specified (or not)
         * in the constructor.
         */
        curlcpp_writer_type get_function() const;
    protected:
        /**
         * Utility method used to validate the function pointer eventually
         * specified.
         */
        void set_writer_ptr(curlcpp_writer_type);
    private:
        curlcpp_writer_type _writer_ptr;
        ostream *_stream_ptr;
    };
}

#endif /* defined(__curlcpp__curl_writer__) */