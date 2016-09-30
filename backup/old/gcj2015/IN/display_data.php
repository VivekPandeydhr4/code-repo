<?php
date_default_timezone_set('Asia/Kolkata');
$date = date('Y-m-d');
$myConn = MySqlConnection();
$start_date='2015-08-01';$end_date='2015-08-31';
$Insights = array();
/***********************************************/
 /* $FB = new Tapjoy();print_r($FB->get_insight($start_date, $end_date)) ;   */
 /* exit(0);  */
/* $Tapjoy = new Tapjoy(); */
/* print_r($Tapjoy->get_campaignsInsight($start_date, $end_date)); */
/* exit(0); */
/* $obj = new FB_creative('6029061365797');  */
/* print_r($obj->get_insight($start_date, $end_date)); */
/* exit(0); */
//$pgConn = RedshiftConnection();
//$result = RedshiftExecute($pgConn,"SELECT * from carromledger_time limit 1");//, purchasetime_ist, changemoney from P2_tambola_temp_table_vik where source = 'inapp_purchase' and cohort like '6028976514997_%' and install_date_ist between '2015-08-01' and '2015-08-30' ORDER BY userid");
//$arr=pg_fetch_all($result);
//var_dump($arr);

 
//exit(0);
/* $obj_adset = new FB_campaign('6029542939797'); */
/* print_r($obj_adset->users_n_their_purchases($start_date, $end_date)); */
/* exit(0); */
/* $FB = new Facebook(); $Google = new Google(); */
/* array_push($Insights, $FB->get_insight($start_date, $end_date)); */
/* array_push($Insights, $Google->get_insight($start_date, $end_date)); */
/* print_r($Insights); */

/**********************************************/
$code = $_REQUEST['code'];
if($code <=28 || $code >=38){
  $start_date =  $_REQUEST['startDate'];
  $end_date = $_REQUEST['endDate'];
}

if($_REQUEST['network'] === 'facebook') $AdNetwork= new Facebook();
else if($_REQUEST['network'] === 'google')  $AdNetwork = new Google();
else if($_REQUEST['network'] === 'tapjoy')  $AdNetwork = new Tapjoy();
else $AdNetwork = FALSE;

switch($code)
  {
  case 1: //All network
    $FB = new Facebook(); $Google = new Google(); $Tapjoy = new Tapjoy(); //$Inmobi = new Inmobi();
    array_push($Insights, $FB->get_insight($start_date, $end_date));
    array_push($Insights, $Google->get_insight($start_date, $end_date));
    array_push($Insights, $Tapjoy->get_insight($start_date, $end_date));
    //array_push($Insights, $Inmobi->get_insight($start_date, $end_date));
    break;
    
  case 2: //network
    array_push($Insights, $AdNetwork->get_insight($start_date, $end_date));
    break;
    
  case 3: //All campaigns
    $FB= new Facebook(); $Google = new Google();
    $fb_Insights = $FB->get_campaignsInsight($start_date, $end_date);
    $google_Insights = $Google->get_campaignsInsight($start_date, $end_date);
    $Insights = array_merge($fb_Insights,$google_Insights);
    break;
    
  case 4: //Network campaigns
    $Insights = $AdNetwork->get_campaignsInsight($start_date, $end_date);
    break;
    
  case 5: // Campaign
    $camp = $AdNetwork->get_campaign($_REQUEST['id']);    
    $Insights = $camp->get_insight($start_date, $end_date);
    break;
    
  case 6: // All Adsets
    $FB= new Facebook(); $Google = new Google();
    $fb_Insights = $FB->get_adsetsInsight($start_date, $end_date);
    $google_Insights = $Google->get_adsetsInsight($start_date, $end_date);
    $Insights = array_merge($fb_Insights,$google_Insights); 
    break;
    
  case 7: //Network adsets
    $Insights = $AdNetwork->get_adsetsInsight($start_date, $end_date);
    break;
    
  case 8:// Campaign adsets
    $camp = $AdNetwork->get_campaign($_REQUEST['id']);
    $Insights = $camp->get_adsetsInsight($start_date, $end_date);
    break;
    
  case 9: //Adset
    $adst = $AdNetwork->get_adset($_REQUEST['id']);
    $Insights = $adst->get_insight($start_date, $end_date);
    break;    
    
  case 10: //All ads
    $FB= new Facebook(); $Google = new Google();
    $fb_Insights = $FB->get_adsInsight($start_date, $end_date);
    $google_Insights = $Google->get_adsInsight($start_date, $end_date);
    $Insights = array_merge($fb_Insights,$google_Insights); 
    break;
    
  case 11: //Network ads
    $Insights = $AdNetwork->get_adsInsight($start_date, $end_date);
    break;   

  case 12: // campaign ads
    $camp = $AdNetwork->get_campaign($_REQUEST['id']);
    $Insights = $camp->get_adsInsight($start_date, $end_date);
    break;   

  case 13: // adset ads 
    $adst = $AdNetwork->get_adset($_REQUEST['id']);
    $Insights = $adst->get_adsInsight($start_date, $end_date);
    break;

  case 14: // ad
    $ad = $AdNetwork->get_ad($_REQUEST['id']);
    $Insights = $ad->get_insight($start_date, $end_date);
    break;

  /* case 15: // all creatives */
  /*   /\*$FB= new Facebook(); $Google = new Google(); */
  /*   $fb_Insights = $FB->get_creativesInsight($start_date, $end_date); */
  /*   $google_Insights = $Google->creativesInsight($start_date, $end_date); */
  /*   $Insights = array_merge($fb_Insights,$google_Insights); */
  /*   *\/ */
  /*   break; */
    
  /* case 16: //Network creatives */
  /*   /\*$Insights = $AdNetwork->get_creativesInsight($start_date, $end_date);*\/ */
  /*   break;     */

  /* case 17: //campaign creatives */
  /*   /\*$camp = $AdNetwork->get_campaign($_REQUEST['id']); */
  /*     $Insights = $camp->get_creativesInsight($start_date, $end_date);*\/ */
  /*   break; */
  
  /* case 18: //adset creatives */
  /*   $adst = $AdNetwork->get_adset($_REQUEST['id']); */
  /*   $Insights = $adst->get_creativesInsight($start_date, $end_date); */
  /*   break; */

  /* case 19: //ad craetives :  Not looking possible because facebook gives insights upto ad level not below that. */
  /*   break; */

  /* case 20:// creative insight */
  /*   /\*$creatv = $AdNetwork->get_creative($_REQUEST['id']); */
  /*     $Insights = $creatv->get_insight($start_date, $end_date);*\/ */
  /*   break; */

  /* case 28://Network placements */
  /*   /\*$Insights = $AdNetwork->get_placementsInsight($start_date, $end_date);*\/ */
  /*   break; */

  /* case 29: //FB cohart report    */
  /*   //$Insights = FB_adsetCohartReport($_REQUEST['id'],$_REQUEST['date']);       */
  /*   break; */

  /* case 31:// overall graph  */
  /*   //$fb_graphInsight = FB_graphInsight(); */
  /*   //$google_graphInsight = Google_graphInsight(); */
  /*   //$Insights = Merge_insights($fb_graphInsight, $google_graphInsight); */
  /*   break; */


    /////////////////////////////////////////////////////////////////////
    //USING OLDER FUNCTION DEFINITION OF PROCEDURAL STYLE 
  case 15: // all creatives
    $fb_Insights = FB_allCreativesInsight($start_date, $end_date);
    $google_Insights = Google_allCreativesInsight($start_date, $end_date);
    $Insights = array_merge($fb_Insights,$google_Insights);
    break;

  case 16: //Network creatives
    if($_REQUEST['network'] === 'facebook')
      $Insights = FB_allCreativesInsight($start_date, $end_date);
    else if($_REQUEST['network'] === 'google')
      $Insights = Google_allCreativesInsight($start_date, $end_date);
    break;    

  case 17: //campaign creatives
    if($_REQUEST['network'] === 'facebook')
      $Insights = FB_campaignCreativesInsight($_REQUEST['id'], $start_date, $end_date);
    else if($_REQUEST['network'] === 'google')
      $Insights = Google_campaignCreativesInsight($_REQUEST['id'], $start_date, $end_date);
    break;
  
  case 18: //adset creatives
    if($_REQUEST['network'] === 'facebook')
      $Insights = FB_adsetCreativesInsight($_REQUEST['id'], $start_date, $end_date);
    else if($_REQUEST['network'] === 'google')
      $Insights = Google_adsetCreativesInsight($_REQUEST['id'], $start_date, $end_date);
    break;

  case 19: //ad craetives :  Not looking possible because facebook gives insights upto ad level not below that.
    break;
  case 20:// creative insight
    if($_REQUEST['network'] === 'facebook')
      $Insights = FB_creativeInsight($_REQUEST['id'], $start_date, $end_date);
    else if($_REQUEST['network'] === 'google')
      $Insights = Google_creativeInsight($_REQUEST['id'], $start_date, $end_date);
    break;

  case 28://Network placements
    if($_REQUEST['network'] === 'facebook')
      $Insights = FB_allPlacementsInsight( $start_date, $end_date);
    else if($_REQUEST['network'] === 'google')
      $Insights = Google_allPlacementsInsight( $start_date, $end_date);
    break;
  case 29: //FB cohart report   
    //$Insights = FB_adsetCohartReport($_REQUEST['id'],$_REQUEST['date']);      
    break;
  case 31:// overall graph 
    //$fb_graphInsight = FB_graphInsight();
    //$google_graphInsight = Google_graphInsight();
    //$Insights = Merge_insights($fb_graphInsight, $google_graphInsight);
    break;

    ///////////////////////////////////////////////////////////////////////////

  case 32:// network graph
    $Insights = $AdNetwork->get_rowGraphData();
    break;

  case 33:// campaign graph
    $camp =  $AdNetwork->get_campaign($_REQUEST['id']);
    $Insights = $camp->get_rowGraphData();
    break;

  case 34:// adset graph
    $adst = $AdNetwork->get_adset($_REQUEST['id']);
    $Insights = $adst->get_rowGraphData();
    break;

  case 35:// ad graph
    $ad = $AdNetwork->get_ad($_REQUEST['id']);
    $Insights = $ad->get_rowGraphData();
    break;
    
  case 36: // creative graph
    /*$creatv = $AdNetwork->get_creative($_REQUEST['id']);
      $Insights = $creatv->get_rowGraphData();*/
    break;

  case 37:
    break;

  case 38://User and their purchases for the given campaign
    $camp = $AdNetwork->get_campaign($_REQUEST['id']);
    $Insights = $camp->users_n_their_purchases($start_date, $end_date);
    break;

  case 39://User and their purchases for the given adset
    $adst = $AdNetwork->get_adset($_REQUEST['id']);
    $Insights = $adst->users_n_their_purchases($start_date, $end_date);
    break;
   default:
    break;
  }

