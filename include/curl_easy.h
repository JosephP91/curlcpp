/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 - Giuseppe Persico
 * File - curl_easy.h
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

#ifndef __curlcpp__curl_easy__
#define __curlcpp__curl_easy__

#include <algorithm>
#include <curl/curl.h>
#include <memory>

#include "curl_config.h"
#include "curl_interface.h"
#include "curl_pair.h"
#include "curl_ios.h"
#include "curl_form.h"
#include "curl_easy_info.h"

#define CURLCPP_DEFINE_OPTION(opt, value_type)\
    template <> struct option_t<opt> {\
        using type = value_type;\
    }

#define CURLCPP_DEFINE_INFO(info,value_type)\
    template <> struct info_t<info> {\
        using type = value_type;\
    }

namespace curl  {
    // Definition of CURLINFO_* constants)
    namespace detail_info {
        template <CURLINFO> struct info_t;
        template <CURLINFO info> using Info_type = typename info_t<info>::type;
        // Last URL used
        CURLCPP_DEFINE_INFO(CURLINFO_EFFECTIVE_URL,char *);
        // Response code
        CURLCPP_DEFINE_INFO(CURLINFO_RESPONSE_CODE,long);
        // Last proxy connect response code
        CURLCPP_DEFINE_INFO(CURLINFO_HTTP_CONNECTCODE,long);
        // Remote time of the retrieved document.
        CURLCPP_DEFINE_INFO(CURLINFO_FILETIME,long);
        // Total time of previous transfer.
        CURLCPP_DEFINE_INFO(CURLINFO_TOTAL_TIME,double);
        // Time from start until name resolving completed.
        CURLCPP_DEFINE_INFO(CURLINFO_NAMELOOKUP_TIME,double);
        // Time from start until remote hosst proxy completed.
        CURLCPP_DEFINE_INFO(CURLINFO_CONNECT_TIME,double);
        // Time fron start until SSL/SSH handshake completed.
        CURLCPP_DEFINE_INFO(CURLINFO_APPCONNECT_TIME,double);
        // Time from start until just before the transfter begins.
        CURLCPP_DEFINE_INFO(CURLINFO_PRETRANSFER_TIME,double);
        // Time from start until just when the first byte is received.
        CURLCPP_DEFINE_INFO(CURLINFO_STARTTRANSFER_TIME,double);
        // Time taken for all redirect steps before the final transfer.
        CURLCPP_DEFINE_INFO(CURLINFO_REDIRECT_TIME,double);
        // Total number of redirects that were followed.
        CURLCPP_DEFINE_INFO(CURLINFO_REDIRECT_COUNT,long);
        // URL a redirect would take you to, had you enabled redirects.
        CURLCPP_DEFINE_INFO(CURLINFO_REDIRECT_URL,char *);
        // Number of bytes uploaded.
        CURLCPP_DEFINE_INFO(CURLINFO_SIZE_UPLOAD,double);
        // Number of bytes downloaded.
        CURLCPP_DEFINE_INFO(CURLINFO_SIZE_DOWNLOAD,double);
        // Average download speed.
        CURLCPP_DEFINE_INFO(CURLINFO_SPEED_DOWNLOAD,double);
        // Average upload speed.
        CURLCPP_DEFINE_INFO(CURLINFO_SPEED_UPLOAD,double);
        // Number of bytes of all headers received.
        CURLCPP_DEFINE_INFO(CURLINFO_HEADER_SIZE,long);
        // Number of bytes sent in the issued HTTP requests.
        CURLCPP_DEFINE_INFO(CURLINFO_REQUEST_SIZE,long);
        // Certificate verification result.
        CURLCPP_DEFINE_INFO(CURLINFO_SSL_VERIFYRESULT,long);
        // A list of OpenSSL crypto engines.
        CURLCPP_DEFINE_INFO(CURLINFO_SSL_ENGINES,struct curl_slist *);
        // Content length from the Content-Length header.
        CURLCPP_DEFINE_INFO(CURLINFO_CONTENT_LENGTH_DOWNLOAD,long);
        // Upload size.
        CURLCPP_DEFINE_INFO(CURLINFO_CONTENT_LENGTH_UPLOAD,long);
        // Content type from the Content-Type header.
        CURLCPP_DEFINE_INFO(CURLINFO_CONTENT_TYPE,char *);
        // User's private data pointer.
        CURLCPP_DEFINE_INFO(CURLINFO_PRIVATE,char *);
        // Avaiable HTTP authentication methods.
        CURLCPP_DEFINE_INFO(CURLINFO_HTTPAUTH_AVAIL,long);
        // Avaiable HTTP proxy authentication methods.
        CURLCPP_DEFINE_INFO(CURLINFO_PROXYAUTH_AVAIL,long);
        // The errno from the las failure to connect.
        CURLCPP_DEFINE_INFO(CURLINFO_OS_ERRNO,long);
        // Number of new succesful connections used for previous trasnfer.
        CURLCPP_DEFINE_INFO(CURLINFO_NUM_CONNECTS,long);
        // IP Address of the last connection.
        CURLCPP_DEFINE_INFO(CURLINFO_PRIMARY_IP,char *);
        // Port of the last connection.
        CURLCPP_DEFINE_INFO(CURLINFO_PRIMARY_PORT,long);
        // Local-end IP address of last connection.
        CURLCPP_DEFINE_INFO(CURLINFO_LOCAL_IP,char *);
        // Local-end port of last connection.
        CURLCPP_DEFINE_INFO(CURLINFO_LOCAL_PORT,long);
        // List of all known cookies.
        CURLCPP_DEFINE_INFO(CURLINFO_COOKIELIST,struct curl_slist *);
        // Last socket used.
        CURLCPP_DEFINE_INFO(CURLINFO_LASTSOCKET,long);
        // This option is avaiable in libcurl 7.45 or greater.
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072D00
        // The session's active socket.
        CURLCPP_DEFINE_INFO(CURLINFO_ACTIVESOCKET,curl_socket_t *);
#endif
        // The entry path after logging in to an FTP server.
        CURLCPP_DEFINE_INFO(CURLINFO_FTP_ENTRY_PATH,char *);
        // Certificate chain
        CURLCPP_DEFINE_INFO(CURLINFO_CERTINFO,struct curl_certinfo *);
        // This costant is avaiable with libcurl < 7.48
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM < 0x073000
        // TLS session info that can be used for further processing.
        CURLCPP_DEFINE_INFO(CURLINFO_TLS_SESSION,struct curl_tlssessioninfo *);
#else
        // TLS session info that can be used for further processing.
        CURLCPP_DEFINE_INFO(CURLINFO_TLS_SSL_PTR,struct curl_tlssessioninfo *);
#endif
        // Whether or not a time conditional was met.
        CURLCPP_DEFINE_INFO(CURLINFO_CONDITION_UNMET,long);
        // RTSP session ID.
        CURLCPP_DEFINE_INFO(CURLINFO_RTSP_SESSION_ID,char *);
        // RTSP CSeq that will next be used.
        CURLCPP_DEFINE_INFO(CURLINFO_RTSP_CLIENT_CSEQ,long);
        // RTPS CSeq that will next be expected.
        CURLCPP_DEFINE_INFO(CURLINFO_RTSP_SERVER_CSEQ,long);
        // RTSP CSeq last received.
        CURLCPP_DEFINE_INFO(CURLINFO_RTSP_CSEQ_RECV,long);
    }
    
