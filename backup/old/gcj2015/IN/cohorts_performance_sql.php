<?php
date_default_timezone_set('Asia/Kolkata'); 
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
  $result=FALSE;
  while(!$result){
  echo $sql. PHP_EOL; //exit(0);
  $result = pg_query($pgConn, $sql);
  if(!$result) {echo pg_last_error($pgConn);echo "\n Retrying ... \n";}
  else return $result;}
}
function MySqlConnection()
{
  // MySql connection to the database 'ads';
  $servername = "localhost";
  $username = "ads";
  $password = "ads";
  $db = "ads";
  $conn = new mysqli($servername, $username, $password, $db);
  if ($conn->connect_error)  {echo "Connection failed to the db ads: " . $conn->connect_error. PHP_EOL; return FALSE;}
  echo "Connected successfully to the $db database!". PHP_EOL;
  return $conn; 
}
function RedshiftCloseConnection($pgConn) { pg_close($pgConn);}
function MySqlCloseConnection($myConn) {mysqli_close($myConn);}
exit(0);
/********************************************************************************************************/

$app = $argv[1];
$min_time_UTC = $argv[2];//'2015-06-01' the date we read rows after,  in ledgers and install_track;
$last_time_UTC = $argv[3];
$current_time_UTC = $argv[4];

$devices_cohort = $app."_cohort_vkp";
$devices_login_info = $app."_dli_vkp";
$devices_perf = $app."_perf_vkp";
$user_purchases = $app."_purchases_vik";
/*******************************************************************************/
$app_id =''; $ledgertable ='';
if($app === 'TeenPatti')  {$app_id = "com.octro.teenpatti"; $ledgertable = 'tpledger_timeuser2';}
else if($app === 'TPL')  {$app_id = "com.octro.teenpattilive";$ledgertable = 'tpledger_timeuser2';}
else if($app === 'Rummy')  {$app_id = "com.octro.rummy"; $ledgertable = 'rmledger_time';}
else if($app === 'Tambola')  {$app_id = "com.octro.tambola";$ledgertable = 'tamledger_time';}
else if($app === 'Carrom')  {$app_id = "com.octro.carromlive";$ledgertable = 'carromledger_time';}
/********************************************************************************************************/
$pgConn = RedshiftConnection();

if($last_time_UTC<=$min_time_UTC){
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_cohort");
$sql1 =  "CREATE TABLE $devices_cohort AS
SELECT   media_source as adnetwork,fb_campaign_id,fb_adset_id,customer_user_id as deviceid,date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist
FROM     apf_cb2 
WHERE    customer_user_id<>'' and media_source<>'Organic' and  media_source<>'' and app_id='$app_id' and eventtime >='$min_time_UTC' and eventtime<'$current_time_UTC'
GROUP BY media_source,fb_campaign_id,fb_adset_id,customer_user_id,date(install_time + interval '19800 seconds')";

$sql1_1 = "DELETE FROM $devices_cohort  WHERE adnetwork='Facebook Ads' and fb_adset_id='' ";
$sql1_2 = "UPDATE $devices_cohort SET adnetwork= case when adnetwork='Facebook Ads' then 'Facebook' when adnetwork='googleadwords_int' then 'Google' when adnetwork='tapjoy_int' then 'Tapjoy' when adnetwork='inmobi_int' then 'Inmobi' when adnetwork='cheetahmobile_int' then 'Cheetah' end";
$result = RedshiftExecute($pgConn,$sql1); if(!$result) die("Failed_1 !\n" ); else echo "Successfull_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_1); if(!$result) die("Failed_1_1 !\n" ); else echo "Successfull_1_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_2); if(!$result) die("Failed_1_2 !\n" ); else echo "Successfull_1_2 !\n\n";

$sql2 = "CREATE TABLE $devices_login_info AS
SELECT  adnetwork,fb_campaign_id,fb_adset_id,deviceid, install_date_ist, install_time_ist,  a.userid, (a.eventtime + interval '45000 seconds') as eventtime_ist, '0000-00-00 00:00:00' as jointime_ist
FROM $devices_cohort NATURAL JOIN (select userid, eventtime from install_track where eventtime >='$min_time_PDT' and eventtime < '$current_time_PDT' and app ='$app') a
WHERE (a.eventtime + interval '45000 seconds') >= install_time_ist";
$result = RedshiftExecute($pgConn, $sql2);
if(!$result) die("Failed_2 !\n" ); else echo "Successfull_2 !\n\n";
}

