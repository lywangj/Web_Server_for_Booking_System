#include "BookResourceFactory.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <string>
#include "json.hpp"
#include "DBResponse.h"

mutex task_mutex;

using namespace nlohmann;

BookResourceFactory::BookResourceFactory() {

    DBResponse dbserver {};
    _dbserver = dbserver;

    _resource = make_shared<Resource>();
    _resource->set_path(
        "/{name: .+}"
        "/{email: .+}"
        "/{event: [0-9]*}"
        "/{seat: [0-9]*}");
    _resource->set_method_handler("GET", 
        [&](const auto session) {
            get_handler(session);
        });
}

shared_ptr<Resource> BookResourceFactory::get_resource() const {
        return _resource;
}

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

// void add_booking(string name, string email, int event, int seat) {
//     // _dbserver.add_particpant_to_db(name, email, event, seat);
//     cout << " dd " << name << endl;
// }

void BookResourceFactory::get_handler(const shared_ptr<Session> session) {
    const auto [name, email, booked_event, booked_seats] = get_path_parameters(session);

    int result = 1;

    auto add_booking = [](DBResponse _dbserver, const string name, \
                            const string email, const int event, const int seat) {
        _dbserver.add_particpant_to_db(name, email, event, seat);
    };

    auto record_booking = [](DBResponse _dbserver, const int event, const int seat) {
        unique_lock<mutex> lk(task_mutex);
        _dbserver.book_seats_to_db(event, seat);
        lk.unlock();
    };

    thread recorder(record_booking, _dbserver, booked_event, booked_seats);
    thread adder(add_booking, _dbserver, name, email, booked_event, booked_seats);
    

    adder.join();
    recorder.join();

    auto content = to_json(result);
    // session->close(restbed::OK);
    session->close(OK, content, 
        {{"Content-Type", "application/json"},
         {"Content-Length", to_string(content.size())}});
}