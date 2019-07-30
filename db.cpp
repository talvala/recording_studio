
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
    string album;
    
    do
    {
        cout << endl
        << " 1 - Albums recorded in date range \n"
        << " 2 - # of songs a musician has recorded in date range \n"
        << " 3 - # of albums a musician participated in date range\n"
        << " 4 - Most popular instrument \n"
        << " 5 - Instrument in a given album \n"
        << " 6 - Most populaar producer in date range \n"
        << " 7 - Most populaar manufacturer \n"
        << " 8 - # of musicians who recorded over the years \n"
        << " 9 - Musician with largest number of collaborations \n"
        << " 10 - Most popular genre \n"
        << " 11 - Technician that recorded the most tracks in date range \n"
        << " 12 - First album that has been recorded \n"
        << " 13 - List of songs in more than 2 albums \n"
        << " 14 - List of tehnicians that participated in an entire album \n"
        << " 15 - Musician who recorded the most wide range of genres \n"
        << " 16 - Exit"
        << " Enter your choice and press return: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                cout << "Please enter start date (YYYY-MM-DD format): \n";
                cin >> start_date;
                cout << "Please enter end date (YYYY-MM-DD format): \n";
                cin >> end_date;
                query = "select Albun_Name from Album where Album_Rec_Start > '" + start_date + "' and Album_Rec_End < '" + end_date + "';";
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
                query = "select count(Track_Musicians.Track_ID) from Track_Musicians join Track on Track.Track_ID = Track_Musicians.Track_ID  join Musician on Track_Musicians.Musician_ID = Musician.Musician_ID where Track.Track_Date between '" + start_date +"' and '" + end_date + "' and Musician.Musician_Name = '" + musician + "' group by Track_Musicians.Track_ID;";
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
                query = "select Instrument.Instrument_type from Musician_Instruments left join Instrument on Musician_Instruments.Instrument_ID = Instrument.Instrument_ID left join Track_Musicians on Musician_Instruments.Musician_ID = Track_Musicians.Musician_ID group by Instrument.Instrument_type order by count(Instrument.Instrument_type) desc limit 1;";
                run_query(query);
                break;
            case 5:
                cin.ignore();
                cout << "Please enter album name: \n";
                getline(cin, album);
                query = "select distinct Instrument_type from Album_Tracks left join Track_Musicians on Album_Tracks.Track_ID = Track_Musicians.Track_ID left join Musician_Instruments on Track_Musicians.Musician_ID = Musician_Instruments.Musician_ID left join Instrument on Musician_Instruments.Instrument_ID = Instrument.Instrument_ID left join Album on Album_Tracks.Albun_ID = Album.Albun_ID where Albun_Name = '" + album + "' limit 1;";
                run_query(query);
                break;
            case 6:
                cin.ignore();
                cout << "Please enter start date (YYYY-MM-DD format): \n";
                cin >> start_date;
                cout << "Please enter end date (YYYY-MM-DD format): \n";
                cin >> end_date;
                query = "select Producer_Name from (Select Album_Producers.Producer_ID, Producer_Name from Album_Producers left join Album on Album_Producers.Albun_ID = Album.Albun_ID left join Producer on Album_Producers.Producer_ID = Producer.Producer_ID where  Album_Rec_Start > '" + start_date + "' and Album_Rec_End < '" + end_date + "') as b group by Producer_ID order by count(Producer_ID) limit 1;";
                run_query(query);
                break;
            case 7:
                query = "select Instrument.Instrument_Manufacturer from Musician_Instruments left join Instrument on Musician_Instruments.Instrument_ID = Instrument.Instrument_ID left join Track_Musicians on Musician_Instruments.Musician_ID = Track_Musicians.Musician_ID group by Instrument.Instrument_Manufacturer order by count(Instrument.Instrument_Manufacturer) desc limit 1;";
                run_query(query);
                break;
            case 8:
                query = "select count(distinct (Track_Musicians.Musician_ID)) from Track_Musicians right join Track on Track_Musicians.Track_ID = Track.Track_ID;";
                run_query(query);
                break;
            case 9:
                query = "select Musician_name from (select Track_ID from Track_Musicians group by Track_ID order by count(Track_ID) desc limit 1 ) as b left join Track_Musicians on Track_Musicians.Track_ID = b.Track_ID left join Musician on Track_Musicians.Musician_ID = Musician.Musician_ID limit 1;";
                run_query(query);
                break;
            case 10:
                query = "select Genre_Name from (select * from Track left join Genre on Track.Genre = Genre.Genre_ID) as b group by Genre_ID order by count(Genre_ID) desc limit 1;";
                run_query(query);
                break;
            case 11:
                cin.ignore();
                cout << "Please enter start date (YYYY-MM-DD format): \n";
                cin >> start_date;
                cout << "Please enter end date (YYYY-MM-DD format): \n";
                cin >> end_date;
                query = "select Technition.Technition_Name from Technition join Track on Technition.Technition_ID = Track.Technition_ID where Track_Date between '" + start_date +"' and '" + end_date +  "' group by Technition.Technition_ID order by count(Technition.Technition_ID) desc limit 1;";
                run_query(query);
                break;
            case 12:
                query = "select Albun_Name from Album order by Album_Rec_End asc limit 1;";
                run_query(query);
                break;
            case 13:
                run_query("select Track.Track_Name, count(Album_tracks.Track_ID) as 'Track_ID_count'  from Album_Tracks  join Track on Track.Track_ID = Album_Tracks.Track_ID where 'Track_ID_count' >= '2' group by Album_Tracks.Track_ID;");
                break;
            case 14:
                query = "Select Technition_Name from (Select distinct count(Albun_ID), Technition_ID, Number_Of_tracks, Technition_Name from (select distinct Track.Track_ID, Track.Technition_ID, Album_Tracks.Albun_ID, Number_Of_tracks, Technition_Name from Track left join Album_Tracks on Track.Track_ID = Album_Tracks.Track_ID left join Album on Album_Tracks.Albun_ID = Album.Albun_ID left join Technition on Track.Technition_ID = Technition.Technition_ID) as b group by Albun_ID, Technition_ID Having count(Albun_ID) = Number_Of_tracks limit 1) as c;";
                run_query(query);
                break;
            case 15:
                query = "select Musician_Name from (select distinct Genre_ID, Track_Musicians.Musician_ID, Musician.Musician_Name from Track left join Genre on Track.Genre = Genre.Genre_ID left join Track_Musicians on Track.Track_ID = Track_Musicians.Track_ID left join Musician on Track_Musicians.Musician_ID = Musician.Musician_ID) as b group by Musician_ID order by Musician_ID desc limit 1;";
                run_query(query);
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
