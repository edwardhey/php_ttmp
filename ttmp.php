<?php
echo ttmp_hash("妹"),"\n";


$dicts = array("你妹|妹","半月|月","fuck|k");

$hash = array();
foreach($dicts as $dict){
	$tmp = explode("|",$dict);
	if(!isset($hash[$tmp[1]])){
		$hash[$tmp[1]] = array();
	};
	$hash[$tmp[1]][ttmp_hash($tmp[0])] = $tmp[0];
}

var_dump($hash);
echo ttmp_check("株洲网讯 11月21日，荷塘公安分局桂花路派出所接到家住天元区的胡某报案，称其妻子刘英(化名)在桂花路段失踪已有2天。12月14日，记者从荷塘区公安分局获悉，该案系一起抢劫杀人烹尸案，现已被侦破，两名犯罪嫌疑人都已被刑事拘留。 离奇失踪后，亲友收到了神秘短信 刘英失踪那天，是11月19日。当日下午4时许，其丈夫胡某曾多次拨打妻子手机，却始终未能联系上。当晚8时许，刘英的姐夫收到一条神秘短信：“我有事，出去一会，很快回来写给姐姐。” “这个号码半年前，就已转给刘英的姐夫使用。”刘英知道这一情况，为何还特意注明写给姐姐？ 更令人疑惑的是，当晚刘英的车仍然停靠在桂花路上，而按照胡某的说法，“再重要的事，妻子也会先把车开回家。”综合刘英种种反常行为，警方判断这并不是一起单纯的人口失踪案件。 侦查民警调取刘英失踪当天的活动轨迹,发现她最终失踪于新华西路,最后联系人就是牌友李某。通过缜密侦查，民警发现李某有重大作案嫌疑。12月7日下午，荷塘区公安分局刑侦大队民警在麻园将李某抓获。另一名犯罪嫌疑人刘某也于当日被抓获。 肢解后，被害人尸体遭对方烹煮3天3夜 刘英和李某常在一起打麻将。事发之日下午，刘英和往常一样来到了桂花路附近的麻将馆，麻将打到一半时，李某以“卖二手房很赚钱”为由，极力劝说刘英购买位于荷塘区茨中村另一名犯罪嫌疑人刘某的一套二手房。 刘英答应跟李某先去看看房子，然而，到达刘某家中。李某与刘某马上对刘英实施了抢劫，连同黄金饰品和现金在内，非法获利案值不足两万。得手后，李某与刘某，竟用刀和锤子残忍地将刘英杀害并肢解。为躲避警方追查，两人在将尸块烹煮3天3夜后，才分批次抛尸荒野。 “抛尸的地点都很远，最远的甚至在湘潭。”荷塘分局刑侦大队队长田颖说。据悉，犯罪嫌疑人李某，1994年因盗窃罪被判有期徒刑15年，另一名犯罪嫌疑人刘某则有吸毒史，两人均为无业人员。李某与刘某为此次成功作案，已谋划半月之久。",$hash),"\n";
//echo ttmp_check("你妹",$hash),"\n";