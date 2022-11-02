#pragma once
// #ifndef __DB_RESPONSE_H__
// #define __DB_RESPONSE_H__
// #include <iostream>
// #include <fstream>
// #include <vector>
#include <string>
// #include <cassert>
#include <mysql/mysql.h>
// #include "interface.h"

using namespace std;
// int qstate;
// MYSQL* conn;
// MYSQL_ROW row;
// MYSQL_RES* res;

    // MYSQL* conn;
    // int qstate;

typedef struct connection_details
{
    const char *server, *user, *pwd, *database;
} Cdetails;

typedef struct Member_details
{
    const string name, email;
    const int event, seat;
} Member_d;

typedef struct Movie_details
{
    string id, name, genre, format, showDate, showTime, ticketPrice, seat;
} Movie_d;

class DBResponse {
    
private:

    // MYSQL* conn;
    // int qstate;


public:

    MYSQL* conn;
    int qstate;

    DBResponse();

    int add_particpant_to_db(const string name, const string email, const int event, const int seat);

    // void connecting();

    // void connecting() {
    // // cout << server << " " << user << " " << pwd << " " << database << endl;

    //     Cdetails mysqlD;
    //     mysqlD.server = "localhost";  // where the mysql database is
    //     mysqlD.user = "root";         // user
    //     mysqlD.pwd = "og21893";       // the password for the database
    //     mysqlD.database = "movie";	  // the databse

    //     conn = mysql_init(0);
    //     if (conn) {
    //         cout << "Database Connected" << endl;
    //         cout << "Wait to continue..." << endl;
    //     } else {
    //         cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    //     }
        
