#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

int json = 1;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void printUsage()
{
    const char* usage = 
    "Usage: "
    "bible_cli $book $chapter [$verse]"

    "Example: "
    "bible_cli ephesians 2 9";

    printf("%s\n", usage);
}

int main(int argc, char** argv)
{
    // create curl object
    std::string url = "https://mintz5.duckdns.org/bible";

    if(argc >= 3){
        for(int i = 1; i <= argc-1; i++)
        {
            url = url + "/" + argv[i];
        }
    }else{
        printUsage();
        return 1;
    }

    if(json)
    {
        url += "?json=true";
    }
    
    CURL *curl;
    // CURLcode res;
    std::string rBuff;

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rBuff);
        // res = curl_easy_perform(curl);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }else
    {
        std::cout << "curl_easy_init() failed\n";
    }    
    // Remove unwanted fields
    rapidjson::Document d;
    rapidjson::ParseResult ok = d.Parse(rBuff.c_str());
    std::vector<std::string> unwanted{
      "Color",
      "NextChapterLink",
      "PreviousChapterLink",
      "ListAllBooksLink",
      "StartVerse",
      "EndVerse",
      "SingleVerse",
      "HTMLTitle",
    };
    for (int i=0; i < unwanted.size(); i++){
      d.RemoveMember(unwanted[i].c_str());
    }
    rapidjson::StringBuffer buff; //(d.GetAllocator());
    rapidjson::Writer<rapidjson::StringBuffer>writer(buff);
    d.Accept(writer);
    std::cout << buff.GetString() << std::endl;

}
