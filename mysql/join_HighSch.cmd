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

