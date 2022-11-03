#include "BookResourceFactory.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "json.hpp"
#include "DBResponse.h"

using namespace nlohmann;

BookResourceFactory::BookResourceFactory() {
    std::cout << "BookResourceFactory1" << endl;
    DBResponse dbserver {};
    _dbserver = dbserver;
    _resource = make_shared<Resource>();
    _resource->set_path(
        // "/events"
        "/{name: .+}"
        "/{email: .+}"
        "/{event: [0-9]*}"
        "/{seat: [0-9]*}");
    std::cout << "BookResourceFactory2" << endl;
    _resource->set_method_handler("GET", 
        [&](const auto session) {
            get_handler(session);
        });
    std::cout << "BookResourceFactory3" << endl;
}

shared_ptr<Resource> BookResourceFactory::get_resource() const {
        return _resource;
}

// float BookResourceFactory::calculate(float num1, float num2, string operation) {
//     if(operation == "add") {
//         return num1 + num2;
//     }
//     else if(operation == "subtract") {
//         return num1 - num2;
//     }
//     else if(operation == "multiply") {
//         return num1 * num2;
//     }
//     else if(operation == "divide") {
//         return num1 / num2;
//     }
// }

tuple<string, string, int, int> BookResourceFactory::get_path_parameters(
        const shared_ptr<Session> session) const {
    const auto& request = session->get_request();
    const auto applied_name = request->get_path_parameter("name");
    const auto applied_email = request->get_path_parameter("email");
    auto applied_event = atoi(request->get_path_parameter("event").c_str());
    auto applied_seat = atoi(request->get_path_parameter("seat").c_str());
    std::cout << "Recieved data : " << applied_name << " " << applied_email \
        << " " << applied_event << " " << applied_seat << endl;
    return make_tuple(applied_name, applied_email, applied_event, applied_seat);
} 

string BookResourceFactory::to_json(int update_result) {
    ostringstream str_stream;
    str_stream << update_result;
    json jsonResult = {
        {"result", str_stream.str()}
    };
    return jsonResult.dump();
}

void BookResourceFactory::get_handler(const shared_ptr<Session> session) {
    const auto [name, email, booked_event, booked_seats] = get_path_parameters(session);
    // auto result = calculate(num1, num2, operation);
    int result = 1;

    result = _dbserver.add_particpant_to_db(name, email, booked_event, booked_seats);
    // _dbserver.test();

    std::cout << "BookResourceFactory: get_handler1" << endl;
    auto content = to_json(result);
    std::cout << "BookResourceFactory: get_handler2" << endl;
    // session->close(restbed::OK);
    session->close(OK, content, 
        {{"Content-Type", "application/json"},
         {"Content-Length", to_string(content.size())}});
    std::cout << "BookResourceFactory: get_handler3" << endl;
}