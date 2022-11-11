#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <string.h>

#define RELEASE "1.0.1"

int main(int argc, char *argv[])
{

    // if -a is passed, let all = true
    // if -c is passed, country = true
    // if -l is passed, location = true
    // if -r is passed, region = true
    // if -o is passed, organization = true
    // if -t is passed, timezone = true
    // if -p is passed, postal = true
    // if -h is passed, hostnames = true
    // if -ct is passed, city = true
    // if --help is passed, print help and exit
    // if --version is passed, print version and exit

    // if flags are passed but doesnt match any of the above, print error and exit
    bool all = false;
    bool location = false;
    bool country = false;
    bool region = false;
    bool organization = false;
    bool timezone = false;
    bool postal = false;
    bool hostnames = false;
    bool city = false;
    bool noargs = false;
    if (argc == 2)
    {
        if (strcmp(argv[1], "--version") == 0)
        {
            printf("MyIP Version: %s\n", RELEASE);
            printf("CURL Version: %s\n", curl_version());
            return 0;
        }
        else if (strcmp(argv[1], "-a") == 0)
        {
            all = true;
        }
        else if (strcmp(argv[1], "-l") == 0)
        {
            location = true;
        }
        else if (strcmp(argv[1], "--help") == 0)
        {
            printf("Usage: %s [OPTION]", argv[0]);
            printf(" \
-a: all | \
-l: location | \
-c: country | \
-r: region | \
-o: organization | \
-t: timezone | \
-p: postal | \
-h: hostnames | \
-ct: city | \
--help | \
--version\n");
            return 0;
        }
        else if (strcmp(argv[1], "-c") == 0)
        {
            country = true;
        }
        else if (strcmp(argv[1], "-r") == 0)
        {
            region = true;
        }
        else if (strcmp(argv[1], "-o") == 0)
        {
            organization = true;
        }
        else if (strcmp(argv[1], "-t") == 0)
        {
            timezone = true;
        }
        else if (strcmp(argv[1], "-p") == 0)
        {
            postal = true;
        }
        else if (strcmp(argv[1], "-h") == 0)
        {
            hostnames = true;
        }
        else if (strcmp(argv[1], "-ct") == 0)
        {
            city = true;
        }
        else
        {
            printf("Invalid argument: %s\n", argv[1]);
            printf("Type %s --help for help\n", argv[0]);
            return 1;
        }
    }
    else if (argc > 2)
    {
        printf("Too many arguments\n");
        printf("Type %s --help for help\n", argv[0]);
        return 1;
    }
    else
    {
        noargs = true;
    }

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl)
    {
        if (all)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io");
        }
        else if (location)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/loc");
        }
        else if (country)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/country");
        }
        else if (region)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/region");
        }
        else if (organization)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/org");
        }
        else if (timezone)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/timezone");
        }
        else if (postal)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/postal");
        }
        else if (hostnames)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/hostname");
        }
        else if (city)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/city");
        }
        else if (noargs)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/ip");
        }
    }

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

    // flush stdout
    if (noargs || all)
    {
        printf("\n");
    }

    /* Check for errors */
    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}