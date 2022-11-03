#include <cstdlib>
#include <iostream>
#include "BookResourceFactory.h"
#include "BookServiceSettingsFactory.h"
#include "BookService.h"
// #include "DBResponse.h"
// #include <mysql/mysql.h>

// using namespace std;


int main(const int, const char**)
{
    auto book_resource_factory = make_shared<BookResourceFactory>();
    auto book_service_settings_factory = 
        make_shared<BookServiceSettingsFactory>();

    std::cout << "Web Server starts ...1" << endl;
    
    BookService calc_service {
        book_resource_factory, book_service_settings_factory};

    std::cout << "Web Server starts ...2" << endl;

    calc_service.start();

    std::cout << "Web Server starts ...3" << endl;
    
    return EXIT_SUCCESS;
}

// cmake -Hsys_backend -Bsys_backend/build
// cmake --build sys_backend/build --config Release --target all

// sys_backend/build/BookingAPI