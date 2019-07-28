
/*
  By Default g++ uses clang compiler which comes with Xcode which is not a genuine compiler so you need to reinstall to have genuine compiler for g++
  You can check version with g++ --version
  1. Install macports using brew
  2. sudo port selfupdate
  3. sudo port install gcc46
  4. sudo port select --set gcc mp-gcc46
  5. Now check again gcc --version it should Say (gcc (MacPorts gcc46 4.6.4_11) 4.6.4) ...
  

  Installing and running mysql
  1. brew install mysql
  2. g++ -o demo1 -I/usr/local/include -I/usr/local/include/mysql -W -lmysqlclient -L/usr/local/lib demo1.cpp 
  3. Run ./demo1
*/

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
// #include <vector> 
#include <mysql.h>
#include <string>

using namespace std;

void run_query (const std::string& query) {
    // std::vector<std::string> tables;
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL *connection, mysql;
    
    mysql_init(&mysql);
    
    connection = mysql_real_connect(&mysql,"127.0.0.1","root","root","studio",0,0,0);
    
    // cout << connection;
    if (connection == NULL)
    {
        std::cout << mysql_error(&mysql) << std::endl;
        // return tables;
    }
    int state;
    state = mysql_query(connection, query.c_str());
    if (state !=0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }
    
    result = mysql_store_result(connection);
    
    std::cout << "result: " << mysql_num_rows(result) << std::endl;
    while ( ( row=mysql_fetch_row(result)) != NULL )
    {
        cout << row[0] << std::endl;
    }
    
    mysql_free_result(result);
    mysql_close(connection);
}

int main(void)
{
    int choice;
    string variables;
    string query;
    string start_date;
    string end_date;
    string musician;
    
    do
    {
        cout << endl
        << " 1 - Albums recorded in date range \n"
        << " 2 - # of songs a musician has recorded in date range \n"
        << " 3 - # of albums a musician participated in date range\n"
        << " 4 - Exit.\n"
        << " 5 - Start the game.\n"
        << " 6 - Story.\n"
        << " 7 - Help.\n"
        << " 8 - # of musicians who recorded over the years \n"
        << " 9 - Start the game.\n"
        << " 10 - Story.\n"
        << " 11 - Help.\n"
        << " 12 - Exit.\n"
        << " 13 - List of songs in more than 2 albums \n"
        << " 14 - Story.\n"
        << " 15 - Help.\n"
        << " Enter your choice and press return: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                cout << "Please enter start date (YYYY-MM-DD format): \n";
                cin >> start_date;
                cout << "Please enter end date (YYYY-MM-DD format): \n";
                cin >> end_date;
                query = "select Albun_Name from Album where '" + start_date + "'" + " between Album_Rec_Start and Album_Rec_End and '" + end_date + "'" + " between Album_Rec_Start and Album_Rec_End;";
                run_query(query);
                break;
            case 2:
                cin.ignore();
                cout << "Please enter musician name: \n";
                getline(cin, musician);
                cout << "Please enter start date (YYYY-MM-DD format): \n";
                cin >> start_date;
                cout << "Please enter end date (YYYY-MM-DD format): \n";
                cin >> end_date;
                query = "select count(Track_Musicians.Track_ID) from Track_Musicians join Track on Track.Track_ID = Track_Musicians.Track_ID  join Musician on Track_Musicians.Musician_ID = Musician.Musician_ID where Track.Track_Date between '" + start_date +"' and '" + end_date + "' and Musician.Musician_Name = '" + musician + "' group by Track_Musicians.Track_ID";
                run_query(query);
                break;
            case 3:
                cin.ignore();
                cout << "Please enter musician name: \n";
                getline(cin, musician);
                cout << "Please enter start date (YYYY-MM-DD format): \n";
                cin >> start_date;
                cout << "Please enter end date (YYYY-MM-DD format): \n";
                cin >> end_date;
                query = "select count(Album_Tracks.Albun_ID) from Track_Musicians join Track on Track.Track_ID = Track_Musicians.Track_ID join Musician on Track_Musicians.Musician_ID = Musician.Musician_ID join Album_Tracks on Album_Tracks.Track_ID = Track.Track_ID where Track.Track_Date between '" + start_date + "' and '" + end_date + "' and Musician.Musician_Name = '" + musician + "'  group by Album_Tracks.Track_ID;";
                run_query(query);
                break;
            case 4:
                //code to help the user like give him
                //extra information about the mode and the controller
                break;
            case 5:
                //code to start the game
                break;
            case 6:
                //code to make score for this game to count how many times u win the game
                break;
            case 7:
                //code to make option for the game
                break;
            case 8:
                cout << "enter variables: \n" ;
                cin >> variables;
                query = "show " + variables + ";";
                run_query(query);
                break;
            case 9:
                //code to start the game
                break;
            case 10:
                //code to make score for this game to count how many times u win the game
                break;
            case 11:
                //code to make option for the game
                break;
            case 12:
                //code to help the user like give him
                //extra information about the mode and the controller
                break;
            case 13:
                run_query("select Track.Track_Name, count(Album_tracks.Track_ID) as 'Track_ID_count'  from Album_Tracks  join Track on Track.Track_ID = Album_Tracks.Track_ID where 'Track_ID_count' >= '2' group by Album_Tracks.Track_ID;");
                break;
            case 14:
                //code to make score for this game to count how many times u win the game
                break;
            case 15:
                
                break;
            case 16:
                cout << "End of Program.\n";
                break;
            default:
                cout << "Not a Valid Choice. \n"
                << "Choose again.\n";
                break;
        }
        
    }
    while (choice !=16);
        return 0;

    
}
