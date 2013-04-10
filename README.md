Description
===========
An MySQL UDF which can be used to test if a file exists. This can be used to verify if a database records points to an existing file.

It returns 1 if the file exists and 0 if the file is missing.

Installation
============
$ gcc -o udf_fileexists.so udf_fileexists.c `mysql_config --include` -shared -fPIC

mysql> CREATE FUNCTION udf_fileexists RETURNS INTEGER SONAME 'udf_fileexists.so';

Example
=======

    mysql> SELECT udf_fileexists('/etc/hosts');
    +------------------------------+
    | udf_fileexists('/etc/hosts') |
    +------------------------------+
    |                            1 |
    +------------------------------+
    1 row in set (0.00 sec)
    
    mysql> SELECT udf_fileexists('/does/not/exist');
    +-----------------------------------+
    | udf_fileexists('/does/not/exist') |
    +-----------------------------------+
    |                                 0 |
    +-----------------------------------+
    1 row in set (0.00 sec)
    
    mysql> CREATE TABLE files(filename VARCHAR(200));
    Query OK, 0 rows affected (0.01 sec)
    
    mysql> INSERT INTO files VALUES('/etc/hosts'),('/etc'),('/does/not/exist'),('/nonexistend');
    Query OK, 4 rows affected (0.00 sec)
    Records: 4  Duplicates: 0  Warnings: 0
    
    mysql> SELECT filename,udf_fileexists(filename) FROM files;
    +-----------------+--------------------------+
    | filename        | udf_fileexists(filename) |
    +-----------------+--------------------------+
    | /etc/hosts      |                        1 |
    | /etc            |                        1 |
    | /does/not/exist |                        0 |
    | /nonexistend    |                        0 |
    +-----------------+--------------------------+
    4 rows in set (0.00 sec)
    
    mysql> SELECT filename,udf_fileexists(filename) AS `exists` FROM files WHERE udf_fileexists(filename);
    +------------+--------+
    | filename   | exists |
    +------------+--------+
    | /etc/hosts |      1 |
    | /etc       |      1 |
    +------------+--------+
    2 rows in set (0.01 sec)
    
