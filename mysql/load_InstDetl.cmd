# InstDetl is table of 'college completion details'
CREATE TABLE InstDetl
(
  unitid INT,                                      # unique id 
  chronname VARCHAR(255),                          # Institution name
  city VARCHAR(20),
  state CHAR(2),
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

LOAD DATA INFILE 'cc_institution_details.csv' INTO TABLE InstDetl 
FIELDS TERMINATED BY ',' 
OPTIONALLY ENCLOSED BY '"'   # optional double quotes
LINES TERMINATED BY '\r'  # The raw csv file ends with a '^M'
IGNORE 1 LINES   # ignore header
(unitid, chronname, @dum, @dum, level, control, 
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

#InstDetl4y contains only 4-year colleges, and excludes private for-profit colleges
CREATE TABLE InstDetl4y
SELECT * from InstDetl
WHERE level='4-year' AND control != 'Private for-profit' 