else{
$sql1 =  "CREATE TEMPORARY TABLE temp_cohort_vkp AS
SELECT   media_source as adnetwork,fb_campaign_id,fb_adset_id,customer_user_id as deviceid,date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist
FROM     apf_cb2
WHERE    customer_user_id<>'' and media_source<>'Organic' and  media_source<>'' and app_id='$app_id' and eventtime >='$last_time_UTC' and eventtime<'$current_time_UTC'
GROUP BY media_source,fb_campaign_id,fb_adset_id,customer_user_id,date(install_time + interval '19800 seconds')";
$sql1_1 = "DELETE FROM temp_cohort_vkp  WHERE adnetwork='Facebook Ads' and fb_adset_id='' ";
$sql1_2 = "UPDATE temp_cohort_vkp SET adnetwork= case when adnetwork='Facebook Ads' then 'Facebook' when adnetwork='googleadwords_int' then 'Google' when adnetwork='tapjoy_int' then 'Tapjoy' when adnetwork='inmobi_int' then 'Inmobi' when adnetwork='cheetahmobile_int'
then 'Cheetah' end";
$result = RedshiftExecute($pgConn,$sql1); if(!$result) die("Failed_1 !\n" ); else echo "Successfull_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_1); if(!$result) die("Failed_1_1 !\n" ); else echo "Successfull_1_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_2); if(!$result) die("Failed_1_2 !\n" ); else echo "Successfull_1_2 !\n\n";

// build cohort2 from temp_vkp by making it disjoint from original cohort.
$sql1_3 = "CREATE TEMPORARY TABLE new_cohort_vkp by discarding some rows from temp_cohort_vkp";



$sql2 = "INSERT INTO $devices_login_info (SELECT  adnetwork,fb_campaign_id,fb_adset_id,deviceid, install_date_ist, install_time_ist,  a.userid, (a.eventtime + interval '45000 seconds') as eventtime_ist, '0000-00-00 00:00:00' as jointime_ist
FROM new_cohort_vkp NATURAL JOIN (select userid, eventtime from install_track where eventtime >='$min_time_PDT' and eventtime <'$current_time_PDT' and app ='$app') a
WHERE (a.eventtime + interval '45000 seconds') >= install_time_ist)";
$result = RedshiftExecute($pgConn, $sql2); if(!$result) die("Failed_2 !\n" ); else echo "Successfull_2 !\n\n";

$sql3 = "INSERT INTO $devices_login_info (SELECT  adnetwork,fb_campaign_id,fb_adset_id,deviceid, install_date_ist, install_time_ist,  a.userid, (a.eventtime + interval '45000 seconds') as eventtime_ist, '0000-00-00 00:00:00' as jointime_ist
FROM $devices_cohort NATURAL JOIN (select userid, eventtime from install_track where eventtime >='$last_time_PDT' and eventtime <'$current_time_PDT' and app ='$app') a
WHERE (a.eventtime + interval '45000 seconds') >= install_time_ist)";
$result = RedshiftExecute($pgConn, $sql3); if(!$result) die("Failed_3 !\n" ); else echo "Successfull_3 !\n\n";

$sql4 = "INSERT INTO $devices_cohort (SELECT * FROM new_cohort_vkp)";
$result = RedshiftExecute($pgConn, $sql4); if(!$result) die("Failed_4 !\n" ); else echo "Successfull_4 !\n\n";

}

$sql5 =" UPDATE $devices_login_info SET jointime_ist = a.min_eventtime
FROM (select adnetwork,fb_campaign_id,fb_adset_id,deviceid, install_date_ist, min(eventtime_ist) as min_eventtime FROM $devices_login_info GROUP BY adnetwork,fb_campaign_id,fb_adset_id,deviceid, install_date_ist) a
WHERE $devices_login_info.adnetwork = a.adnetwork and $devices_login_info.fb_campaign_id = a.fb_campaign_id and $devices_login_info.fb_adset_id = a.fb_adset_id and $devices_login_info.deviceid = a.deviceid and $devices_login_info.install_date_ist = a.install_date_ist";
$result = RedshiftExecute($pgConn, $sql5); if(!$result) die("Failed_5 !\n" ); else echo "Successfull_5 !\n\n";

//FINAL RETENTION TABLE AT REDSHIFT
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_perf");
$sql7 = "CREATE TABLE $devices_perf AS
SELECT adnetwork,fb_campaign_id,fb_adset_id, deviceid,install_date_ist,
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
FROM $devices_login_info
GROUP BY adnetwork,fb_campaign_id,fb_adset_id, deviceid, install_date_ist";
$result = RedshiftExecute($pgConn, $sql7);if(!$result) die("Failed_7 !\n" ); else echo "Successfull_7 !\n\n";

$sql8 = " UPDATE $devices_perf
SET sumd1 = (case when sumd1 >0 then 1 else 0 end),
    sumd3 = (case when sumd3 >0 then 1 else 0 end),
    sumd7 = (case when sumd7 >0 then 1 else 0 end),
    sumd14 = (case when sumd14 >0 then 1 else 0 end)";
$result = RedshiftExecute($pgConn, $sql8);if(!$result) die("Failed_8 !\n" ); else echo "successfull_8 !\n\n";
/*----------------------------------------------------------------------------------------------------------*/
$sql9 = "CREATE TEMPORARY TABLE $devices_ledger AS
SELECT userid, (eventtime + inerval'45000 seconds') as ledgertime_ist, source, changemoney FROM $ledgertable  WHERE eventtime >='$min_time_PDT' and eventtime<'$current_time_PDT' and (source ='inapp_purchase' OR source ='tapjoy' OR source ~ '^[pvrtcsn][0-9-]')";

