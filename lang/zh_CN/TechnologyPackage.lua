-- translation for Technology Package

local te = {
	["technology"] = "方技传", 
	["designer:technology"] = "淬毒",

	["guanlu"] = "管辂",
	["tuiyan"] = "推演",
	[":tuiyan"] = "出牌阶段，你使用任意一张牌比在该阶段使用的前一张牌点数大，则这张牌可以指定任一角色为目标（无视规则）",
	["tianji"] = "天机",
	[":tianji"] = "若你在出牌阶段，使用的牌都符合“推演”，且不少于三张，则回合结束后，进行一个额外的回合",
	["mingfa"] = "命罚",
	[":mingfa"] = "锁定技，你因“天机”获得额外回合开始前，从牌堆亮出一张牌，若黑桃花色，则失去2点体力",
	["$Tuiyan"] = "%from 将 %card 的目标改为了 %to",
	["$Mingfa"] = "%from 翻开牌堆顶的一张牌。为 %card",

	["dukui"] = "杜夔",
	["yueli"] = "乐理",
	[":yueli"] = "当你回复1点体力时，可防止此效果，改为摸两张牌；当你受到1点伤害时，可防止此效果，改为弃置两张牌；当你摸两张牌时，可防止此效果，改为回复1点体力；当你弃置两张牌时，可防止此效果，改为失去1点体力",
	["yueli_h2d"] = "乐理①",
	[":yueli_h2d"] = "当你回复1点体力时，可防止此效果，改为摸两张牌",
	["#Yueli_rec"] = "%from 将 %arg 点体力回复转换为摸 %arg2 张牌",
	["yueli_m2t"] = "乐理②",
	[":yueli_m2t"] = "当你受到1点伤害时，可防止此效果，改为弃置两张牌",
	["#Yueli_dmg"] = "%from 通过弃掉 %arg2 张牌抵消了对自己的 %arg 点伤害",
	["yueli_d2h"] = "乐理③",
	[":yueli_d2h"] = "当你摸两张牌时，可防止此效果，改为回复1点体力",
	["#Yueli_dnc"] = "%from 用少摸 %arg 张牌的代价为自己回复了 %arg2 点体力",
	["yueli_t2m"] = "乐理④",
	[":yueli_t2m"] = "当你弃置两张牌时，可防止此效果，改为失去1点体力",
	["#Yueli_cd"] = "%from 用失去 %arg 点体力的代价收回了 %arg2 张弃牌",

	["zhouxuan"] = "周宣", 
	["mengjie"] = "梦结",
	[":mengjie"] = "在你的回合外，每失去一张手牌，可以横置一名角色",
	["mengJie"] = "梦解",
	[":mengJie"] = "任意武将牌横置的角色成为基本牌或非延时锦囊的目标时，你也可以成为该牌的目标，结算后重置该角色的武将牌。当你成为基本牌或非延时锦囊的目标时，可以使所有武将牌横置的角色都成为该牌的目标，结算后重置这些角色的武将牌",

	["zhujianping"] = "朱建平",
	["bianxiang"] = "变相",
	[":bianxiang"] = "回合开始阶段，可以使用技能“英魂”；判定阶段，可以使用技能“鬼才”；摸牌阶段，若你没有手牌，可以使用技能“英姿”；出牌阶段，若你未受伤，可以使用技能“挑衅”；弃牌阶段，可以使用技能“琴音”；回合结束阶段，若你手牌数小于当前体力，可以使用技能“据守”。每技能每阶段限一次",
	["tiaoxin_clone"] = "挑衅",

	["cv:zhouxuan"] = "",
	["cv:zhujianping"] = "",
	["cv:guanlu"] = "",
	["cv:dukui"] = "",
}

local techer = {"zhouxuan", "zhujianping", "guanlu", "dukui"}

for _, player in ipairs(techer) do
	te["designer:" .. player] = te["designer:technology"]
end

return te
