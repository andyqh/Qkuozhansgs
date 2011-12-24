-- translation for CyanPackage

return {
	["cyan"] = "★青龙★", 

--QUN#03 北海太守
	["cyankongrong"] = "孔融",
	["designer:cyankongrong"] = "宇文天启",
	["rangli"] = "让梨",
	["pear"] = "梨",
	[":rangli"] = "摸牌阶段摸牌前，你可以放弃摸牌并指定一名可以给你两张牌的角色，该角色必须给你两张手牌，然后该角色在自己的下一个摸牌阶段摸牌时额外摸两张牌（让梨效果可以累积）\
★如孔融让梨张辽，张辽选择发动突袭跳过摸牌阶段，孔融下次依然让梨张辽，若这次张辽没有发动突袭，可以额外摸4张牌",
	["@pear"] = "梨",
	["@rangli-ask"] = "%src 向你发动了【让梨】，你必须选择两张手牌给他，否则由他抽取你两张手牌",

--WEI#03 邓哀王
	["cyancaochong"] = "曹冲",
	["designer:cyancaochong"] = "竹影澜轩",
	["weighing"] = "称象",
	[":weighing"] = "锁定技，你的回合外，每当你的手牌数不等于你的当前体力值时，你须将手牌弃至或补至等同于你当前体力值的张数",
	["kuanhou"] = "宽厚",
	[":kuanhou"] = "你每受到一次伤害，若你的武将牌正面朝上，你可将你的武将牌翻面，然后在伤害来源的回合结束时可令一名其他角色进行一个额外的出牌阶段",
	["#Kuanhou"] = "%from 令 %to 立即进行一个额外的出牌阶段",

--SHU#03 中流砥柱
	["cyanliaohua"] = "廖化",
	["designer:cyanliaohua"] = "玩玩百姐",
	["guolie"] = "果烈",
	[":guolie"] = "当你造成一次伤害时，可防止此伤害，改为与受伤害的角色交换手牌",
	["#Guolie"] = "%from 与 %to 交换了手牌",
	["zhongshu"] = "终蜀",
	[":zhongshu"] = "出牌阶段，你的【杀】能攻击到手牌数与你体力差为1的任一角色",

--WU#03 性不协俗
	["cyanyufan"] = "虞翻",
	["designer:cyanyufan"] = "游神ViVA",
	["shuaijin"] = "率进",
	[":shuaijin"] = "你每用黑色牌对其他角色造成一次伤害，可以观看牌堆顶一张牌，然后将该牌交给任意一名角色",
	["liufang"] = "流放",
	[":liufang"] = "回合外，每失去一张牌，可进行一次判定，若为黑色基本牌或黑色锦囊牌，你立即获得失去的那张牌",

--WEI#04 长者之风
--http://www.qsanguosha.com/forum.php?mod=viewthread&tid=5800
	["cyanlidian"] = "李典",
	["designer:cyanlidian"] = "sailiss",
	["ruji"] = "儒计",
	[":ruji"] = "回合开始时，你可摸一张牌后与任一其他角色拼点，若你赢，你展示目标角色手牌后弃置目标角色处（包括判定区）的一张牌。若你没赢，对方摸两张牌",
	["caishi"] = "才逝",
	[":caishi"] = "锁定技，回合结束时，你须弃置两张手牌（不足则全弃）后摸一张牌",
	["#Caishi"] = "%from 的锁定技【%arg】被触发，必须弃掉 %arg2 张手牌",
	["@ruji-card"] = "请选择【儒计】的拼点牌和拼点目标",
	["ruji_success"] = "儒计成功",
	["ruji_fail"] = "儒计失败",
	["#RujiSucc"] = "%from 将 %to 的全部手牌示众",

--EX#T2 北地枪王
--http://blog.sina.com.cn/s/blog_7d07da460100y0x3.html
	["cyanzhangxiu"] = "张绣",
	["designer:cyanzhangxiu"] = "浦原秀一",
	["baiming"] = "百鸣",
	[":baiming"] = "锁定技，当你使用的【杀】即将对目标造成伤害时，你须将该伤害转移给目标攻击范围内的另一名角色",
	["#Baiming"] = "%from 的锁定技【%arg】被触发，%from 必须选择 %to 攻击范围内除 %to 外的一名角色",
	["#BaimingRechoose"] = "%from 选择了 %to 为【%arg】的目标",
	["junling"] = "军令",
	[":junling"] = "主公技，出牌阶段，你可以指定任意一名角色对其攻击范围内的另一名角色使用一张【杀】，若该角色不如此做，你从他那里获得一张手牌，每阶段限一次",
	["junling-slash"] = "%src 发动了技能【军令】，目标是 %dest，请打出一张【杀】以响应", 

--SHU#04 天使之艺
	["cyanpuyuan"] = "蒲元",
	["designer:cyanpuyuan"] = "天使之艺",
	["hunren"] = "魂刃",
	[":hunren"] = "锁定技,当你装备某种武器时可获得额外的效果直到你失去此武器：\
0.无武器 获得“天妒”\
1.【诸葛连弩】获得“集智”\
2.【雌雄双股剑】获得“仁德”\
3.【青釭剑】获得“绝境”\
4.【古锭刀】获得“英魂”\
5.【寒冰剑】获得“天香”\
6.【青龙偃月刀】获得“武圣”\
7.【贯石斧】获得“断粮”\
8.【丈八蛇矛】获得“咆哮”\
9.【朱雀羽扇】获得“八阵”\
10.【方天画戟】获得“无双”\
11.【麒麟弓】获得“烈弓”\
12.【银月枪】获得“龙胆”\
13.【倚天剑】获得“奸雄”\
14.【杨修剑】获得“放逐”\
15.【SP银月枪】获得“倾国”",
	["#HunrenSkill"] = "%from 的锁定技【%arg】被触发，失去了技能【%arg2】",
	["cuihuo"] = "淬火",
	[":cuihuo"] = "锁定技,当你失去装备区里的武器时,你回复1点体力值;若在你的出牌阶段失去,则每阶段限用一次",

--SHU#05 倒戈之悟
	["cyanfanqiangzhangda"] = "范彊张达",
	["designer:cyanfanqiangzhangda"] = "筱音",
	["qianpan"] = "潜叛",
	[":qianpan"] = "锁定技，当你受到伤害时，势力变为吴或蜀；当其他角色令你回复体力时，你的势力变为该角色的势力。相异势力角色的非延时锦囊对你无效",
	["#Qianpan"] = "%from 的锁定技【%arg2】被触发，势力变为 %arg",
	["#QianpanProtect"] = "%from 的锁定技【%arg2】被触发， %to 的非延时锦囊【%arg】对其无效",
	["anshi"] = "暗弑",
	[":anshi"] = "出牌阶段，若有其他角色处于濒死状态，你可以暂时获得技能“完杀”，若如此做，回合结束时你失去“完杀”和当前的所有体力",
	["#AnshiSuicide"] = "%from 受到技能【%arg】的影响，失去了<b>【<font color=black>完杀</font>】</b>技能",

--QUN#04 伏波之后
	["cyanmateng"] = "马腾",
	["designer:cyanmateng"] = "曉ャ絕對",
	["jiaozei"] = "剿贼",
	[":jiaozei"] = "当你使用的【杀】被【闪】抵消时，你可与目标角色拼点，若你赢，该【杀】依旧造成伤害",
	["#Jiaozei"] = "%from 发动了技能【%arg】，对 %to 强制造成伤害",
	["zhaobing"] = "招兵",
	[":zhaobing"] = "主公技，其他群雄角色可以替你出拼点牌",
	["$Zhaobing"] = "%from 响应了 %to 的【招兵】，提供了 %card 为 %to 的拼点牌",
	["@zhaobing-pindian"] = "%src 发动了主公技【招兵】，你可以为其提供一张牌用于拼点",

	["cv:cyankongrong"] = "",
	["cv:cyanzhangxiu"] = "",
	["cv:cyanyufan"] = "",
	["cv:cyanpuyuan"] = "",
	["cv:cyanlidian"] = "",
	["cv:cyancaochong"] = "",
	["cv:cyanliaohua"] = "",
	["cv:cyanfanqiangzhangda"] = "",
	["cv:cyanmateng"] = "",
}