// TEMPORARY TABLE 1 FOR PURCHASES COMPUTATIONS
$sql10 = "CREATE TEMPORARY TABLE P1 AS
SELECT adnetwork,fb_campaign_id,fb_adset_id,install_date_ist,install_time_ist,deviceid,userid, 0 as nGames
FROM $devices_login_info
GROUP BY adnetwork,fb_campaign_id,fb_adset_id, install_date_ist, install_time_ist, deviceid, userid";
$result = RedshiftExecute($pgConn, $sql10); if(!$result) die("Failed_10 !\n" ); else echo "Successfull_10 !\n\n";

$sql11 = "UPDATE P1
SET nGames = a.nGames
FROM (SELECT adnetwork,fb_adset_id,install_date_ist,install_time_ist,deviceid,userid,count(*) as nGames FROM P1 NATURAL JOIN (SELECT * FROM $devices_ledger WHERE source <>'inapp_purchase' AND source <>'tapjoy') WHERE install_time_ist <= ledgertime_ist  GROUP BY adnetwork,fb_adset_id, install_date_ist, install_time_ist, deviceid, userid) a
WHERE P1.adnetwork = a.adnetwork and P1.fb_adset_id=a.fb_adset_id and P1.install_date_ist=a.install_date_ist and P1.deviceid=a.deviceid and P1.userid =a.userid";
$result = RedshiftExecute($pgConn, $sql11); if(!$result) die("Failed_11 !\n" ); else echo "Successfull_11 !\n\n";

// PURCHSE INFORMATIONS OF USERS
RedshiftExecute($pgConn, "DROP TABLE if exists $user_purchases");
$sql12 = "CREATE TABLE  $user_purchases AS
SELECT * FROM P1 NATURAL JOIN (SELECT * FROM $purchase_ledgers WHERE source ='inapp_purchase' OR source = 'tapjoy')
WHERE install_time_ist<=ledgertime_ist";
$result = RedshiftExecute($pgConn, $sql12);if(!$result) die("Failed_12 !\n" ); else echo "Successfull_12 !\n\n";

$sql13 = "CREATE TEMPORARY TABLE  P3 AS
SELECT adnetwork,fb_adset_id,install_date_ist,deviceid,
 sum(case when source='inapp_purchase' then 1 else 0 end)  numpurchases,
 sum(case when source='inapp_purchase' then changemoney else 0 end)  coinpurchased,
 sum(case when source='tapjoy' then 1 else 0 end)  tapjoycount,
 sum(case when source='tapjoy' then changemoney else 0 end)  tapjoychips
FROM $user_purchases
GROUP BY adnetwork,fb_adset_id,install_date_ist,deviceid";
$result = RedshiftExecute($pgConn, $sql13);if(!$result) die("Failed_13 !\n" ); else echo "Successfull_13 !\n\n";

$sql14 = "UPDATE $devices_perf
SET numpurchases = P3.numpurchases, coinpurchased = P3.coinpurchased, tapjoycount=P3.tapjoycount , tapjoychips= P3.tapjoychips
FROM P3
WHERE P3.adnetwork = $devices_perf.adnetwork and P3.fb_adset_id=$devices_perf.fb_adset_id and P3.install_date_ist=$devices_perf.install_date_ist and P3.deviceid=$devices_perf.deviceid ";
$result = RedshiftExecute($pgConn, $sql14);if(!$result) die("Failed_14 !\n" ); else echo "Successfull_14 !\n\n";


$sql15 = "UPDATE $devices_perf
SET upurchasers = a.upurchasers
FROM (SELECT adnetwork,fb_adset_id,install_date_ist,deviceid,count(distinct userid) as upurchasers FROM $user_purchases WHERE source='inapp_purchase' GROUP BY adnetwork,fb_adset_id,install_date_ist,deviceid) a
WHERE $devices_perf.adnetwork=a.adnetwork and $devices_perf.fb_adset_id=a.fb_adset_id and $devices_perf.install_date_ist=a.install_date_ist and $devices_perf.deviceid=a.deviceid";
$result = RedshiftExecute($pgConn, $sql15);if(!$result) die("Failed_15 !\n" ); else echo "Successfull_15 !\n\n";


$sql16 ="UPDATE $devices_perf
SET  ngames = a.nGames
FROM (select adnetwork,fb_adset_id,install_date_ist,deviceid,sum(nGames) as nGames FROM P1 GROUP BY adnetwork,fb_adset_id,install_date_ist,deviceid) a
WHERE $devices_perf.adnetwotk = a.adnetwotk and $devices_perf.fb_adset_id= a.fb_adset_id and  $devices_perf.install_date_ist = a.install_date_ist and $devices_perf.deviceid=a.deviceid";
$result = RedshiftExecute($pgConn, $sql16);if(!$result) die("Failed_16 !\n" ); else echo "Successfull_16 !\n\n";

// MYSQL PORTING

   
////////////////////////////////////////////////////////////  DONE  ///////////////////////////////////////////////////////////////////////////////
/*...........................................................................................................*/