    // Detail namespace
    namespace detail {
        template <CURLoption> struct option_t;
        template <CURLoption opt> using Option_type = typename option_t<opt>::type;
        CURLCPP_DEFINE_OPTION(CURLOPT_WRITEDATA, void*);
        /* The full URL to get/put */
        CURLCPP_DEFINE_OPTION(CURLOPT_URL, const char*);
        /* Port number to connect to, if other than default. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PORT, long);
        /* Name of proxy to use. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXY, const char*);
        /* "user:password;options" to use when fetching. */
        CURLCPP_DEFINE_OPTION(CURLOPT_USERPWD, const char*);
        /* "user:password" to use with proxy. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXYUSERPWD, const char*);
        /* Range to get, specified as an ASCII string. */
        CURLCPP_DEFINE_OPTION(CURLOPT_RANGE, const char*);
        /* Specified file stream to upload from (use as input): */
        CURLCPP_DEFINE_OPTION(CURLOPT_READDATA, void*);
        /* Buffer to receive error messages in, must be at least CURL_ERROR_SIZE
         * bytes big. If this is not used, error messages go to stderr instead: */
        CURLCPP_DEFINE_OPTION(CURLOPT_ERRORBUFFER, char*);
        /* Function that will be called to store the output (instead of fwrite). The
        * parameters will use fwrite() syntax, make sure to follow them. */
        CURLCPP_DEFINE_OPTION(CURLOPT_WRITEFUNCTION,
        		size_t(*)(void *ptr, size_t size, size_t nmemb, void *userdata));

        /* Function that will be called to read the input (instead of fread). The
        * parameters will use fread() syntax, make sure to follow them. */
        CURLCPP_DEFINE_OPTION(CURLOPT_READFUNCTION,
        		size_t(*)(void *buffer, size_t size, size_t nitems, void *instream));

        /* Time-out the read operation after this amount of seconds */
        CURLCPP_DEFINE_OPTION(CURLOPT_TIMEOUT, long);
        /* If the CURLOPT_INFILE is used, this can be used to inform libcurl about
         * how large the file being sent really is. That allows better error
         * checking and better verifies that the upload was successful. -1 means
         * unknown size.
         *
         * For large file support, there is also a _LARGE version of the key
         * which takes an off_t type, allowing platforms with larger off_t
         * sizes to handle larger files.  See below for INFILESIZE_LARGE. */
        CURLCPP_DEFINE_OPTION(CURLOPT_INFILESIZE, long);
        /* POST static input fields. */
        CURLCPP_DEFINE_OPTION(CURLOPT_POSTFIELDS, const char*);
        /* Set the referrer page (needed by some CGIs) */
        CURLCPP_DEFINE_OPTION(CURLOPT_REFERER, const char*);
        /* Set the FTP PORT string (interface name, named or numerical IP address)
        Use i.e '-' to use default address. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTPPORT, const char*);
        /* Set the User-Agent string (examined by some CGIs) */
        CURLCPP_DEFINE_OPTION(CURLOPT_USERAGENT, const char*);
        /* If the download receives less than "low speed limit" bytes/second
         * during "low speed time" seconds, the operations is aborted.
         * You could i.e if you have a pretty high speed connection, abort if
         * it is less than 2000 bytes/sec during 20 seconds.
         */
        /* Set the "low speed limit" */
        CURLCPP_DEFINE_OPTION(CURLOPT_LOW_SPEED_LIMIT, long);

        /* Set the "low speed time" */
        CURLCPP_DEFINE_OPTION(CURLOPT_LOW_SPEED_TIME, long);

        /* Set the continuation offset.
        *
        * Note there is also a _LARGE version of this key which uses
        * off_t types, allowing for large file offsets on platforms which
        * use larger-than-32-bit off_t's.  Look below for RESUME_FROM_LARGE.
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_RESUME_FROM, long);

        /* Set cookie in request: */
        CURLCPP_DEFINE_OPTION(CURLOPT_COOKIE, const char*);

        /* This points to a linked list of headers, struct curl_slist kind. This
        list is also used for RTSP (in spite of its name) */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTPHEADER, const struct curl_slist*);

