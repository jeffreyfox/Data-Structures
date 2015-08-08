 select County, District, Count(*) as cnt from CombinedRef where API_as_avg_nw > 900 group by District ORDER BY cnt DESC;

SELECT County, District, School, City, Zip, API_as_avg_nw, ETOT_asian, ETOT_all, asian_pct
FROM `CombinedRef`
WHERE API_as_avg_nw >900
AND ETOT_asian >500
ORDER BY `CombinedRef`.`ETOT_asian` DESC 
