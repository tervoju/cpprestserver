
#include <unistd.h>
#include <jsoncpp/json/json.h>

#include "lithium_http_server.hh"

int sr_start(int profiles, int frequency)
{

    sleep(10);
    return 0;
}

int main()
{

    // Define an api with one HTTP GET route.

    li::http_api api;
    api.get("/hello") = [&](li::http_request &request, li::http_response &response)
    {
        //auto params = request.get_parameters(s::my_param = int(), s::my_param2 = std::string());
        //response.write("hello " + params.param2);
        response.write("hello ");
    };
     api.post("/smartray") = [&](li::http_request &request, li::http_response &response)
    {
        //Json::Value body;
        std::cout << "post smartray" << std::endl;
        auto params = request.post_parameters(s::name = std::string(), s::type = std::string(), s::json_key = std::string());
        std::cout << "smartray: " << params.json_key << std::endl;
        response.write("smartray "+ params.json_key);
    };
    api.post("/dude/{{name}}") = [&](li::http_request &request, li::http_response &response)
    {
        std::cout << "post dude" << std::endl;
        auto params = request.url_parameters(s::name = std::string());
        //auto body = request.body();
        response.write("hello " + params.name);
        //response.write("dude "); 
    };

    // Start a http server.
    li::http_serve(api, 8876);
}