        /* This points to a linked list of post entries, struct curl_httppost */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTPPOST, const struct curl_httppost*);

        /* name of the file keeping your private SSL-certificate */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSLCERT, const char*);

        /* password for the SSL or SSH private key */
        CURLCPP_DEFINE_OPTION(CURLOPT_KEYPASSWD, const char*);

        /* send TYPE parameter? */
        CURLCPP_DEFINE_OPTION(CURLOPT_CRLF, long);

        /* send linked-list of QUOTE commands */
        CURLCPP_DEFINE_OPTION(CURLOPT_QUOTE, curl_slist*);

        /* send FILE * or void * to store headers to, if you use a callback it
        is simply passed to the callback unmodified */
        CURLCPP_DEFINE_OPTION(CURLOPT_HEADERDATA, void*);

        /* point to a file to read the initial cookies from, also enables
        "cookie awareness" */
        CURLCPP_DEFINE_OPTION(CURLOPT_COOKIEFILE, const char*);

        /* What version to specifically try to use.
        See CURL_SSLVERSION defines below. */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSLVERSION, long);

        /* What kind of HTTP time condition to use, see defines */
        CURLCPP_DEFINE_OPTION(CURLOPT_TIMECONDITION, long);

        /* Time to use with the above condition. Specified in number of seconds
        since 1 Jan 1970 */
        CURLCPP_DEFINE_OPTION(CURLOPT_TIMEVALUE, long);

        /* 35 = OBSOLETE */

        /* Custom request, for customizing the get command like
        HTTP: DELETE, TRACE and others
        FTP: to use a different list command
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_CUSTOMREQUEST, const char*);

        /* HTTP request, for odd commands like DELETE, TRACE and others */
        CURLCPP_DEFINE_OPTION(CURLOPT_STDERR, FILE*);

        /* 38 is not used */

        /* send linked-list of post-transfer QUOTE commands */
        CURLCPP_DEFINE_OPTION(CURLOPT_POSTQUOTE, curl_slist*);

        CURLCPP_DEFINE_OPTION(CURLOPT_VERBOSE, long);      /* talk a lot */
        CURLCPP_DEFINE_OPTION(CURLOPT_HEADER, long);       /* throw the header out too */
        CURLCPP_DEFINE_OPTION(CURLOPT_NOPROGRESS, long);   /* shut off the progress meter */
        CURLCPP_DEFINE_OPTION(CURLOPT_NOBODY, long);       /* use HEAD to get http document */
        CURLCPP_DEFINE_OPTION(CURLOPT_FAILONERROR, long);  /* no output on http error codes >= 400 */
        CURLCPP_DEFINE_OPTION(CURLOPT_UPLOAD, long);       /* this is an upload */
        CURLCPP_DEFINE_OPTION(CURLOPT_POST, long);         /* HTTP POST method */
        CURLCPP_DEFINE_OPTION(CURLOPT_DIRLISTONLY, long);  /* bare names when listing directories */

        CURLCPP_DEFINE_OPTION(CURLOPT_APPEND, long);       /* Append instead of overwrite on upload! */

        /* Specify whether to read the user+password from the .netrc or the URL.
        * This must be one of the CURL_NETRC_* enums below. */
        CURLCPP_DEFINE_OPTION(CURLOPT_NETRC, long);

        CURLCPP_DEFINE_OPTION(CURLOPT_FOLLOWLOCATION, long);  /* use Location: Luke! */

        CURLCPP_DEFINE_OPTION(CURLOPT_TRANSFERTEXT, long); /* transfer data in text/ASCII format */
        CURLCPP_DEFINE_OPTION(CURLOPT_PUT, long);          /* HTTP PUT */

        /* 55 = OBSOLETE */

        /* DEPRECATED
        * Function that will be called instead of the internal progress display
        * function. This function should be defined as the curl_progress_callback
        * prototype defines. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROGRESSFUNCTION, curl_progress_callback);

        /* Data passed to the CURLOPT_PROGRESSFUNCTION and CURLOPT_XFERINFOFUNCTION
        callbacks */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROGRESSDATA, void*);

        /* We want the referrer field set automatically when following locations */
        CURLCPP_DEFINE_OPTION(CURLOPT_AUTOREFERER, long);

        /* Port of the proxy, can be set in the proxy string as well with:
        "[host]:[port]" */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXYPORT, long);

        /* size of the POST input data, if strlen() is not good to use */
        CURLCPP_DEFINE_OPTION(CURLOPT_POSTFIELDSIZE, long);

        /* tunnel non-http operations through a HTTP proxy */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTPPROXYTUNNEL, long);

        /* Set the interface string to use as outgoing network interface */
        CURLCPP_DEFINE_OPTION(CURLOPT_INTERFACE, const char*);

        /* Set the krb4/5 security level, this also enables krb4/5 awareness.  This
        * is a string, 'clear', 'safe', 'confidential' or 'private'.  If the string
        * is set but doesn't match one of these, 'private' will be used.  */
        CURLCPP_DEFINE_OPTION(CURLOPT_KRBLEVEL, const char*);

        /* Set if we should verify the peer in ssl handshake, set 1 to verify. */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_VERIFYPEER, long);

        /* The CApath or CAfile used to validate the peer certificate
        this option is used only if SSL_VERIFYPEER is true */
        CURLCPP_DEFINE_OPTION(CURLOPT_CAINFO, const char*);

        /* 66 = OBSOLETE */
        /* 67 = OBSOLETE */

        /* Maximum number of http redirects to follow */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAXREDIRS, long);

        /* Pass a long set to 1 to get the date of the requested document (if
        possible)! Pass a zero to shut it off. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FILETIME, long);

        /* This points to a linked list of telnet options */
        CURLCPP_DEFINE_OPTION(CURLOPT_TELNETOPTIONS, curl_slist*);

        /* Max amount of cached alive connections */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAXCONNECTS, long);

        /* Renamed / obsoleted since 7.37 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM > 0x072500
        CURLCPP_DEFINE_OPTION(CURLOPT_OBSOLETE72, long); /* OBSOLETE, do not use! */
#else
        CURLCPP_DEFINE_OPTION(CURLOPT_CLOSEPOLICY, long);
