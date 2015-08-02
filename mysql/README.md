Three tables can be generated automatically from shell script:
 createMySQLcmd.sh  Institution_Characteristics_II.csv InstCharII
 createMySQLcmd.sh  Student_Charges.csv StudChrg
 createMySQLcmd.sh  FANP.csv FANP
Others are written manually

source load*.cmd; //load individual tables into database
source join.cmd; //join tables together
source dump.cmd; //save table into csv format