$sql9 = "CREATE TABLE $devices_users AS
SELECT distinct userid FROM $devices_login_info";
$result = RedshiftExecute($pgConn, $sql9); if(!$result) die("Failed_9 !\n" ); else echo "Successfull_9 !\n\n";

$sql10 = "CREATE TABLE $devices_user_ledgers AS
SELECT * FROM $devices_users NATURAL JOIN (SELECT userid, (eventtime + inerval'45000 seconds') as ledgertime_ist, source, changemoney FROM $ledgertable  WHERE eventtime >='$min_time_PDT' and eventtime<'$current_time_PDT' and (source ='inapp_purchase' OR source ='tapjoy' OR source ~ '^[pvrtcsn][0-9-]'))";

$sql11 = "CREATE TABLE ";



/*.......................... PURCHASE WORK ..........................................*/

//EXTRACTING GAME LEDGERS FROM LEDGER TABLE
$sql10 = "CREATE TEMPORARY TABLE game_ledgers_vik AS
select * from $ledgertable where eventtime >='$min_date_UTC' and source ~ '^[pvrtcsn][0123456789-]' and  changemoney<>0";
$result = RedshiftExecute($pgConn, $sql10); if(!$result) die("Failed_10 !\n" ); else echo "Successfull_10 !\n\n";

//EXTRACTING INAPP AND TAPJOY PURCHASES FROM LEDGER TABLE
$sql11 = "CREATE TEMPORARY TABLE purchase_ledgers_vik AS
SELECT userid,(eventtime+interval '45000 seconds') as purchasetime_ist,source,changemoney
FROM $ledgertable
WHERE eventtime >='$min_date_UTC' AND source='inapp_purchase' OR source = 'tapjoy'";
$result = RedshiftExecute($pgConn, $sql11); if(!$result) die("Failed_11 !\n" ); else echo "Successfull_11 !\n\n";

// TEMPORARY TABLE 1 FOR PURCHASES COMPUTATIONS
RedshiftExecute($pgConn, "DROP TABLE if exists P1_$table");
$sql12 = "CREATE TEMPORARY TABLE  _vik AS
SELECT deviceid, cohort, install_date_ist, install_time_ist, userid, 0 as nGames
FROM $devices_login_info
GROUP BY deviceid, cohort, install_date_ist, install_time_ist, userid";
$result = RedshiftExecute($pgConn, $sql7);
if(!$result) die("Failed_7 !\n" ); else echo "Successfull_7 !\n\n";


//UPDATING NGAMES COLUMN
$sql7_2 = "UPDATE P1_$table
SET nGames = a.nGames
FROM (SELECT  deviceid, cohort, install_date_ist, install_time_ist,P1_$table.userid, count(*) as nGames FROM P1_$table , P0_$table b WHERE  P1_$table.userid=b.userid and P1_$table.install_time_ist<=(b.eventtime + interval '45000 seconds')  GROUP BY deviceid, cohort, install_date_ist, install_time_ist,P1_$table.userid ) a
WHERE  P1_$table.userid = a.userid and P1_$table.deviceid=a.deviceid and P1_$table.cohort=a.cohort
";
$result = RedshiftExecute($pgConn, $sql7_2);
if(!$result) die("Failed_7_2 !\n" ); else echo "Successfull_7_2 !\n\n";




exit(0);
/////////////

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
select * from $ledgertable where date(eventtime)>='$date_floor_UTC' and source ~ '^[pvrtcsn][0123456789-]' and  changemoney<>0";
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
WHERE date(eventtime) >='$date_floor_UTC' AND source='inapp_purchase' OR source = 'tapjoy'";
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

if($AdNetwork == 'Facebook'){
$sql9_2="Update P2_$table SET campaign= a.fb_campaign_id
FROM (SELECT distinct fb_campaign_id, fb_adset_id FROM apf_cb2 WHERE fb_campaign_id<>'' and fb_adset_id<>'') a
WHERE split_part(P2_$table.cohort,'_',1) = a.fb_adset_id";
$result = RedshiftExecute($pgConn, $sql9_2);
if(!$result) die("Failed_9_2 !\n" ); else echo "Successfull_9_2 !\n\n";
}

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


$sql11 = "UPDATE $devices_perf_at_RS
SET numpurchases = P3_$table.numpurchases, coinpurchased = P3_$table.coinpurchased, tapjoycount=P3_$table.tapjoycount , tapjoychips= P3_$table.tapjoychips
FROM P3_$table
WHERE P3_$table.deviceid= $devices_perf_at_RS.deviceid and P3_$table.cohort = $devices_perf_at_RS.cohort";
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

$sql13 = "UPDATE $devices_perf_at_RS
SET upurchasers = P4_$table.upurchasers
FROM P4_$table
WHERE P4_$table.deviceid= $devices_perf_at_RS.deviceid and P4_$table.cohort = $devices_perf_at_RS.cohort";
$result = RedshiftExecute($pgConn, $sql13);
if(!$result) die("Failed_13 !\n" ); else echo "Successfull_13 !\n\n";

