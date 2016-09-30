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
/*******************************************************************/
$app = $argv[1];
$AdNetwork = $argv[2];
$devices_n_their_cohort = $AdNetwork."_$app"."_devices_n_their_cohort_vik";
$devices_login_info = $AdNetwork."_$app"."_devices_login_info_vik";
$table = $AdNetwork."_$app"."_temp_table_vik";
$devices_perf_at_RS = $AdNetwork."_$app"."_devices_perf_vik";
/*******************************************************************************/
$app_id ='';
$ledgertable ='';
if($app === 'TeenPatti')  {$app_id = "com.octro.teenpatti"; $ledgertable = 'tpledger_timeuser2';}
else if($app === 'TPL')  {$app_id = "com.octro.teenpattilive";$ledgertable = 'tpledger_timeuser2';}
else if($app === 'Rummy')  {$app_id = "com.octro.rummy"; $ledgertable = 'rmledger_time';}
else if($app === 'Tambola')  {$app_id = "com.octro.tambola";$ledgertable = 'tamledger_time';}
else if($app === 'Carrom')  {$app_id = "com.octro.carromlive";$ledgertable = 'carromledger_time';}
/********************************************************************************************************/
$pgConn = RedshiftConnection();

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

?>