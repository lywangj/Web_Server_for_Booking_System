// cmake -Hsys_backend -Bsys_backend/build
// cmake --build sys_backend/build --config Release --target all

// sys_backend/build/BookingAPI

#include <cstdlib>
#include <iostream>
#include "BookResourceFactory.h"
#include "BookServiceSettingsFactory.h"
#include "BookService.h"


int main(const int, const char**)
{
    auto book_resource_factory = make_shared<BookResourceFactory>();
    auto book_service_settings_factory = 
        make_shared<BookServiceSettingsFactory>();
    
    BookService calc_service {
        book_resource_factory, book_service_settings_factory};

    std::cout << "Web Server Connected Successfully ... " << endl;

    calc_service.start();
    
    return EXIT_SUCCESS;
}
