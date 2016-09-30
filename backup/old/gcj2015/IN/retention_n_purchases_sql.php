<?php
 
function RedshiftConnection()
{
  $pgconn;

  if (! isset($pgconn))
    {
      $pgconn = pg_connect('host=tp-cluster1.cnykqqtxhbhz.us-east-1.redshift.amazonaws.com port=5439 dbname=tpledger user=vikas password=vIkas.pandey123') or die('Could not connect: ' . pg_last_error());
    }
  echo "Connected Successfully\n";
  return $pgconn;
}
function RedshiftExecute($pgConn, $sql)
{
  $result = FALSE;
  while(!$result){
  echo $sql. PHP_EOL; 
  $result = pg_query($pgConn, $sql);
  if(!$result) {echo pg_last_error($pgConn);$result=FALSE; echo "\nRetrying.....\n";}
  else return $result;
  }
}
function RedshiftCloseConnection($pgConn){  pg_close($pgConn); }

$app = $argv[1];
$devices_n_their_cohort = $app."_devices_n_their_cohort_vik";
$devices_login_info = $app."_devices_login_info_vik";
$table = $app."_temp_table_vik";
$device_perf = $app."_device_perf_vik";
$app_id ='';
$ledgertable ='';
if($app === 'TeenPatti')  {$app_id = "com.octro.teenpatti"; $ledgertable = 'tpledger_timeuser2';}
else if($app === 'TPL')  {$app_id = "com.octro.teenpattilive";$ledgertable = 'tpledger_timeuser2';}
else if($app === 'Rummy')  {$app_id = "com.octro.rummy"; $ledgertable = 'rmledger_time';}
else if($app === 'Tambola')  {$app_id = "com.octro.tambola";$ledgertable = 'tamledger_time';}
else if($app === 'Carrom')  {$app_id = "com.octro.carromlive";$ledgertable = 'carromledger_time';}

$pgConn = RedshiftConnection();

// DEVICES WITH THEIR COHORT
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_n_their_cohort");
$sql1 = "CREATE TABLE $devices_n_their_cohort AS
SELECT customer_user_id as deviceid, fb_adset_id || '_' || date(install_time + interval '19800 seconds') as cohort, date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist FROM apf_cb2
WHERE customer_user_id<>'' and fb_adset_id <>'' and app_id ='$app_id'
GROUP BY customer_user_id, fb_adset_id, date(install_time + interval '19800 seconds')";
$result = RedshiftExecute($pgConn, $sql1);
if(!$result) die("Failed_1 !\n" ); else echo "Successfull_1 !\n\n";

$result = RedshiftExecute($pgConn, "SELECT COUNT(*) as count FROM $devices_n_their_cohort");
$Rows = pg_fetch_all($result);
foreach($Rows as $Row) {if($Row['count']==0) exit(0);}

// DEVICES LOGIN INFO FROM INSTALL TRACK
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_login_info");
$sql2 = "CREATE TEMPORARY TABLE $devices_login_info AS
SELECT deviceid, cohort, install_date_ist, install_time_ist, (eventtime + interval '45000 seconds') as eventtime_ist, userid
FROM $devices_n_their_cohort NATURAL JOIN install_track
WHERE app = '$app' and (eventtime + interval '45000 seconds') >= install_time_ist";
$result = RedshiftExecute($pgConn, $sql2);
if(!$result) die("Failed_2 !\n" ); else echo "Successfull_2 !\n\n";

// TEMPORARY TABLE 1 FOR RETENTION COMPUTATIONS
RedshiftExecute($pgConn, "DROP TABLE if exists R1_$table");
$sql3 = "CREATE TEMPORARY TABLE  R1_$table AS
SELECT  deviceid, cohort, install_date_ist, install_time_ist, min(eventtime_ist) as jointime_ist
FROM $devices_login_info
GROUP BY deviceid, cohort, install_date_ist, install_time_ist";
$result = RedshiftExecute($pgConn, $sql3);
if(!$result) die("Failed_3 !\n" ); else echo "Successfull_3 !\n\n";

//TEMPORARY TABLE 2 FOR RETENTION COMPUTATIONS
RedshiftExecute($pgConn, "DROP TABLE if exists R2_$table");
$sql4 = "CREATE TEMPORARY TABLE R2_$table AS
SELECT deviceid, cohort, install_date_ist, install_time_ist, jointime_ist, eventtime_ist
FROM $devices_login_info NATURAL JOIN R1_$table";
$result = RedshiftExecute($pgConn, $sql4);
if(!$result) die("Failed_4 !\n" ); else echo "Successfull_4 !\n\n";

