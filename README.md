	This project is develop a cloud Gateway, which can support 
a variety of drivers,collect field data, then push the data to the 
cloud.At present, it only supports modbus rtu driver and aliyun.

# compile the sqlite3 for arm process

1. Extract the sqlite3 src to sqlite3-arm

2. mkdir install.   in /opt/sqlite3-arm

3. ./configure --host=arm-linux-gnueabihf --prefix=/opt/sqlite3-arm/install

4. make

5. make install

6. copy the /install/bin/sqlite3 to Armboard/usr/local/bin

7. copy the /install/lib/sqlite3.so.0.8.6 to Armboard/usr/local/lib

8. copy the /install/include/sqlite3 to our project.

# /********** log **************/

# 05311730:

(1) the project can running ok, in arm board.

(2) the pthread func can not work.

(3) the sqlite3 operator ok.
	
(4) we can read the cfg.db->dev_table ok.

(5) there are many warning compile.

(6) transmit paras to thread is the key.

# 06041011:
(1) the project compile has no warning.

# 06041409:
(1) modify the struct, not use point(*), but use arrary,malloc size.
    then can tx para to thread ok.
