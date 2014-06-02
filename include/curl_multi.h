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

namespace curl {
    class curl_multi : public curl_interface<CURLM,CURLMcode> {
    public:
        class CurlMessage {
        public:
            CurlMessage(CURLMSG message, curl_easy easy, void *whatever, CURLcode result) : message(message), easy(easy), whatever(whatever), result(result) {};
            // Returns the message
            inline const CURLMSG getMessage() const noexcept {
                return this->message;
            }
            // Returns the exit code
            inline const CURLcode getResult() const noexcept {
                return this->result;
            }
            // Returns the curl easy handler
            inline const curl_easy get_url() const noexcept {
                return this->easy;
            }
            // Returns other stuff.
            inline const void *getWhatever() const noexcept {
                return this->whatever;
            }
        private:
            const CURLMSG message;
            const curl_easy easy;
            const void *whatever;
            const CURLcode result;
        };
        curl_multi();
        curl_multi(const long);
        ~curl_multi();
        template<typename T> void add(const curl_pair<CURLMoption,T> &);
        template<typename T> void add(const vector<curl_pair<CURLMoption,T>> &);
        template<typename T> void add(const list<curl_pair<CURLMoption,T>> &);
        curl_multi &addHandle(const curl_easy &) noexcept;
        curl_multi &addHandle(const vector<curl_easy> &) noexcept;
        curl_multi &removeHandle(const curl_easy &) noexcept;
        bool perform();
        bool socketAction(curl_socket_t, int, int *);
        const vector<CurlMessage> infoRead();
        void fdSet(fd_set *, fd_set *, fd_set *, int *);
        void timeout(long *);
        void assign(curl_socket_t, void *);
        void wait(curl_waitfd [], unsigned int, int, int *);
        const int getActiveTransfers() const noexcept;
        const int getMessageQueued() const noexcept;
    protected:
        const string to_string(const CURLMcode) const noexcept;
    private:
        int message_queued;
        int active_transfers;
        vector<curl_easy> handlers;
    };
    
    // Implementation of add method
    template<typename T> void curl_multi::add(const curl_pair<CURLMoption,T> &pair) {
        CURLMcode code = curl_multi_setopt(this->get_url(),pair.first(),pair.second());
        if (code != CURLM_OK) {
            throw curl_error(this->to_string(code),__FUNCTION__);
        }
    }
    // Implementation of add overloaded method
    template<typename T> void curl_multi::add(const vector<curl_pair<CURLMoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLMoption,T> option) { this->add(option); } );
    }
    // Implementation of add overloaded method
    template<typename T> void curl_multi::add(const list<curl_pair<CURLMoption,T>> &pairs) {
        for_each(pairs.begin(),pairs.end(),[this](curl_pair<CURLMoption,T> option) { this->add(option); } );
    }
}

#endif	/* curl_multi_H */