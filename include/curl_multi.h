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

#include <memory>
#include <vector>
#include <unordered_map>

#include "curl_easy.h"

#define CURLCPP_DEFINE_OPTION(opt, value_type)\
    template <> struct moption_t<opt> {\
        using type = value_type;\
    }

namespace curl {
    namespace detail {
        template <CURLMoption>
        struct moption_t;

        template <CURLMoption opt>
        using MOption_type = typename moption_t<opt>::type;

        /*
         * If a pipelined connection is currently processing a chunked
         * (Transfer-encoding: chunked) request with a current chunk length
         * larger than CURLMOPT_CHUNK_LENGTH_PENALTY_SIZE, that pipeline will
         * not be considered for additional requests.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_CHUNK_LENGTH_PENALTY_SIZE, long);

        /*
         * If a pipelined connection is currently processing a request with a
         * Content-Length larger than this
         * CURLMOPT_CONTENT_LENGTH_PENALTY_SIZE, that pipeline will then not be
         * considered for additional requests.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_CONTENT_LENGTH_PENALTY_SIZE, long);

        /*
         * The set number will be used as the maximum amount of simultaneously
         * open connections that libcurl may keep in its connection cache after
         * completed use. By default libcurl will enlarge the size for each
         * added easy handle to make it fit 4 times the number of added easy
         * handles.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_MAXCONNECTS, long);

        /*
         * The set number will be used as the maximum amount of simultaneously
         * open connections to a single host (a host being the same as a host
         * name + port number pair). For each new session to a host, libcurl
         * will open a new connection up to the limit set by
         * CURLMOPT_MAX_HOST_CONNECTIONS.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_MAX_HOST_CONNECTIONS, long);

        /*
         * The set max number will be used as the maximum amount of outstanding
         * requests in a pipelined connection. Only used if pipelining is
         * enabled.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_MAX_PIPELINE_LENGTH, long);

        /*
         * Pass a long for the amount. The set number will be used as the
         * maximum number of simultaneously open connections in total using
         * this multi handle.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_MAX_TOTAL_CONNECTIONS, long);

        /*
         * Set the bits parameter to 1 to make libcurl use HTTP pipelining for
         * HTTP/1.1 transfers done using this multi handle, as far as possible.
         * This means that if you add a second request that can use an already
         * existing connection, the second request will be "piped" on the same
         * connection rather than being executed in parallel.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_PIPELINING, long);

        /*
         * Pass a servers array of char *, ending with a NULL entry. This is a
         * list of server types prefixes (in the Server: HTTP header) that are
         * blacklisted from pipelining, i.e server types that are known to not
         * support HTTP pipelining. The array is copied by libcurl.
         *
         * Note that the comparison matches if the Server: header begins with
         * the string in the blacklist, i.e "Server: Ninja 1.2.3" and "Server:
         * Ninja 1.4.0" can both be blacklisted by having "Ninja" in the
         * backlist.
         *
         * Pass a NULL pointer to clear the blacklist.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_PIPELINING_SERVER_BL, char**);

        /*
         * Pass a hosts array of char *, ending with a NULL entry. This is a
         * list of sites that are blacklisted from pipelining, i.e sites that
         * are known to not support HTTP pipelining. The array is copied by
         * libcurl.
         *
         * Pass a NULL pointer to clear the blacklist.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_PIPELINING_SITE_BL, char**);

        /*
         * A data pointer to pass to the socket callback set with the
         * CURLMOPT_SOCKETFUNCTION option.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_SOCKETDATA, void*);

        /*
         * The callback gets status updates with changes since the previous
         * time the callback was called.  See curl_multi_socket_action for more
         * details on how the callback is used and should work.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_SOCKETFUNCTION, int(*)(CURL* easy, curl_socket_t socket, int action, void* userp, void* socketp));

        /*
         * A data pointer to pass to the timer callback set with the
         * CURLMOPT_TIMERFUNCTION option.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_TIMERDATA, void*);

        /*
         * Your callback function timer_callback should install a non-repeating
         * timer with an interval of timeout_ms.
         */
        CURLCPP_DEFINE_OPTION(CURLMOPT_TIMERFUNCTION, int(*)(CURLM* multi, long timeout_ms, void* userp));
    }

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
            explicit curl_message(const CURLMsg *);
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
        explicit curl_multi(long globalOptions);
        /**
         * Move constructor which moves internal data to another object.
         */
        curl_multi(curl_multi&&) NOEXCEPT;
        /**
         * Move assignment operator which moves internal data to another object.
         */
        curl_multi& operator=(curl_multi&&) NOEXCEPT;
        /**
         * Destructor to deallocate all the resources using
         * libcurl.
         */
        ~curl_multi() NOEXCEPT override;
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
        template<typename Iterator> void add(Iterator, Iterator);

        /**
        * Allows users to specify an option for the current multi handler,
        * specify an option statically and enforce its corresponding type.
        */
        template <CURLMoption Opt> void add(detail::MOption_type<Opt>);

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
        std::vector<std::unique_ptr<curl_message>> get_info();
        /**
         * This method tries to obtain information regarding an easy handler 
         * that has been added to the multi handler.
         */
        std::unique_ptr<curl_message> get_info(const curl_easy &);
        /**
         * This method checks if the transfer on a curl_easy object is finished.
         */
        bool is_finished(const curl_easy &);
        /**
         * This method returhns the next finished curl_easy (if there is), otherwise nullptr is returned
         */
        curl_easy* get_next_finished();
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
        bool socket_action(curl_socket_t, int);
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
        void wait(struct curl_waitfd [], unsigned int, int, int *);
        /**
         * This function creates an association in the multi handle between the given
         * socket and a private pointer of the application.
         */
        void assign(curl_socket_t, void *);
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

        /**
         * Simple getter method used to return the multi handle.
         */
        CURLM *get_curl() const;
    private:
        struct multi_deleter {
            void operator()(CURLM* ptr) const;
        };

        using multi_ptr = std::unique_ptr<CURLM, multi_deleter>;

        int message_queued;
        int active_transfers;
        multi_ptr curl;
        std::unordered_map<CURL*, curl_easy*> handles;
    };
    
    // Implementation of add method
    template<typename T> void curl_multi::add(const curl_pair<CURLMoption,T> &pair) {
        const CURLMcode code = curl_multi_setopt(this->curl.get(),pair.first(),pair.second());
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

    // Implementation of overloaded add method.
    template <CURLMoption Opt> void curl_multi::add(detail::MOption_type<Opt> val) {
        const auto code = curl_multi_setopt(this->curl.get(), Opt, val);
        if (code != CURLM_OK) {
            throw curl_multi_exception(code, __FUNCTION__);
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

#undef CURLCPP_DEFINE_OPTION
#endif	/* defined(__curlcpp__curl_multi__) */