#endif

        /* 73 = OBSOLETE */

        /* Set to explicitly use a new connection for the upcoming transfer.
        Do not use this unless you're absolutely sure of this, as it makes the
        operation slower and is less friendly for the network. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FRESH_CONNECT, long);

        /* Set to explicitly forbid the upcoming transfer's connection to be re-used
        when done. Do not use this unless you're absolutely sure of this, as it
        makes the operation slower and is less friendly for the network. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FORBID_REUSE, long);

        /* Set to a file name that contains random data for libcurl to use to
        seed the random engine when doing SSL connects. */
        CURLCPP_DEFINE_OPTION(CURLOPT_RANDOM_FILE, const char*);

        /* Set to the Entropy Gathering Daemon socket pathname */
        CURLCPP_DEFINE_OPTION(CURLOPT_EGDSOCKET, const char*);

        /* Time-out connect operations after this amount of seconds, if connects are
        OK within this time, then fine... This only aborts the connect phase. */
        CURLCPP_DEFINE_OPTION(CURLOPT_CONNECTTIMEOUT, long);

        /* Function that will be called to store headers (instead of fwrite). The
        * parameters will use fwrite() syntax, make sure to follow them. */
        CURLCPP_DEFINE_OPTION(CURLOPT_HEADERFUNCTION,
        		size_t(*)(void *buffer, size_t size, size_t nitems, void *userdata));

        /* Set this to force the HTTP request to get back to GET. Only really usable
        if POST, PUT or a custom request have been used first.
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTPGET, long);

        /* Set if we should verify the Common name from the peer certificate in ssl
        * handshake, set 1 to check existence, 2 to ensure that it matches the
        * provided hostname. */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_VERIFYHOST, long);

        /* Specify which file name to write all known cookies in after completed
        operation. Set file name to "-" (dash) to make it go to stdout. */
        CURLCPP_DEFINE_OPTION(CURLOPT_COOKIEJAR, const char*);

        /* Specify which SSL ciphers to use */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_CIPHER_LIST, const char*);

        /* Specify which HTTP version to use! This must be set to one of the
        CURL_HTTP_VERSION* enums set below. */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTP_VERSION, long);

        /* Specifically switch on or off the FTP engine's use of the EPSV command. By
        default, that one will always be attempted before the more traditional
        PASV command. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_USE_EPSV, long);

        /* type of the file keeping your SSL-certificate ("DER", "PEM", "ENG") */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSLCERTTYPE, const char*);

        /* name of the file keeping your private SSL-key */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSLKEY, const char*);

        /* type of the file keeping your private SSL-key ("DER", "PEM", "ENG") */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSLKEYTYPE, const char*);

        /* crypto engine for the SSL-sub system */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSLENGINE, const char*);

        /* set the crypto engine for the SSL-sub system as default
        the param has no meaning...
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSLENGINE_DEFAULT, long);

        /* DNS cache timeout */
        CURLCPP_DEFINE_OPTION(CURLOPT_DNS_CACHE_TIMEOUT, long);

        /* send linked-list of pre-transfer QUOTE commands */
        CURLCPP_DEFINE_OPTION(CURLOPT_PREQUOTE, curl_slist*);

        /* set the debug function */
        CURLCPP_DEFINE_OPTION(CURLOPT_DEBUGFUNCTION, int(*)(CURL *handle,
            curl_infotype type,
            char *data,
            size_t size,
            void *userptr));

        /* set the data for the debug function */
        CURLCPP_DEFINE_OPTION(CURLOPT_DEBUGDATA, void*);

        /* mark this as start of a cookie session */
        CURLCPP_DEFINE_OPTION(CURLOPT_COOKIESESSION, long);

        /* The CApath directory used to validate the peer certificate
        this option is used only if SSL_VERIFYPEER is true */
        CURLCPP_DEFINE_OPTION(CURLOPT_CAPATH, const char*);

        /* Instruct libcurl to use a smaller receive buffer */
        CURLCPP_DEFINE_OPTION(CURLOPT_BUFFERSIZE, long);

        /* Instruct libcurl to not use any signal/alarm handlers, even when using
        timeouts. This option is useful for multi-threaded applications.
        See libcurl-the-guide for more background information. */
        CURLCPP_DEFINE_OPTION(CURLOPT_NOSIGNAL, long);

        /* Provide a CURLShare for mutexing non-ts data */
        CURLCPP_DEFINE_OPTION(CURLOPT_SHARE, CURLSH*);

        /* indicates type of proxy. accepted values are CURLPROXY_HTTP (default),
        CURLPROXY_SOCKS4, CURLPROXY_SOCKS4A and CURLPROXY_SOCKS5. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXYTYPE, long);

        /* Set the Accept-Encoding string. Use this to tell a server you would like
        the response to be compressed. Before 7.21.6, this was known as
        CURLOPT_ENCODING */
        CURLCPP_DEFINE_OPTION(CURLOPT_ACCEPT_ENCODING, const char*);

        /* Set pointer to private data */
        CURLCPP_DEFINE_OPTION(CURLOPT_PRIVATE, void*);

        /* Set aliases for HTTP 200 in the HTTP Response header */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTP200ALIASES, curl_slist*);

        /* Continue to send authentication (user+password) when following locations,
        even when hostname changed. This can potentially send off the name
        and password to whatever host the server decides. */
        CURLCPP_DEFINE_OPTION(CURLOPT_UNRESTRICTED_AUTH, long);

        /* Specifically switch on or off the FTP engine's use of the EPRT command (
        it also disables the LPRT attempt). By default, those ones will always be
        attempted before the good old traditional PORT command. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_USE_EPRT, long);

        /* Set this to a bitmask value to enable the particular authentications
        methods you like. Use this in combination with CURLOPT_USERPWD.
        Note that setting multiple bits may cause extra network round-trips. */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTPAUTH, long);

        /* Set the ssl context callback function, currently only for OpenSSL ssl_ctx
        in second argument. The function must be matching the
        curl_ssl_ctx_callback proto. */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_CTX_FUNCTION,
        		CURLcode(*)(CURL *curl, void *ssl_ctx, void *userptr));

        /* Set the userdata for the ssl context callback function's third
        argument */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_CTX_DATA, void*);

        /* FTP Option that causes missing dirs to be created on the remote server.
        In 7.19.4 we introduced the convenience enums for this option using the
        CURLFTP_CREATE_DIR prefix.
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_CREATE_MISSING_DIRS, long);

        /* Set this to a bitmask value to enable the particular authentications
        methods you like. Use this in combination with CURLOPT_PROXYUSERPWD.
        Note that setting multiple bits may cause extra network round-trips. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXYAUTH, long);

        /* FTP option that changes the timeout, in seconds, associated with
        getting a response.  This is different from transfer timeout time and
        essentially places a demand on the FTP server to acknowledge commands
        in a timely manner. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_RESPONSE_TIMEOUT, long);

        /* Set this option to one of the CURL_IPRESOLVE_* defines (see below) to
        tell libcurl to resolve names to those IP versions only. This only has
        affect on systems with support for more than one, i.e IPv4 _and_ IPv6. */
        CURLCPP_DEFINE_OPTION(CURLOPT_IPRESOLVE, long);

        /* Set this option to limit the size of a file that will be downloaded from
        an HTTP or FTP server.

        Note there is also _LARGE version which adds large file support for
        platforms which have larger off_t sizes.  See MAXFILESIZE_LARGE below. */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAXFILESIZE, long);

        /* See the comment for INFILESIZE above, but in short, specifies
        * the size of the file being uploaded.  -1 means unknown.
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_INFILESIZE_LARGE, curl_off_t);

        /* Sets the continuation offset.  There is also a long version of this;
        * look above for RESUME_FROM.
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_RESUME_FROM_LARGE, curl_off_t);

        /* Sets the maximum size of data that will be downloaded from
        * an HTTP or FTP server.  See MAXFILESIZE above for the long version.
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAXFILESIZE_LARGE, curl_off_t);

        /* Set this option to the file name of your .netrc file you want libcurl
        to parse (using the CURLOPT_NETRC option). If not set, libcurl will do
        a poor attempt to find the user's home directory and check for a .netrc
        file in there. */
        CURLCPP_DEFINE_OPTION(CURLOPT_NETRC_FILE, const char*);

        /* Enable SSL/TLS for FTP, pick one of:
        CURLUSESSL_TRY     - try using SSL, proceed anyway otherwise
        CURLUSESSL_CONTROL - SSL for the control connection or fail
        CURLUSESSL_ALL     - SSL for all communication or fail
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_USE_SSL, long);

        /* The _LARGE version of the standard POSTFIELDSIZE option */
        CURLCPP_DEFINE_OPTION(CURLOPT_POSTFIELDSIZE_LARGE, curl_off_t);

        /* Enable/disable the TCP Nagle algorithm */
        CURLCPP_DEFINE_OPTION(CURLOPT_TCP_NODELAY, long);

        /* When FTP over SSL/TLS is selected (with CURLOPT_USE_SSL), this option
        can be used to change libcurl's default action which is to first try
        "AUTH SSL" and then "AUTH TLS" in this order, and proceed when a OK
        response has been received.

        Available parameters are:
        CURLFTPAUTH_DEFAULT - let libcurl decide
        CURLFTPAUTH_SSL     - try "AUTH SSL" first, then TLS
        CURLFTPAUTH_TLS     - try "AUTH TLS" first, then SSL
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTPSSLAUTH, long);

        CURLCPP_DEFINE_OPTION(CURLOPT_IOCTLFUNCTION, curlioerr(*)(CURL *handle, int cmd, void *clientp));
        CURLCPP_DEFINE_OPTION(CURLOPT_IOCTLDATA, void*);

        /* zero terminated string for pass on to the FTP server when asked for
        "account" info */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_ACCOUNT, const char*);

        /* feed cookies into cookie engine */
        CURLCPP_DEFINE_OPTION(CURLOPT_COOKIELIST, const char*);

        /* ignore Content-Length */
        CURLCPP_DEFINE_OPTION(CURLOPT_IGNORE_CONTENT_LENGTH, long);

        /* Set to non-zero to skip the IP address received in a 227 PASV FTP server
        response. Typically used for FTP-SSL purposes but is not restricted to
        that. libcurl will then instead use the same IP address it used for the
        control connection. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_SKIP_PASV_IP, long);

        /* Select "file method" to use when doing FTP, see the curl_ftpmethod
        above. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_FILEMETHOD, long);

        /* Local port number to bind the socket to */
        CURLCPP_DEFINE_OPTION(CURLOPT_LOCALPORT, long);

        /* Number of ports to try, including the first one set with LOCALPORT.
        Thus, setting it to 1 will make no additional attempts but the first.
        */
        CURLCPP_DEFINE_OPTION(CURLOPT_LOCALPORTRANGE, long);

        /* no transfer, set up connection and let application use the socket by
        extracting it with CURLINFO_LASTSOCKET */
        CURLCPP_DEFINE_OPTION(CURLOPT_CONNECT_ONLY, long);

        /* Function that will be called to convert from the
        network encoding (instead of using the iconv calls in libcurl) */
        CURLCPP_DEFINE_OPTION(CURLOPT_CONV_FROM_NETWORK_FUNCTION, CURLcode(*)(char *ptr, size_t length));

        /* Function that will be called to convert to the
        network encoding (instead of using the iconv calls in libcurl) */
        CURLCPP_DEFINE_OPTION(CURLOPT_CONV_TO_NETWORK_FUNCTION, CURLcode(*)(char *ptr, size_t length));

        /* Function that will be called to convert from UTF8
        (instead of using the iconv calls in libcurl)
        Note that this is used only for SSL certificate processing */
        CURLCPP_DEFINE_OPTION(CURLOPT_CONV_FROM_UTF8_FUNCTION, CURLcode(*)(char *ptr, size_t length));

        /* if the connection proceeds too quickly then need to slow it down */
        /* limit-rate: maximum number of bytes per second to send or receive */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAX_SEND_SPEED_LARGE, curl_off_t);
        CURLCPP_DEFINE_OPTION(CURLOPT_MAX_RECV_SPEED_LARGE, curl_off_t);

        /* Pointer to command string to send if USER/PASS fails. */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_ALTERNATIVE_TO_USER, const char*);

        /* callback function for setting socket options */
        CURLCPP_DEFINE_OPTION(CURLOPT_SOCKOPTFUNCTION, int(*)(void *clientp,
            curl_socket_t curlfd,
            curlsocktype purpose));
        CURLCPP_DEFINE_OPTION(CURLOPT_SOCKOPTDATA, void*);

        /* set to 0 to disable session ID re-use for this transfer, default is
        enabled (== 1) */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_SESSIONID_CACHE, long);

        /* allowed SSH authentication methods */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSH_AUTH_TYPES, long);

        /* Used by scp/sftp to do public/private key authentication */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSH_PUBLIC_KEYFILE, const char*);
        CURLCPP_DEFINE_OPTION(CURLOPT_SSH_PRIVATE_KEYFILE, const char*);

        /* Send CCC (Clear Command Channel) after authentication */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_SSL_CCC, long);

        /* Same as TIMEOUT and CONNECTTIMEOUT, but with ms resolution */
        CURLCPP_DEFINE_OPTION(CURLOPT_TIMEOUT_MS, long);
        CURLCPP_DEFINE_OPTION(CURLOPT_CONNECTTIMEOUT_MS, long);

        /* set to zero to disable the libcurl's decoding and thus pass the raw body
        data to the application even when it is encoded/compressed */
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTP_TRANSFER_DECODING, long);
        CURLCPP_DEFINE_OPTION(CURLOPT_HTTP_CONTENT_DECODING, long);

        /* Permission used when creating new files and directories on the remote
        server for protocols that support it, SFTP/SCP/FILE */
        CURLCPP_DEFINE_OPTION(CURLOPT_NEW_FILE_PERMS, long);
        CURLCPP_DEFINE_OPTION(CURLOPT_NEW_DIRECTORY_PERMS, long);

        /* Set the behaviour of POST when redirecting. Values must be set to one
        of CURL_REDIR* defines below. This used to be called CURLOPT_POST301 */
        CURLCPP_DEFINE_OPTION(CURLOPT_POSTREDIR, long);

        /* used by scp/sftp to verify the host's public key */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSH_HOST_PUBLIC_KEY_MD5, const char*);

        /* Callback function for opening socket (instead of socket(2)). Optionally,
        callback is able change the address or refuse to connect returning
        CURL_SOCKET_BAD.  The callback should have type
        curl_opensocket_callback */
        CURLCPP_DEFINE_OPTION(CURLOPT_OPENSOCKETFUNCTION, curl_socket_t(*)(void *clientp,
            curlsocktype purpose,
            struct curl_sockaddr *address));
        CURLCPP_DEFINE_OPTION(CURLOPT_OPENSOCKETDATA, void*);

        /* POST volatile input fields. */
        CURLCPP_DEFINE_OPTION(CURLOPT_COPYPOSTFIELDS, const char*);

        /* set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXY_TRANSFER_MODE, long);

        /* Callback function for seeking in the input stream */
        CURLCPP_DEFINE_OPTION(CURLOPT_SEEKFUNCTION, int(*)(void *userp, curl_off_t offset, int origin));
        CURLCPP_DEFINE_OPTION(CURLOPT_SEEKDATA, void*);

        /* CRL file */
        CURLCPP_DEFINE_OPTION(CURLOPT_CRLFILE, const char*);

        /* Issuer certificate */
        CURLCPP_DEFINE_OPTION(CURLOPT_ISSUERCERT, const char*);

        /* (IPv6) Address scope */
        CURLCPP_DEFINE_OPTION(CURLOPT_ADDRESS_SCOPE, long);

        /* Collect certificate chain info and allow it to get retrievable with
        CURLINFO_CERTINFO after the transfer is complete. */
        CURLCPP_DEFINE_OPTION(CURLOPT_CERTINFO, long);

        /* "name" and "pwd" to use when fetching. */
        CURLCPP_DEFINE_OPTION(CURLOPT_USERNAME, const char*);
        CURLCPP_DEFINE_OPTION(CURLOPT_PASSWORD, const char*);

        /* "name" and "pwd" to use with Proxy when fetching. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXYUSERNAME, const char*);
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXYPASSWORD, const char*);

        /* Comma separated list of hostnames defining no-proxy zones. These should
        match both hostnames directly, and hostnames within a domain. For
        example, local.com will match local.com and www.local.com, but NOT
        notlocal.com or www.notlocal.com. For compatibility with other
        implementations of this, .local.com will be considered to be the same as
        local.com. A single * is the only valid wildcard, and effectively
        disables the use of proxy. */
        CURLCPP_DEFINE_OPTION(CURLOPT_NOPROXY, const char*);

        /* block size for TFTP transfers */
        CURLCPP_DEFINE_OPTION(CURLOPT_TFTP_BLKSIZE, long);

        /* Socks Service */
        CURLCPP_DEFINE_OPTION(CURLOPT_SOCKS5_GSSAPI_SERVICE, const char*);

        /* Socks Service */
        CURLCPP_DEFINE_OPTION(CURLOPT_SOCKS5_GSSAPI_NEC, long);

        /* set the bitmask for the protocols that are allowed to be used for the
        transfer, which thus helps the app which takes URLs from users or other
        external inputs and want to restrict what protocol(s) to deal
        with. Defaults to CURLPROTO_ALL. */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROTOCOLS, long);

        /* set the bitmask for the protocols that libcurl is allowed to follow to,
        as a subset of the CURLOPT_PROTOCOLS ones. That means the protocol needs
        to be set in both bitmasks to be allowed to get redirected to. Defaults
        to all protocols except FILE and SCP. */
        CURLCPP_DEFINE_OPTION(CURLOPT_REDIR_PROTOCOLS, long);

        /* set the SSH knownhost file name to use */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSH_KNOWNHOSTS, const char*);

        /* set the SSH host key callback, must point to a curl_sshkeycallback
        function */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSH_KEYFUNCTION, int(*)(CURL *easy,
            const struct curl_khkey *knownkey,
            const struct curl_khkey *foundkey,
            enum curl_khmatch,
            void *clientp));

        /* set the SSH host key callback custom pointer */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSH_KEYDATA, void*);

        /* set the SMTP mail originator */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAIL_FROM, const char*);

        /* set the SMTP mail receiver(s) */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAIL_RCPT, curl_slist*);

        /* FTP: send PRET before PASV */
        CURLCPP_DEFINE_OPTION(CURLOPT_FTP_USE_PRET, long);

        /* RTSP request method (OPTIONS, SETUP, PLAY, etc...) */
        CURLCPP_DEFINE_OPTION(CURLOPT_RTSP_REQUEST, long);

        /* The RTSP session identifier */
        CURLCPP_DEFINE_OPTION(CURLOPT_RTSP_SESSION_ID, const char*);

        /* The RTSP stream URI */
        CURLCPP_DEFINE_OPTION(CURLOPT_RTSP_STREAM_URI, const char*);

        /* The Transport: header to use in RTSP requests */
        CURLCPP_DEFINE_OPTION(CURLOPT_RTSP_TRANSPORT, const char*);

        /* Manually initialize the client RTSP CSeq for this handle */
        CURLCPP_DEFINE_OPTION(CURLOPT_RTSP_CLIENT_CSEQ, long);

        /* Manually initialize the server RTSP CSeq for this handle */
        CURLCPP_DEFINE_OPTION(CURLOPT_RTSP_SERVER_CSEQ, long);

        /* The stream to pass to INTERLEAVEFUNCTION. */
        CURLCPP_DEFINE_OPTION(CURLOPT_INTERLEAVEDATA, void*);

        /* Let the application define a custom write method for RTP data */
        CURLCPP_DEFINE_OPTION(CURLOPT_INTERLEAVEFUNCTION, size_t(*)(void *ptr, 
            size_t size, 
            size_t nmemb,
            void *userdata));

        /* Turn on wildcard matching */
        CURLCPP_DEFINE_OPTION(CURLOPT_WILDCARDMATCH, long);

        /* Directory matching callback called before downloading of an
        individual file (chunk) started */
        CURLCPP_DEFINE_OPTION(CURLOPT_CHUNK_BGN_FUNCTION, long(*)(
            const void *transfer_info, 
            void *ptr,
            int remains));

        /* Directory matching callback called after the file (chunk)
        was downloaded, or skipped */
        CURLCPP_DEFINE_OPTION(CURLOPT_CHUNK_END_FUNCTION, long(*)(void *ptr));

        /* Change match (fnmatch-like) callback for wildcard matching */
        CURLCPP_DEFINE_OPTION(CURLOPT_FNMATCH_FUNCTION, int(*)(void *ptr,
            const char *pattern,
            const char *string));

        /* Let the application define custom chunk data pointer */
        CURLCPP_DEFINE_OPTION(CURLOPT_CHUNK_DATA, void*);

        /* FNMATCH_FUNCTION user pointer */
        CURLCPP_DEFINE_OPTION(CURLOPT_FNMATCH_DATA, void*);

        /* send linked-list of name:port:address sets */
        CURLCPP_DEFINE_OPTION(CURLOPT_RESOLVE, curl_slist*);

        /* Set a username for authenticated TLS */
        CURLCPP_DEFINE_OPTION(CURLOPT_TLSAUTH_USERNAME, const char*);

        /* Set a password for authenticated TLS */
        CURLCPP_DEFINE_OPTION(CURLOPT_TLSAUTH_PASSWORD, const char*);

        /* Set authentication type for authenticated TLS */
        CURLCPP_DEFINE_OPTION(CURLOPT_TLSAUTH_TYPE, long);

        /* Set to 1 to enable the "TE:" header in HTTP requests to ask for
        compressed transfer-encoded responses. Set to 0 to disable the use of TE:
        in outgoing requests. The current default is 0, but it might change in a
        future libcurl release.

        libcurl will ask for the compressed methods it knows of, and if that
        isn't any, it will not ask for transfer-encoding at all even if this
        option is set to 1.

        */
        CURLCPP_DEFINE_OPTION(CURLOPT_TRANSFER_ENCODING, long);

        /* Callback function for closing socket (instead of close(2)). The callback
        should have type curl_closesocket_callback */
        CURLCPP_DEFINE_OPTION(CURLOPT_CLOSESOCKETFUNCTION, int(*)(void *clientp, curl_socket_t item));
        CURLCPP_DEFINE_OPTION(CURLOPT_CLOSESOCKETDATA, void*);

        /* allow GSSAPI credential delegation */
        CURLCPP_DEFINE_OPTION(CURLOPT_GSSAPI_DELEGATION, long);

        /* Set the name servers to use for DNS resolution */
        CURLCPP_DEFINE_OPTION(CURLOPT_DNS_SERVERS, const char*);

        /* Time-out accept operations (currently for FTP only) after this amount
        of miliseconds. */
        CURLCPP_DEFINE_OPTION(CURLOPT_ACCEPTTIMEOUT_MS, long);

        /* Set TCP keepalive */
        CURLCPP_DEFINE_OPTION(CURLOPT_TCP_KEEPALIVE, long);

        /* non-universal keepalive knobs (Linux, AIX, HP-UX, more) */
        CURLCPP_DEFINE_OPTION(CURLOPT_TCP_KEEPIDLE, long);
        CURLCPP_DEFINE_OPTION(CURLOPT_TCP_KEEPINTVL, long);

        /* Enable/disable specific SSL features with a bitmask, see CURLSSLOPT_* */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_OPTIONS, long);

        /* Set the SMTP auth originator */
        CURLCPP_DEFINE_OPTION(CURLOPT_MAIL_AUTH, const char*);

        /* Wait for pipelining/multiplexing */
        CURLCPP_DEFINE_OPTION(CURLOPT_PIPEWAIT, long);

        /* Options added in 7.31 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x071F00
        /* Enable/disable SASL initial response */
        CURLCPP_DEFINE_OPTION(CURLOPT_SASL_IR, long);
