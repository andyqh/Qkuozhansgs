-- translation for RedPackage

return {
	["red"] = "★朱雀★", 

--WEI#01
	["redzhonghui"] = "钟会",
	["designer:redzhonghui"] = "插画：寒秋，设计：宇文天启",
	["cv:redzhonghui"] = "",
	["tongmoux"] = "同享",
	[":tongmoux"] = "出牌阶段出牌前,指定一名角色为谋友并获得以下技能直到该角色下个回合结束:互为谋友的两名角色在其出牌阶段可以共享对方的手牌(见详解)",
	["tongmoux_tie"] = "指定一名角色成为你的谋友",
	["#Tongmoux_forbidden"] = "%from 拥有技能【%arg2】，为了避免无限刷牌的情况发生，你只能发动一次【%arg】",
--	["mycard"] = "我的手牌",
	["tongmouxv"] = "同享",
	["xianhaix"] = "天扰",
	[":xianhaix"] = "你可以将你的天灾手牌放在任意角色的判定区内，然后摸一张牌",

--WEI#02
	["redxunyou"] = "荀攸",
	["designer:redxunyou"] = "插画：寒秋，设计：黄书",
	["cv:redxunyou"] = "",
	["baichux"] = "千策",
	[":baichux"] = "游戏开始时，额外发给你一张牌，你须将一张手牌牌置于你的武将牌上之称为“策”。出牌阶段，你可以打出任意一张手牌替换一次“策”。回合内你每使用一张点数小于“策”的牌时可摸一张牌(限五次)；回合外你可将点数不小于“策”的牌当【闪】使用或打出",
	["@baichux"] = "请选择一张手牌作为“策”",
	["jix"] = "策",
	
--QUN#01
	["redhejin"] = "何进",
	["designer:redhejin"] = "幻象迷宫",
	["cv:redhejin"] = "",
	["tonglu"] = "同戮",
	[":tonglu"] = "出牌阶段，你可以令场上武将牌正面朝上的角色依次选择是否愿意将自己的武将牌翻面。若如此做，你的下一张【杀】造成的伤害+X。X为愿意翻面的武将数量",
	["liehou"] = "列侯",
	[":liehou"] = "弃牌阶段弃牌后，你可选择一个背面向上的角色，令其获得你弃掉的牌或摸一张牌",
	["zide"] = "自得",
	[":zide"] = "锁定技，回合结束阶段，若你在本回合内没有发动“同戮”，立即摸一张牌",
	["tonglu:agree"] = "翻翻更健康~",
	["tonglu:deny"] = "翻你妹啊！",
	["#TongluBuff"] = "%from 的【同戮】生效，【杀】的伤害增加了 %arg, 达到了 %arg2 点",
	["liehou:get"] = "令一名背面朝上的角色获得你的弃牌",
	["liehou:draw"] = "令一名背面朝上的角色摸一张牌",
	["liehou:cancel"] = "不发动",
	["#Liehou"] = "%to 回收了 %from 的 %arg 张弃牌",
	["@wocao"] = "蓄力",

--SHU#01
	["redguansuo"] = "关索",
	["designer:redguansuo"] = "宇文天启、俊逸不凡",
	["cv:redguansuo"] = "",
	["xiefang"] = "撷芳",
	[":xiefang"] = "你可以将其他角色装备区里的武器当【杀】、非武器当【闪】使用或打出",
	["xiefang:slash"] = "你想发动技能【撷芳·杀】吗？",
	["xiefang:jink"] = "你想发动技能【撷芳·闪】吗？",
	["yanyun"] = "偃云",
	[":yanyun"] = "若你使用的“撷芳”【杀】被闪避，可以继续对目标使用一张非“撷芳”【杀】",
	["@yanyun-slash"] = "您可以再打出一张非“撷芳”【杀】来发动偃云的追杀效果", 

--WU#01
	["redyanbaihu"] = "严白虎",
	["designer:redyanbaihu"] = "俊逸不凡",
	["cv:redyanbaihu"] = "",
	["jielue"] = "劫掠",
	[":jielue"] = "出牌阶段，你使用的【杀】指定目标后，可先附带拼点的效果，若你赢，你获得目标角色的拼点牌",

--SHU#02
	["redwutugu"] = "兀突骨",
	["designer:redwutugu"] = "春哥姨妈",
	["cv:redwutugu"] = "",
	["chuzhen"] = "出阵",
	[":chuzhen"] = "觉醒技，回合开始阶段，若你已受伤，你须增加1点体力上限并获得技能“鳞甲”（锁定技，【南蛮入侵】及普通【杀】对你无效；你受到的火焰伤害+1）及“助兵”（摸牌阶段，你可放弃摸牌并展示牌堆顶X张牌，X为你的已损失体力值。其中每有一张黑桃牌，即视为你将此牌当作【南蛮入侵】使用。之后，你获得其余的牌）",
	["#ChuzhenWake"] = "%from 发现自己已经受伤，大吼一声，正式觉醒！",
	["linjia"] = "鳞甲",
	[":linjia"] = "锁定技，【南蛮入侵】及普通【杀】对你无效；你受到的火焰伤害+1",
	["zhubing"] = "助兵",
	[":zhubing"] = "摸牌阶段，你可放弃摸牌并展示牌堆顶的X张牌，X为你的已损失体力值。其中每有一张黑桃牌，即视为你将此牌当作【南蛮入侵】使用。之后，你获得其余的牌",
	["#LinjiaNullify"] = "%from 的锁定技【%arg】被触发，【%arg2】对其无效", 
	["#LinjiaDamage"] = "%from 的锁定技【鳞甲】的负面技能被触发，由 %arg 点火焰伤害增加到 %arg2 点火焰伤害",

--QUN#02
	["redchunyuqiong"] = "淳于琼",
	["designer:redchunyuqiong"] = "连营",
	["cv:redchunyuqiong"] = "",
	["xujiu"] = "酗酒",
	[":xujiu"] = "回合开始阶段，你可将一张黑色手牌置于武将牌上称之为“酿”，你每次使用【杀】造成伤害时，可将一张正面向上的“酿”翻面，若如此做，该伤害+1",
	["niangA"] = "酿",
	["niangB"] = "翻面的酿",
	["@xujiu-ask"] = "你可以将一张黑桃或梅花手牌移出游戏作为“酿”",
	["#XujiuBuff"] = "%from 的【酗酒】效果被触发，伤害从 %arg 点上升至 %arg2 点",
	["xuebi"] = "削鼻",
	[":xuebi"] = "锁定技，回合结束阶段，若你的“酿”大于三张，必须立即弃掉所有“酿”并减去一点体力上限",
	["#Xuebi"] = "%from 的锁定技【%arg】被触发，失去了一点体力上限和所有的 %arg2",

--WU#02
	["redsunluban"] = "孙鲁班",
	["designer:redsunluban"] = "天狼欧阳杉",
	["cv:redsunluban"] = "",
	["jiaochong"] = "骄宠",
	[":jiaochong"] = "出牌阶段出牌前，你可以弃掉在摸牌阶段获得的所有牌，重新摸取等量的牌，每阶段限用一次",
	["goulian"] = "媾连",
	[":goulian"] = "出牌阶段，你可以弃一张手牌并选择一名男性角色，该角色进行二选一：1.回复1点体力，并在你下次行动前替你承担一次伤害；2.摸两张牌，跳过自己下一次的摸牌阶段(在你下个摸牌阶段之前)，并令你下个摸牌阶段额外摸一张牌。每阶段限一次\
★受到放权影响时，提前触发媾连的效果并清除场上的所有媾连状态，你可以再次发动媾连",
	["goulian:a"] = "回复1点体力",
	["goulian:b"] = "摸两张牌",
	["@goulian"] = "媾连",
	["#GoulianA"] = "%from 选择了回复体力并为 %to 承担下回合之前的一次伤害",
	["#GoulianB"] = "%from 选择了提前摸牌并允许 %to 下回合额外摸一张牌",
	["#GoulianAdamage"] = "%from 为 %to 承担了本次的全部伤害",
	["#GoulianBdraw"] = "%from 的技能【%arg】生效，额外摸了两张牌",

--EX#T1
	["rednanmanwang"] = "南蛮王",
	["super_zaiqi"] = "象兵",
	[":super_zaiqi"] = "摸牌阶段，你可以放弃摸牌并展示牌堆顶的X张牌，X为你已损失的体力值+1，其中每有一张红桃牌，你回复1点体力；每有一张黑桃牌，即视为你将此牌当作【南蛮入侵】使用。然后弃掉这些红桃和黑桃牌，将其余的牌收入手牌。当红桃结果多于黑桃结果时，你的势力为蜀，否则为群",
	["designer:rednanmanwang"]="插画:寒秋",
	["cv:rednanmanwang"] = "墨染の飞猫",
}
