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
    mysqlD.database = "movie";	  // the databse

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