$Insights_string = json_encode($Insights);
print_r($Insights_string);
/**************************************************/
abstract class AdObject
{
  protected $id;
  protected $sql;  
  function Edit($sql){}

  function Graph($sql){}
  function FieldValues($field)
  {
    global $myConn;
    //echo $this->sql;
    $Result = $myConn->query($this->sql);
    if(!$Result) echo $myConn->error.PHP_EOL;
    $output = array();
    while($Row = $Result->fetch_assoc())
      array_push($output,$Row[$field]);
    return $output;
  }
  function Insights()
  {
    global $myConn;
    //echo $this->sql;
    $Result = $myConn->query($this->sql);
    if(!$Result) echo $myConn->error.PHP_EOL;
    $output = array();
    while($Row = $Result->fetch_assoc())
      array_push($output,$Row);
    return $output;
  }
  function Row_graph()
  {
    global $myConn;
    //echo $this->sql;
    $Result = $myConn->query($this->sql);
    if(!$Result) echo $myConn->error.PHP_EOL;
    $output = array();
    while($Row = $Result->fetch_assoc())
      array_push($output,$Row);

    $avge = array('Reach'=>0,'Impressions'=>0,'Frequency'=>0,'Spend'=>0,'Results'=>0,'Clicks'=>0,'CPI'=>0,'CPC'=>0,'CPM'=>0,'CTR'=>0);
    $cnt = count($output);
    foreach($avge as $k=>$value)
      {   
	foreach($output as $data_row)
	  if(array_key_exists($k,$data_row)) $avge[$k]+=$data_row[$k];
	if($cnt>0) $avge[$k] /= $cnt;
      }    
    $graph_data[0]=$avge;$graph_data[1]=$output;
    return $graph_data;
  }
}
class AdNetwork extends AdObject
{

}
class Inmobi extends AdNetwork
{//an app is treated as a campaign
  function __construct()
  {
    $this->id = 'inmobi';
  }
  function Edit()
  {
    //Will do when required
  }
  function get_details()
  {
    return FALSE;
  }
  function get_insight($start_date,$end_date)
  {
    $this->sql = "SELECT 'inmobi' as network, 'network' as type,'0' as Id, 'Inmobi' as Name , 'ACTIVE' as Status , '' as Daily_budget, '' as Bid_type, '' as Objective, '' as Reach, '' as Impressions, '' as Frequency, '' as Spend, '' as Results, '' as Relevance_score, '' as CPI, '' as CPC, '' as CPM, '' as CTR";
    $Insights = parent::Insights();
    $Insights=array_merge($Insights[0], array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));      
    return $Insights;
  }
  function get_campaignsInsight($start_date,$end_date)
  {        
    $Insight = array('Id' =>'TPL','Name'=>'TPL','network'=>'inmobi','type'=>'campaign','Status'=>'ACTIVE','Reach'=>'','Impressions'=>'', 'Frequency'=>'','Spend'=>'','Results'=>'','Relevance_score'=>'','Clicks'=>'','Daily_budget'=>'','Objective'=>'','Bid_type'=>'','CPI'=>'', 'CPC'=>'', 'CPM'=>'', 'CTR'=>'');

    $Insights[0] = array_merge($Insight,Tapjoy::cumulative_retention('tpl',$start_date,$end_date)); $Insights[0]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] = 'TeenPatti';
    $Insights[1] = array_merge($Insight,Tapjoy::cumulative_retention('teenpatti',$start_date,$end_date)); $Insights[1]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] = 'Rummy';
    $Insights[2] = array_merge($Insight,Tapjoy::cumulative_retention('rummy',$start_date,$end_date)); $Insights[2]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] ='Tambola'; 
    $Insights[3] = array_merge($Insight,Tapjoy::cumulative_retention('tambola',$start_date,$end_date)); $Insights[3]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] = 'Carrom';
    $Insights[4] = array_merge($Insight,Tapjoy::cumulative_retention('carrom',$start_date,$end_date)); $Insights[4]['Pvalue']='';   
    return $Insights;
  }
  


  static function cumulative_retention($app,$start_date, $end_date)
  {
    global $myConn;
    $app_name = $app; //Facebook::app_of_given_campaign($campaignId);//cohort_table_4_given_campaign($myConn, $campaignId);
    if($app_name)
      {
	$retention_table = $app_name . "_device_perf_inmobi";
	$sql = "SELECT count(*) as total, sum(a.d1_active) as d1, sum(a.d3_active) as d3,sum(a.d7_active) as d7, sum(a.d14_active) as d14, sum(a.upurchasers) as upurchasers, sum(a.numpurchases) as numpurchases, sum(a.coinpurchased) as coinpurchased, sum(a.tapjoycount) as tapjoycount, sum(a.tapjoychips) as tapjoychips  FROM ( Select * from $retention_table where install_date_ist between '$start_date' and '$end_date') as a";
	//echo $sql.PHP_EOL;      
	$query_result = $myConn->query($sql);
	if($query_result == FALSE)  {echo 'Error in fetching retention data from the $retention_table table. ';}
	$Arr = array();
	if($Row = $query_result->fetch_array())
	  {
	    $Arr['Total'] = $Row['total']; $Arr['D1'] = $Row['d1']; $Arr['D3'] = $Row['d3']; $Arr['D7'] = $Row['d7'];$Arr['D14'] = $Row['d14'];$Arr['Nsessions']='';$Arr['Ngames']='';;$Arr['Upurchasers']=$Row['upurchasers'];$Arr['Numpurchases'] = $Row['numpurchases'];$Arr['Coinpurchased']=$Row['coinpurchased'];$Arr['Tapjoycount']=$Row['tapjoycount'];$Arr['Tapjoychips']=$Row['tapjoychips'];
	    return  $Arr;
	  }
      }
    return array('Total'=>'-1','D1'=>'-1','D3'=>'-1','D7'=>'-1','D14'=>'-1','Nsessions'=>'-1','Ngames'=>'-1','Upurchasers'=>'-1','Numpurchases'=>'-1','Coinpurchased'=>'-1','Tapjoycount'=>'-1','Tapjoychips'=>'-1');
  }

}


class Tapjoy extends AdNetwork
{//an app is treated as a campaign
  function __construct()
  {
    $this->id = 'tapjoy';
  }
  function Edit()
  {
    //Will do when required
  }
  function get_details()
  {
    return FALSE;
  }
  function get_insight($start_date,$end_date)
  {
    $this->sql = "SELECT 'tapjoy' as network, 'network' as type,'0' as Id, 'Tapjoy' as Name , 'ACTIVE' as Status , '' as Daily_budget, '' as Bid_type, '' as Objective, '' as Reach, '' as Impressions, '' as Frequency, '' as Spend, '' as Results, '' as Relevance_score, '' as CPI, '' as CPC, '' as CPM, '' as CTR";
    $Insights = parent::Insights();
    $Insights=array_merge($Insights[0], array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));      
    return $Insights;
  }
  function get_campaignsInsight($start_date,$end_date)
  {        
    $Insight = array('Id' =>'TPL','Name'=>'TPL','network'=>'tapjoy','type'=>'campaign','Status'=>'ACTIVE','Reach'=>'','Impressions'=>'', 'Frequency'=>'','Spend'=>'','Results'=>'','Relevance_score'=>'','Clicks'=>'','Daily_budget'=>'','Objective'=>'','Bid_type'=>'','CPI'=>'', 'CPC'=>'', 'CPM'=>'', 'CTR'=>'');

    $Insights[0] = array_merge($Insight,Tapjoy::cumulative_retention('tpl',$start_date,$end_date)); $Insights[0]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] = 'TeenPatti';
    $Insights[1] = array_merge($Insight,Tapjoy::cumulative_retention('teenpatti',$start_date,$end_date)); $Insights[1]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] = 'Rummy';
    $Insights[2] = array_merge($Insight,Tapjoy::cumulative_retention('rummy',$start_date,$end_date)); $Insights[2]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] ='Tambola'; 
    $Insights[3] = array_merge($Insight,Tapjoy::cumulative_retention('tambola',$start_date,$end_date)); $Insights[3]['Pvalue']='';   
    $Insight['Id']=$Insight['Name'] = 'Carrom';
    $Insights[4] = array_merge($Insight,Tapjoy::cumulative_retention('carrom',$start_date,$end_date)); $Insights[4]['Pvalue']='';   
    return $Insights;
  }
  


  static function cumulative_retention($app,$start_date, $end_date)
  {
    global $myConn;
    $app_name = $app; //Facebook::app_of_given_campaign($campaignId);//cohort_table_4_given_campaign($myConn, $campaignId);
    if($app_name)
      {
	$retention_table = $app_name . "_device_perf_tapjoy";
	$sql = "SELECT count(*) as total, sum(a.d1_active) as d1, sum(a.d3_active) as d3,sum(a.d7_active) as d7, sum(a.d14_active) as d14, sum(a.upurchasers) as upurchasers, sum(a.numpurchases) as numpurchases, sum(a.coinpurchased) as coinpurchased, sum(a.tapjoycount) as tapjoycount, sum(a.tapjoychips) as tapjoychips  FROM ( Select * from $retention_table where install_date_ist between '$start_date' and '$end_date') as a";
	//echo $sql.PHP_EOL;      
	$query_result = $myConn->query($sql);
	if($query_result == FALSE)  {echo 'Error in fetching retention data from the $retention_table table. ';}
	$Arr = array();
	if($Row = $query_result->fetch_array())
	  {
	    $Arr['Total'] = $Row['total']; $Arr['D1'] = $Row['d1']; $Arr['D3'] = $Row['d3']; $Arr['D7'] = $Row['d7'];$Arr['D14'] = $Row['d14'];$Arr['Nsessions']='';$Arr['Ngames']='';;$Arr['Upurchasers']=$Row['upurchasers'];$Arr['Numpurchases'] = $Row['numpurchases'];$Arr['Coinpurchased']=$Row['coinpurchased'];$Arr['Tapjoycount']=$Row['tapjoycount'];$Arr['Tapjoychips']=$Row['tapjoychips'];
	    return  $Arr;
	  }
      }
    return array('Total'=>'-1','D1'=>'-1','D3'=>'-1','D7'=>'-1','D14'=>'-1','Nsessions'=>'-1','Ngames'=>'-1','Upurchasers'=>'-1','Numpurchases'=>'-1','Coinpurchased'=>'-1','Tapjoycount'=>'-1','Tapjoychips'=>'-1');
  }

}