#endif

        /* Options added in 7.32 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072000
        /* Function that will be called instead of the internal progress display
        * function. This function should be defined as the curl_xferinfo_callback
        * prototype defines. (Deprecates CURLOPT_PROGRESSFUNCTION) */
        CURLCPP_DEFINE_OPTION(CURLOPT_XFERINFOFUNCTION, curl_xferinfo_callback);
#endif

        /* Options added in 7.33 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072100
        /* The XOAUTH2 bearer token */
        CURLCPP_DEFINE_OPTION(CURLOPT_XOAUTH2_BEARER, const char*);

        /* Set the interface string to use as outgoing network
        * interface for DNS requests.
        * Only supported by the c-ares DNS backend */
        CURLCPP_DEFINE_OPTION(CURLOPT_DNS_INTERFACE, const char*);

        /* Set the local IPv4 address to use for outgoing DNS requests.
        * Only supported by the c-ares DNS backend */
        CURLCPP_DEFINE_OPTION(CURLOPT_DNS_LOCAL_IP4, const char*);

        /* Set the local IPv4 address to use for outgoing DNS requests.
        * Only supported by the c-ares DNS backend */
        CURLCPP_DEFINE_OPTION(CURLOPT_DNS_LOCAL_IP6, const char*);
#endif

		/* Options added in 7.34 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072200
        /* Set authentication options directly */
        CURLCPP_DEFINE_OPTION(CURLOPT_LOGIN_OPTIONS, const char*);
