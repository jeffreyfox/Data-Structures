SELECT 
'CDSCode', 'County', 'District', 'School', 'City', 'Zip', 'API_charter', 'API_avg_nw', 'API_aa_avg_nw', 'API_as_avg_nw', 'API_hi_avg_nw', 'API_wh_avg_nw', 'API_el_avg_nw', 'ETOT_asian', 'ETOT_all', 'asian_pct', 'UC_GRADS_asian', 'GRADS_asian', 'UC_CSU_pct_asian', 'UC_GRADS_all', 'GRADS_all', 'UC_CSU_pct_all' 
UNION
SELECT *
FROM CombinedRef ORDER BY API_as_avg_nw DESC
INTO OUTFILE 'combined1.csv'
FIELDS ENCLOSED BY '"' TERMINATED BY ',' ESCAPED BY ""  # escaped by set as empty to change \N to NULL for null output
LINES TERMINATED BY '\n';