    //     conn = mysql_real_connect \
    //         (conn, mysqlD.server, mysqlD.user, mysqlD.pwd, mysqlD.database, 0, NULL, 0);
    //     if (conn) {
    //         cout << "Database Connected To MySql" << conn << endl;
    //         cout << "Wait to continue..." << endl;
    //     } else {
    //         cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    //     }
    // }

/*
    static int ShowMovieList() {

        print_title();
        qstate = mysql_query(conn, "select * from movie_tb");
        if (!qstate) {
            res = mysql_store_result(conn);
            printf("-------------------------------------------------------------------------------------------------------------\n");
            printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Name", "Genre", "Format", "Show Date", "Show Time", "Price");
            printf("-------------------------------------------------------------------------------------------------------------\n");
            while ((row = mysql_fetch_row(res)))
            {
                printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
            }
            printf("-------------------------------------------------------------------------------------------------------------\n");
        }
        else {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        return print_bottom_line();
    }


    static int ShowMyTicket() {

        string input;
        print_title();
        cin.ignore(1, '\n');
        cout << "Enter Your Id Or Name: ";
        getline(cin, input);
        string findbyname_query = "select * from  customer_tb where id = '"+input+"' or name = '"+input+"'";
        const char* qn = findbyname_query.c_str();
        qstate = mysql_query(conn, qn);

        cout << endl;
        int c = 0;
        if (!qstate) {
            res = mysql_store_result(conn);
            while ((row = mysql_fetch_row(res))) {
                cout << "ID: " << row[0] << "\nName: " << row[1] << "\nPhone: " << row[2] << "\nMovie: " << row[3] << "\nFormat: " << row[4] << "\nSeat: " << row[5] << "\nPrice: " << row[6] << "\nShow Date: " << row[7] << "\nShow Time: " << row[8] << endl << endl;
                c++;
            }

            if (c == 0) {
                cout << "No ticket with this input" << endl;
            }
        }
        else
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

        char choose;
        cout << "Press 'y' to Search again, other to continue:";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
            return ShowMyTicket();
        else
            return print_bottom_line();
    }

    static int CheckSeat() {

        print_title();

        cin.ignore(1, '\n');
        qstate = mysql_query(conn, "select * from  movie_tb");

        if (!qstate){
            res = mysql_store_result(conn);
            printf("-------------------------------------\n");
            printf("| %-15s | %-15s |\n", "Name", "Seat");
            while ((row = mysql_fetch_row(res))) {
                printf("| %-15s | %-15s |\n", row[1], row[7]);
            }
            printf("-------------------------------------\n");
        }
        else
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        
        return print_bottom_line();
    }

    static int AddNewMovie() {

        Movie_d new_movie;

        cin.ignore(1, '\n');
        cout << "Enter Name: ";
        getline(cin, new_movie.name);
        cout << "Enter Genre: ";
        getline(cin, new_movie.genre);
        cout << "Enter format: ";
        getline(cin, new_movie.format);
        cout << "Enter Show Date (dd-mm-yyyy): ";
        getline(cin, new_movie.showDate);
        cout << "Enter Show Time: ";
        getline(cin, new_movie.showTime);
        cout << "Enter Ticket Price: ";
        getline(cin, new_movie.ticketPrice);
        cout << "Enter Seat: ";
        getline(cin, new_movie.seat);

        string insert_query = 
            "insert into movie_tb (m_name, m_genre, m_format, m_showdate, m_showtime, m_ticketprice, m_seat) \
                values ('"+new_movie.name+"','"+new_movie.genre+"','"+new_movie.format+"', \
                STR_TO_DATE('"+new_movie.showDate+"', '%d-%m-%Y'),'"+new_movie.showTime+"', \
                '"+new_movie.ticketPrice+"', '"+new_movie.seat+"')";

        // c_str converts string to constant char and this is required
        const char* q = insert_query.c_str(); 

        qstate = mysql_query(conn, q);

        if (!qstate) {
            cout << endl << "Successfully added in database." << endl;
        }
        else
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

        char choose;
        cout << "Press 'y' to Insert again, other to continue:";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
            return AddNewMovie();
        else
            return print_bottom_line();
    }

    static int DeleteMovie() {

        int itemId;
        string items[5000];
        int indexForId = 0;
        bool HaveException = false, NotInDatabase = false;

        print_title();
        qstate = mysql_query(conn, "select * from movie_tb");
        if (!qstate) {
            res = mysql_store_result(conn);
            printf("--------------------------------------------------\n");
            printf("| %-10s | %-15s | %-15s |\n", "Column Id", "Name", "Price");
            printf("--------------------------------------------------\n");
            while ((row = mysql_fetch_row(res))) {
                printf("| %-10s | %-15s | %-15s |\n", row[0], row[1], row[6]);
                items[indexForId] = row[0];
                indexForId++;
            }
            printf("--------------------------------------------------\n");
        }
        else
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

        try {
            cout << endl;
            cout << "Enter Item ID: ";
            cin >> itemId;
            cout << endl;
        }
        catch (exception e) {
            cout << "Please Enter a valid NUMBER." << endl;
            HaveException = true;
            goto ExitMenu;
        }

        if (HaveException == false) {
            stringstream streamid;
            string strid;
            streamid << itemId;
            streamid >> strid;

            for (int i = 0; i < indexForId; i++) {
                if (strid != items[i])
                    NotInDatabase = true;
                else
                    NotInDatabase = false;
                    break;
            }

            if (NotInDatabase == false) {
                string delete_query = "delete from movie_tb where m_id = '"+strid+"'";
                const char* qd = delete_query.c_str();
                qstate = mysql_query(conn, qd);

                if (!qstate)
                    cout << "Successfully Deleted." << endl;
                else
                    cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }
            else
                cout << "Item Not Found in database." << endl;
        }
        ExitMenu:
        char choose;
        cout << "Press 'y' to Delete another, other to continue:";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
            return DeleteMovie();
        else
            return print_bottom_line();
    }


    static int EditMovie() {

        Movie_d original_movie;
        Movie_d modified_movie;

        string items[5000];
        int itemId;
        bool HaveException = false;
        bool NotInDatabase = false;
        int indexForId = 0;

        print_title();
        qstate = mysql_query(conn, "select m_id, m_name from movie_tb");
        if (!qstate) {
            res = mysql_store_result(conn);
            printf("--------------------------------\n");
            printf("| %-10s | %-15s |\n", "Column Id", "Name");
            while ((row = mysql_fetch_row(res))) {
                printf("| %-10s | %-15s |\n", row[0], row[1]);
                items[indexForId] = row[0];
                indexForId++;
            }
            printf("--------------------------------\n");
        } else
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

        try {
            cout << endl;
            cout << "Enter Item ID: ";
            cin >> itemId;
            cout << endl;
        }
        catch (exception e) {
            cout << "Please Enter a valid NUMBER." << endl;
            HaveException = true;
            goto ExitMenu;
        }

        if (HaveException == false) {
            stringstream streamid;
            string strid;
            streamid << itemId;
            streamid >> strid;

            for (int i = 0; i < indexForId; i++) {
                if (strid != items[i]) {
                    NotInDatabase = true;
                } else {
                    NotInDatabase = false;
                    break;
                }
            }

            if (NotInDatabase == false) {
                string findbyid_query = "select * from movie_tb where m_id = '"+strid+"'";
                const char* qi = findbyid_query.c_str();
                qstate = mysql_query(conn, qi);

                if (!qstate) {
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res)) {
                        cout << "Column ID: " << row[0] << "\nName: "
                             << row[1] << "\nGenre: " << row[2] << "\nFormat: " << row[3] << "\nShow Date: " << row[4] << "\nShow Time: " << row[5] << "\nTicket Price: " << row[6] << "\nSeat: " << row[7] << endl << endl;

                        // original_movie.id = row[0];
                        original_movie.name = row[1];
                        original_movie.genre = row[2];
                        original_movie.format = row[3];
                        original_movie.showDate = row[4];
                        original_movie.showTime = row[5];
                        original_movie.ticketPrice = row[6];
                        original_movie.seat = row[7];
                        // modified_movie
                    }
                } else
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

                cin.ignore(1, '\n');
                string defaultString = "xN";
                cout << "Enter Name (" << defaultString << "  to not change): ";
                getline(cin, modified_movie.name);
                if (modified_movie.name == defaultString)
                    modified_movie.name = original_movie.name;
                cout << "Enter Genre (" << defaultString << "  to not change): ";
                getline(cin, modified_movie.genre);
                if (modified_movie.genre == defaultString)
                    modified_movie.genre = original_movie.genre;
                cout << "Enter Format (" << defaultString << "  to not change): ";
                getline(cin, modified_movie.format);
                if (modified_movie.format == defaultString)
                    modified_movie.format = original_movie.format;
                cout << "Enter Show Date (" << defaultString << "  to not change): ";
                getline(cin, modified_movie.showDate);
                if (modified_movie.showDate == defaultString)
                    modified_movie.showDate = original_movie.showDate;
                cout << "Enter Show Time (" << defaultString << "  to not change): ";
                getline(cin, modified_movie.showTime);
                if (modified_movie.showTime == defaultString)
                    modified_movie.showTime = original_movie.showTime;
                cout << "Enter Ticket Price (" << defaultString << "  to not change): ";
                cin >> modified_movie.ticketPrice;
                if (modified_movie.ticketPrice == defaultString)
                    modified_movie.ticketPrice = original_movie.ticketPrice;
                cout << "Enter Seat (" << defaultString << "  to not change): ";
                cin >> modified_movie.seat;
                if (modified_movie.seat == defaultString)
                    modified_movie.seat = original_movie.seat;

                string update_query = "update movie_tb set m_name = '" \
                    +modified_movie.name+"', m_genre = '"+modified_movie.genre+"', m_format = '" \
                    +modified_movie.format+"', m_showdate = '"+modified_movie.showDate+"', m_showtime = '" \
                    +modified_movie.showTime+"', m_ticketprice = '"+modified_movie.ticketPrice+"', m_seat = '" \
                    +modified_movie.seat+"' where m_id = '"+strid+"'";
                const char* qu = update_query.c_str();
                qstate = mysql_query(conn, qu);

                if (!qstate)
                    cout << endl << "Successfully Saved In Database." << endl;
                else
                    cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            else
                cout << "Item Not Found in database." << endl;
        }
        ExitMenu:
        char choose;
        cout << "Press 'y' to Edit another, other to continue:";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
            return EditMovie();
        else
            return print_bottom_line();
    }

    static int BookTicket() {

        string c_name = "";
        string c_phone = "";
        string c_seat = "";
        string getId = "";
        char chooseEditOrBuy;
        int itemIndex = 0;
        float totalPrice = 0.0;
        string totPrice = "";
        bool purchase, itemFalse = false, exitcode = false;

        string storeId[5000];
        Movie_d tgt_movie;
        // string storeid = "";
        // string storename = "";
        // string storegenre = "";
        // string storeformat = "";
        // string storeshowDate = "";
        // string storeshowTime = "";
        // string storeticketPrice = "";
        // string storeseat = "";
        int storeIndex = 0, storeIndexN = 0;

        print_title();
        qstate = mysql_query(conn, "select * from movie_tb");
        if (!qstate) {

            res = mysql_store_result(conn);

            printf("---------------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-15s | %-7s | %-15s | %-15s | %-10s | %-5s |\n", "Column Id", "Name", "Format", "Show Date", "Show Time", "Price", "Seat");
            while ((row = mysql_fetch_row(res))) {

                if (atoi(row[7]) > 0) {
                    printf("| %-10s | %-15s | %-7s | %-15s | %-15s | %-10s | %-5s |\n", row[0], row[1], row[3], row[4], row[5], row[6], row[7]);
                    storeId[storeIndex] = row[0];
                    storeIndex++;
                }
            }
            printf("---------------------------------------------------------------------------------------------------\n");
        }
        else
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

        itemFalse = true;
        for (;;) {
            cout << "Enter a Movie ID's (q to exit): ";
            cin >> getId;

            if (getId == "q") {
                exitcode = true;
                break;
            }

            for(int i = 0; i < storeIndex; i++) {
                if (getId == storeId[i]) {
                    itemFalse = false;
                    break;
                }
            }
            if (itemFalse) {
                cout << "Enter a valid number." << endl;
                itemFalse = true;
            } else
                break;
        }

        if (!exitcode) {
            cout << "Enter Customer Name: "; cin >> c_name;
            cout << "Enter Customer Phone: "; cin >> c_phone;
            cout << "Book Seat: "; cin >> c_seat;

            string selectMovie = "select * from movie_tb where m_id = '"+getId+"'";
            const char* qn = selectMovie.c_str();
            qstate = mysql_query(conn, qn);

            if (!qstate) {
                res = mysql_store_result(conn);

                printf("--------------------------------------------------------------------\n");
                printf("| %-10s | %-15s | %-15s | %-15s |\n", "Column Id", "Name", "Format", "Price");
                while ((row = mysql_fetch_row(res))) {
                    if (atoi(row[7]) > 0) {
                        printf("| %-10s | %-15s | %-15s | %-15s |\n", row[0], row[1], row[3], row[6]);
                        tgt_movie.id = row[0];
                        tgt_movie.name = row[1];
                        tgt_movie.genre = row[2];
                        tgt_movie.format = row[3];
                        tgt_movie.showDate = row[4];
                        tgt_movie.showTime = row[5];
                        tgt_movie.ticketPrice = row[6];
                        tgt_movie.seat = row[7];
                    }
                }
                printf("--------------------------------------------------------------------\n");
            } else
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

            string updatQuery = "update movie_tb set m_seat = m_seat - '"+c_seat+"' where m_id = '" +getId+ "'";
            const char* un = updatQuery.c_str();
            qstate = mysql_query(conn, un);

            totalPrice = strtof((tgt_movie.ticketPrice).c_str(), 0) * strtof((c_seat).c_str(), 0);
            stringstream tPrice;
            tPrice << totalPrice;
            tPrice >> totPrice;

            string insert_query = \
                "insert into customer_tb (name, phone, movie, format, seat, price, showdate, showtime) values ('" \
                    +c_name+"','"+c_phone+"','"+tgt_movie.name+"', '"+tgt_movie.format+"', '" \
                    +c_seat+"', '"+totPrice+"', '"+tgt_movie.showDate+"', '"+tgt_movie.showTime+"')";
            const char* in = insert_query.c_str();
            qstate = mysql_query(conn, in);

            if(!qstate) {
                cout << endl << "Purchase Successfully Done." << endl;
                cout << endl << "Total Price: " << totalPrice << endl;
            }
        }

        char choose;
        cout << "Press 'y' to Book another ticket, other to continue:";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
            return BookTicket();
        else
            return print_bottom_line();
    }
*/
};

// #endif 
