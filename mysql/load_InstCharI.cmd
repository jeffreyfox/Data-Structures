#
CREATE TABLE InstCharI
(
  UNITID INT,
  ADDR VARCHAR(255),
  CITY VARCHAR(20), 
  STABBR CHAR(2),
  ZIP CHAR(10),
  MEDICAL INT,
  CCBASIC INT,
  CCIPUG INT,
  CCIPGRAD INT,
  CCUGPROF INT,
  CCENRPRF INT,
  CCSIZSET INT,
  CARNEGIE INT,
  INSTSIZE INT
);

LOAD DATA INFILE 'Institution_Characteristics_I.csv' INTO TABLE InstCharI
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'   # optional double quotes
LINES TERMINATED BY '\n'  
IGNORE 1 LINES   # ignore header
(UNITID, @dum, ADDR, CITY, STABBR, ZIP,
@dum, @dum, @dum, @dum, @dum, @dum, @dum, @dum, 
@dum, @dum, @dum, @dum, @dum, @dum, @dum, @dum, 
@dum, @dum, @dum, @dum, @dum, @dum, @dum, @dum, 
MEDICAL, 
@dum, @dum, @dum, @dum, @dum, @dum, @dum,
@dum, @dum, @dum, @dum, @dum, @dum, @dum,
CCBASIC, CCIPUG, CCIPGRAD, CCUGPROF, CCENRPRF, CCSIZSET, CARNEGIE, @dum,
INSTSIZE);

