#!/bin/bash
# shell script to create MySQL query command file

if [ "$#" -ne 2 ] ; then
    echo "[Error]: Wrong number of arguments. Usage: createsQL [csv file name] [SQL table name]"
    exit
fi
   
csv=$1
table=$2

if [ ! -f $csv ] ; then
   echo "File $csv does not exist!" 
   exit
fi

echo "Creating SQL loading commands csv file: $csv"

columns=`head -1 $csv | sed 's/,/ INT, /g' | sed -e 's/\r/ INT/'`

cmd=load_${table}.cmd

echo -en "CREATE TABLE $table\n($columns);\n" > $cmd

echo "LOAD DATA INFILE '$csv' INTO TABLE $table FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n' IGNORE 1 LINES;" >> $cmd


echo "$cmd generated!"