//FINAL RETENTION TABLE AT REDSHIFT
RedshiftExecute($pgConn, "DROP TABLE if exists $device_perf");
$sql5 = "CREATE TABLE $device_perf AS
SELECT deviceid, cohort, install_date_ist, install_time_ist, jointime_ist,
 sum(case when date_trunc('day', eventtime_ist - interval '1 day') = date_trunc('day', jointime_ist) then 1 else 0 end) sumd1,
 sum(case when date_trunc('day', eventtime_ist - interval '3 day') = date_trunc('day', jointime_ist) then 1 else 0 end) sumd3,
 sum(case when date_trunc('day', eventtime_ist - interval '7 day') = date_trunc('day', jointime_ist) then 1 else 0 end) sumd7,
 sum(case when date_trunc('day', eventtime_ist - interval '14 day') = date_trunc('day', jointime_ist) then 1 else 0 end) sumd14,
 count(*) as nsessions,
 sum(0) ngames,
 sum(0) upurchasers,
 sum(0) numpurchases,
 sum(0) coinpurchased,
 sum(0) tapjoycount,
 sum(0) tapjoychips
FROM R2_$table
GROUP BY deviceid, cohort, install_date_ist, install_time_ist, jointime_ist";
$result = RedshiftExecute($pgConn, $sql5);
if(!$result) die("Failed_5 !\n" ); else echo "Successfull_5 !\n\n";

$sql6 = " UPDATE $device_perf
SET sumd1 = (case when sumd1 >0 then 1 else 0 end),
    sumd3 = (case when sumd3 >0 then 1 else 0 end),
    sumd7 = (case when sumd7 >0 then 1 else 0 end),
    sumd14 = (case when sumd14 >0 then 1 else 0 end)";
$result = RedshiftExecute($pgConn, $sql6);
if(!$result) die("Failed_6 !\n" ); else echo "successfull_6 !\n\n";


/*.......................... PURCHASE WORK ..........................................*/

 $purchase_ledgers = $app."_purchase_ledgers_vik"; 

// TEMPORARY TABLE 1 FOR PURCHASES COMPUTATIONS
RedshiftExecute($pgConn, "DROP TABLE if exists P1_$table");
$sql7 = "CREATE TEMPORARY TABLE  P1_$table AS
SELECT deviceid, cohort, install_date_ist, install_time_ist, userid, 0 as nGames
FROM $devices_login_info
GROUP BY deviceid, cohort, install_date_ist, install_time_ist, userid";
$result = RedshiftExecute($pgConn, $sql7);
if(!$result) die("Failed_7 !\n" ); else echo "Successfull_7 !\n\n";

$sql7_1 = "CREATE TEMPORARY TABLE P0_$table AS
select * from $ledgertable where date(eventtime)>='2015-06-01' and source ~ '^[pvrtcsn][0123456789-]' and  changemoney<>0
"; 
$result = RedshiftExecute($pgConn, $sql7_1);
if(!$result) die("Failed_7_1 !\n" ); else echo "Successfull_7_1 !\n\n";
 

//UPDATING NGAMES COLUMN
$sql7_2 = "UPDATE P1_$table
SET nGames = a.nGames
FROM (SELECT  deviceid, cohort, install_date_ist, install_time_ist,P1_$table.userid, count(*) as nGames FROM P1_$table , P0_$table b WHERE  P1_$table.userid=b.userid and P1_$table.install_time_ist<=(b.eventtime + interval '45000 seconds')  GROUP BY deviceid, cohort, install_date_ist, install_time_ist,P1_$table.userid ) a
WHERE  P1_$table.userid = a.userid and P1_$table.deviceid=a.deviceid and P1_$table.cohort=a.cohort
";
$result = RedshiftExecute($pgConn, $sql7_2);
if(!$result) die("Failed_7_2 !\n" ); else echo "Successfull_7_2 !\n\n";



//EXTRACTING INAPP AND TAPJOY PURCHASES FROM LEDGER TABLE
RedshiftExecute($pgConn, "DROP TABLE if exists $purchase_ledgers");
$sql8 = "CREATE TEMPORARY TABLE $purchase_ledgers AS
SELECT userid,(eventtime+interval '45000 seconds') as purchasetime_ist,source,changemoney
FROM $ledgertable
WHERE date(eventtime) >='2015-06-01'  AND source='inapp_purchase' OR source = 'tapjoy'";
$result = RedshiftExecute($pgConn, $sql8);
if(!$result) die("Failed_8 !\n" ); else echo "Successfull_8 !\n\n";


// PURCHSE INFORMATIONS OF USERS
RedshiftExecute($pgConn, "DROP TABLE if exists P2_$table");
$sql9 = "CREATE TABLE  P2_$table AS
SELECT deviceid, cohort,'00000000000000000000' as campaign, install_date_ist, install_time_ist, userid, purchasetime_ist, source, changemoney
FROM P1_$table NATURAL JOIN $purchase_ledgers
WHERE purchasetime_ist >= install_time_ist";
$result = RedshiftExecute($pgConn, $sql9);
if(!$result) die("Failed_9 !\n" ); else echo "Successfull_9 !\n\n";

$sql9_2="Update P2_$table SET campaign= a.fb_campaign_id
FROM (SELECT distinct fb_campaign_id, fb_adset_id FROM apf_cb2 WHERE fb_campaign_id<>'' and fb_adset_id<>'') a
WHERE split_part(P2_$table.cohort,'_',1) = a.fb_adset_id";
$result = RedshiftExecute($pgConn, $sql9_2);
if(!$result) die("Failed_9_2 !\n" ); else echo "Successfull_9_2 !\n\n";


