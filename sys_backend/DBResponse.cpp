// g++ main.cpp -o output -L/usr/lib/mysql -lmysqlclient

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "DBResponse.h"
#include <mysql/mysql.h>


using namespace std;

MYSQL* conn;


// typedef struct connection_details
// {
//     const char *server, *user, *pwd, *database;
// } Cdetails;


DBResponse::DBResponse() {
    // cout << server << " " << user << " " << pwd << " " << database << endl;

    Cdetails mysqlD;
    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "root";         // user
    mysqlD.pwd = "og21893";       // the password for the database
    mysqlD.database = "events";	  // the databse

    conn = mysql_init(0);
    if (conn) {
        cout << "Database Connected" << endl;
        cout << "Wait to continue..." << endl;
    } else {
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
        
    conn = mysql_real_connect \
        (conn, mysqlD.server, mysqlD.user, mysqlD.pwd, mysqlD.database, 0, NULL, 0);
    if (conn) {
        cout << "Database Connected To MySql" << conn << endl;
        cout << "Wait to continue..." << endl;
    } else {
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
}

void test() {
    cout << "test" << endl;
}

int add_particpant_to_db(const string name, const string email, const int event, const int seat) {

    // Member_d member;

    string insert_query = 
        "insert into member_tb (name, email, event, seat) values ('" \
            +name+"','"+email+"','"+to_string(event)+"', '"+to_string(seat)+"')";

    cout << insert_query << endl;

    // c_str converts string to constant char and this is required
    const char* q = insert_query.c_str(); 

    // MYSQL* conn = DBResponse::get_conn();

    int qstate = mysql_query(conn, q);

    if (!qstate) {
        cout << endl << "Successfully added in database." << endl;
        return 1;
    }

    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    return 0;
    
}