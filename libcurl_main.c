#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream) {
    char *output = (char *)stream;
    if (strlen(output) + strlen((char *)buffer) > 999999) return 0;
    strcat(output, (char *)buffer);
    
    printf("size = %d nmemb = %d\n", size, nmemb);
    return size*nmemb;
}

int main(void)
{
    CURL *curl;
    CURLcode res;
    char str[100000];


    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl) {
//Get
#if 1
        curl_easy_setopt(curl, CURLOPT_URL, "https://210.13.68.150:20011/app-avn/network/1.0/genWitoken");
#else   
//Check
        curl_easy_setopt(curl, CURLOPT_URL, "https://210.13.68.150:20011/app-avn/network/1.0/checkWitoken");
#endif   
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, str);

//POST
//Get
#if 1
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "data={\"token\":\"eaf687469b55b0398eee81e612f8f183\",\"timestamp\":\"\",\"vin\":\"5iyT\"}");
#else
//Check			
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "data={\"token\":\"eaf687469b55b0398eee81e612f8f183\",\"timestamp\":\"\",\"vin\":\"5iyT\", \"witoken\":\"bf713500c764f7dea3f41b039198b65b\"}");
#endif

		struct curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/x-www-form-urlencoded");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                     curl_easy_strerror(res));

        str[9999] = '/0';
        printf("str \n %s \n", str);

        curl_slist_free_all(plist);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
