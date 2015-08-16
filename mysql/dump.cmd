#
#SELECT 'unitid', 'chronname', 'city', 'state', 'level', 'control', 'long_x', 'lat_y', 'site', 'student_count', 'basic', 'flagship', 'awards_per_value', 'ft_pct', 'fte_value', 'med_sat_value', 'retain_value', 'vsa_grad_after4_first', 'vsa_grad_after6_first', 'asian_grad_100_rate', 'asian_grad_150_rate'
#UNION
#SELECT *
#FROM ccic4y
#INTO OUTFILE 'cc_institution_refined.csv'
#FIELDS ENCLOSED BY '"' TERMINATED BY ',' ESCAPED BY ""  # escaped by set as empty to change \N to NULL for null output
#LINES TERMINATED BY '\n';

SELECT 'chronname', 'long_x', 'lat_y', 'student_count', 'ADDR','CITY', 'STABBR', 'ZIP','asian_grad_100_rate','asian_grad_150_rate' 
UNION
SELECT `chronname`, `long_x`, `lat_y`, `student_count`, `ADDR`,`CITY`, `STABBR`, `ZIP`,`asian_grad_100_rate`,`asian_grad_150_rate` 
FROM CombinedAll WHERE STABBR='CA' AND chronname LIKE 'university of california%'
INTO OUTFILE 'UC.csv'
FIELDS ENCLOSED BY '"' TERMINATED BY ',' ESCAPED BY "" 
LINES TERMINATED BY '\n';


SELECT 'chronname', 'long_x', 'lat_y', 'student_count', 'ADDR','CITY', 'STABBR', 'ZIP','asian_grad_100_rate','asian_grad_150_rate' 
UNION
SELECT `chronname`, `long_x`, `lat_y`, `student_count`, `ADDR`,`CITY`, `STABBR`, `ZIP`,`asian_grad_100_rate`,`asian_grad_150_rate` 
FROM CombinedAll WHERE STABBR='CA' AND 
(chronname LIKE '%State%' OR chronname LIKE 'California Maritime Academy')
INTO OUTFILE 'CSU.csv'
FIELDS ENCLOSED BY '"' TERMINATED BY ',' ESCAPED BY "" 
LINES TERMINATED BY '\n';