//PURCHASE AGGREGATION FOR COHORTS
RedshiftExecute($pgConn, "DROP TABLE if exists P3_$table");
$sql10 = "CREATE TEMPORARY TABLE  P3_$table AS
SELECT deviceid, cohort, install_date_ist, install_time_ist,
 sum(case when source='inapp_purchase' then 1 else 0 end)  numpurchases,
 sum(case when source='inapp_purchase' then changemoney else 0 end)  coinpurchased,
 sum(case when source='tapjoy' then 1 else 0 end)  tapjoycount,
 sum(case when source='tapjoy' then changemoney else 0 end)  tapjoychips
FROM P2_$table
GROUP BY deviceid, cohort, install_date_ist, install_time_ist";
$result = RedshiftExecute($pgConn, $sql10);
if(!$result) die("Failed_10 !\n" ); else echo "Successfull_10 !\n\n";


$sql11 = "UPDATE $device_perf
SET numpurchases = P3_$table.numpurchases, coinpurchased = P3_$table.coinpurchased, tapjoycount=P3_$table.tapjoycount , tapjoychips= P3_$table.tapjoychips
FROM P3_$table
WHERE P3_$table.deviceid= $device_perf.deviceid and P3_$table.cohort = $device_perf.cohort";
$result = RedshiftExecute($pgConn, $sql11);
if(!$result) die("Failed_11 !\n" ); else echo "Successfull_11 !\n\n";

RedshiftExecute($pgConn, "DROP TABLE if exists P4_$table");
$sql12 = "CREATE TEMPORARY TABLE  P4_$table AS
SELECT deviceid, cohort, install_date_ist, install_time_ist, count(distinct userid) as upurchasers
FROM P2_$table
WHERE source = 'inapp_purchase'
GROUP BY deviceid, cohort, install_date_ist, install_time_ist";
$result = RedshiftExecute($pgConn, $sql12);
if(!$result) die("Failed_12 !\n" ); else echo "Successfull_12 !\n\n";

$sql13 = "UPDATE $device_perf
SET upurchasers = P4_$table.upurchasers
FROM P4_$table
WHERE P4_$table.deviceid= $device_perf.deviceid and P4_$table.cohort = $device_perf.cohort";
$result = RedshiftExecute($pgConn, $sql13);
if(!$result) die("Failed_13 !\n" ); else echo "Successfull_13 !\n\n";

$sql14 ="UPDATE $device_perf
SET  ngames = a.nGames
FROM (select deviceid, cohort, install_date_ist, install_time_ist, sum(nGames) as nGames FROM P1_$table GROUP BY deviceid, cohort, install_date_ist, install_time_ist) a
WHERE $device_perf.deviceid=a.deviceid and $device_perf.cohort = a.cohort and $device_perf.install_date_ist= a.install_date_ist and  $device_perf.install_time_ist = a.install_time_ist;
";
$result = RedshiftExecute($pgConn, $sql14);
if(!$result) die("Failed_14 !\n" ); else echo "Successfull_14 !\n\n";

RedshiftCloseConnection($pgConn);
exit(0);

/*


$sql12 = "CREATE TABLE  P5_$table AS
SELECT install_time_ist, cohort,userid, purchasetime_ist, changemoney FROM P2_$table 
WHERE source = 'inapp_purchase';

SELECT userid, purchasetime_ist , changemoney from $user_purchase_table where source = 'inapp_purchase' and cohort like '$adset'.'_% and install_date_ist between $start_date and $end_date;

SELECT userid, purchasetime_ist , changemoney from () where 

 */

/*
RedshiftExecute($pgConn, "DROP TABLE IF EXISTS $devices_login_info");
RedshiftExecute($pgConn, "DROP TABLE IF EXISTS R1_$table");
RedshiftExecute($pgConn, "DROP TABLE IF EXISTS R2_$table");
RedshiftExecute($pgConn, "DROP TABLE IF EXISTS P1_$table");
RedshiftExecute($pgConn, "DROP TABLE IF EXISTS $purchase_ledgers");
RedshiftExecute($pgConn, "DROP TABLE IF EXISTS P2_$table");
RedshiftExecute($pgConn, "DROP TABLE IF EXISTS P3_$table");
*/

//(SELECT numpurchases, coinpurchased, tapjoycount, tapjoychips FROM P3_$table WHERE P3_$table.deviceid= $device_perf.deviceid and P3_$table.cohort = $device_perf.cohort) a";
/*SET numpurchases = (SELECT numpurchases FROM P3_$table a WHERE a.deviceid = $device_perf.deviceid and a.cohort = $device_perf.cohort),
    coinpurchased = (SELECT coinpurchased FROM P3_$table a WHERE a.deviceid = $device_perf.deviceid and a.cohort = $device_perf.cohort),
    tapjoycount = (SELECT tapjoycount FROM P3_$table a WHERE a.deviceid = $device_perf.deviceid and a.cohort = $device_perf.cohort),
    tapjoychips = (SELECT tapjoychips FROM P3_$table a WHERE a.deviceid = $device_perf.deviceid and a.cohort = $device_perf.cohort)";*/

////////////////////////////////////////////////////////////////////////////////////////////////
?>