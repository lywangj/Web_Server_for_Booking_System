cmake_minimum_required(VERSION 3.0)

project(BookingAPI)

add_executable(BookingAPI 
    main.cpp 
    BookResourceFactory.cpp
    BookService.cpp
    BookServiceSettingsFactory.cpp)
target_link_libraries(BookingAPI restbed)
target_link_libraries(BookingAPI mysqlclient)
target_link_options(BookingAPI PUBLIC -L/usr/lib/mysql)
target_include_directories(BookingAPI PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_property(TARGET BookingAPI PROPERTY CXX_STANDARD 17)