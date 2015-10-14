/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_multi.h
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __curlcpp__curl_multi__
#define __curlcpp__curl_multi__

#include "curl_easy.h"

using curl::curl_easy;
using curl::curl_multi_exception;

namespace curl {
    /**
     * As libcurl documentation says, the multi interface offers several abilities that
     * the easy interface doesn't. They are mainly:
     * 1. Enable a "pull" interface. The application that uses libcurl decides where and
     *    when to ask libcurl to get/send data.
     * 2. Enable multiple simultaneous transfers in the same thread without making it 
     *    complicated for the application.
     * 3. Enable the application to wait for action on its own file descriptors and curl's
     *    file descriptors simultaneous easily.
    */
    class curl_multi : public curl_interface<CURLMcode> {
    public:
        /**
         * The multi interface gives users the opportunity to get information about
         * transfers. This information is wrapped in the following class. In this
         * way users can access this information in an easy and efficient way.
         * This class is nested because these messages are only sent when using the
         * multi interface.
         */
        class curl_message {
        public:
            /**
             * The attributes will be initialized with constructors parameters. With
             * this constructor we provide a fast way to build this kind of object.
             */
            curl_message(const CURLMsg *);
            /**
             * Inline getter method used to return
             * the message for a single handler.
             */
            CURLMSG get_message() const;
            /**
             * Inline getter method used to return
             * the code for a single handler.
             */
            CURLcode get_code() const;
            /**
             * Inline getter method used to return
             * other data.
             */
            const void *get_other() const;
        private:
            const CURLMSG message;
            const void *whatever;
            const CURLcode code;
        };
        /**
         * Simple default constructor. It is used to give a
         * default value to all the attributes and provide a
         * fast way to create an object of this type. It also
         * initializes the curl environment with the default
         * values.
         */
        curl_multi();
        /**
         * Overloaded constructor. Gives users the opportunity
         * to initialize the entire curl environment using custom
         * options.
         */
        explicit curl_multi(const long);
        /**
         * Copy constructor to perform a correct copy of the curl 
         * handler and attributes.
         */
        curl_multi(const curl_multi &);
        /**
         * Assignment operator. Let's apply the rule of three to
         * avoid strange situations!
         */
        curl_multi &operator=(const curl_multi &);
        /**
         * Destructor to deallocate all the resources using
         * libcurl.
         */
        ~curl_multi() NOEXCEPT;
        /**
         * This method allows users to add an option to the multi
         * handler, using an object of curl_pair type.
         */
        template<typename T> void add(const curl_pair<CURLMoption,T> &);
        /**
         * Allows users to specify a list of options for the current
         * easy handler. In this way, you can specify any iterable data
         * structure.
         */
        template<typename Iterator> void add(Iterator, const Iterator);
        /**
         * Overloaded add method. Allows users to specify an easy handler
         * to add to the multi handler, to perform more transfers at the same
         * time.
         */
        void add(const curl_easy &);
        /**
         * This method removes an easy handler from the multi handler.
         */
        void remove(const curl_easy &);
        /**
         * This method tries to obtain information about all the handlers added
         * to the multi handler.
         */
        vector<unique_ptr<curl_message>> get_info();
        /**
         * This method tries to obtain information regarding an easy handler 
         * that has been added to the multi handler.
         */
        unique_ptr<curl_message> get_info(const curl_easy &);
        /**
         * This method checks if the transfer on a curl_easy object is finished.
         */
        bool is_finished(const curl_easy &);
        /**
         * Perform all the operations. Go baby! If the performing operations
         * have finished, the method returns true. Else, returns false. Check
         * online documentation for further documentation.
         */
        bool perform();
        /**
         * This method wraps the libcurl function that reads/writes available data
         * given an action. Read the libcurl online documentation to learn more
         * about this function!
         */
        bool socket_action(const curl_socket_t, const int);
        /**
         * This method wraps the libcurl function that extracts file descriptor 
         * information from the multi handler.
         * Read the libcurl online documentation to learn more about this function.
         */
        void set_descriptors(fd_set *, fd_set *, fd_set *, int *);
        /**
         * This function polls on all file descriptors used by the curl easy handles
         * contained in the given multi handle set.
         */
        void wait(struct curl_waitfd [], const unsigned int, const int, int *);
        /**
         * This function creates an association in the multi handle between the given
         * socket and a private pointer of the application.
         */
        void assign(const curl_socket_t, void *); 
        /**
         * If you are using the libcurl multi interface you should call this method
         * to figure out how long your application should wait for socket actions
         * - at most - before proceeding.
         */
        void timeout(long *);
        /**
         * Inline getter method used to return the currently active transfers.
         */
        int get_active_transfers() const NOEXCEPT;
        /**
         * Inline getter method used to return the currently queued messages.
         */
        int get_message_queued() const NOEXCEPT;
    private:
        int message_queued;
        int active_transfers;
        CURLM *curl;
    };
    
    // Implementation of add method
    template<typename T> void curl_multi::add(const curl_pair<CURLMoption,T> &pair) {
        const CURLMcode code = curl_multi_setopt(this->curl,pair.first(),pair.second());
        if (code != CURLM_OK) {
            throw curl_multi_exception(code,__FUNCTION__);
        }
    }
    
    // Implementation of overloaded add method.
    template<typename Iterator> void curl_multi::add(Iterator begin, const Iterator end) {
        for (; begin != end; ++begin) {
            this->add(*begin);
        }
    }

    // Implementation of get_active_transfers method.
    inline int curl_multi::get_active_transfers() const NOEXCEPT {
        return this->active_transfers;
    }

    // Implementation of get_message_queued method.
    inline int curl_multi::get_message_queued() const NOEXCEPT {
        return this->active_transfers;
    }

    // Implementation of curl_message get_message method.
    inline CURLMSG curl_multi::curl_message::get_message() const {
        return this->message;
    }

    // Implementation of curl_message get_code method.
    inline CURLcode curl_multi::curl_message::get_code() const {
        return this->code;
    }

    // Implementation of curl_message get_other method.
    inline const void *curl_multi::curl_message::get_other() const {
        return this->whatever;
    }
}

#endif	/* defined(__curlcpp__curl_multi__) */
