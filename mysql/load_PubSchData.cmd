#
DROP TABLE PubSchData;
CREATE TABLE PubSchData
(
CDSCode CHAR(14), 
NCESDist CHAR(7), 
NCESSchool INT, 
StatusType VARCHAR(15), 
County VARCHAR(31), 
District VARCHAR(63),
School VARCHAR(127), 
Street VARCHAR(127), 
StreetAbr VARCHAR(127), 
City VARCHAR(15), 
Zip VARCHAR(15), 
State CHAR(2), 
MailStreet VARCHAR(31), 
MailStrAbr VARCHAR(15), 
MailCity VARCHAR(15), 
MailZip VARCHAR(15), 
MailState VARCHAR(15), 
Phone VARCHAR(15), 
Ext VARCHAR(4), 
Website VARCHAR(31), 
OpenDate VARCHAR(15), 
ClosedDate VARCHAR(15), 
Charter CHAR(1), 
CharterNum INT, 
FundingType VARCHAR(20), 
DOC INT,
DOCType VARCHAR(30), 
SOC INT, 
SOCType VARCHAR(31), 
EdOpsCode VARCHAR(15), 
EdOpsName VARCHAR(15), 
EILCode VARCHAR(15), 
EILName VARCHAR(30), 
GSoffered VARCHAR(5), 
GSserved VARCHAR(5), 
Virtual CHAR(1), 
Latitude FLOAT,
Longitude FLOAT
);
LOAD DATA INFILE 'Public_School_Data.csv' INTO TABLE PubSchData FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES;

DROP TABLE PubSchDataRef;
CREATE TABLE PubSchDataRef
SELECT CDSCode, NCESDist, NCESSchool, County, District, School FROM PubSchData WHERE County IN ('Alameda', 'Santa Clara', 'San mateo', 'San Francisco') AND StatusType='Active' AND (SOCType LIKE 'K-12 Schools%' OR SOCType LIKE 'High Schools%');