$sql14 ="UPDATE $devices_perf_at_RS
SET  ngames = a.nGames
FROM (select deviceid, cohort, install_date_ist, install_time_ist, sum(nGames) as nGames FROM P1_$table GROUP BY deviceid, cohort, install_date_ist, install_time_ist) a
WHERE $devices_perf_at_RS.deviceid=a.deviceid and $devices_perf_at_RS.cohort = a.cohort and $devices_perf_at_RS.install_date_ist= a.install_date_ist and  $devices_perf_at_RS.install_time_ist = a.install_time_ist;
";
$result = RedshiftExecute($pgConn, $sql14);
if(!$result) die("Failed_14 !\n" ); else echo "Successfull_14 !\n\n";

exit(0);
/*
if($last_time_UTC<=$min_date){
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_n_their_cohort");
$sql1 = "CREATE TABLE  $devices_n_their_cohort AS
select media_source as adnetwork,fb_campaign_id,fb_adset_id,customer_user_id as deviceid,date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist from apf_cb2 where customer_user_id<>'' and media_source<> 'Organic' and  media_source <>'' and app_id='$app_id' and eventtime<'$current_time_UTC' group by media_source,fb_campaign_id,fb_adset_id,customer_user_id,date(install_time + interval '19800 seconds')";
$sql1_1 = "DELETE FROM $devices_n_their_cohort WHERE adnetwork='Facebook Ads' and fb_adset_id='' ";
$sql1_2 = "UPDATE $devices_n_their_cohort SET adnetwork= case when adnetwork='Facebook Ads' then 'Facebook' when adnetwork='googleadwords_int' then 'Google' when adnetwork='tapjoy_int' then 'Tapjoy' when adnetwork='inmobi_int' then 'Inmobi' when adnetwork='cheetahmobile_int' then 'Cheetah' end";
$result = RedshiftExecute($pgConn,$sql1); if(!$result) die("Failed_1 !\n" ); else echo "Successfull_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_1); if(!$result) die("Failed_1_1 !\n" ); else echo "Successfull_1_1 !\n\n";
$result = RedshiftExecute($pgConn, "SELECT COUNT(*) as count FROM $devices_n_their_cohort");
$Rows = pg_fetch_all($result);foreach($Rows as $Row) {if($Row['count']==0) exit(0);}
$result = RedshiftExecute($pgConn,$sql1_2); if(!$result) die("Failed_1_2 !\n" ); else echo "Successfull_1_2 !\n\n";

RedshiftExecute($pgConn, "DROP TABLE if exists $devices_login_info");
$sql2 = "CREATE TEMPORARY TABLE $devices_login_info AS
SELECT  adnetwork,fb_campaign_id,fb_adset_id,deviceid, install_date_ist, install_time_ist, (a.eventtime + interval '45000 seconds') as eventtime_ist, a.userid
FROM $devices_n_their_cohort NATURAL JOIN (select userid, eventtime, app from install_track where eventtime >'$min_date' and app ='$app') a
WHERE (a.eventtime + interval '45000 seconds') >= install_time_ist";
$result = RedshiftExecute($pgConn, $sql2);
if(!$result) die("Failed_2 !\n" ); else echo "Successfull_2 !\n\n";
}
else{
RedshiftExecute($pgConn, "DROP TABLE if exists cohort1");
$sql1 = "CREATE TABLE cohort1 AS
select media_source as adnetwork,fb_campaign_id,fb_adset_id,customer_user_id as deviceid,date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist from apf_cb2 where customer_user_id<>'' and media_source<> 'Organic' and  media_source <>'' and app_id='$app_id' and eventtime >='$last_time_UTC' and eventtime<'$current_time_UTC' group by media_source,fb_campaign_id,fb_adset_id,customer_user_id,date(install_time + interval '19800 seconds')";
$sql1_1 = "DELETE FROM cohort1 WHERE adnetwork='Facebook Ads' and fb_adset_id='' ";
$sql1_2 = "UPDATE cohort1 SET adnetwork= case when adnetwork='Facebook Ads' then 'Facebook' when adnetwork='googleadwords_int' then 'Google' when adnetwork='tapjoy_int' then 'Tapjoy' when adnetwork='inmobi_int' then 'Inmobi' when adnetwork='cheetahmobile_int' then 'Cheetah' end";
$result = RedshiftExecute($pgConn,$sql1); if(!$result) die("Failed_1 !\n" ); else echo "Successfull_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_1); if(!$result) die("Failed_1_1 !\n" ); else echo "Successfull_1_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_2); if(!$result) die("Failed_1_2 !\n" ); else echo "Successfull_1_2 !\n\n";
}
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*******************************************************************/
/* $app = $argv[1]; */
/* $devices_n_their_cohort = $app."_devices_with_cohort_vik"; */
/* $devices_login_info = $app."_devices_login_details_vik"; */
/* $table = $app."_temp_vik"; */
/* $devices_perf_at_RS = $app."_devices_performance_vik"; */
/********************************************************************************************************/
/*$pgConn = RedshiftConnection();

//$today_date=date("Y-m-d");$yesterday_date_utc=date("Y-m-d", strtotime($today_date)-(19800+86400));
$last_time_UTC=$argv[2];
$current_time_UTC =$argv[3];
if($last_time_UTC==='2015-01-01 00:00:00'){
//CREATING COHORT TABLE FROM SCRATCH.IT IS CREATED ONLY ONCE AND NEEDS TO BE UPDATED(incrementally) WITH NEW DATA IN apf_cb2.
$sql1 = "CREATE TABLE  $devices_n_their_cohort AS
select media_source as adnetwork,fb_campaign_id,fb_adset_id,customer_user_id as deviceid,date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist from apf_cb2 where customer_user_id<>'' and media_source<> 'Organic' and  media_source <>'' and app_id='$app_id' and eventtime<'$current_time_UTC' group by media_source,fb_campaign_id,fb_adset_id,customer_user_id,date(install_time + interval '19800 seconds')";
$sql1_1 = "DELETE FROM $devices_n_their_cohort WHERE adnetwork='Facebook Ads' and fb_adset_id='' ";
$sql1_2 = "UPDATE $devices_n_their_cohort SET adnetwork= case when adnetwork='Facebook Ads' then 'Facebook' when adnetwork='googleadwords_int' then 'Google' when adnetwork='tapjoy_int' then 'Tapjoy' when adnetwork='inmobi_int' then 'Inmobi' when adnetwork='cheetahmobile_int' then 'Cheetah' end";
$result = RedshiftExecute($pgConn,$sql1); if(!$result) die("Failed_1 !\n" ); else echo "Successfull_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_1); if(!$result) die("Failed_1_1 !\n" ); else echo "Successfull_1_1 !\n\n";
$result = RedshiftExecute($pgConn,$sql1_2); if(!$result) die("Failed_1_2 !\n" ); else echo "Successfull_1_2 !\n\n";
}

sleep(120);
//UPDATING COHORT TABLE FROM YESTERDAY DATA AT apf_cb2 (i.e. APSFLYER DATA)
$sql2 = "SELECT media_source,fb_campaign_id,fb_adset_id,customer_user_id,date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist  FROM apf_cb2 WHERE eventtime >= '$last_time_UTC' and eventtime <'$current_time_UTC' and customer_user_id<>'' and media_source<> 'Organic' and  media_source <>'' and app_id='$app_id' GROUP BY media_source,fb_campaign_id,fb_adset_id,customer_user_id,date(install_time + interval '19800 seconds')";
$Rows=RedshiftExecute($pgConn,$sql2);
//var_dump($Rows);
$Rows = pg_fetch_all($Rows);
foreach($Rows as $row)
  {
    if($row['media_source']=='Facebook Ads') $ms ='Facebook';else if($row['media_source']=='googleadwords_int') $ms = 'Google';else if($row['media_source']=='tapjoy_int') $ms = 'Tapjoy'; else if($row['media_source']=='inmobi_int') $ms = 'Inmobi'; 
    else if($row['media_source']=='cheetahmobile_int') $ms = 'Cheetah'; else continue;
    $fci=$row['fb_campaign_id'];$fai=$row['fb_adset_id'];$cui=$row['customer_user_id'];$idi=$row['install_date_ist'];$iti=$row['install_time_ist']; 

    $sql3="SELECT count(*) as cnt, min(install_time_ist) as install_time_ist from $devices_n_their_cohort where adnetwork='$ms' and fb_adset_id='$fai' and deviceid ='$cui' and install_date_ist='$idi'";
    $ret=RedshiftExecute($pgConn,$sql3);
    $ret = pg_fetch_all($ret);
    $cnt=0;$install_time_ist='';
    foreach($ret as $r) {$cnt=$r['cnt']; $install_time_ist=$r['install_time_ist'];}

    if($cnt==0) RedshiftExecute($pgConn,"INSERT INTO $devices_n_their_cohort(adnetwork,fb_campaign_id,fb_adset_id,deviceid,install_date_ist,install_time_ist) VALUES('$ms', '$fci', '$fai', '$cui', '$idi', '$iti')");
    else if( $cnt==1 && $install_time_ist !='' && $install_time_ist >$iti) RedshiftExecute($pgConn,"UPDATE $devices_n_their_cohort SET install_time_ist='$iti' WHERE adnetwork='$ms' and fb_adset_id='$fai' and deviceid='$cui' and install_date_ist='$idi'");
    else echo "Invalid entry in cohort table $cui,$idi".PHP_EOL;
  }
echo 'successfull'.PHP_EOL;
exit(0);

*/