class Facebook extends AdNetwork
{
  function __construct()
  {
    $this->id = 'facebook';
  }
  function Edit()
  {
    //Will do when required
  }
  function get_details()
  {
    return FALSE;
  }

  function get_campaign($campaignId) {$camp= new FB_campaign($campaignId); return $camp;}
  function get_adset($adsetId) {$as = new FB_adset($adsetId); return $as;}
  function get_ad($adId) {$ad = new FB_ad($adId); return $ad;}
  function get_rowGraphData()
  {
    $this->sql = "SELECT OI.Date, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, sum(OI.Clicks) as Clicks, sum(OI.Spend)/sum(OI.Results) as CPI,  sum(OI.Spend)/sum(OI.Clicks) as CPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM F_campaignInsights OI WHERE OI.Date_preset = 'today' GROUP BY OI.date";
    return parent::Row_graph();

  }

  function get_insight($start_date,$end_date)
  {
    //left to do
    $Campaigns_insight = $this->get_campaignsInsight($start_date,$end_date);
    $Insight = array('Id' =>'0','network'=>'facebook','Name'=>'Facebook','type'=>'network','Status'=>'ACTIVE','Reach'=>0,'Impressions'=>0, 'Frequency'=>0,'Spend'=>0,'Results'=>0,'Relevance_score'=>-1,'Clicks'=>0,'Daily_budget'=>'','Objective'=>'','Bid_type'=>'','Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Nsessions'=>'','Ngames'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'');
    
    foreach($Campaigns_insight as $campaign)
      {
	$Insight['Reach'] += $campaign['Reach'];
	$Insight['Impressions'] += $campaign['Impressions'];
	$Insight['Spend'] += $campaign['Spend'];
	$Insight['Results'] += $campaign['Results'];
	$Insight['Clicks'] += $campaign['Clicks'];
      }
    if($Insight['Reach']) $Insight['Frequency'] = $Insight['Impressions']/$Insight['Reach'];
    if($Insight['Results']) $Insight['CPI'] = $Insight['Spend']/$Insight['Results'];      
    if($Insight['Clicks']) $Insight['CPC'] = $Insight['Spend']/$Insight['Clicks'];      
    if($Insight['Impressions']) $Insight['CPM'] = $Insight['Spend']/$Insight['Impressions'];
    if($Insight['Impressions']) $Insight['CTR'] = $Insight['Clicks']/ $Insight['Impressions'];
    return $Insight;
  }
  
  function get_campaignsInsight($start_date,$end_date)
  {
    $this->sql = "SELECT 'facebook' as network, 'campaign' as type,'' as Daily_budget, '' as Bid_type, O.Id, O.Name, O.Status, O.Objective, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, avg(OI.Relevance_score) as Relevance_score, sum(OI.Clicks) as Clicks, sum(OI.Spend)/sum(OI.Results) as CPI, sum(OI.Spend)/sum(OI.Clicks) as CPC,  (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM F_campaign  O, F_campaignInsights OI WHERE O.id =OI.Camp_id and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today' GROUP BY O.Id, O.Name, O.Status, O.Objective";
    $Insights = parent::Insights();
    foreach($Insights as $k=>$insight)	
      {
	$Insights[$k]=array_merge($Insights[$k], Facebook::cumulative_retention_4_a_campaign($insight['Id'],$start_date,$end_date));      
	if($Insights[$k]['Upurchasers']>0) $Insights[$k]['Pvalue'] = ($Insights[$k]['Total'] * $Insights[$k]['CPI'])/$Insights[$k]['Upurchasers'];
	else $Insights[$k]['Pvalue']= -1;
      }
    return $Insights;
  }

  function get_adsetsInsight($start_date, $end_date)
  {
    $this->sql = "SELECT 'facebook' as network, 'adset' as type, '' as Objective, O.Id, O.Name, O.Status, O.Bid_type, O.Daily_budget, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, -1 as Relevance_score, sum(OI.Clicks) as Clicks,sum(OI.Spend)/sum(OI.Results) as CPI, sum(OI.Spend)/sum(OI.Clicks) as CPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM,  sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM F_adset  O, F_adsetInsights OI WHERE O.Id =OI.AdSet_id and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset ='today' GROUP BY O.Id, O.Name, O.Status, O.Bid_type, O.Daily_budget";
    $Insights= parent::Insights();
    foreach($Insights as $k=>$insight)	
      {
	$Insights[$k]=array_merge($Insights[$k], Facebook::cumulative_retention_4_an_adset($insight['Id'],$start_date,$end_date));      
	if($Insights[$k]['Upurchasers']>0) $Insights[$k]['Pvalue'] = ($Insights[$k]['Total'] * $Insights[$k]['CPI'])/$Insights[$k]['Upurchasers'];
	else $Insights[$k]['Pvalue']= -1;
      }
    return $Insights;
  }

