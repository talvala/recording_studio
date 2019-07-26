# recording_studio

In order to get the app to work:

1. clone this repo
2. cd into the folder
3. make sure g++ and gcc are installed
4. check the installation paths (which gcc, which g++)
5. run the following(make sure to update gcc and g++ installation paths): g++ -o demo1 -I/usr/local/include -I/usr/local/include/mysql -W -lmysqlclient -L/usr/local/lib demo1.cpp
6. double click demo1

In case if any change in the code -  re run step 5 and reopen demo1
