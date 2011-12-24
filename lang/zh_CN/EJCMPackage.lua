-- translation for YJCM Package

return {
	["EJCM"] = "二将成名",

	--王元姬
	["wangyuanji"] = "王元姬",
	["cv:wangyuanji"] = "",
	["xianming"] = "贤明",
	[":xianming"] = "出牌阶段出牌前，你可以弃掉在摸牌阶段获得的所有牌，重新摸取等量的牌，每阶段限用一次",
	["xiaosi"] = "孝思",
	[":xiaosi"] = "出牌阶段，你可以弃一张手牌并选择一名男性角色，该角色进行二选一：1.回复1点体力，并在你下次行动前替你承担一次伤害；2.摸两张牌，跳过自己下一次的摸牌阶段(在你下个摸牌阶段之前)，并令你下个摸牌阶段额外摸一张牌。每阶段限一次\
★受到放权影响时，提前触发孝思的效果并清除场上的所有孝思状态，你可以再次发动孝思",
	["xiaosi:a"] = "回复1点体力",
	["xiaosi:b"] = "摸两张牌",
	["@xiaosi"] = "孝思",
	["#XiaosiA"] = "%from 选择了回复体力并为 %to 承担下回合之前的一次伤害",
	["#XiaosiB"] = "%from 选择了提前摸牌并允许 %to 下回合额外摸两张牌",
	["#XiaosiAdamage"] = "%from 为 %to 承担了本次的全部伤害",
	["#XiaosiBdraw"] = "%from 的技能<font color='yellow'><b>【%arg】</b></font>生效，额外摸了两张牌",

	--夏侯令女
	["xiahounv"] = "夏侯令女",
	["cv:xiahounv"] = "",
	["baojie"] = "保节",
	[":baojie"] = "<b>锁定技</b>，杀死你的角色不执行任何奖惩",
	["juhun"] = "拒婚",
	[":juhun"] = "当你的体力值:\
  ◆1. 不大于3点时,回合结束阶段你可摸X张牌。\
  ◆2. 不大于2点时,每当你使用或打出一张黑桃牌,可摸X张牌。\
  ◆3. 不大于1点时,你不能成为男性角色除【桃园结义】和【五谷丰登】外的红色锦囊和红色【杀】的目标。\
  X为你损失的体力值",
  ["#Baojie"] = "%from 的锁定技<font color='yellow'><b>【%arg】</b></font>被触发，%to 不能执行奖惩",

    --鲍三娘
	["baosanniang"] = "鲍三娘",
	["cv:baosanniang"] = "",
	["chengshi"] = "承师",
	[":chengshi"] = "回合开始阶段，你可以进行一次判定：\
  ◆1. 若判定结果为锦囊牌，你获得技能【集智】。\
  ◆2. 若判定结果为基本牌，你获得技能【武圣】。\
  ◆3. 若判定结果为装备牌，你获得技能【枭姬】。\
  无论如何，你都获得该判定牌",
	["zhenshou"] = "镇守",
	[":zhenshou"] = "出牌阶段，你可以将1张手牌移除游戏（可多次替换），并称之为“守”，若如此做，其他角色使用的牌（延时锦囊除外）若与你“守”牌花色相同，则该牌对你无效。",
	["shou"] = "守",
	["#Zhenshou"] = "%from 的技能<font color='yellow'><b>【%arg】</b></font>被触发，%to 所使用的牌<font color='yellow'><b>【%arg2】</b></font>与其<font color='red'><b>【守】</b></font>的花色相同，因此该牌对 %from 无效",

	--胡车儿
	["hucheer"] = "胡车儿",
	["cv:hucheer"] = "",
	["daoji"] = "盗戟",
	[":daoji"] = "出牌阶段，你可以弃掉一张梅花花色手牌，并指定一名有武器的角色，若如此做，你获得该角色的武器，并可以选择将该武器交给其他角色，每阶段限用一次",
	["jingjiu"] = "敬酒",
	[":jingjiu"] = "出牌阶段，你可以将【酒】对其他角色使用",

	--韩当
	["handang"] = "韩当",
	["cv:handang"] = "",
	["qishe"] = "骑射",
	[":qishe"] = "出牌阶段，你可以指定一名在你攻击范围内的角色，你展示并弃掉一张手牌，然后弃掉目标角色的一张手牌，若你弃掉的展示牌与你弃掉该角色的牌的花色相同，则你对其造成1点伤害。",
	["$Qishe"] = "%from 弃掉了这张<font color='red'>【展示牌】</font>",
	["#Qishe"] = "%from 所弃掉的牌的<font color='yellow'><b>【花色】</b></font>与弃掉 %to 的牌的<font color='red'><b>【花色】</b></font>相同",

	--武将技能台词

	--武将阵亡台词
	["~wangyuanji"] = "王元姬·阵亡",
	["~xiahounv"] = "夏侯令女·阵亡",
	["~baosanniang"] = "鲍三娘·阵亡",
	["~handang"] = "韩当·阵亡",
	["~hucheer"] = "胡车儿·阵亡",

	["designer:wangyuanji"] = "插画:王元姬　技能:天狼欧阳杉",
	["designer:xiahounv"] = "战栗贵公子",
	["designer:baosanniang"] = "战栗贵公子",
	["designer:handang"] = "战栗贵公子",
	["designer:hucheer"] = "战栗贵公子",
}