  function get_adsInsight($start_date, $end_date)
  {
  
    $this->sql = "SELECT 'facebook' as network, 'ad' as type, '' as Daily_budget, '' as Objective, O.Id, O.Name, O.Status, O.Bid_type, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, avg(OI.Relevance_score) as Relevance_score, sum(OI.Clicks) as Clicks, sum(OI.Spend)/sum(OI.Results) as CPI, sum(OI.Spend)/sum(OI.Clicks) as CPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR  FROM F_ad  O, F_adInsights OI WHERE O.Id = OI.Ad_id  and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today' GROUP BY O.Id, O.Name, O.Status, O.Bid_type";
    $Insights= parent::Insights();
    foreach($Insights as $k=>$insight)  $Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>''));
    return $Insights;
  }

  function get_creativesInsight()
  {
    $Insights= parent::Insights();
    foreach($Insights as $k=>$insight)  $Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>''));
    return $Insights;
  }
  static function cumulative_retention_4_a_campaign($campaignId, $start_date, $end_date)
  {
    global $myConn;
    $app_name = Facebook::app_of_given_campaign($campaignId);//cohort_table_4_given_campaign($myConn, $campaignId);
    if($app_name)
      {
	$retention_table = $app_name . "_device_perf";
	$sql = "SELECT count(*) as total, sum(a.d1_active) as d1, sum(a.d3_active) as d3,sum(a.d7_active) as d7, sum(a.d14_active) as d14, sum(a.nsessions) as nsessions, sum(a.ngames) as ngames,sum(a.upurchasers) as upurchasers, sum(a.numpurchases) as numpurchases, sum(a.coinpurchased) as coinpurchased, sum(a.tapjoycount) as tapjoycount, sum(a.tapjoychips) as tapjoychips  FROM ( Select * from $retention_table where campaign ='$campaignId' and install_date_ist between '$start_date' and '$end_date') as a";
	//echo $sql.PHP_EOL;      
	$query_result = $myConn->query($sql);
	if($query_result == FALSE)  {echo 'Error in fetching retention data from the $retention_table table. ';}
	$Arr = array();
	if($Row = $query_result->fetch_array())
	  {
	    $Arr['Total'] = $Row['total']; $Arr['D1'] = $Row['d1']; $Arr['D3'] = $Row['d3']; $Arr['D7'] = $Row['d7'];$Arr['D14'] = $Row['d14'];$Arr['Nsessions']=$Row['nsessions'];$Arr['Ngames']=$Row['ngames'];$Arr['Upurchasers']=$Row['upurchasers'];$Arr['Numpurchases'] = $Row['numpurchases'];$Arr['Coinpurchased']=$Row['coinpurchased'];$Arr['Tapjoycount']=$Row['tapjoycount'];$Arr['Tapjoychips']=$Row['tapjoychips'];
	    return  $Arr;
	  }
      }
    return array('Total'=>'-1','D1'=>'-1','D3'=>'-1','D7'=>'-1','D14'=>'-1','Nsessions'=>'-1','Ngames'=>'-1','Upurchasers'=>'-1','Numpurchases'=>'-1','Coinpurchased'=>'-1','Tapjoycount'=>'-1','Tapjoychips'=>'-1');
  }

  function app_of_given_campaign($campaignId)
  {
    global $myConn;

    $sql = "SELECT Name FROM F_campaign WHERE F_campaign.id = '$campaignId'";

    $query_result = $myConn->query($sql);
    if($query_result == FALSE)  {echo 'Error in fetching ad insight. '. $myConn->error; return FALSE;}
    $Row = $query_result->fetch_array();
    $campaign_name = strtolower($Row['Name']);

    if(strpos($campaign_name, "carrom") !==FALSE) $app_name ="carrom";
    else if(strpos($campaign_name, "teen") !==FALSE && strpos($campaign_name, "patti") !==FALSE  && strpos($campaign_name, "live")!==FALSE) $app_name = "tpl";//_device_perf";
    else if(strpos($campaign_name, "teen") !==FALSE && strpos($campaign_name, "patti") !==FALSE) $app_name ="teenpatti";
    else if(strpos($campaign_name, "tambola") !==FALSE) $app_name = "tambola";
    else if(strpos($campaign_name, "rummy") !==FALSE) $app_name = "rummy";
    else $app_name = FALSE;
    return $app_name;
  }

  static function cumulative_retention_4_an_adset($adsetid, $start_date, $end_date)
  {
    global $myConn;
    $app_name = Facebook::app_of_given_adset($adsetid);
    if($app_name)
      {
	$retention_table = $app_name . "_device_perf";
	$sql = "SELECT count(*) as total, sum(a.d1_active) as d1, sum(a.d3_active) as d3,sum(a.d7_active) as d7, sum(a.d14_active) as d14,sum(a.nsessions) as nsessions, sum(a.ngames) as ngames,  sum(a.upurchasers) as upurchasers, sum(a.numpurchases) as numpurchases, sum(a.coinpurchased) as coinpurchased, sum(a.tapjoycount) as tapjoycount, sum(a.tapjoychips) as tapjoychips  FROM ( Select * from $retention_table where cohort like '$adsetid"."%' and install_date_ist between '$start_date' and '$end_date') as a";
	//echo $sql.PHP_EOL;      
	$query_result = $myConn->query($sql);
	if($query_result == FALSE)  {echo 'Error in fetching retention data from the $retention_table table. ';}
	$Arr = array();
	if($Row = $query_result->fetch_array())
	  {
	    $Arr['Total'] = $Row['total']; $Arr['D1'] = $Row['d1']; $Arr['D3'] = $Row['d3']; $Arr['D7'] = $Row['d7'];$Arr['D14'] = $Row['d14'];$Arr['Nsessions']=$Row['nsessions'];$Arr['Ngames']=$Row['ngames'];$Arr['Upurchasers']=$Row['upurchasers'];$Arr['Numpurchases'] = $Row['numpurchases'];
	    $Arr['Coinpurchased']=$Row['coinpurchased'];$Arr['Tapjoycount']=$Row['tapjoycount'];$Arr['Tapjoychips']=$Row['tapjoychips'];
	    return  $Arr;
	  }
      }
    return array('Total'=>'-1','D1'=>'-1','D3'=>'-1','D7'=>'-1','D14'=>'-1','Nsessions'=>'-1','Ngames'=>'-1','Upurchasers'=>'-1','Numpurchases'=>'-1','Coinpurchased'=>'-1','Tapjoycount'=>'-1','Tapjoychips'=>'-1');
  }  
  function app_of_given_adset($adsetId)
  {
    global $myConn;   
    $sql = "SELECT F_campaign.Name FROM F_adset , F_campaign WHERE F_adset.camp_id = F_campaign.Id and F_adset.id = '$adsetId'";    
    $query_result = $myConn->query($sql);
    if($query_result == FALSE)  {echo 'Error in fetching campaign name. '. $myConn->error; return FALSE;}  
    $Row = $query_result->fetch_array();
    $campaign_name = strtolower($Row['Name']);
    if(strpos($campaign_name, "carrom") !==FALSE) $app_name ="carrom";
    else if(strpos($campaign_name, "teen") !==FALSE && strpos($campaign_name, "patti") !==FALSE  && strpos($campaign_name, "live")!==FALSE) $app_name = "tpl";//_device_perf";
    else if(strpos($campaign_name, "teen") !==FALSE && strpos($campaign_name, "patti") !==FALSE) $app_name ="teenpatti";
    else if(strpos($campaign_name, "tambola") !==FALSE) $app_name = "tambola";
    else if(strpos($campaign_name, "rummy") !==FALSE) $app_name = "rummy";
    else $app_name = FALSE;

    return $app_name; 
  }
}

class Google extends AdNetwork
{
  function __construct()
  {
    $this->id = 'google';
  }
  function get_details()
  {

  }
  function get_campaign($campaignId) {$camp= new G_campaign($campaignId); return $camp;}
  function get_adset($adsetId) {$as = new G_adset($adsetId); return $as;}
  function get_ad($adId) {$ad = new G_ad($adId); return $ad;}
  function get_rowGraphData()
  {
    $Id = $this->id;
  $this->sql = "SELECT OI.Date, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Cost/1000000) as Spend, sum(OI.Conversions) as Results, sum(OI.Clicks) as Clicks, sum(OI.Cost/1000000)/sum(OI.Conversions) as CPI, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, sum(OI.Cost/1000)/sum(OI.Impressions) as CPM,  sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_campaignReports OI WHERE OI.Date_preset = 'TODAY' and Status = 'ENABLED' GROUP BY OI.Date";
    return parent::Row_graph();
  }


