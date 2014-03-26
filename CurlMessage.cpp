/* 
 * File:   CurlMessage.cpp
 * Author: Giuseppe
 * 
 * Created on March 25, 2014, 11:08 PM
 */

#include "CurlMessage.h"

using curl::CurlMulti;

const CURLMSG CurlMulti::CurlMessage::getMessage() const noexcept {
    return this->message;
}

const CurlEasy CurlMulti::CurlMessage::getCurl() const noexcept {
    return this->curl;
}

const void *CurlMulti::CurlMessage::getWhatever() const noexcept {
    return this->whatever;
}

const CURLcode CurlMulti::CurlMessage::getResult() const noexcept {
    return this->result;
}

