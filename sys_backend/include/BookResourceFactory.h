#pragma once

#include <string>
#include <tuple>

#include "DBResponse.h"
#include "IResourceFactory.h"

class BookResourceFactory : public IResourceFactory {

public:

    BookResourceFactory();
    shared_ptr<Resource> get_resource() const final;

private:

    // float calculate(float num1, float num2, string operation);

    tuple<string, string, int, int> 
            get_path_parameters(const shared_ptr<Session> session) const;
            
    string to_json(int result);

    void get_handler(const shared_ptr<Session> session);

    shared_ptr<Resource> _resource;
};