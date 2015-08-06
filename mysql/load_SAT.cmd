DROP TABLE SAT;
CREATE TABLE SAT
(
CDS CHAR(14),
RTYPE CHAR(1),
SNAME VARCHAR(128), 
DNAME VARCHAR(64), 
CNAME VARCHAR(20), 
Enroll912 INT, 
NumTstTakr INT, 
AvgScrRead INT, 
AvgScrMath INT, 
AvgScrWrite INT, 
NumGE1500 INT, 
PctGE1500 DOUBLE
);
LOAD DATA INFILE '2013_14_SAT.csv' INTO TABLE SAT FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES;