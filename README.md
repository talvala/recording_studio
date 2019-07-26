# recording_studio

Download DB:

1. download DB dump
2. (import the dump)
3. run sql server: /usr/local/mysql/support-files/mysql.server start
4. login to mysql console: mysql -u root
5. create database studio
6. exit mysql console
7. import the dump: mysql -u root -p studio < studio_backup.sql
8. enter mysql console again and make sure all tables are in

Run application:

1. clone this repo
2. cd into the folder
3. make sure g++ and gcc are installed
4. check the installation paths (which gcc, which g++)
5. run the following (make sure to update gcc and g++ installation paths): g++ -o demo1 -I/usr/local/include -I/usr/local/include/mysql -W -lmysqlclient -L/usr/local/lib demo1.cpp
6. double click demo1

*In case if any change in the code -  re run step 5 and reopen demo1*
