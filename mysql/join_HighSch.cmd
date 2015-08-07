DROP TABLE tmp1;
DROP TABLE tmp2;
DROP TABLE tmp3;
DROP TABLE tmp4;
DROP TABLE tmp5;

# combine PubSchDataRef and SAT
CREATE TABLE tmp1  # combined table
(SELECT PubSchDataRef.*, 
SAT.AvgScrRead  AS SAT_AvgScrRead, 
SAT.AvgScrMath  AS SAT_AvgScrMath, 
SAT.AvgScrWrite AS SAT_AvgScrWrite, 
NumGE1500 AS SAT_NumGE1500,
PctGE1500 AS SAT_PctGE1500   
FROM PubSchDataRef LEFT JOIN SAT
ON PubSchDataRef.CDSCode=SAT.CDS);

# combine tmp1 and ACT
CREATE TABLE tmp2  # combined table
(SELECT tmp1.*, 
ACT.AvgScrEng AS ACT_AcgScrEng,
ACT.AvgScrRead AS ACT_AvgScrRead,
ACT.AvgScrMath AS ACT_AvgScrMath,
ACT.AvgScrSci AS  ACT_AvgScrSci,
ACT.NumGE21 AS ACT_NumGE21,
ACT.PctGE21 AS ACT_PctGE21
FROM tmp1 LEFT JOIN ACT
ON tmp1.CDSCode=ACT.CDS);

# combine tmp2 and AP
CREATE TABLE tmp3  # combined table
(SELECT tmp2.*, 
AP.NumTstTakr AS AP_NumTstTakr,
AP.NumScr1 AS AP_NumScr1,
AP.NumScr2 AS AP_NumScr2,
AP.NumScr3 AS AP_NumScr3,
AP.NumScr4 AS AP_NumScr4,
AP.NumScr5 AS AP_NumScr5
FROM tmp2 LEFT JOIN AP
ON tmp2.CDSCode=AP.CDS);

# combine tmp3 and API
CREATE TABLE tmp4  # combined table
(SELECT tmp3.*, 
API.charter AS API_charter,
API.avg_nw AS API_avg_nw,
API.aa_avg_nw AS API_aa_avg_nw,
API.as_avg_nw AS API_as_avg_nw,
API.hi_avg_nw AS API_hi_avg_nw,
API.wh_avg_nw AS API_wh_avg_nw,
API.el_avg_nw AS API_el_avg_nw
FROM tmp3 LEFT JOIN API
ON tmp3.CDSCode=API.CDS);

# combine tmp4 and EnroRef
CREATE TABLE CombinedAll  # combined table
(SELECT tmp4.*, 
EnroRef.ETOT_asian, 
EnroRef.ETOT_all, 
EnroRef.asian_pct
FROM tmp4 LEFT JOIN EnroRef
ON tmp4.CDSCode=EnroRef.CDS_CODE);

DROP TABLES tmp1, tmp2, tmp3, tmp4;
