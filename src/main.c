#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // if --version is passed, print version and exit
    if (argc > 1 && strcmp(argv[1], "--version") == 0)
    {
        printf("%s", curl_version());
        return 0;
    }
    // if -a is passed, let all = true
    bool all = false;
    if (argc > 1 && strcmp(argv[1], "-a") == 0)
    {
        all = true;
    }
    // if -l is passed, location = true

    bool location = false;
    if (argc > 1 && strcmp(argv[1], "-l") == 0)
    {
        location = true;
    }
    // if -c is passed, country = true
    // if -r is passed, region = true
    // if -o is passed, organization = true
    // if -t is passed, timezone = true
    // if -p is passed, postal = true
    // if -h is passed, hostnames = true
    // if -ct is passed, city = true
    // if --help is passed, print help and exit

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
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
--version");
        return 0;
    }
    bool country = false;
    if (argc > 1 && strcmp(argv[1], "-c") == 0)
    {
        country = true;
    }
    bool region = false;
    if (argc > 1 && strcmp(argv[1], "-r") == 0)
    {
        region = true;
    }
    bool organization = false;
    if (argc > 1 && strcmp(argv[1], "-o") == 0)
    {
        organization = true;
    }
    bool timezone = false;
    if (argc > 1 && strcmp(argv[1], "-t") == 0)
    {
        timezone = true;
    }
    bool postal = false;
    if (argc > 1 && strcmp(argv[1], "-p") == 0)
    {
        postal = true;
    }
    bool hostnames = false;
    if (argc > 1 && strcmp(argv[1], "-h") == 0)
    {
        hostnames = true;
    }
    bool city = false;
    if (argc > 1 && strcmp(argv[1], "-ct") == 0)
    {
        city = true;
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
        else
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/ip");
        }

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}