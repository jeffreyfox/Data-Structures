DROP TABLE tmp1;
DROP TABLE tmp2;
DROP TABLE tmp3;
DROP TABLE tmp4;
DROP TABLE tmp5;

# combine InstDetl and InstGrad
CREATE TABLE tmp1  # combined table
SELECT InstDetl4y.*, InstGrad4y.asian_grad_100_rate, InstGrad4y.asian_grad_150_rate 
FROM InstDetl4y LEFT JOIN InstGrad4y
ON InstDetl4y.unitid=InstGrad4y.unitid;

# combine InstCharI
CREATE TABLE tmp2  # combined table
SELECT tmp1.*, 
InstCharI.ADDR,
InstCharI.CITY,
InstCharI.STABBR,
InstCharI.ZIP,
InstCharI.MEDICAL,
InstCharI.CCBASIC,
InstCharI.CCIPUG,
InstCharI.CCIPGRAD,
InstCharI.CCUGPROF,
InstCharI.CCENRPRF,
InstCharI.CCSIZSET,
InstCharI.CARNEGIE,
InstCharI.INSTSIZE
FROM tmp1 LEFT JOIN InstCharI
ON tmp1.unitid=InstCharI.UNITID;

# combine InstCharII
CREATE TABLE tmp3  # combined table
SELECT tmp2.*, 
InstCharII.RELAFFIL, 
InstCharII.OPENADMP, 
InstCharII.ADMCON1, InstCharII.ADMCON2,
InstCharII.ADMCON3, InstCharII.ADMCON4,
InstCharII.ADMCON5, InstCharII.ADMCON6,
InstCharII.ADMCON7,
InstCharII.APPLCNM, InstCharII.APPLCNW,
InstCharII.ADMSSNM, InstCharII.ADMSSNW,
InstCharII.SATVR25, InstCharII.SATVR75,
InstCharII.SATMT25, InstCharII.SATMT75,
InstCharII.SATWR25, InstCharII.SATWR75,
InstCharII.ACTCM25, InstCharII.ACTCM75,
InstCharII.APPLFEEU, InstCharII.APPLFEEG,
InstCharII.FT_UG,
InstCharII.FTGDNIDP,
InstCharII.APPLCN,
InstCharII.ADMSSN 
FROM tmp2 LEFT JOIN InstCharII
ON tmp2.unitid=InstCharII.UNITID;

# combine StudChrg
CREATE TABLE tmp4  # combined table
SELECT tmp3.*, 
StudChrg.CHG2AY3, StudChrg.CHG3AY2, 
StudChrg.CHG5AY3, StudChrg.CHG6AY3, 
StudChrg.CHG7AY3, StudChrg.CHG8AY3
FROM tmp3 LEFT JOIN StudChrg
ON tmp3.unitid=StudChrg.UNITID;

# combine FANP
CREATE TABLE tmp5  # combined table
SELECT tmp4.*, 
FANP.GIS4N42,
FANP.GIS4G42, FANP.GIS4T42,
FANP.GIS4A42, FANP.GIS4N52,
FANP.GIS4G52, FANP.GIS4T52,
FANP.GIS4A52, FANP.NPIS442,
FANP.NPIS452, FANP.GRN4N42,
FANP.GRN4G42, FANP.GRN4T42,
FANP.GRN4A42, FANP.GRN4N52, 
FANP.GRN4G52, FANP.GRN4T52, 
FANP.GRN4A52, FANP.NPT442 
FROM tmp4 LEFT JOIN FANP
ON tmp4.unitid=FANP.UNITID;

# combine EnroRace
CREATE TABLE CombinedAll  # combined table
SELECT tmp5.*, 
EnroRace.UND_EFTOTLT, EnroRace.GRA_EFTOTLT, EnroRace.TOT_EFTOTLT, 
EnroRace.UND_EFASIAT, EnroRace.GRA_EFASIAT, EnroRace.TOT_EFASIAT, 
EnroRace.UND_EFNRALT, EnroRace.GRA_EFNRALT, EnroRace.TOT_EFNRALT
FROM tmp5 LEFT JOIN EnroRace
ON tmp5.unitid=EnroRace.UNITID;

