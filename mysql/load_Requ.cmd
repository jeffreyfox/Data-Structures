CREATE TABLE Requ
(CDS_CODE CHAR(14), 
ETHNIC INT, 
GENDER CHAR(1), 
GRADS INT, 
UC_GRADS INT, 
YEAR INT);
LOAD DATA INFILE 'Requirement.csv' INTO TABLE Requ FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES;


DROP TABLE Requ1;

CREATE TABLE Requ1
(SELECT CDS_CODE, SUM(GRADS) AS GRADS_all, SUM(UC_GRADS) AS UC_GRADS_all
FROM Requ
GROUP BY CDS_CODE);

DROP TABLE Requ2;

CREATE TABLE Requ2
(SELECT CDS_CODE, SUM(GRADS) AS GRADS_asian, SUM(UC_GRADS) AS UC_GRADS_asian
FROM Requ
WHERE ETHNIC =2
GROUP BY CDS_CODE);

DROP TABLE Requ3;

CREATE TABLE Requ3
(SELECT Requ2.CDS_CODE, 
Requ2.UC_GRADS_asian, Requ2.GRADS_asian,
Requ1.UC_GRADS_all, Requ1.GRADS_all
FROM Requ2 LEFT JOIN Requ1 on Requ2.CDS_CODE=Requ1.CDS_CODE);

CREATE TABLE RequRef
(SELECT *, 
(UC_GRADS_asian/GRADS_asian) AS UC_CSU_pct_asian,
(UC_GRADS_all/GRADS_all) AS UC_CSU_pct_all
 from Requ3);

DROP TABLES Requ1, Requ2, Requ3

