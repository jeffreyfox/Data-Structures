# combined file of the 4
# ccid is table of 'college completion details'
DROP TABLE ccid;
CREATE TABLE ccid
(
  unitid INT,                                      # unique id 
  chronname VARCHAR(255),                          # Institution name
  city VARCHAR(32),                                # Institution city
  state VARCHAR(20),                               # Institution state
  level VARCHAR(8),                                # Level of institution (4-year, 2-year)
  control VARCHAR(128),                            # Control of institution (Public, Private not-for-profit, Private for-profit)
  long_x DOUBLE(9, 6),                             # Institution longitude
  lat_y DOUBLE(9, 6),                              # Institution latitude
  site VARCHAR(255),                               # Institution Web site address
  student_count INT,                               # Total number of undergraduates in 2010
  basic VARCHAR(255),                              # Carnegie Foundation for the Advancement of Teaching Basic Classification (2010 version)
  flagship CHAR(1) DEFAULT 'N',                      # Denotes Public flagship institutions
  awards_per_value DOUBLE(3, 1) DEFAULT NULL,      # Completions per 100 FTE undergraduate students (average 2011, 2012, and 2013)
  ft_pct DOUBLE(3, 1) DEFAULT NULL,                # Percentage of undergraduates who attend full-time
  fte_value INT DEFAULT NULL,                      # total number of full-time equivalent undergraduates
  med_sat_value INT DEFAULT NULL,                  # Median estimated SAT value for incoming students
  retain_value DOUBLE(3, 1) DEFAULT NULL,          # share of freshman students retained for a second year
  vsa_grad_after4_first DOUBLE(3, 1) DEFAULT NULL, # First-time, full-time students who graduated from this institution within four years
  vsa_grad_after6_first DOUBLE(3, 1) DEFAULT NULL, # First-time, full-time students who graduated from this institution within six years
  PRIMARY KEY (unitid)
);

LOAD DATA INFILE 'cc_institution_details.csv' INTO TABLE ccid 
FIELDS TERMINATED BY ',' 
OPTIONALLY ENCLOSED BY '"'   # optional double quotes
LINES TERMINATED BY '\r'  # The raw csv file ends with a '^M'
IGNORE 1 LINES   # ignore header
(unitid, chronname, city, state, level, control, 
basic, @dummy, @flagship, long_x, lat_y, site, 
student_count, awards_per_value, @dummy, @dummy, @dummy, @dummy, 
@dummy, @dummy, ft_pct, fte_value, @dummy, med_sat_value,
@dummy, @dummy, @dummy, @dummy, @dummy, @dummy,
@dummy, @dummy, @dummy, @dummy, @dummy, retain_value,
@dummy, @dummy, @dummy, @dummy, @vsa_grad_after4_first, @dummy,
@dummy, @dummy, @vsa_grad_after6_first, @dummy, @dummy, @dummy )
SET flagship = IF(@flagship = 'X', 'Y', 'N'),
vsa_grad_after4_first = IF(@vsa_grad_after4_first = 'NULL', NULL, @vsa_grad_after4_first),
vsa_grad_after6_first = IF(@vsa_grad_after6_first = 'NULL', NULL, @vsa_grad_after6_first);


#ccid4y contains only 4-year colleges, and excludes private for-profit colleges
DROP TABLE ccid4y;
CREATE TABLE ccid4y
SELECT * from ccid
WHERE level='4-year' AND control != 'Private for-profit' 

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

# graduation rate for all races ('X')
CREATE TABLE tmp1
(SELECT unitid, grad_100_rate AS 'grad_100_rate', grad_150_rate AS 'grad_150_rate'
FROM ccig 
WHERE year=2013 AND gender='B' AND race='X' AND cohort='4y bach');

# graduation rate for asians ('A')
CREATE TABLE tmp2
(SELECT unitid, grad_100_rate AS 'asian_grad_100_rate', grad_150_rate AS 'asian_grad_150_rate'
FROM ccig 
WHERE year=2013 AND gender='B' AND race='A' AND cohort='4y bach');

# combine two tables into ccig4y
DROP TABLE ccig4y;
CREATE TABLE ccig4y  # combined table
SELECT tmp1.*, tmp2.asian_grad_100_rate, tmp2.asian_grad_150_rate
FROM tmp1 LEFT JOIN tmp2
ON tmp1.unitid=tmp2.unitid;

DROP TABLE tmp1;
DROP TABLE tmp2;
