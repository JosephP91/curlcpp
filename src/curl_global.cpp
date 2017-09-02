#include "curl_global.h"

using curl::curl_global;

curl_global::curl_global() {
    const CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
    if (code != CURLE_OK) {
        throw curl_easy_exception(code, __FUNCTION__);
    }
}

curl_global::curl_global(const long flag) {
    const CURLcode code = curl_global_init(flag);
    if (code != CURLE_OK) {
        throw curl_easy_exception(code, __FUNCTION__);
    }
}

curl_global::~curl_global() {
    curl_global_cleanup();
}