#endif

		/* Options added in 7.36 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072400
        /* Enable/disable TLS NPN extension (http2 over ssl might fail without) */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_ENABLE_NPN, long);

        /* Enable/disable TLS ALPN extension (http2 over ssl might fail without) */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_ENABLE_ALPN, long);

        /* Time to wait for a response to a HTTP request containing an
        * Expect: 100-continue header before sending the data anyway. */
        CURLCPP_DEFINE_OPTION(CURLOPT_EXPECT_100_TIMEOUT_MS, long);
#endif

        /* Options added in 7.37 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072500
        /* This points to a linked list of headers used for proxy requests only,
        struct curl_slist kind */
        CURLCPP_DEFINE_OPTION(CURLOPT_PROXYHEADER, curl_slist*);

        /* Pass in a bitmask of "header options" */
        CURLCPP_DEFINE_OPTION(CURLOPT_HEADEROPT, long);
#endif

        /* Options added in 7.39 */
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072700
        /* The public key in DER form used to validate the peer public key
        this option is used only if SSL_VERIFYPEER is true */
        CURLCPP_DEFINE_OPTION(CURLOPT_PINNEDPUBLICKEY, const char*);
#endif

        // Available since 7.40
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072800
        /* Path to Unix domain socket */
        CURLCPP_DEFINE_OPTION(CURLOPT_UNIX_SOCKET_PATH, const char*);
