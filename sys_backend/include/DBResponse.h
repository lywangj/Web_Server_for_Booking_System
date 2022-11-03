#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <mysql/mysql.h>

using namespace std;

typedef struct connection_details
{
    const char *server, *user, *pwd, *database;
} Cdetails;

typedef struct Member_details
{
    const string name, email;
    const int event, seat;
} Member_d;

typedef struct Event_details
{
    string id, name, genre, format, showDate, showTime, ticketPrice, seat;
} Event_d;

class DBResponse {
    
private:

    MYSQL* conn;
    // int qstate;


public:

    DBResponse() {

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

    int add_particpant_to_db(const string name, const string email, const int event, const int seat) {

        string insert_query = 
            "insert into member_tb (name, email, event, seat) values ('" \
                +name+"','"+email+"','"+to_string(event)+"', '"+to_string(seat)+"')";

        // c_str converts string to constant char and this is required
        const char* q = insert_query.c_str(); 

        int qstate = mysql_query(conn, q);

        if (!qstate) {
            cout << endl << "Successfully added in database." << endl;
            return 1;
        }

        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        return 0;
    }

};
