
#include <unistd.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <thread>   

#include "lithium_http_server.hh"

using namespace std;

bool capturePointCloud = false;
    int frequency = 0;
    int profiles = 0;

int sr_start(int profiles, int frequency)
{
    std::cout << "capture pointcloud: " << frequency << std::endl;
    sleep(10);
    capturePointCloud = false;
    return 0;
}
void sr_driver()
{

while(1)
    {
        if (capturePointCloud)
        {
            std::cout << "capture pointcloud " << frequency << std::endl;
            sr_start(frequency, profiles);
        }
        sleep(1);
    }
}

void sr_api()
{
      li::http_api api;

    api.get("/smartray") = [&](li::http_request &request, li::http_response &response)
    {
        response.write("Smartray ECCO65 - use POST for configuring data capture");
    };

    api.post("/smartray") = [&](li::http_request &request, li::http_response &response)
    {
        Json::Value bodyJson;
        Json::Reader jsonReader;
        std::cout << "post smartray" << std::endl;
        auto params = request.post_parameters(s::name = std::string(), s::type = std::string(), s::json_key = std::string());
        std::cout << "smartray: " << params.json_key << std::endl;
        auto body = response.http_ctx.body_;
        std::string bodyString = std::string(body).c_str();
        bool parsingOK = jsonReader.parse(bodyString, bodyJson);
        if (parsingOK)
        {
            std::cout << "OK parsing the string" << std::endl;
            frequency = bodyJson["frequency"].asInt();
            profiles = bodyJson["profiles"].asInt();
            capturePointCloud = true;

        }
        response.write("smartray request reseived - ok");
    };
    // Start a http server.
    li::http_serve(api, 8876);

}

int main()
{


    // init stuff and create connection to scanner
    // init rest api

    // thread to start scanner
    // thread to create api

    std::thread sr_thread (sr_driver);   
    std::thread sr_api_thread (sr_api);

    // synchronize threads:
    sr_thread.join();                
    sr_api_thread.join();              
    std::cout << "threads completed.\n";
}