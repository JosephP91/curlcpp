/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 - Qiangqiang Wu
 * File - curl_option.h
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

#include <type_traits>
#include <string>
#include "curl_pair.h"

namespace curl {
    namespace detail {
        template <class V>
        struct value_wrapper_t {
            using type = V;
        };

        template <size_t N>
        struct value_wrapper_t<const char[N]> {
            using type = std::string;
        };

        template <size_t N>
        struct value_wrapper_t<const wchar_t[N]> {
            using type = std::string;
        };

        template <class V>
        using Value_t = typename value_wrapper_t<V>::type;
    }  // of namespace detail

    template <class V>
    inline curl_pair<CURLoption, detail::Value_t<V>> 
        make_option(const CURLoption opt, const V& val)
    {
        return curl_pair<CURLoption, detail::Value_t<V>>(opt, val);
    }
    
    template <class V>
    inline curl_pair<CURLformoption, detail::Value_t<V>>
        make_formoption(const CURLformoption opt, const V& val)
    {
        return curl_pair<CURLformoption, detail::Value_t<V>>(opt, val);
    }
}  // of namespace curl