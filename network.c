#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mingw\include\curl\curl.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) return 0;
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

// Fixed signature to perfectly match your BONG.c extern reference
void FetchBongData(const char *payload, char *outputBuffer, int maxLen) {
    CURL *curl;
    struct MemoryStruct chunk = { malloc(1), 0 };

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/predict");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        
        if (curl_easy_perform(curl) == CURLE_OK && chunk.memory) {
            snprintf(outputBuffer, maxLen, "%s", chunk.memory);
        } else {
            snprintf(outputBuffer, maxLen, "[!] Server Offline. Running fallback mode.");
        }
        curl_easy_cleanup(curl);
    }
    free(chunk.memory);
}
