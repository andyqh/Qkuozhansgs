-- translation for KusoPackage

return {
	["kuso"] = "灌汤包", 

	["kusoking"] = "屎皇帝",
	["designer:kusoking"] = "宇文天启",
	["cv:kusoking"] = "",
	["huaxu"] = "花溆",
	[":huaxu"] = "回合内，你每造成一次伤害，可令受到伤害的角色获得一个和伤害牌相同花色的屎标记。拥有屎标记的角色回合内每使用一张和屎标记相同花色的牌，（在结算前）立即产生和对应花色屎相同的效果。你的回合开始之前，清除场上所有的屎标记",
	["@hana1"] = "红花",
	["@hana2"] = "菱花",
	["@hana3"] = "黑花",
	["@hana4"] = "草花",
	["#Gotoshit"] = "%from 大施魔法，将 %to 的 %arg 花色手牌都变成了 <font color=gold><b>屎</b></font>",
	["$HuaxuDamage1"] = "%from 将 %card 看成了 <font color=gold><b>屎</b></font>[火焰属性]",
	["$HuaxuDamage2"] = "%from 将 %card 看成了 <font color=gold><b>屎</b></font>[无属性]",
	["$HuaxuDamage4"] = "%from 将 %card 看成了 <font color=gold><b>屎</b></font>[雷电属性]",
	["$HuaxuDamage3"] = "%from 将 %card 看成了 <font color=gold><b>屎</b></font>[体力流失]",
	["liaoting"] = "蓼汀",
	[":liaoting"] = "限定技，出牌阶段，你可以弃掉4张手牌，若均为屎，（在弃掉之前）立即产生以下效果：1、若你为反贼，主公立即死亡；2、若你为主公或忠臣，所有反贼和内奸立即死亡；3、若你为内奸，摸五张牌，所有反贼和忠臣立即死亡。若之后你依然存活且游戏未结束，回复体力至体力上限",
	["liaot"] = "汀",

	["tianyin"] = "天音",
	["designer:tianyin"] = "鎏铄天音",
	["cv:tianyin"] = "",
	["skydao"] = "天道",
	[":skydao"] = "锁定技，你的回合外，你每受到一次伤害，增加1点体力上限",
	["#SkydaoMAXHP"] = "%from 的锁定技【%arg2】被触发，增加了一点体力上限，目前体力上限是 %arg",
	["noqing"] = "无情",
	[":noqing"] = "锁定技，你受到伤害时，若你的体力是全场最少或同时为最少，则所有人必须减少1点体力或1点体力上限",
	["noqing:hp"] = "体力",
	["noqing:max_hp"] = "体力上限",
	["#NoqingLoseHp"] = "受到 %from 【%arg】锁定技的影响，%to 流失了一点体力",
	["#NoqingLoseMaxHp"] = "受到 %from 【%arg】锁定技的影响，%to 流失了一点体力上限",

	["tenkei"] = "天启",
	["designer:tenkei"] = "宇文天启",
	["cv:tenkei"] = "",
	["eatdeath"] = "拾尸",
	[":eatdeath"] = "当有角色死亡时，你可以失去一个因“拾尸”获得的技能(如果有的话)，然后失去一点体力上限并获得该角色当前的所有武将技",

	["shenzilong"] = "神子龙",
	["designer:shenzilong"] = "官方内测第一版",
	["cv:shenzilong"] = "",
	["super_juejing"] = "绝境",
	[":super_juejing"] = "锁定技，摸牌阶段，你不摸牌；你的手牌数永远为4",
	[":super_longhun"] = "你的牌可按下列规则使用（或打出）：红桃当【桃】，方块当火属性的【杀】，梅花当【闪】，黑桃当【无懈可击】",
	["duojian"] = "夺剑",
	[":duojian"] = "回合开始阶段，若场上（其他玩家的装备区和所有玩家的判定区）有青釭剑，你可以获得并装备之",

--cards
	["kuso_cards"] = "小笼包",

	["sacrifice"] = "舍己为人",
	[":sacrifice"] = "出牌时机：出牌阶段。\
使用目标：任意一名已受伤的角色。\
作用效果：你失去一点体力，令目标回复一点体力",

	["clear_shirt"] = "渌水罗衣",
	[":clear_shirt"] = "锁定技，装备在你下家的装备区内，装备者对其上家造成的伤害始终无效",
	["#CSProtect"] = "因为【%arg2】的影响，%from 受到的 %arg 点伤害无效",

	["kawaii_dress"] = "百花裙",
	[":kawaii_dress"] = "锁定技，当你的体力为1时，任何伤害对你无效。当你失去装备区里的【百花裙】时，你立即摸两张牌。男性角色试图装备【百花裙】时，会受到惩罚",
	["#KawaiiDressProtect"] = "%from 受到【百花裙】保护，将 %arg 点伤害[%arg2] 无效化", 
	["#KawaiiHurt"] = "%from 被【%arg】发现不是女性，将受到惩罚", 
	["#KawaiiAngry"] = "%from 被【%arg】发现有 %arg2 的气息，顿时勃然大怒，猛然收缩！", 

	["fiveline"] = "五道杠",
	[":fiveline"] = "<br><font color=blue>德杠</font>·体力为1时可以发动【仁德】<br><font color=green>智杠</font>·体力为2时可以发动【集智】<br><font color=gold>体杠</font>·体力为3时可以发动【结姻】<br><font color=red>美杠</font>·体力为4时可以发动【国色】<br><font color=brown>劳杠</font>·体力为5时可以发动【苦肉】",

	["emigration"] = "暗度陈仓",
	[":emigration"] = "出牌阶段，对任意一名角色使用，将【暗度陈仓】横置于目标角色判定区里，目标角色回合判定阶段进行判定；若判定结果是黑色，则跳过目标角色的弃牌阶段，将【暗度陈仓】弃置",

	["ufo"] = "不明飞行物",
	[":ufo"] = "锁定技，回合开始阶段，将你的手牌补至上限，若补牌数为0，此装备转移到下家的装备区内",
	["#UFOMoving"] = "%arg 抛弃了可怜的 %from，投入 %to 的怀抱",
	["#UFODraw"] = "%arg 大显神威，%from 瞠目结舌",

--joy
	["stink"] = "屁",
	[":stink"] = "出牌阶段对下家使用，除非目标角色打出一张【闪】，否则必须和自己的下家（你的下下家）交换位置",
	["haochou"] = "你的上家对你放了一个臭屁，除非你能【闪】开，否则就完蛋了……",
}
