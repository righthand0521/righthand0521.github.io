#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curl/curl.h>


struct upload_status {
    int lines_read;
};
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1))
    {
        return 0;
    }

    char *payload_text[] = {
        "From: " "" "\r\n",
        "To: " "" "\r\n",
        "Subject: libcurl Test\r\n",
        "Hello, libcurl.",
        NULL
    };
    const char *data = payload_text[upload_ctx->lines_read];
    if (!data)
    {
        return 0;
    }
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;

    return len;
}
#define MAIL_SERVER     "smtp://msa.hinet.net"
#define MAIL_FROM       "righthand0521@gmail.com"
#define MAIL_TO         "righthand0521@gmail.com"
int send_mail()
{
    CURL *curl = curl_easy_init();
    if (curl == NULL)
    {
        fprintf(stderr, "[%s][%d]ERROR: %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return (int)CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, MAIL_SERVER);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, MAIL_FROM);
    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, MAIL_TO);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    struct upload_status upload_ctx;
    upload_ctx.lines_read = 0;
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK)
    {
        printf("[%s][%d]Send Mail from %s to %s Successfully\n", __FUNCTION__, __LINE__, MAIL_FROM, MAIL_TO);
    }
    else
    {
        fprintf(stderr, "[%s][%d]ERROR: %s\n", __FUNCTION__, __LINE__, curl_easy_strerror(res));
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    return (int)res;
}

int http_request()
{
    CURL *curl = curl_easy_init();
    if (curl == NULL)
    {
        fprintf(stderr, "[%s][%d]ERROR: %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return (int)CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    // example.com is redirected, so we tell libcurl to follow redirection
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Perform the request, res will get the return code
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "[%s][%d]ERROR: %s\n", __FUNCTION__, __LINE__, curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);

    return (int)res;
}


int main(int argc, char **argv)
{
    typedef int (*executeFunc)();
    struct exampleType {
        char *functionName;
        executeFunc eFunc;
    } example[] = {
        {"HTTP Request", http_request}
        , {"Send Email", send_mail}
    };
    int numberOfExample = sizeof(example) / sizeof(example[0]);

    int option;
    if (argc != 2)
    {
        printf("Usage: %s <Option>\n", argv[0]);
        for (option=0; option<numberOfExample; ++option)
        {
            printf("%3d. %s\n", (option+1), example[option].functionName);
        }
        return EXIT_SUCCESS;
    }

    option = atoi(argv[1]);
    if ((option > numberOfExample) || (option < 1))
    {
        fprintf(stderr, "ERROR Option!\n");
        return EXIT_FAILURE;
    }
    int retVal = example[option-1].eFunc();
    if (retVal != CURLE_OK)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