#endif

        //OCSP STAPLING requires curl 7.41 or later, so check if available
#if defined(LIBCURL_VERSION_NUM) && LIBCURL_VERSION_NUM >= 0x072900
        /* Set if we should verify the certificate status. */
        CURLCPP_DEFINE_OPTION(CURLOPT_SSL_VERIFYSTATUS, long);
#endif
    }
    // End of namespace detail
    
    /**
     * Easy interface is used to make requests and transfers. 
     * You don't have to worry about freeing data or things like
     * that. The class will do it for you.
     */
    class curl_easy : public curl_interface<CURLcode> {
    public:
        /**
         * The default constructor will initialize the easy handler
         * using libcurl functions.
         */
        curl_easy();
        /**
         * This overloaded constructor allows users to specify a
         * stream where they want to put the output of the libcurl
         * operations.
         */
        template<class T> explicit curl_easy(curl_ios<T> &);
        /**
         * This overloaded constructor allows users to specify a flag
         * used to initialize libcurl environment.
         */
        explicit curl_easy(long);
        /**
         * This overloaded constructor specifies the environment
         * initialization flags and an output stream for the libcurl output.
         */
        template<class T> curl_easy(long, curl_ios<T> &);
        /**
         * Copy constructor to handle pointer copy. Internally, it uses
         * a function which duplicates the easy handler.
         */
        curl_easy(const curl_easy &);
        /**
         * Move constructor that moves an easy handler from an istance to
         * another.
         */
        curl_easy(curl_easy &&) NOEXCEPT;
        /**
         * Assignment operator used to perform assignment between objects
         * of this class.
         */
        curl_easy &operator=(const curl_easy &);
        /**
         * Override of equality operator. It has been overridden to check
         * whether two curl_easy objects are equal.
         */
        bool operator==(const curl_easy &) const;
        /**
         * The destructor will perform cleanup operations.
         */
        ~curl_easy() NOEXCEPT override;
        /**
         * Allows users to specify an option for the current easy handler,
         * using a curl_pair object.
         */
        template<typename T> void add(const curl_pair<CURLoption,T>&);
        /**
         * Allows users to specify a list of options for the current
         * easy handler. In this way, you can specify any iterable data
         * structure.
         */
        template<typename Iterator> void add(Iterator, Iterator);
        /**
        * Allows users to specify an option for the current easy handler,
        * specify an option statically and enforce its corresponding type.
        */
        template <CURLoption Opt> void add(detail::Option_type<Opt>);
        /**
         * Using this function, you can explicitly pause a running connection, 
         * and you can resume a previously paused connection.
         */
        void pause(int);
        /**
         * This function converts the given input string to an URL encoded
         * string and returns a newly allocated string.
         */
        void escape(std::string &);
        /**
         * This function converts the given URL encoded input string to a
         * "plain string" and returns a newly allocated string.
         */
        void unescape(std::string &);
        /**
         * This function performs all the operations a user has specified
         * with the add methods. If the performing operation has finished
         * the method returns true otherwise false.
         */
        void perform();
        /**
         * Re-initializes all options previously set on a specified CURL handle
         * to the default values. This puts the handle back to the initial state.
         */
        void reset() NOEXCEPT;
        /**
         * This method allows to get information about the current curl session.
         */
        template<CURLINFO Info> curl_easy_info<detail_info::Info_type<Info>> get_info();
        /**
         * Simple getter method used to return the easy handle.
         */
        CURL *get_curl() const;
    private:
        CURL *curl;
    };
    
    // Implementation of default constructor.
    template<class T> curl_easy::curl_easy(curl_ios<T> &writer) : curl_interface() {
        this->curl = curl_easy_init();
        if (this->curl == nullptr) {
            throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
        }
        this->add(curl_pair<CURLoption,curlcpp_callback_type>(CURLOPT_WRITEFUNCTION,writer.get_function()));
        this->add(curl_pair<CURLoption,void *>(CURLOPT_WRITEDATA, static_cast<void*>(writer.get_stream())));
    }
    
    // Implementation of overridden constructor.
    template<class T> curl_easy::curl_easy(const long flag, curl_ios<T> &writer) : curl_interface(flag) {
        this->curl = curl_easy_init();
        if (this->curl == nullptr) {
            throw curl_easy_exception("Null pointer intercepted",__FUNCTION__);
        }
        this->add(curl_pair<CURLoption, curlcpp_callback_type>(CURLOPT_WRITEFUNCTION,writer.get_function()));
        this->add(curl_pair<CURLoption, void*>(CURLOPT_WRITEDATA, static_cast<void*>(writer.get_stream())));
    }
    
    // Implementation of overloaded add method.
    template<typename Iterator> void curl_easy::add(Iterator begin, const Iterator end) {
        for (; begin != end; ++begin) {
            this->add(*begin);
        }
    }

    // Implementation of overloaded add method.
    template <CURLoption Opt> void curl_easy::add(detail::Option_type<Opt> val) {
        const auto code = curl_easy_setopt(this->curl, Opt, val);
        if (code != CURLE_OK) {
            throw curl_easy_exception(code, __FUNCTION__);
        }
    }

    // Implementation of add method.
    template<typename T> void curl_easy::add(const curl_pair<CURLoption,T>& pair) {
        const CURLcode code = curl_easy_setopt(this->curl,pair.first(),pair.second());
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
    }
    
    // Implementation of get_info method.
    template<CURLINFO Info> curl_easy_info<detail_info::Info_type<Info>> curl_easy::get_info() {
        detail_info::Info_type<Info> val;
        const CURLcode code = curl_easy_getinfo(this->curl,Info,&val);
        if (code != CURLE_OK) {
            throw curl_easy_exception(code,__FUNCTION__);
        }
        curl_easy_info<detail_info::Info_type<Info>> easy_info(val);
        return easy_info;
    }
    
    // Implementation of get_curl method.
    inline CURL *curl_easy::get_curl() const {
        return this->curl;
    }
}

#undef CURLCPP_DEFINE_OPTION
#endif	/* defined(__curlcpp__curl_easy__) */