/*

// PREPARING COHORT(as device-cohort pair) FOR THE GIVEN APP AND NETWORK FROM 'apf_cb2' TABLE ON REDSHIFT
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_n_their_cohort");
if($AdNetwork == 'Facebook')
  {
    $sql1 = "CREATE TEMPORARY TABLE $devices_n_their_cohort AS 
    SELECT customer_user_id as deviceid, fb_adset_id || '_' || date(install_time + interval '19800 seconds') as cohort, date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist FROM apf_cb2
WHERE customer_user_id<>'' and fb_adset_id <>'' and app_id ='$app_id'
GROUP BY customer_user_id, fb_adset_id, date(install_time + interval '19800 seconds')";
  }
else if($AdNetwork == 'Google')
  {
    $sql1="CREATE TEMPORARY TABLE $devices_n_their_cohort AS
    SELECT customer_user_id as deviceid, 'google_' || date(install_time + interval '19800 seconds') as cohort, date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist FROM apf_cb2
WHERE customer_user_id<>'' and media_source='googleadwords_int' and app_id ='$app_id' 
GROUP BY customer_user_id, date(install_time + interval '19800 seconds')";
  }
else if($AdNetwork == 'Tapjoy')
  {
    $sql1= "CREATE TEMPORARY TABLE $devices_n_their_cohort AS
    SELECT customer_user_id as deviceid, 'tapjoy_' || date(install_time + interval '19800 seconds') as cohort, date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist FROM apf_cb2
WHERE customer_user_id<>'' and media_source='tapjoy_int' and app_id ='$app_id' 
GROUP BY customer_user_id, date(install_time + interval '19800 seconds')";
  }
else if($AdNetwork == 'Inmobi')
  {
    $sql1="CREATE TEMPORARY TABLE $devices_n_their_cohort AS
    SELECT customer_user_id as deviceid, 'inmobi_' || date(install_time + interval '19800 seconds') as cohort, date(install_time + interval '19800 seconds') as install_date_ist, min(install_time + interval '19800 seconds') as install_time_ist FROM apf_cb2
WHERE customer_user_id<>'' and media_source='inmobi_int' and app_id ='$app_id' 
GROUP BY customer_user_id, date(install_time + interval '19800 seconds')";
  }
else{die("Invalid network passed to the program: $AdNetwork");} 
$result = RedshiftExecute($pgConn, $sql1);
if(!$result) die("Failed_1 !\n" ); else echo "Successfull_1 !\n\n";

//SKIPPING THE COMPUTATIONS BELOW IF COHORT SIZE IS ZERO.
$result = RedshiftExecute($pgConn, "SELECT COUNT(*) as count ,min(install_date_ist) as date_floor_ist FROM $devices_n_their_cohort");
$Rows = pg_fetch_all($result);
$date_floor_ist = "2013-11-15";
foreach($Rows as $Row) {if($Row['count']==0) exit(0);$date_floor_ist=$Row['date_floor_ist'];}
$date_floor_UTC = date("Y-m-d",strtotime($date_floor_ist) - (45000));

// DEVICES LOGIN INFO FROM INSTALL TRACK
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_login_info");
$sql2 = "CREATE TEMPORARY TABLE $devices_login_info AS
SELECT deviceid, cohort, install_date_ist, install_time_ist, (eventtime + interval '45000 seconds') as eventtime_ist, userid
FROM $devices_n_their_cohort NATURAL JOIN (select userid, eventtime, app from install_track where date(eventtime)>='$date_floor_UTC') a
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
RedshiftExecute($pgConn, "DROP TABLE if exists $devices_perf_at_RS");
$sql5 = "CREATE TEMPORARY TABLE $devices_perf_at_RS AS
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

$sql6 = " UPDATE $devices_perf_at_RS
SET sumd1 = (case when sumd1 >0 then 1 else 0 end),
    sumd3 = (case when sumd3 >0 then 1 else 0 end),
    sumd7 = (case when sumd7 >0 then 1 else 0 end),
    sumd14 = (case when sumd14 >0 then 1 else 0 end)";
$result = RedshiftExecute($pgConn, $sql6);
if(!$result) die("Failed_6 !\n" ); else echo "successfull_6 !\n\n";

*/
/*.......................... PURCHASE WORK ..........................................*/
/*
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
select * from $ledgertable where date(eventtime)>='$date_floor_UTC' and source ~ '^[pvrtcsn][0123456789-]' and  changemoney<>0";
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
WHERE date(eventtime) >='$date_floor_UTC' AND source='inapp_purchase' OR source = 'tapjoy'";
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

if($AdNetwork == 'Facebook'){
$sql9_2="Update P2_$table SET campaign= a.fb_campaign_id
FROM (SELECT distinct fb_campaign_id, fb_adset_id FROM apf_cb2 WHERE fb_campaign_id<>'' and fb_adset_id<>'') a
WHERE split_part(P2_$table.cohort,'_',1) = a.fb_adset_id";
$result = RedshiftExecute($pgConn, $sql9_2);
if(!$result) die("Failed_9_2 !\n" ); else echo "Successfull_9_2 !\n\n";
}

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


$sql11 = "UPDATE $devices_perf_at_RS
SET numpurchases = P3_$table.numpurchases, coinpurchased = P3_$table.coinpurchased, tapjoycount=P3_$table.tapjoycount , tapjoychips= P3_$table.tapjoychips
FROM P3_$table
WHERE P3_$table.deviceid= $devices_perf_at_RS.deviceid and P3_$table.cohort = $devices_perf_at_RS.cohort";
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

$sql13 = "UPDATE $devices_perf_at_RS
SET upurchasers = P4_$table.upurchasers
FROM P4_$table
WHERE P4_$table.deviceid= $devices_perf_at_RS.deviceid and P4_$table.cohort = $devices_perf_at_RS.cohort";
$result = RedshiftExecute($pgConn, $sql13);
if(!$result) die("Failed_13 !\n" ); else echo "Successfull_13 !\n\n";

$sql14 ="UPDATE $devices_perf_at_RS
SET  ngames = a.nGames
FROM (select deviceid, cohort, install_date_ist, install_time_ist, sum(nGames) as nGames FROM P1_$table GROUP BY deviceid, cohort, install_date_ist, install_time_ist) a
WHERE $devices_perf_at_RS.deviceid=a.deviceid and $devices_perf_at_RS.cohort = a.cohort and $devices_perf_at_RS.install_date_ist= a.install_date_ist and  $devices_perf_at_RS.install_time_ist = a.install_time_ist;
";
$result = RedshiftExecute($pgConn, $sql14);
if(!$result) die("Failed_14 !\n" ); else echo "Successfull_14 !\n\n";

$myConn = MySqlConnection();
$devices_perf_at_mysql = 'all_cohorts_devices_perf';
$mySql1 = "CREATE TABLE IF NOT EXISTS $devices_perf_at_mysql(
deviceid VARCHAR(30),
install_date_ist DATE,
adnetwork VARCHAR(20),
app VARCHAR(30),
campaign VARCHAR(30),
cohort VARCHAR(40),
jointime_ist DATETIME,
d1_active TINYINT,
d3_active TINYINT,
d7_active TINYINT,
d14_active TINYINT,
nsessions BIGINT,
ngames BIGINT,
upurchasers INTEGER,
numpurchases INTEGER,
coinpurchased BIGINT,
tapjoycount INTEGER,
tapjoychips BIGINT,
PRIMARY KEY(cohort,deviceid,adnetwork,app)
)";
if($myConn->query($mySql1) != TRUE){ echo "Error in creating table $devices_perf_at_mysql  mysql: " . $myConn->error. PHP_EOL; }

$pgsql_query = "SELECT * FROM $devices_perf_at_RS";
$query_result = RedshiftExecute($pgConn, $pgsql_query);
$Rows = pg_fetch_all($query_result);
$cnt = 0;

$temp_file= "/tmp/devices_perf_temp_file.csv";
file_put_contents($temp_file,"");
$fp = fopen($temp_file, 'a');
$str = "";
if($Rows)
  {
    foreach($Rows as $Row)
      {    
	$deviceid = $Row['deviceid'];$install_date_ist=$Row['install_date_ist'];$cohort = $Row['cohort'];$jointime_ist=$Row['jointime_ist'];$d1_active=$Row['sumd1'];$d3_active=$Row['sumd3'];$d7_active=$Row['sumd7'];$d14_active=$Row['sumd14'];$nsessions=$Row['nsessions'];$ngames = $Row['ngames'];$upurchasers=$Row['upurchasers'];$numpurchases = $Row['numpurchases'];$coinpurchased = $Row['coinpurchased']; $tapjoycount= $Row['tapjoycount'];$tapjoychips=$Row['tapjoychips'];
	
	if($AdNetwork === 'Facebook')
	  {
	    $segment = explode('_',$cohort); 
	    $adset = $segment[0];
	    
	    $inner_result = $myConn->query("SELECT Camp_id FROM F_adset WHERE Id ='$adset'");
	    $inner_Row = $inner_result->fetch_array();
	    $campaign = $inner_Row['Camp_id'];	    
	  }
	else $campaign = '';
	$str.= "$deviceid,$install_date_ist,$AdNetwork,$app,$campaign,$cohort,$jointime_ist,$d1_active,$d3_active,$d7_active,$d14_active,$nsessions,$ngames,$upurchasers,$numpurchases,$coinpurchased,$tapjoycount,$tapjoychips\n";
	$cnt = $cnt +1;
	if( $cnt % 10 === 0) { fwrite($fp, $str);$str = "";}      
      }
    fwrite($fp, $str);
    $mysql_query = "LOAD DATA LOCAL INFILE '$temp_file' REPLACE INTO TABLE $devices_perf_at_mysql FIELDS TERMINATED BY ','  LINES TERMINATED BY '\n' (deviceid,install_date_ist,adnetwork,app,campaign,cohort,jointime_ist,d1_active,d3_active,d7_active,d14_active,nsessions,ngames,upurchasers,numpurchases,coinpurchased,tapjoycount,tapjoychips)";
    if ($myConn->query($mysql_query) === TRUE)
      {
	$result = $myConn->query("SELECT count(*) as count from $devices_perf_at_mysql");
	$Row = $result->fetch_array();
	if($Row['count']===$cnt)     echo "Loading to $devices_perf_at_mysql is successfull\n";
	echo "Failed insertions Count: ".($cnt - $Row['count']) .PHP_EOL;
      }
    else echo "Data file loading at mysql failed". $myConn->error. PHP_EOL;
    file_put_contents($temp_file,'');
  }
else "No current retention for the $app is  available!\n";
$query_result = RedshiftExecute($pgConn, "DROP TABLE IF EXISTS $devices_perf_at_RS");

RedshiftCloseConnection($pgConn);
*/
?>
