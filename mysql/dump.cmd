SELECT 'unitid', 'chronname', 'city', 'state', 'level', 'control', 'long_x', 'lat_y', 'site', 'student_count', 'basic', 'flagship', 'awards_per_value', 'ft_pct', 'fte_value', 'med_sat_value', 'retain_value', 'vsa_grad_after4_first', 'vsa_grad_after6_first', 'asian_grad_100_rate', 'asian_grad_150_rate'
UNION
SELECT *
FROM ccic4y
INTO OUTFILE 'cc_institution_refined.csv'
FIELDS ENCLOSED BY '"' TERMINATED BY ',' ESCAPED BY ""  # escaped by set as empty to change \N to NULL for null output
LINES TERMINATED BY '\n';
