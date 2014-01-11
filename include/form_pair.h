//
//  form_pair.h
//  curl_wrapper
//
//  Created by Giuseppe Persico on 11/01/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef curl_wrapper_form_pair_h
#define curl_wrapper_form_pair_h

#include "http_post.h"

template<class T> class http_post::form_pair {
public:
    form_pair(CURLformoption option, T value) : option(option), value(value) {}
    const CURLformoption first() const noexcept;
    const T second() const noexcept;
private:
    const CURLformoption option;
    const T value;
};

template<typename T> inline const CURLformoption http_post::form_pair<T>::first() const noexcept {
    return this->option;
}

template<typename T> inline const T http_post::form_pair<T>::second() const noexcept {
    return this->value;
}


#endif