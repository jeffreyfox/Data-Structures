DROP TABLE Enroll;

CREATE TABLE Enroll
(
CDS_CODE CHAR(14), 
ETHNIC INT, 
GENDER CHAR(1), 
E7 INT, 
E8 INT, 
E9 INT, 
E10 INT, 
E11 INT, 
E12 INT, 
EUS INT, 
ETOT INT, 
D7 INT, 
D8 INT, 
D9 INT, 
D10 INT, 
D11 INT, 
D12 INT, 
DUS INT, 
DTOT INT, 
YEAR INT);
LOAD DATA INFILE 'Enrollment.csv' INTO TABLE Enroll FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES;

DROP TABLE Enro1;

CREATE TABLE Enro1
(SELECT CDS_CODE, SUM(ETOT) AS ETOT_all
FROM Enroll
GROUP BY CDS_CODE);

DROP TABLE Enro2;

CREATE TABLE Enro2
(SELECT CDS_CODE, SUM(ETOT) AS ETOT_asian
FROM Enroll
WHERE ETHNIC =2
GROUP BY CDS_CODE);

DROP TABLE Enro3;

CREATE TABLE Enro3
(SELECT Enro2.CDS_CODE, Enro2.ETOT_asian, Enro1.ETOT_all 
FROM Enro2 LEFT JOIN Enro1 on Enro2.CDS_CODE=Enro1.CDS_CODE);

CREATE TABLE EnroRef
(SELECT *, (ETOT_asian/ETOT_all) as asian_pct from Enro3);

DROP TABLES Enro1, Enro2, Enro3

