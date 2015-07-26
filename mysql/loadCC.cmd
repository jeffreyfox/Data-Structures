#
CREATE TABLE colleges
(
  unitid INT,  #unique id 
  chronname VARCHAR(255), # Institution name
  city VARCHAR(32),  # Institution city
  state VARCHAR(16), # Institution state
  level VARCHAR(8),  # Level of institution (4-year, 2-year)
  control VARCHAR(128),  # Control of institution (Public, Private not-for-profit, Private for-profit)
  long_x DOUBLE(9, 6),  # Institution longitude
  lat_y DOUBLE(9, 6), # Institution latitude
  site VARCHAR(255), # Institution Web site address
  student_count INT, # Total number of undergraduates in 2010
  basic VARCHAR(255), # Carnegie Foundation for the Advancement of Teaching Basic Classification (2010 version)
  flagship VARCHAR(4), # Denotes Public flagship institutions
  awards_per_value DOUBLE(3, 1), # Completions per 100 FTE undergraduate students (average 2011, 2012, and 2013)
  ft_pct DOUBLE(3, 1), # Percentage of undergraduates who attend full-time
  fte_value INT, # total number of full-time equivalent undergraduates
  med_sat_value INT, # Median estimated SAT value for incoming students
  retain_value DOUBLE(3, 1), # share of freshman students retained for a second year
  vsa_grad_after4_first DOUBLE(3, 1), # First-time, full-time students who graduated from this institution within four years
  vsa_grad_after6_first DOUBLE(3, 1), # First-time, full-time students who graduated from this institution within six years
  PRIMARY KEY (unitid)
);



LOAD DATA INFILE 'cc_institution_details.csv' INTO TABLE colleges 
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\r'  # The raw csv file ends with a '^M'
IGNORE 1 LINES   # ignore header
(unitid, chronname, city, state, level, control, 
basic, @dummy, flagship, long_x, lat_y, site, 
student_count, awards_per_value, @dummy, @dummy, @dummy, @dummy, 
@dummy, @dummy, ft_pct, fte_value, @dummy, med_sat_value,
@dummy, @dummy, @dummy, @dummy, @dummy, @dummy,
@dummy, @dummy, @dummy, @dummy, @dummy, retain_value,
@dummy, @dummy, @dummy, @dummy, vsa_grad_after4_first, @dummy,
@dummy, @dummy, vsa_grad_after6_first, @dummy, @dummy, @dummy 
);
