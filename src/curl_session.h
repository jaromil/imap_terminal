#ifndef __curl_session__
#define __curl_session__

#include <string>
#include <exception>
#include <vector>
#include <curl/curl.h>
#include <stdexcept>

namespace imap_terminal
{
    class CCurlSession
    {
    public:
        CCurlSession();
        virtual ~CCurlSession();

        class CCUrlRuntimeError : public std::runtime_error
        {
        public:
            CCUrlRuntimeError(const std::string& message);
        };

    protected:
        const CURL* easyHandle() const;
        CURL* easyHandle();
        
        virtual void handleData(std::string data);

        void perform();

        //cURL slist wrapper
        class CSList
        {
        public:
            CSList();
            virtual ~CSList();

            CSList& operator<<(const std::string& s);
            struct curl_slist* slist();
            
        private:
            CSList(const CSList&);
            struct curl_slist* m_pCurlSList;
        };

    private:
        static void __globalInit();
        static bool __global_init;

        CCurlSession(const CCurlSession&);
        void raiseCurlRuntimeError() const;
        
        CURL* m_EasyHandle;
        std::vector<char> m_ErrorBuffer;

        static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
        std::string m_sCurlOutput;
    };
}

#endif