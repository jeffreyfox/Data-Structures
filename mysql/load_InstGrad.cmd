#

CREATE TABLE InstGrad
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

LOAD DATA INFILE 'cc_institution_grads.csv' INTO TABLE InstGrad
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n'  
IGNORE 1 LINES   # ignore header
(unitid, year, gender, race, cohort, grad_cohort, @grad_100, @grad_150, @grad_100_rate, @grad_150_rate) 
SET grad_100 = IF(@grad_100 = 'NULL', NULL, @grad_100),
grad_150 = IF(@grad_150 = 'NULL', NULL, @grad_150),
grad_100_rate = IF(@grad_100_rate = 'NULL', NULL, @grad_100_rate),
grad_150_rate = IF(@grad_150_rate = 'NULL', NULL, @grad_150_rate);

# graduation rate for all races ('X')
CREATE TABLE tmp1
(SELECT unitid, grad_100_rate AS 'grad_100_rate', grad_150_rate AS 'grad_150_rate'
FROM InstGrad 
WHERE year=2013 AND gender='B' AND race='X' AND cohort='4y bach');

# graduation rate for asians ('A')
CREATE TABLE tmp2
(SELECT unitid, grad_100_rate AS 'asian_grad_100_rate', grad_150_rate AS 'asian_grad_150_rate'
FROM InstGrad 
WHERE year=2013 AND gender='B' AND race='A' AND cohort='4y bach');

# combine two tables
CREATE TABLE InstGrad4y  # combined table
SELECT tmp1.*, tmp2.asian_grad_100_rate, tmp2.asian_grad_150_rate
FROM tmp1 LEFT JOIN tmp2
ON tmp1.unitid=tmp2.unitid;

DROP TABLE tmp1;
DROP TABLE tmp2;
