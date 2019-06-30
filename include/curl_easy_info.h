/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_easy_info.h
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

#ifndef curl_easy_info_h
#define curl_easy_info_h

#include <vector>
#include <string>
#include <utility>

namespace curl {
    /**
     * This object contains a pair which contains curl easy get_info result.
     */
    template<typename T> class curl_easy_info {
    public:
        explicit curl_easy_info(T pointer) : _pointer(pointer) {}

        T get() const {
            return _pointer;
        }
    private:
        T _pointer;
    };
    
    /**
     * Template specialization for char *
     */
    template<> class curl_easy_info<char *> {
    public:
        explicit curl_easy_info(char *pointer) : _pointer(pointer) {}

        std::string get() const {
            if (_pointer == nullptr) {
                return std::string("");
            }
            return std::string(_pointer);
        }
    private:
        char *_pointer;
    };
    
    /**
     * Template specialization for struct curl_slist *.
     */
    template<> class curl_easy_info<struct curl_slist *> {
    public:
        explicit curl_easy_info(struct curl_slist *pointer) : _pointer(pointer) {}

        ~curl_easy_info() {
            if (_pointer != nullptr) {
                curl_slist_free_all(_pointer);
            }
        }
        std::vector<std::string> get() {
            struct curl_slist *backup = _pointer;
            std::vector<std::string> infos;
            while (backup != nullptr) {
                if (backup->data != nullptr) {
                    std::string str(backup->data);
                    infos.push_back(str);
                }
                backup = backup->next;
            }
            return infos;
        }
    private:
        struct curl_slist *_pointer;
    };
}

#endif /* curl_easy_info_h */
