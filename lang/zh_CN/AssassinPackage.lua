-- translation for AssassinPackage

return {    
	["Assassin"] = "刺客列传", 
	["guoxiu"]="郭修",	
	["pofuchenzhou"]="破釜",
	[":pofuchenzhou"]="锁定技，你使用黑色的【杀】造成的伤害+1。出牌阶段，若你造成一次伤害，你获得一个破釜标记\
回合结束时，若你没有破釜标记，你流失1点体力。",
	["#pofuBuf"]="%from 的锁定技【破釜】被触发，%arg 的伤害增加了1点",
	["#chenzhouLoseHP"]="%from 的锁定技【沉舟】被触发，回合结束时将流失1点体力",	
	["@pofu"]="破釜",
	["wufu"]="伍孚",
	["bujing"]="不惊",
	[":bujing"]="锁定技，你不能成为【乐不思蜀】和【兵粮寸断】的目标。",	
	["qingkai"]="轻铠",
	[":qingkai"]="锁定技，每次你受到伤害时，当伤害不小于1点时，该伤害始终-1",
	["#qingkai"]="%from 的锁定技【轻铠】，他受到的伤害从%arg 降低至%arg2 点",
	["bishou"]="匕首",
	[":bishou"]="当你使用【杀】指定一名角色为目标后，你可以进行判定，若结果为黑桃，此【杀】不可被闪避",	
	["jiping"] = "吉平",
	["dusha"]="毒杀",
	[":dusha"]="在你的回合外，有人使用【桃】时，你可进行一次判定，\
若结果为梅花，桃的效果无效\
若结果为黑桃，桃的效果无效并且该角色流失1点体力\
★额外的，你不能在有角色濒死求桃时发动毒杀",
	["#dushafailed"]="%from 试着像皇后一样在桃子上做手脚，结果失败了",
	["#dushaclub"]="%from给了%arg一个毒桃子，这个桃子不能回复体力",
	["#dushaspade"]="%from给了%arg一个剧毒的桃子，这个桃子吃了会掉血",
	["cuidu"]="淬毒",
	[":cuidu"]="锁定技，你使用的【火杀】造成的伤害+1",
	["#cuidu"] = "%from 的【淬毒】技能被触发，火系伤害从 %arg 点上升至 %arg2 点",
	["hanlong"]="韩龙",
	["yuanxing"]="远行",
	[":yuanxing"]="锁定技，你在计算与其它角色的距离或其它角色计算与你的距离时，始终+1",	
	["liwei"]="立威",
	[":liwei"]="你每受到1次南蛮入侵或万箭齐发造成的伤害，可弃一张牌进行一次判定\
若结果为梅花，你回复1点体力并摸两张牌。\
若结果为黑桃，伤害你的角色受到2点伤害或弃置3张手牌",
	["chizhizhe"]="持质者",
	["youguai"]="诱拐",
	[":youguai"]="一名角色每受到【杀】造成的一次伤害，你可以弃一张手牌，并令其进行一次判定。判定结果为：\
♥~该角色回复1点体力，你和该角色各摸1张牌\
♦~该角色摸2张牌,伤害来源弃1张手牌\
♣~伤害来源必须弃2张手牌，否则将其武将牌翻面\
♠~伤害来源受到该角色的1点伤害并将其武将牌翻面",
	["#youguaiheart"]="%from 给了%to 一根棒棒糖，%to 蹦蹦跳跳地跟 %from 进了山",
	["#youguaidiamond"]="%to 舔了舔%from的棒棒糖，满心幽怨地说：%from 你一定要等我哦~",
	["#youguaiclub"]="%to 心爱的两张牌被%from 拐走了",
	["#youguaiclubnodiscard"]="%to 禁不住%from 的诱惑，跟他进了山",
	["#youguaispade"]="%to 心甘情愿地被情敌%arg 爆了一天一夜的菊花，义无反顾地跟%from 进了山",
	["bangpiao"]="绑票",
	[":bangpiao"]="出牌阶段，你可以弃置所有手牌，指定任意一名角色武将牌翻面\
额外的，若出牌阶段开始时你没有手牌，或场上仅有两名存活角色的情况下，你不能发动【绑票】",
	["#bangpiao"]="%arg被%from给绑票了",	
	["sipiao"]="撕票",
	[":sipiao"]="出牌阶段，你可以指定一个已经翻面的角色与你拼点，若你赢，该角色受到2点伤害，每回合限用一次",
	["#sipiao"]="%from将新鲜的肉票%arg给剁了",
	["liuye"]="刘晔",	
	["shaqie"]="杀妾",
	[":shaqie"]="锁定技，你对女性角色使用【杀】时，对方需连续使用两张【闪】才能抵消",
	["#shaqie"]="%from 的锁定技【杀妾】生效，%arg 必需连续使用两张【闪】才能抵消",
	["shengyan"]="盛宴",
	[":shengyan"]="回合外，若有人使用锦囊且指定了不止一个目标，你是其中之一时，你可以弃一张手牌并进行一次判定，若结果不为红桃，则你对其造成1点伤害，并跳过对你的结算。",
	["#ShengyanAvoid"] = "%from 发动了技能【盛宴】，跳过了锦囊 %arg 对他的结算", 
	["#ShengyanFailed"] = "%from 自己喝开了闷酒", 
	["@shaqie-jink-1"] = "对方拥有【杀妾】技能，您必须出两张【闪】来闪避", 
	["@shaqie-jink-2"] = "对方拥有【杀妾】技能，您还需要出一张【闪】来闪避",
	["wuhuan"] = "无欢",
	[":wuhuan"] = "锁定技，你的【酒】始终视为【闪】",
	["yinfan"]="隐蕃",
	["tiaobo"]="挑拨",
	[":tiaobo"]="出牌阶段，你可以弃一张牌并选择两名角色。视为你选择的两名角色互相使用了一张【杀】。\
额外的，此【杀】不受空城限制。每回合中，你最多能使用一次挑拨",
	["tiaobocard"]="杀意",
	["lianzuo"]="连坐",
	[":lianzuo"]="锁定技，你每受一次伤害，可进行一次判定，\
除非结果为黑桃，否则你可指定另一名角色与你承受同样点数与属性的伤害\
★额外的，你不能指定伤害来源为连坐的目标",
	["#lianzuo"]="%from 与%arg2 被%arg 【连坐】了",
	["weike"]="魏客",
	["taolue"]="韬略",
	[":taolue"]="你每受到一次伤害，可摸一张牌并进行一次判定：若结果不为梅花，则目标来源必须进行二选一：弃两张手牌或流失1点体力\
★流失体力意味着反馈刚烈等受伤害而触发的技能将不能发动",	
	["#taolue"]="无知的%arg 搬着小板凳听 %from 讲了半天文韬武略，开始产生了幻觉",
	["quanjiu"]="劝酒",	
	[":quanjiu"]="锁定技，你的黑桃手牌始终视为【酒】。",	
	["fanjiangzhangda"]="范疆张达",
	["fankang"]="反抗",
	[":fankang"] = "每当【杀】或【决斗】对你造成了伤害时，你可以弃一张牌，然后进行一次判定\
若结果的点数为1、7、4换言之就是【一起死】，你对伤害来源造成X点伤害，X为你此次受到的伤害点数+1\
若结果的点数为2、5、8换言之就是【爱我吧】，你摸2张牌", 
	["#fankang174"]="%from 对%arg说：“要死你先死！” ",
	["#fankang258"]="%from 始终觉得%arg还是爱自己的",   
	["#fankangfailed"]="此时%arg嘤咛一声开始脱自己的衣服，%from暗骂一声无耻，但兵器还是脱了手",
	["xugong"]="许贡",
	["menke"]="门客",
	[":menke"]="出牌阶段，你可以弃一张红色手牌，指定最多三名其他角色依次判定\
若为红色，目标角色对其攻击范围内，你指定的另一名角色造成1点伤害。\
否则目标角色摸一张牌。每回合限一次",
	["#menke"]="%from的门客%to在乘着月黑风高对%arg进行了刺杀。",
	["#menkefailed"]="%from的门客%to称其身体有恙抱病在床。",
	["wangni"]="亡匿",
	[":wangni"]="出牌阶段，你可以主动弃掉两张黑色手牌，和你指定的任意一名存活的吴势力角色互换位置。每回合限一次",
	["#wangni"]="%from与%to交换了地理位置",
	["luyi"]="路遗",
	["mimou"]="密谋",
	[":mimou"]="出牌阶段，你可以将你任意一张方片手牌当【无中生有】使用",
	["weisui"]="未遂",
	[":weisui"]="锁定技，你使用【杀】或【决斗】造成伤害前必须进行一次判定，除非结果为黑桃，否则你不能造成伤害",	
	["#weisuifailed"]="%from 的锁定技【未遂】被触发，对%to 使用的%arg不能造成伤害",
	["designer:jiping"]="roxiel",	
	["designer:hanlong"]="roxiel",
	["designer:chizhizhe"]="roxiel",	
	["designer:liuye"]="插画:寒秋 技能:roxiel",
	["designer:yinfan"]="roxiel",		
	["designer:wufu"]="插画:寒秋 技能:roxiel",
	["designer:guoxiu"]="roxiel",
	["designer:weike"]="roxiel",
	["designer:fanjiangzhangda"]="roxiel",
	["designer:xugong"]="roxiel",
	["designer:luyi"]="插画:寒秋 技能:roxiel",
	["Taichie"] = "太极易", 
	["zhangsong"]="张松",
	["jinghan"]="精悍",
	[":jinghan"]="锁定技，当你未装备防具时，决斗及红色的杀对你无效",
	["#jinghan"]="%from的锁定技【精悍】被触发，%arg的%arg2对其无效",
	["qiangzhi"]="强识",
	[":qiangzhi"]="其他角色的非延时锦囊牌,在使用并结算之后你可以进行一次判定，若为红色，你获得这张牌\
★额外的，强识的对象不能是无懈可击",
	["#qiangzhi"]="%from 过目不忘，将%arg记忆在了脑海中",
	["#qiangzhifailed"]="%from 年纪大了，记忆力有些衰退",
	["shadowEX"]="影子",
	["ansha"]="暗杀",
	[":ansha"] = "当你使用的【杀】被【闪】抵消时，你可以进行两次判定，若结果都为方片，目标角色立即死亡。", 
	["#ansha"]="%to 被%from 暗杀掉了",
	["jimie"] = "寂灭",
	[":jimie"] = "<b>觉醒技</b>，回合开始阶段，若你已受伤，你须减1点体力上限，回复1点体力，并永久获得技能“曙光”（锁定技，你的黑桃判定牌均视为方片花色）",
	["#JimieWake"] = "%from 触发了觉醒技【寂灭】",
	["shangsan"]="殇散",
	[":shangsan"]="锁定技，你的所有【决斗】均视为【杀】",
	["shuguang"] = "曙光", 
	[":shuguang"] = "锁定技，你的黑桃判定牌均视为方片花色", 
	["#ShuguangJudge"] = "%from 的锁定技【曙光】被触发， 判定牌的花色由黑桃变成了方片", 
	["gexuan"]="葛玄",
	[":xiulian"]="每次你受到或造成伤害时，可以进行一次判定，若结果为红色，你将获得一个修炼标记\
每次你的回合开始时，判断你的修炼程度。\
一个修炼标记，炼精化气:永久获得技能雷符。\
★雷符:你的杀始终带有雷电属性，你的杀造成伤害前你可以进行一次判定，若为黑色，你的杀伤害+1\
两个修炼标记，炼气化神:永久获得技能焚天。\
★焚天:每当你使用的【杀】被【闪】抵消时，可令目标角色判定，若为【红桃】，你指定任意一名角色并对其造成1点火焰伤害。\
◆可以指定目标角色本身为【焚天】的目标。)\
三个修炼标记，炼神返虚:永久获得技能虚无。\
★虚无:每当黑色的卡牌对你造成伤害时，你可以进行一次判定，若结果为黑色，你回复X点体力。X为此次你受到伤害的点数。\
四个修炼标记，聚虚合道:永久获得技能天雷。\
★天雷:每当你使用或打出一张【杀】或【闪】时（在结算前），可令三名角色依次判定，若为黑色，你对其造成1点雷电伤害。\
五个修炼标记，渡劫飞升:永久获得技能渡劫。\
★渡劫:锁定技，你未装备防具时，若需要打出一张【杀】或【闪】时，可进行一次判定，除非结果为【红桃】，否则视为你打出了一张【杀】或【闪】\
额外的，渡劫飞升后葛玄增加2点体力上限。",
	["xiulian"]="修炼",
	["@xiulian"]="修炼",
	["#xiulianl1"]="%from 已经修炼到☆炼精化气☆阶段",
	["#xiulianl2"]="%from 已经修炼到☆炼气化神☆阶段",
	["#xiulianl3"]="%from 已经修炼到☆炼神返虚☆阶段",
	["#xiulianl4"]="%from 已经修炼到☆聚虚合道☆阶段",
	["#xiulianl5"]="%from 已经修炼到★渡劫飞升★阶段",
	["xiulianlevel1"]="雷符",
	[":xiulianlevel1"]="你的杀始终带有雷电属性，你的杀造成伤害前你可以进行一次判定，若为黑色，你的杀伤害+1",
	["#xiulianlevel1"]="%from 使用了一张雷符，伤害增加了1点。",
	["#xiulianlevel1failed"]="%from 掏出一张符咒，却发现是一张卫生纸。",
	["xiulianlevel2"]="焚天",
	[":xiulianlevel2"]="每当你使用的【杀】被【闪】抵消时，可令目标角色判定，若为【红桃】，你指定任意一名角色并对其造成1点火焰伤害。\
◆可以指定目标角色本身为【焚天】的目标。", 
	["#xiulianlevel2"]="%from 催动真气施展了烈焰焚天。",
	["#xiulianlevel2failed"]="%from 催动了半天真气，放出了一个屁。",
	["xiulianlevel3"]="虚无",
	[":xiulianlevel3"]="每当黑色的卡牌对你造成伤害时，你可以进行一次判定，若结果为黑色，你回复X点体力。X为此次你受到伤害的点数",
	["#xiulianlevel3"]="%from 化身为一片虚无，运功疗伤。",
	["#xiulianlevel3failed"]="%from 想变成一只萌宠，却变成了一棵大树。",
	["xiulianlevel4"]="天雷",
	[":xiulianlevel4"]="每当你使用或打出一张【杀】或【闪】时（在结算前），可令三名角色依次判定，若为黑色，你对其造成1点雷电伤害",
	["@tianlei"]="请指定【天雷】的目标",
	["#xiulianlevel4"]="%from催动神识引发了一道九天神雷劈中了%to",
	["#xiulianlevel4failed"]="%from的一道天雷劈歪了。",
	["xiulianlevel5"]="渡劫",
	[":xiulianlevel5"]="锁定技，你未装备防具时，若需要打出一张【杀】或【闪】时，可进行一次判定\
除非结果为【红桃】，否则视为你打出了一张【杀】或【闪】",	
	["#xiulianlevel5"]="%from 已经快渡了九九八十一劫了，马上就可以取得真经了，白日飞升指日可待。",
	["#xiulianlevel5failed"]="%from 终于明白天劫不论你身在何方都是闪不掉的。",
	["#xiulianlevelup"]="%from 潜心修炼，终于得以窥见天道。",
	["#xiulianlevelupfailed"]="%from 功力不足以战胜心魔，需重新来过。",
	["dancer"]="舞姬",
	["dance"]="跳舞",
	[":dance"]="出牌阶段开始时，你可以选择弃置2张手牌或翻面，然后你进行一次判定\
♥~此时随机选取一名角色流失1点体力\
♦~你最多指定3名已受伤角色回复1点体力\
♣~此时随机选取一名角色，该角色【运功自爆】死亡，若其最大生命值小于4，其他角色受到X-1点伤害，\
否则其他角色受到X-2点伤害。X为被选取角色的最大体力值，伤害来源为被选取的角色。\
你自己也会受到自爆的影响。\
♠~除你之外的所有角色立即受到来源于该角色自己的1点伤害",
    ["#dancedebug"]="%arg this",
    ["@dancereason"]="弃牌跳舞",
	["@dance"]="请指定【艳舞】的目标",	
	["dancediamond"]="艳舞",	
	["#dancebomb"]="%from 的绝世风姿令天地风云变色，%arg不禁悲从中来，长叹一声，运功自爆了",
	["#dancebombself"]="%from 孤独地站在乱世的巅峰，长叹一声，运功自爆了",
	["#dancebombing"]="由于离%arg太近，%arg2 被炸伤了",
	["#dancespade"]="由于%from总是穿着衣服跳舞，%arg 为了抗议而自残",
	["#danceheart"]="%from 为%arg跳了一支艳舞",
	["#danceheartself"]="%from 在跳舞时扭伤了脚",
	["#dancediamond"]="%to 内牛满面，仿佛满心的创伤都被治愈了",
	["archer"]="猎姬",
	["archershoot"]="溅射",
	[":archershoot"]="每当你使用了1张【万箭齐发】，在其结算后，可进行一次判定，若为红色，你开始对场上随机的1名角色打出了一张杀，持续X次\
★X为场上除你以外的存活角色数，且最大为3",
	["#archershoot"]="%from 乱射的流矢射中了%arg",
	["#archershootfailed"]="%from 发现自己没有备用的箭矢了",
	["archerskill"]="拔箭",
	[":archerskill"]="锁定技，【万箭齐发】对你无效;若其他角色使用的【万箭齐发】在结算完时进入弃牌堆，你立即获得它",
	["spreadingshoot"]="乱射",
	[":spreadingshoot"]="<b>主公技</b>，摸牌阶段，若你已受伤，你可放弃摸牌并展示牌堆顶的X张牌，X为你的已损失体力值。\
其中每有一张方片牌，即视为你将此牌当作【万箭齐发】使用。之后，你获得其余的牌",
	["zhangling"] = "张陵",	
	["zombiemaster"] = "炉鼎",
    ["#zombiemaster"] = "%from将%arg丢到了炉鼎里炼成了一只小僵尸",
	[":zombiemaster"] = "每次当你于回合外失去牌时，可进行一次判定，将非红桃结果的判定牌置于你的武将牌上，称为“小僵尸”\
★在你拥有小僵尸的情况下，每次对你使用桃时你会额外回复X点体力，X为小僵尸的数目且最大为2",
	["#zombieskill"] = "%from 拥有僵尸体制，桃的效果将增加",
	["zombies"] = "小僵尸",
	["zombiebomb"] = "尸爆",	
	[":zombiebomb"] = "出牌阶段,你可以令任意一只小僵尸自爆，你须指定一名角色，然后你进行一次判定\
♥~该角色受到1点火属性伤害并翻面。\
♠~你自己的武将牌翻面",
	["#zbfailed"]="%from的小僵尸自己跑出去玩了",
	["#zbHeart"] = "%from的小僵尸运功【自爆】了，%arg被炸伤了",	
	["#zbSpade"] = "%from 的★小僵尸★还没冲出去就爆炸了",
	["zombiepoison"] = "瘟疫",
	[":zombiepoison"] = "出牌阶段,你使用所有小僵尸酝酿一次瘟疫，然后你进行一次判定\
♦~除你之外的所有角色受到X点火属性伤害。X为你的小僵尸数目，且最大为3。\
♣~场上所有角色流失1点体力",	
    ["#zpfailed"]="小僵尸都跑去看文艺节目了",
	["#zpDiamond"] = "受到【瘟疫】的影响，%arg火毒攻心了",	
	["#zpClub"] = "受到【瘟疫】的影响，%arg被感染了",	
	["fengchu"] = "凤雏",
	["buzhen"] = "布阵",	
	[":buzhen"] = "出牌阶段，你可以弃掉2张手牌，然后选择一名【阵眼】角色，然后进行一次判定决定阵法效果：\
♥青龙:【阵中】角色每回复1点体力，你也会回复1点体力。\
♦白虎:你每次受到伤害时，【阵中】角色必须弃1张手牌\
♣朱雀:【阵眼】角色每受到1点伤害，你可以摸两张牌\
♠玄武:【阵中】角色每次受到伤害前，你可以弃一张牌阻止此伤害。\
★你和你指定的角色称为【阵眼】，处于你们之间的角色即视为在你的【阵中】\
★【阵眼】其中之一死亡时，阵法会失效。额外的，你再次使用布阵时，会清除之前的阵法效果",
	["@zhenyan"] = "阵眼",	
	["@zhenzhong"] = "阵中",
    ["@buzhen1"] = "青龙",
	["@buzhen2"] = "白虎",	
	["@buzhen3"] = "朱雀",	
	["@buzhen4"] = "玄武",
	["buzhen1"] = "青龙阵",
	["buzhen2"] = "白虎阵",	
	["buzhen3"] = "朱雀阵",	
	["buzhen4"] = "玄武阵",
	["#buzhen1"] = "%from【青龙阵】的效果被触发，%arg每回复1点体力可以令其也回复1点体力",
	["#buzhen2"] = "%from【白虎阵】的效果被触发，每次受伤阵中的%arg必须弃1张手牌",	
	["#buzhen3"] = "%from【朱雀阵】的效果被触发，阵眼%arg每受到1点伤害可以令其摸两张牌",	
	["#buzhen4"] = "%from发动了【玄武阵】的效果，阻止了%arg此次受到的伤害",
	["$buzhen1"] = "青龙阵",
	["$buzhen2"] = "白虎阵",	
	["$buzhen3"] = "朱雀阵",	
	["$buzhen4"] = "玄武阵",
	["lianyu"] = "炼狱",
	[":lianyu"] = "当你对一名【阵中】角色使用一张【杀】时，你可以令所有【阵中】角色成为你的目标",
	["#lianyu"] = "由于%from的【炼狱】，%to均成为了%arg的目标",
	["designer:zhangsong"]="roxiel",	
	["designer:shadowEX"]="roxiel",
	["designer:gexuan"]="roxiel",
	["designer:dancer"]="roxiel",
	["designer:archer"]="roxiel",	
	["designer:zhangling"]="roxiel",
	["designer:fengchu"]="roxiel",	
	["~zhangsong"]="竟当我没有存在过",	
	["~shadowEX"]="我还会回来的",
	["~gexuan"] = "形神俱灭",
	["~dancer"] = "你还没看够我曼妙的舞姿呢~",
	["~archer"] = "你不是要借箭吗?!",
	["~zhangling"] = "尸毒 攻心了",
	["~fengchu"] = "谁知天狗流量坠，不使将军衣锦回。",
	["~jiping"]="越老越要毒啊",	
	["~hanlong"]="唉，我离你们太遥远了",
	["~chizhizhe"]="生在污谭命所之，虚心抱菊满情丝",
	["~liuye"]="此生无酒不欢",
	["~yinfan"]="离人以言 重于剑戟",		
	["~wufu"]="你不是我的主子，我不是你的奴才，怎么叫造反？",
	["~guoxiu"]="勇过聂政 功逾介子",
	["~weike"]="我与备正相谈甚欢呐",
	["~fanjiangzhangda"]="小人物的事再大，也是小事",
	["~xugong"]="汝等必死于匹夫之手",
	["~luyi"]="脱剑膝前横，言其请愿状，奈何终未遂",
	["cv:chizhizhe"] = "谷歌娘",
}