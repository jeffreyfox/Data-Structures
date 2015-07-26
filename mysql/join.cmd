DROP TABLE ccic4y;
CREATE TABLE ccic4y  # combined table
SELECT ccid4y.*, ccig4y.asian_grad_100_rate, ccig4y.asian_grad_150_rate 
FROM ccid4y LEFT JOIN ccig4y
ON ccid4y.unitid=ccig4y.unitid;