  function get_insight($start_date,$end_date)
  {    
    $Campaigns_insight = $this->get_campaignsInsight($start_date,$end_date);
    $Insight = array('Id' =>'0','network'=>'google','Name'=>'Google','type'=>'network','Status'=>'ENABLED','Reach'=>0,'Impressions'=>0, 'Frequency'=>0,'Spend'=>0,'Results'=>0,'Relevance_score'=>-1,'Clicks'=>0,'Daily_budget'=>'','Objective'=>'','Bid_type'=>'','Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>'');
    
    foreach($Campaigns_insight as $campaign)
      {
	$Insight['Reach'] += $campaign['Reach'];
	$Insight['Impressions'] += $campaign['Impressions'];
	$Insight['Spend'] += $campaign['Spend'];
	$Insight['Results'] += $campaign['Results'];
	$Insight['Clicks'] += $campaign['Clicks'];
      }
    if($Insight['Reach']) $Insight['Frequency'] = $Insight['Impressions']/$Insight['Reach'];
    if($Insight['Results']) $Insight['CPI'] = $Insight['Spend']/$Insight['Results'];      
    if($Insight['Clicks']) $Insight['CPC'] = $Insight['Spend']/$Insight['Clicks'];      
    if($Insight['Impressions']) $Insight['CPM'] = $Insight['Spend']/$Insight['Impressions'];
    if($Insight['Impressions']) $Insight['CTR'] = $Insight['Clicks']/ $Insight['Impressions'];
    return $Insight;    
  }
  function get_campaignsInsight($start_date, $end_date)
  {
    $this->sql = "SELECT 'google' as network, 'campaign' as type, '' as Objective, -1 as Relevance_score, OI.Id, sum(OI.Impressions) as Impressions,  sum(OI.Reach) as Reach,  sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Cost/1000000) as Spend, sum(OI.Clicks) as Clicks, sum(OI.Conversions) as Results, sum(OI.Cost/1000000)/sum(OI.Conversions) as CPI, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, (sum(OI.Cost/1000000)*1000)/sum(OI.Impressions) as CPM,sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_campaignReports OI WHERE OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' GROUP BY OI.Id";
    
    $Insights = parent::Insights();
    foreach($Insights as $k=>$insight) 
      {
	$Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
	$aid = $insight['Id']; 
	$this->sql = "SELECT OI.Name, OI.Status, OI.Bid_type, OI.Daily_budget/1000000 as Daily_budget FROM G_campaignReports OI WHERE OI.Id = '$aid' and OI.Date >= '$start_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' ORDER BY OI.Date DESC LIMIT 1";
	$Id_info = parent::Insights();
	$Insights[$k]=array_merge($Insights[$k],$Id_info[0]);
      }
    return $Insights;        
  }

  function get_adsetsInsight($start_date , $end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT 'google' as network, 'adset' as type, '' as Reach, '' as Frequency, -1 as Relevance_score, OI.Id, sum(OI.Impressions) as Impressions, sum(OI.Cost/1000000) as Spend, sum(OI.Clicks) as Clicks, sum(OI.Conversions) as Results, sum(OI.Cost/1000000)/sum(OI.Conversions) as CPI, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, (sum(OI.Cost/1000000)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_adgroupReports OI WHERE  OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' GROUP BY OI.Id";
    $Insights = parent::Insights();
    foreach($Insights as $k=>$insight) 
      {
	$Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
	$aid = $insight['Id']; 
	$this->sql = "SELECT '' as Daily_budget, '' as Objective, OI.Name, OI.Status, OI.Bid_type FROM G_adgroupReports OI WHERE OI.Id = '$aid'  and  OI.Date >= '$start_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' ORDER BY OI.Date DESC LIMIT 1";
	$Id_info = parent::Insights();
	$Insights[$k]=array_merge($Insights[$k],$Id_info[0]);
      }
    return $Insights;    
  }
  function get_adsInsight($start_date , $end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT 'google' as network, 'ad' as type, '' as Reach, '' as Frequency, -1 as Relevance_score, OI.Id, sum(OI.Impressions) as Impressions, sum(OI.Cost/1000000) as Spend, sum(OI.Clicks) as Clicks, sum(OI.Conversions) as Results, sum(OI.Cost/1000000)/sum(OI.Conversions) as CPI, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, (sum(OI.Cost/1000000)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_adReports OI WHERE  OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' GROUP BY OI.Id";
    $Insights = parent::Insights();
    foreach($Insights as $k=>$insight)
      {
        $Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
        $aid = $insight['Id'];
	$this->sql = "SELECT '' as Daily_budget, '' as Objective, concat($aid,':', OI.Headline) as Name, OI.Status from G_adReports OI WHERE OI.Id = '$aid' and OI.Date >= '$start_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' ORDER BY OI.Date DESC Limit 1";
	$Id_info = parent::Insights();
        $Insights[$k]=array_merge($Insights[$k],$Id_info[0]);       
      }
    return $Insights;
  }

}

class Campaign extends AdObject
{


}
class FB_campaign extends Campaign
{
  function __construct($Id)
  {
    $this->id = $Id;
  }
  function get_adsetsFieldValues($field,array $status=array('ACTIVE'))
  {
    $Id = $this->id;
    $this->sql = "SELECT DISTINCT $field FROM F_adset WHERE Camp_id='$Id' and Status in (".quoted_implode($status).")";
    return parent::FieldValues($field);
  }
  function get_adsFieldValues($field,array $status=array('ACTIVE'))
  {
    $Id = $this->id;
    $this->sql = "SELECT DISTINCT F_ad.$field FROM F_adset,F_ad WHERE F_adset.Id=F_ad.AdSet_id and Camp_id='$Id' and F_ad.Status in (".quoted_implode($status).")";
    return parent::FieldValues($field);
  }

  function get_rowGraphData()
  {
    $Id = $this->id;
    $this->sql = "SELECT Date, Reach, Impressions, Frequency, Spend, Results, Clicks, Spend/Results as CPI,CPC, CPM, CTR  FROM F_campaignInsights WHERE Camp_id= '$Id' and Date_preset = 'today'";
    return parent::Row_graph();
  }
  
  function get_details()
  {
    // Prepare output
    return FALSE;
  }
 

  function get_insight()
  {
    // Prepare output
    return FALSE;
  }
   
  function get_adsetsInsight($start_date,$end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT 'facebook' as network, 'adset' as type, '' as Objective, C.Name as campaign, O.Id, O.Name, O.Status, O.Bid_type, O.Daily_budget, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, -1 as Relevance_score, sum(OI.Clicks) as Clicks,sum(OI.Spend)/sum(OI.Results) as CPI, sum(OI.Spend)/sum(OI.Clicks) as CPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM,  sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM F_campaign C, F_adset  O, F_adsetInsights OI WHERE C.Id = O.Camp_id and O.Id =OI.AdSet_id and C.Id = '$Id' and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset ='today' GROUP BY C.Name , O.Id, O.Name, O.Status, O.Bid_type, O.Daily_budget";
    $Insights= parent::Insights();
    foreach($Insights as $k=>$insight)
      {
	$Insights[$k]=array_merge($Insights[$k], Facebook::cumulative_retention_4_an_adset($insight['Id'],$start_date,$end_date));      
	if($Insights[$k]['Upurchasers']>0) $Insights[$k]['Pvalue'] = ($Insights[$k]['Total'] * $Insights[$k]['CPI'])/$Insights[$k]['Upurchasers'];
	else $Insights[$k]['Pvalue']=-1;
      }
    return $Insights;
  }

  function get_adsInsight($start_date,$end_date)
  {
    $Id = $this->id;

    $this->sql = "SELECT 'facebook' as network, 'ad' as type, '' as Daily_budget, '' as Objective, C.Name as campaign, O.Id, O.Name, O.Status, O.Bid_type, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, avg(OI.Relevance_score) as Relevance_score, sum(OI.Clicks) as Clicks, sum(OI.Spend)/sum(OI.Results) as CPI, sum(OI.Spend)/sum(OI.Clicks) as CPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR  FROM F_campaign C, F_adset A, F_ad  O, F_adInsights OI WHERE C.Id = A.Camp_id and A.Id = O.AdSet_id and O.Id = OI.Ad_id and C.Id = '$Id' and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today' GROUP BY C.Name, O.Id, O.Name, O.Status, O.Bid_type";
    $Insights= parent::Insights();
    foreach($Insights as $k=>$insight)  $Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
    return $Insights;
  }
  function users_n_their_purchases($start_date, $end_date)
  {
    global $myConn ;
    $Id = $this->id;
    $app_name = Facebook::app_of_given_campaign($Id);
    if($app_name)
      {
	$user_purchase_table = 'P2_'.$app_name."_temp_table_vik";
	$sql = "SELECT userid, purchasetime_ist, changemoney from $user_purchase_table where source = 'inapp_purchase' and campaign ='$Id' and install_date_ist between '$start_date' and '$end_date' ORDER BY userid";

	$pgConn = RedshiftConnection();
	$result = RedshiftExecute($pgConn, $sql);
	$RowsArray = pg_fetch_all($result);
	$output = array();
	$index = 0;
	foreach($RowsArray as $Row)
	  {
	    $output[$index] =array();
	    $output[$index]['User'] = $Row['userid'];
	    $output[$index]['Purchase_time'] = $Row['purchasetime_ist'];
	    $output[$index]['Chips'] = $Row['changemoney'];
	    $output[$index]['Value'] = 0;
	    $index = $index +1;
	  }
	return $output;
      }
    return FALSE;
  }

  function get_creativesInsight($start_date,$end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT DISTINCT F_ad.Creative_id FROM F_campaign, F_adset, F_ad WHERE F_campaign.id=F_adset.camp_id and F_adset.Id = F_ad.AdSet_id and F_campaign.Id = '$Id'";
    $creatv_ids=parent::FieldValues('Creative_id');    
    $Insights=array();
    foreach($creatv_ids as $cid)
      {
	echo $cid.PHP_EOL;
	$creatv = new FB_creative($cid);
	if($ret = $creatv->get_insight($start_date,$end_date)) array_push($Insights,$ret);	
      }
    return $Insights;
  }  
}

class G_campaign extends Campaign
{
  function __construct($Id)
  {
    $this->id = $Id;
  }
  function get_adsetsFieldValues($field,array $status=array('ENABLED'))
  {
    $Id = $this->id;
    $this->sql = "SELECT DISTINCT $field FROM G_adgroupReports WHERE campaignId='$Id' and Status in (".quoted_implode($status).")";
    return parent::FieldValues($field);
  }
  function get_adsFieldValues($field,array $status=array('ENABLED'))
  {
    $Id = $this->id;
    $this->sql = "SELECT DISTINCT $field FROM G_adReports WHERE campaignId='$Id' and Status in (".quoted_implode($status).")";
    return parent::FieldValues($field);
  }
 
  function get_rowGraphData()
  {
    $Id = $this->id;
    $this->sql = "SELECT Date, Reach, Impressions, Frequency, (Cost/1000000) as Spend, Conversions as Results, Clicks, (Cost/1000000)/Conversions as CPI, (CPC/1000000) as CPC, (CPM/1000000) as CPM, TRIM(TRAILING '%' FROM CTR) as CTR  FROM G_campaignReports WHERE Id = '$Id' and Date_preset = 'TODAY' and Status = 'ENABLED'";

    return parent::Row_graph();
  }
  function get_insight($start_date , $end_date)
  {
    return FALSE;
  }

  function get_adsetsInsight($start_date , $end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT 'google' as network, 'adset' as type, '' as Reach, '' as Frequency, -1 as Relevance_score, OI.Id, sum(OI.Impressions) as Impressions, sum(OI.Cost/1000000) as Spend, sum(OI.Clicks) as Clicks, sum(OI.Conversions) as Results, sum(OI.Cost/1000000)/sum(OI.Conversions) as CPI, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, (sum(OI.Cost/1000000)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_adgroupReports OI WHERE  OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' and OI.CampaignId = '$Id' GROUP BY OI.Id";
    $Insights = parent::Insights();
    foreach($Insights as $k=>$insight) 
      {
	$Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
	$aid = $insight['Id']; 
	$this->sql = "SELECT '' as Daily_budget, '' as Objective, OI.Name, OI.Status, OI.Bid_type FROM G_adgroupReports OI WHERE OI.Id = '$aid' and OI.CampaignId = '$Id' and  OI.Date >= '$start_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' ORDER BY OI.Date DESC LIMIT 1";
	$Id_info = parent::Insights();
	$Insights[$k]=array_merge($Insights[$k],$Id_info[0]);
      }
    return $Insights;    
  }
  function get_adsInsight($start_date , $end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT 'google' as network, 'ad' as type, '' as Reach, '' as Frequency, -1 as Relevance_score, OI.Id, sum(OI.Impressions) as Impressions, sum(OI.Cost/1000000) as Spend, sum(OI.Clicks) as Clicks, sum(OI.Conversions) as Results, sum(OI.Cost/1000000)/sum(OI.Conversions) as CPI, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, (sum(OI.Cost/1000000)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_adReports OI WHERE  OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' and OI.CampaignId = '$Id' GROUP BY OI.Id";
    $Insights = parent::Insights();
    foreach($Insights as $k=>$insight)
      {
        $Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
        $aid = $insight['Id'];
	$this->sql = "SELECT '' as Daily_budget, '' as Objective, concat($aid,':', OI.Headline) as Name, OI.Status from G_adReports OI WHERE OI.Id = '$aid' and OI.CampaignId = '$Id' and OI.Date >= '$start_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' ORDER BY OI.Date DESC Limit 1";
	$Id_info = parent::Insights();
        $Insights[$k]=array_merge($Insights[$k],$Id_info[0]);       
      }
    return $Insights;
  }
  function users_n_their_purchases($start_date, $end_date)
  {
    return FALSE;
  }
}

class Adset extends AdObject
{

}

class FB_adset extends Adset
{
  function __construct($Id)
  {
    $this->id = $Id;
  }
  function get_adsFieldValues($field,array $status=array('ACTIVE'))
  {
    $Id = $this->id;
    $this->sql = "SELECT DISTINCT F_ad.$field FROM F_ad WHERE AdSet_id='$Id' and F_ad.Status in (".quoted_implode($status).")";
    return parent::FieldValues($field);
  }
  function get_details()
  {
    // Prepare output
    return FALSE;
  }

  function get_insight()
  {
    // Prepare output
    return FALSE;
  }
  function get_rowGraphData()
  {
    $Id = $this->id;
    $this->sql = "SELECT Date, Reach, Impressions, Frequency, Spend, Results,  Clicks,  Spend/Results as CPI,  CPC,  CPM, CTR FROM F_adsetInsights WHERE AdSet_id= '$Id' and Date_preset = 'today'";
    return parent::Row_graph();
  }  
 
  function get_adsInsight($start_date,$end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT 'facebook' as network, 'ad' as type, '' as Daily_budget, '' as Objective, A.Name as adset, O.Id, O.Name, O.Status, O.Bid_type, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, avg(OI.Relevance_score) as Relevance_score, sum(OI.Clicks) as Clicks, sum(OI.Spend)/sum(OI.Results) as CPI, sum(OI.Spend)/sum(OI.Clicks) as CPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR  FROM F_adset A, F_ad  O, F_adInsights OI WHERE A.Id = O.AdSet_id and O.Id = OI.Ad_id and A.Id = '$Id' and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today' GROUP BY A.Name, O.Id, O.Name, O.Status, O.Bid_type";
    $Insights= parent::Insights();
    foreach($Insights as $k=>$insight)  $Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
    return $Insights;
  }
  function get_creativesInsight($start_date,$end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT DISTINCT F_ad.Creative_id FROM  F_adset, F_ad WHERE F_adset.Id = F_ad.AdSet_id and F_adset.Id = '$Id'";
    $creatv_ids=parent::FieldValues('Creative_id');    
    $Insights=array();
    foreach($creatv_ids as $cid)
      {
	//echo $cid.PHP_EOL;
	$creatv = new FB_creative($cid);
	if($ret = $creatv->get_insight($start_date,$end_date)) array_push($Insights,$ret);	
      }
    return $Insights;
  }

 function users_n_their_purchases($start_date, $end_date)
  {
    global $myConn;
    $Id = $this->id;

    $app_name = Facebook::app_of_given_adset($Id);

    if($app_name)
      {
	$user_purchase_table = 'P2_'.$app_name."_temp_table_vik";
	$sql = "SELECT userid, purchasetime_ist, changemoney from $user_purchase_table where source = 'inapp_purchase' and cohort like '$Id"."_%' and install_date_ist between '$start_date' and '$end_date' ORDER BY userid";
	$pgConn = RedshiftConnection();
	$result = RedshiftExecute($pgConn, $sql);
	$RowsArray = pg_fetch_all($result);
	$output = array();
	$index = 0;
	foreach($RowsArray as $Row)
	  {
	    $output[$index] =array();
	    $output[$index]['User'] = $Row['userid'];
	    $output[$index]['Purchase_time'] = $Row['purchasetime_ist'];
	    $output[$index]['Chips'] = $Row['changemoney'];
	    $output[$index]['Value'] = 0;
	    $index = $index +1;
	  }
	return $output;
      }
    return FALSE;
  }

}
class G_adset extends Adset
{
  function __construct($Id)
  {
    $this->id = $Id;
  }
  function get_details()
  {
    // Prepare output
    return FALSE;
  }

  function get_insight()
  {
    // Prepare output
    return FALSE;
  }

  function get_rowGraphData()
  {
    $Id = $this->id;
    $this->sql = "SELECT Date, Impressions, (Cost/1000000) as Spend, Conversions as Results, Clicks,  (Cost/1000000)/Conversions as CPI, (CPC/1000000) as CPC, (CPM/1000000) as CPM, TRIM(TRAILING '%' FROM CTR) as CTR FROM G_adgroupReports WHERE Id = '$Id' and Date_preset = 'TODAY' and Status = 'ENABLED'";
    return parent::Row_graph();
  }
  function get_adsInsight($start_date , $end_date)
  {
    $Id = $this->id;
    $this->sql = "SELECT 'google' as network, 'ad' as type, '' as Reach, '' as Frequency, -1 as Relevance_score, OI.Id, sum(OI.Impressions) as Impressions, sum(OI.Cost/1000000) as Spend, sum(OI.Clicks) as Clicks, sum(OI.Conversions) as Results, sum(OI.Cost/1000000)/sum(OI.Conversions) as CPI, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, (sum(OI.Cost/1000000)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_adReports OI WHERE  OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' and OI.AdGroupId = '$Id' GROUP BY OI.Id";
    $Insights = parent::Insights();
    foreach($Insights as $k=>$insight)
      {
        $Insights[$k]=array_merge($Insights[$k],array('Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'','Pvalue'=>'','Nsessions'=>'','Ngames'=>''));
        $aid = $insight['Id'];
	$this->sql = "SELECT '' as Daily_budget, '' as Objective, concat($aid,':', OI.Headline) as Name, OI.Status from G_adReports OI WHERE OI.Id = '$aid' and OI.AdGroupId = '$Id' and OI.Date >= '$start_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' ORDER BY OI.Date DESC Limit 1";
	$Id_info = parent::Insights();
        $Insights[$k]=array_merge($Insights[$k],$Id_info[0]);       
      }
    return $Insights;
  }
 function users_n_their_purchases($start_date, $end_date)
  {
    return FALSE;
  }  

}

class Ad extends AdObject
{

}

class FB_ad extends Ad
{
  function __construct($Id)
  {
    $this->id = $Id;
  }
  function get_details()
  {
    // Prepare output
    return FALSE;
  }
  function get_insight()
  {
    // Prepare output
    return FALSE;
  }
  function get_rowGraphData()
  {
    $Id = $this->id;
    $this->sql = "SELECT Date, Reach, Impressions, Frequency, Spend, Results,  Clicks,  Spend/Results as CPI,  CPC,  CPM, CTR FROM F_adInsights WHERE Ad_id= '$Id' and Date_preset = 'today'";
    return parent::Row_graph();
  }

}

class G_ad extends Ad
{
  function __construct($Id)
  {
    $this->id = $Id;
  }
  function get_insight()
  {
    // Prepare output
    return FALSE;
  }
  function get_rowGraphData()
  {
    $Id = $this->id;
    $this->sql = "SELECT Date, Impressions, (Cost/1000000) as Spend, Conversions as Results, Clicks,  (Cost/1000000)/Conversions as CPI, (CPC/1000000) as CPC, (CPM/1000000) as CPM, TRIM(TRAILING '%' FROM CTR) as CTR FROM G_adReports WHERE Id = '$Id' and Date_preset = 'TODAY' and Status = 'ENABLED'";
    return parent::Row_graph();
  }
}

class FB_creative extends AdObject
{
  function __construct($Id) {$this->id = $Id;}

  function get_insight($start_date,$end_date) 
 {
   $Id = $this->id;
   $this->sql="SELECT 'facebook' as network, 'creative' as type ,'' as Name, Id , Image_url from F_creatives where Id = '$Id'";
   $temp =  parent::Insights();     
   if($temp)
     {$creatv_info  = $temp[0];
   $this->sql = "SELECT Id FROM F_ad WHERE Creative_id = '$Id'";
   //echo $this->sql.PHP_EOL;
   $creatv_ads=parent::FieldValues('Id'); $count= count($creatv_ads);
   //var_dump($creatv_ads);
   //echo quoted_implode($creatv_ads).PHP_EOL;
   $this->sql = "SELECT -1 as Relevance_score, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Spend) as Spend, sum(OI.Results) as Results, sum(OI.Clicks) as Clicks FROM F_adInsights OI WHERE OI.Ad_id in (".quoted_implode($creatv_ads).") and OI.Date >='$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today'";   
   //echo $this->sql;
   $Insight = parent::Insights();
   //var_dump($Insight);
   if($Insight['Reach']) $Insight['Frequency'] = ($Insight['Impressions']/$Insight['Reach']);
   if($Insight['Results']) $Insight['CPI'] = ($Insight['Spend']/$Insight['Results']);
   if($Insight['Clicks']) $Insight['CPC'] = ($Insight['Spend']/$Insight['Clicks']);
   if($Insight['Impressions']) $Insight['CPM'] = ($Insight['Spend']*1000)/$Insight['Impressions'];
   if($Insight['Impressions']) $Insight['CTR'] = ($Insight['Clicks']/$Insight['Impressions']);
   $Insight = array_merge($creatv_info,$Insight);
   return $Insight;
     }
   else return FALSE;
 }
}


//$obj_fb = new Facebook();  
//print_r($obj_fb->get_rowGraphData());
/* print_r($obj_fb->get_insight('2015-08-01','2015-08-25') );  */
/*print_r($obj_fb->get_adsetsInsight('2015-08-01','2015-08-25') ); */
/* print_r($obj_fb->get_campaignsInsight('2015-08-01','2015-08-25') ); */

//$obj_camp = new G_campaign('286092245'); 
/* print_r($obj_camp->get_adsetsInsight('2015-08-01','2015-08-25')); */
//print_r($obj_camp->get_rowGraphData());
/* $obj_adset = new FB_adset('6028976514997'); */
/* print_r($obj_adset->get_adsInsight('2015-08-01','2015-08-25')); */


/* $obj_camp = new G_campaign('286092245'); */
/* print_r($obj_camp->get_adsInsight('2015-08-01','2015-08-25')); */
//print_r($obj_camp->get_adsetsInsight('2015-08-01','2015-08-25'));

/* $obj_adset = new G_adset('19503771605');  */
/* print_r($obj_adset->get_adsInsight('2015-08-01','2015-08-25'));  */

/* $obj_adset = new G_ad('77734005965'); */
/* print_r($obj_adset->get_rowGraphData()); */

//$obj_g= new Google();
//print_r($obj_g->get_insight('2015-08-01','2015-08-25') );  
//print_r($obj_g->get_adsInsight('2015-08-01','2015-08-25') );  
//print_r($obj_g->get_adsetsInsight('2015-08-01','2015-08-25') ); 
//print_r($obj_g->get_campaignsInsight('2015-08-01','2015-08-25') );
//$Insights = array('Reach'=>0,'Impressions'=>0,'Frequency'=>0,'Spend'=>0,'Results'=>0,'Relevance_score'=>-1,'Clicks'=>0,'CPI'=>0,'CPC'=>0,'CPM'=>0,'CTR'=>0,'Total'=>'','D1'=>'','D3'=>'','D7'=>'','D14'=>'','Upurchasers'=>'','Numpurchases'=>'','Coinpurchased'=>'','Tapjoycount'=>'','Tapjoychips'=>'');
//////////////////////// GLOBAL FUNCTIONS /////////////////////////////


function RedshiftConnection()
{
  $pgconn;

  if (! isset($pgconn))
    {
      $pgconn = pg_connect('host=tp-cluster1.cnykqqtxhbhz.us-east-1.redshift.amazonaws.com port=5439 dbname=tpledger user=vikas password=vIkas.pandey123') or die('Could not connect: ' . pg_last_error());
    }
  //echo "Connected Successfully\n";
  return $pgconn;
}
function RedshiftExecute($pgConn, $sql)
{  
  $result = pg_query($pgConn, $sql);
  if(!$result) {echo 'error'.pg_last_error($pgConn);return FALSE;}
  else return $result;
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
  return $conn; 
}
function quoted_implode($arr)
{
  $str = '';
  foreach($arr as $value) $str .= "'".$value."',";
  $str = rtrim($str,",");
  return $str;
}
function prepare_2D_output_from_mysql_result($result)
{ 
  $output = array(); 
  while($Row = $result->fetch_assoc())
    array_push($output,$Row);
  return $output;
}

////////////////////////////


/*********************  FOR INSIGHTS TO BE CALCULATED USING STORED INSIGHTS IN THE DATABASE **************/
function Google_creativeInsight($creativeId, $start_date, $end_date)
{
  $output = array();
  /*

   */
  return $output;
}
function FB_creativeInsight($creativeId, $start_date, $end_date)
{
  global $date;
  // MySql connection to the database 'ads';
  $servername = "localhost";
  $username = "ads";
  $password = "ads";
  $db = "ads";
  $conn = new mysqli($servername, $username, $password, $db);
  if ($conn->connect_error)  {$conn->error;return FALSE;}
  if(!($result = $conn->query("SELECT Image_url from F_creatives where id = '$creativeId'"))) {echo $conn->error;return FALSE;}
  $row = $result->fetch_array();
  //echo $row['name'].PHP_EOL; return FALSE;
  $output = array();
  $output['Name'] = '';
  $output['Image_url'] = $row['Image_url'];
  $output['network'] = 'facebook';
  $output['type'] = 'creative';
  $output['Id'] = $creativeId;
  $output['Date'] ='';
  $output['Status'] = '';
  $output['Start_date'] = '';
  $output['End_date'] = '';
  $output['Buying_type'] = '';
  $output['Objective'] = '';
  $output['Bid_type'] = '';
  $output['Daily_budget'] = '';
  $output['Lifetime_budget'] = '';

  $output['Reach'] = 0;
  $output['Impressions'] = 0;
  $output['Spend'] = 0;
  $output['Results'] = 0;
  $output['Clicks'] = 0;
  $output['uClicks'] = 0;
  $output['Social_reach'] = 0;
  $output['Social_impressions'] = 0;
  $output['Social_clicks'] = 0; 
  $output['uSocial_clicks'] = 0;
  $output['Total_actions'] = 0;
  $output['uTotal_actions'] = 0;

  $output['Frequency'] = 0;
  $output['Relevance_score'] = 0;
  $output['CPI'] = 0;
  $output['CPC'] = 0;
  $output['uCPC'] = 0;
  $output['CPM'] = 0;
  $output['CPP'] = 0;
  $output['CTR'] = 0;
  $output['uCTR'] = 0;
  $creative_Ads_sql = "SELECT Id FROM F_ad WHERE Creative_id = '$creativeId'";

  $query1_result = $conn->query($creative_Ads_sql);
  if($query1_result == FALSE)  {echo $conn->error;return FALSE;}
  $Count = 0;
  while($Row1 = $query1_result->fetch_array())
    {
      $Ad_ID = $Row1['Id'];
      //$Ad_ID = '6029061217597';
      //$sql = "SELECT OI.Reach, OI.Impressions, OI.Frequency, OI.Spend, OI.Results, OI.Relevance_score, OI.Clicks, OI.uClicks, OI.CPC, OI.uCPC, OI.CPM, OI.CPP, OI.CTR,OI.uCTR, OI.Social_reach, OI.Social_impressions,OI.Social_clicks, OI.uSocial_clicks, OI.Total_actions, OI.uTotal_actions FROM F_adInsights OI WHERE OI.Ad_id = '$Ad_ID' and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today'";

      $sql = "SELECT OI.Ad_ID, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, avg(OI.Relevance_score) as Relevance_score, sum(OI.Clicks) as Clicks, sum(OI.uClicks) as uClicks, sum(OI.Spend)/sum(OI.Clicks) as CPC, sum(OI.Spend)/sum(OI.uClicks) as uCPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM, (sum(OI.Spend)*1000)/sum(OI.Reach) as CPP,  sum(OI.Clicks)/sum(OI.Impressions) as CTR,  sum(OI.Clicks)/sum(OI.Reach)  as uCTR, sum(OI.Social_reach) as Social_reach, sum(OI.Social_impressions) as Social_impressions, sum(OI.Social_clicks) as Social_clicks, sum(OI.uSocial_clicks) as uSocial_clicks, sum(OI.Total_actions) as Total_actions, sum(OI.uTotal_actions) as uTotal_actions FROM F_adInsights OI WHERE OI.Ad_id = '$Ad_ID' and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today' GROUP BY OI.Ad_ID";


      //echo $Ad_ID." : ". $sql. PHP_EOL; 
      $query2_result = $conn->query($sql);
      if($query2_result == FALSE)  {echo "Creative($creativeId) insight failed to include data of the Ad: $Ad_ID .". $conn->error;return FALSE;}
      $Row2 = $query2_result->fetch_array();
      if($Row2== NULL) continue;
      //var_dump($Row2);exit(0);
      $output['Reach'] += $Row2['Reach'];
      $output['Impressions'] += $Row2['Impressions'];
      $output['Spend'] += $Row2['Spend'];
      $output['Results'] += $Row2['Results'];
      $output['Clicks'] += $Row2['Clicks'];
      $output['uClicks'] += $Row2['uClicks'];
      $output['Social_reach'] += $Row2['Social_reach'];
      $output['Social_impressions'] += $Row2['Social_impressions'];
      $output['Social_clicks'] += $Row2['Social_clicks'];
      $output['uSocial_clicks'] += $Row2['uSocial_clicks'];
      $output['Total_actions'] += $Row2['Total_actions'];
      $output['uTotal_actions'] += $Row2['uTotal_actions'];
      $output['Relevance_score'] += $Row2['Relevance_score'];
      $Count = $Count + 1;
    }
  if($output['Reach']) $output['Frequency'] = ($output['Impressions']/$output['Reach']);
  if($Count) $output['Relevance_score'] = ($output['Relevance_score']/$Count);
  if($output['Results']) $output['CPI'] = ($output['Spend']/$output['Results']);
  if($output['Clicks']) $output['CPC'] = ($output['Spend']/$output['Clicks']);
  if($output['uClicks']) $output['uCPC'] = ($output['Spend']/$output['uClicks']);
  if($output['Impressions']) $output['CPM'] = ($output['Spend']/$output['Impressions']);
  if($output['Reach']) $output['CPP'] = (($output['Spend']*1000)/$output['Reach']);
  if($output['Impressions']) $output['CTR'] = ($output['Clicks']/$output['Impressions']);
  if($output['Reach']) $output['uCTR'] =  ($output['Clicks']/$output['Reach']);

  $output['Total'] = '';
  $output['D1'] ='';
  $output['D3'] = '';
  $output['D7'] = '';
  $output['D14'] = '';
  $output['Upurchasers']='';
  $output['Numpurchases'] = '';
  $output['Coinpurchased'] = '';
  $output['Tapjoycount'] = '';
  $output['Tapjoychips'] = '';
  mysqli_close($conn);
  return $output;
}  

function Google_adsetCreativesInsight($adsetId, $start_date, $end_date)
{
  $output = array();
  /*
    PREPARE output
  */
  return $output;
}

function FB_adsetCreativesInsight($adsetId, $start_date, $end_date)
{
  global $date;
  // MySql connection to the database 'ads';
  $servername = "localhost";
  $username = "ads";
  $password = "ads";
  $db = "ads";
  $conn = new mysqli($servername, $username, $password, $db);
  if ($conn->connect_error)  {$conn->error;return FALSE;}

  $all_creative_sql = "SELECT DISTINCT F_ad.Creative_id FROM F_adset, F_ad, F_adInsights WHERE F_adset.Id = F_ad.AdSet_id and F_ad.Id = F_adInsights.Ad_id and F_adset.Id = '$adsetId' and F_adInsights.Date >= '$start_date' and F_adInsights.Date <= '$end_date' and F_adInsights.date_preset = 'today'";//F_ad where status = 'ACTIVE'";
  $query_result = $conn->query($all_creative_sql);
  if($query_result == FALSE)  {echo $conn->error;return FALSE;}

  $output = array();
  while($Row = $query_result->fetch_array())
    {
      $creativeId = $Row['Creative_id'];
      if($ret = FB_creativeInsight($creativeId, $start_date, $end_date))
        array_push($output, $ret);
    }
  mysqli_close($conn);
  return $output;  

}
function Google_campaignCreativesInsight($campaignId, $start_date, $end_date)
{
  $output = array();
  /*
    PREPARE output
  */
  return $output;

}

function FB_campaignCreativesInsight($campaignId, $start_date, $end_date)
{
  global $date;
  // MySql connection to the database 'ads';
  $servername = "localhost";
  $username = "ads";
  $password = "ads";
  $db = "ads";
  $conn = new mysqli($servername, $username, $password, $db);
  if ($conn->connect_error)  {$conn->error;return FALSE;}

  $all_creative_sql = "SELECT DISTINCT F_ad.Creative_id FROM F_campaign, F_adset, F_ad, F_adInsights WHERE F_campaign.Id = F_adset.Camp_id and F_adset.Id = F_ad.AdSet_id and F_ad.Id = F_adInsights.Ad_id and F_campaign.Id = '$campaignId' and F_adInsights.Date >= '$start_date' and F_adInsights.Date <= '$end_date' and F_adInsights.date_preset = 'today'";//F_ad where status = 'ACTIVE'";
  $query_result = $conn->query($all_creative_sql);
  if($query_result == FALSE)  {echo $conn->error;return FALSE;}
  
  $output = array();
  while($Row = $query_result->fetch_array())
    {
      $creativeId = $Row['Creative_id'];
      if($ret = FB_creativeInsight($creativeId, $start_date, $end_date))
	array_push($output, $ret);
    }
  mysqli_close($conn);
  return $output;
}

function Google_allCreativesInsight($start_date, $end_date)
{
  $output = array();
  /*
    PREPARE output
  */
  return $output;
}
function FB_allCreativesInsight($start_date, $end_date)
{ 
  global $date;
  // MySql connection to the database 'ads';
  $servername = "localhost";
  $username = "ads";
  $password = "ads";
  $db = "ads";
  $conn = new mysqli($servername, $username, $password, $db);
  if ($conn->connect_error)  {$conn->error;return FALSE;}

  $all_creative_sql = "SELECT DISTINCT Creative_id from F_ad, F_adInsights WHERE F_ad.Id = F_adInsights.Ad_id and F_adInsights.Date >= '$start_date' and F_adInsights.Date <= '$end_date' and F_adInsights.date_preset = 'today'";//F_ad where status = 'ACTIVE'";
  $query_result = $conn->query($all_creative_sql);
  if($query_result == FALSE)  {echo $conn->error;return FALSE;}

  $output = array();
  while($Row = $query_result->fetch_array())
    {
      $creativeId = $Row['Creative_id'];
      //$creativeId = '6029061216397';
      if($ret = FB_creativeInsight($creativeId, $start_date, $end_date))
	array_push($output, $ret);
    }
  mysqli_close($conn);
  return $output;
}



/*********************  FOR INSIGHTS EXPLICITLY STORED IN A DATABASE TABLE **************/

function Google_allPlacementsInsight($start_date, $end_date)
{
  global $date;
  // MySql connection to the database 'ads';
  $servername = "localhost";
  $username = "ads";
  $password = "ads";
  $db = "ads";
  $conn = new mysqli($servername, $username, $password, $db);
  if ($conn->connect_error)  {$conn->error;return FALSE;}

  //$sql = "SELECT O.Id, O.Name,O.Status, O.Bid_type, OI.Date, OI.Reach, OI.Impressions, OI.Frequency, OI.Spend, OI.Results, OI.Relevance_score, OI.Clicks, OI.uClicks, OI.CPC, OI.uCPC, OI.CPM, OI.CPP, OI.CTR,OI.uCTR, OI.Social_reach, OI.Social_impressions,OI.Social_clicks, OI.uSocial_clicks, OI.Total_actions, OI.uTotal_actions FROM F_ad  O, F_adInsights OI WHERE O.Id = OI.Ad_id and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today'";

  //$sql = "SELECT O.Id, O.Name,O.Status, O.Bid_type, sum(OI.Reach) as Reach, sum(OI.Impressions) as Impressions, sum(OI.Impressions)/sum(OI.Reach) as Frequency, sum(OI.Spend) as Spend, sum(OI.Results) as Results, avg(OI.Relevance_score) as Relevance_score, sum(OI.Clicks) as Clicks, sum(OI.uClicks) as uClicks, sum(OI.Spend)/sum(OI.Clicks) as CPC, sum(OI.Spend)/sum(OI.uClicks) as uCPC, (sum(OI.Spend)*1000)/sum(OI.Impressions) as CPM, (sum(OI.Spend)*1000)/sum(OI.Reach) as CPP,  sum(OI.Clicks)/sum(OI.Impressions) as CTR,  sum(OI.Clicks)/sum(OI.Reach)  as uCTR, sum(OI.Social_reach) as Social_reach, sum(OI.Social_impressions) as Social_impressions, sum(OI.Social_clicks) as Social_clicks, sum(OI.uSocial_clicks) as uSocial_clicks, sum(OI.Total_actions) as Total_actions, sum(OI.uTotal_actions)  as uTotal_actions FROM F_ad  O, F_adInsights OI WHERE O.Id = OI.Ad_id and OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'today' GROUP BY O.Id, O.Name,O.Status, O.Bid_type";

  $sql = "SELECT OI.Id, sum(OI.Impressions) as Impressions, sum(OI.Cost/1000000) as Spend, sum(OI.Clicks) as Clicks, sum(OI.Conversions) as Results, sum(OI.Cost/1000000)/sum(OI.Clicks) as CPC, (sum(OI.Cost/1000000)*1000)/sum(OI.Impressions) as CPM, sum(OI.Clicks)/sum(OI.Impressions) as CTR FROM G_placementReports OI WHERE  OI.Date >= '$start_date' and OI.Date <= '$end_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' GROUP BY OI.Id";
  
  $query_result = $conn->query($sql);
  if($query_result == FALSE)  {echo $conn->error;return FALSE;}

  $index = 0;
  $output = array();
  while($Row = $query_result->fetch_array())   
    {
      $output[$index] = array();
      $output[$index]['network'] = 'google';
      $output[$index]['type'] = 'placement';
      $output[$index]['Date'] = '';
      $output[$index]['Id'] = $aid = $Row['Id'];
      $inner_sql = "SELECT OI.DisplayName, OI.Status, OI.Bid_type, OI.Date from G_placementReports OI WHERE OI.Id = '$aid' and OI.Date >= '$start_date' and OI.Date_preset = 'TODAY' and OI.Status = 'ENABLED' ORDER BY OI.Date DESC LIMIT 1";
      //echo $inner_sql.PHP_EOL;
      $inner_query_result = $conn->query($inner_sql);
      if($inner_query_result == FALSE)  {echo $conn->error;return FALSE;}
      if($inner_row = $inner_query_result->fetch_array())
        {
          $output[$index]['Name'] = $aid .': '. $inner_row['DisplayName'];
          $output[$index]['Status'] = $inner_row['Status'];
          $output[$index]['Bid_type'] = $inner_row['Bid_type'];
          $output[$index]['Daily_budget'] = '';
          $output[$index]['Objective'] ='';
        }
      $output[$index]['Reach'] = '';
      $output[$index]['Impressions'] = $Row['Impressions'];
      $output[$index]['Frequency'] = '';
      $output[$index]['Spend'] = ($Row['Spend']);
      $output[$index]['Results'] = $Row['Results'];
      $output[$index]['Relevance_score'] = -1;
      $output[$index]['Clicks'] = $Row['Clicks'];
      if($Row['Results'])$output[$index]['CPI'] = $Row['Spend']/$Row['Results'];else $output[$index]['CPI'] =0.0;
      $output[$index]['CPC'] = $Row['CPC'];
      $output[$index]['CPM'] = $Row['CPM'];
      $output[$index]['CTR'] = $Row['CTR'];

      $output[$index]['Total'] = '';
      $output[$index]['D1'] ='';
      $output[$index]['D3'] = '';
      $output[$index]['D7'] = '';
      $output[$index]['D14'] = '';
      $output[$index]['Upurchasers']='';
      $output[$index]['Numpurchases'] = '';
      $output[$index]['Coinpurchased'] = '';
      $output[$index]['Tapjoycount'] = '';
      $output[$index]['Tapjoychips'] = '';
      $index = $index + 1;   
    }
  mysqli_close($conn);  
  return $output;
}
function FB_allPlacementsInsight($start_date, $end_date)
{
 $output = array();
  /*
    PREPARE output
  */
  return $output;
}

?>