/* 
 * File:   curl_multi.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 11:02 PM
 */

#include <algorithm>
#include "curl_multi.h"

using std::for_each;
using curl::curl_multi;

// Implementation of constructor.
curl_multi::curl_multi() : curl_interface() {
    this->curl = curl_multi_init();
    this->active_transfers = 0;
    this->message_queued = 0;
}

// Implementation of overloaded constructor.
curl_multi::curl_multi(const long flag) : curl_interface(flag) {
    curl_multi();
}

// Implementation of copy constructor to respect the rule of three.
curl_multi::curl_multi(const curl_multi &multi) : message_queued(multi.message_queued), active_transfers(multi.active_transfers), curl(curl_multi_init()) {
    // ... nothing to do here ...
}

// Implementation of assignment operator to perform deep copy.
curl_multi &curl_multi::operator=(const curl_multi &multi) {
    if (this == &multi) {
        return *this;
    }
    this->curl = curl_multi_init();
    this->message_queued = multi.message_queued;
    this->active_transfers = multi.active_transfers;
    return *this;
}

// Implementation of destructor.
curl_multi::~curl_multi() noexcept{
    curl_multi_cleanup(this->curl);
}

// Implementation of get_active_transfers method.
const int curl_multi::get_active_transfers() const noexcept {
    return this->active_transfers;
}

// Implementation of get_message_queued method.
const int curl_multi::get_message_queued() const noexcept {
    return this->message_queued;
}

// Implementation of perform method.
bool curl_multi::perform() {
    const CURLMcode code = curl_multi_perform(this->curl,&this->active_transfers);
    if (code == CURLM_CALL_MULTI_PERFORM) {
        return false;
    }
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
    return true;
}

// Implementation of set_fd method.
void curl_multi::set_fd(fd_set *read, fd_set *write, fd_set *exec, int *max_fd) {
    const CURLMcode code = curl_multi_fdset(this->curl,read,write,exec,max_fd);
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of timeout method.
void curl_multi::timeout(long *timeout) {
    const CURLMcode code = curl_multi_timeout(this->curl,timeout);
    if (code != CURLM_OK) {
        throw curl_error(this->to_string(code),__FUNCTION__);
    }
}

// Implementation of errorto_string method
const string curl_multi::to_string(const CURLMcode code) const noexcept {
    return string(curl_multi_strerror(code));
}