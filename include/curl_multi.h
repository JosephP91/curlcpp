/* 
 * File:   curl_multi.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 11:02 PM
 */

#ifndef curl_multi_H
#define	curl_multi_H

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
         * The multi interface gives users the opportunity to get informations about
         * transfers. These informations are wrapped in the following class. In this
         * way users can access to these informations in an easy and efficiently way.
         * This class is nested because these messages have sense just when using the
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
            const CURLMSG get_message() const;
            /**
             * Inline getter method used to return
             * the code for a single handler.
             */
            const CURLcode get_code() const;
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
         * initialize the curl environment with the default
         * values.
         */
        curl_multi();
        /**
         * Overloaded constructor. Gives users the opportunity
         * to initialize the entire curl environment using customs
         * options.
         */
        explicit curl_multi(const long);
        /**
         * Copy constuctor to perform a correct copy of the curl 
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
        ~curl_multi() noexcept;
        /**
         * This method allows users to add an option to the multi
         * handler, using an object of curl_pair type.
         */
        template<typename T> void add(const curl_pair<CURLMoption,T> &);
        /**
         * Overloaded add method. Allows users to specify a vector of
         * options to add to the multi handler.
         */
        template<typename T> void add(const vector<curl_pair<CURLMoption,T>> &);
        /**
         * Overloaded add method. Allows users to specify a list of options
         * to add to the multi handler.
         */
        template<typename T> void add(const list<curl_pair<CURLMoption,T>> &);
        /**
         * Overloaded add method. Allows users to specify an easy handler
         * to add to the multi handler, to perform more transfers at the same
         * time.
         */
        void add(const curl_easy &);
        /**
         * Overloaded add method. Allows users to specify a vector of easy handlers
         * to add to the multi handler, to perform more transfers at the same time.
         */
        void add(const vector<curl_easy> &);
        /**
         * Overloaded add method. Allows users to specify a list of easy handlers
         * to add to the multi handler, to perform more transfers at the samee time.
         */
        void add(const list<curl_easy> &);
        /**
         * This method allows to remove an easy handler from the multi handler.
         */
        void remove(const curl_easy &);
        /**
         * This method tries to obtain informations regarding an easy handler in 
         * particular, that has been added to the multi handler. 
         */
        unique_ptr<curl_message> get_info(const curl_easy &);
        /**
         * This method checks if the transfer on a curl_easy object is finished.
         */
        bool is_finished(const curl_easy &);
        /**
         * Perform all the operations. Go baby!
         */
        bool perform();
        /**
         * This method wraps the libcurl function that reads/writes available data
         * given an action. Read the libcurl online documentation to learn more
         * about this function!
         * TODO I would like to wrap curl_socket_t, but I don't know ....
         */
        bool socket_action(const curl_socket_t, const int);
        /**
         * This method wraps the libcurl function that extracts file descriptor 
         * information from the multi handler.
         * Read the libcurl online documentation to learn more about this function.
         * TODO I would like to wrap fd_set in curl_file_descriptor. We'll see ...
         */
        void set_fd(fd_set *, fd_set *, fd_set *, int *);
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
         * If you are using the libcurl multi interface your should call this method
         * to figure out how long your application should wait for socket actions
         * - at most - before proceeding.
         */
        void timeout(long *);
        /**
         * Inline getter method used to return the currently active transfers.
         */
        int get_active_transfers() const noexcept;
        /**
         * Inline getter method used to return the currently queued messages.
         */
        int get_message_queued() const noexcept;
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
    
    // Implementation of add overloaded method
    template<typename T> void curl_multi::add(const vector<curl_pair<CURLMoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLMoption,T> option) {
            this->add(option);
        });
    }
    
    // Implementation of add overloaded method
    template<typename T> void curl_multi::add(const list<curl_pair<CURLMoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLMoption,T> option) {
            this->add(option);
        });
    }

    // Implementation of get_active_transfers method.
    inline int curl_multi::get_active_transfers() const noexcept {
        return this->active_transfers;
    }

    // Implementation of get_message_queueed method.
    inline int curl_multi::get_message_queued() const noexcept {
        return this->active_transfers;
    }

    // Implementation of curl_message get_message method.
    inline const CURLMSG curl_multi::curl_message::get_message() const {
        return this->message;
    }

    // Implementation of curl_message get_code method.
    inline const CURLcode curl_multi::curl_message::get_code() const {
        return this->code;
    }

    // Implementation of curl_message get_other method.
    inline const void *curl_multi::curl_message::get_other() const {
        return this->whatever;
    }
}

#endif	/* curl_multi_H */
