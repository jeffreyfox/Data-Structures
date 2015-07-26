#
DROP TABLE grads;

CREATE TABLE grads
(
  unitid INT,
  year INT,
  gender CHAR(1), 
  race VARCHAR(2),
  cohort VARCHAR(16),
  grad_cohort VARCHAR(4),
  grad_100 INT,
  grad_150 INT,
  grad_100_rate DOUBLE(3, 1),
  grad_150_rate DOUBLE(3, 1)
);

LOAD DATA INFILE 'cc_institution_grads.csv' INTO TABLE grads
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n'  
IGNORE 1 LINES;   # ignore header


# select unitid, grad_100_rate, grad_150_rate from grads where year=2013 AND gender='B' AND race='A';
