#
DROP TABLE ccig;

CREATE TABLE ccig
(
  unitid INT,
  year INT,
  gender CHAR(1), 
  race VARCHAR(2),
  cohort VARCHAR(16),
  grad_cohort VARCHAR(4),
  grad_100 INT DEFAULT NULL,
  grad_150 INT DEFAULT NULL,
  grad_100_rate DOUBLE(3, 1) DEFAULT NULL,
  grad_150_rate DOUBLE(3, 1) DEFAULT NULL
);

LOAD DATA INFILE 'cc_institution_grads.csv' INTO TABLE ccig
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n'  
IGNORE 1 LINES   # ignore header
(unitid, year, gender, race, cohort, grad_cohort, @grad_100, @grad_150, @grad_100_rate, @grad_150_rate) 
SET grad_100 = IF(@grad_100 = 'NULL', NULL, @grad_100),
grad_150 = IF(@grad_150 = 'NULL', NULL, @grad_150),
grad_100_rate = IF(@grad_100_rate = 'NULL', NULL, @grad_100_rate),
grad_150_rate = IF(@grad_150_rate = 'NULL', NULL, @grad_150_rate);

DROP TABLE ccig4y;
CREATE TABLE ccig4y
(SELECT unitid, grad_100_rate AS 'asian_grad_100_rate', grad_150_rate AS 'asian_grad_150_rate'
FROM ccig 
WHERE year=2013 AND gender='B' AND race='A' AND cohort='4y bach');
