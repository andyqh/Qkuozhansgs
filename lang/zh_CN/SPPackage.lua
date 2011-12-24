-- translation for SP Package

return {
	["sp"] = "SP",

	--杨修
	["yangxiu"] = "杨修",
	["jilei"] = "鸡肋",
	[":jilei"] = "当你受到伤害时，说出一种牌的类别（基本牌、锦囊牌、装备牌），对你造成伤害的角色不能使用、打出或弃掉该类别的手牌直到回合结束。\
	◆弃牌阶段，若仅剩不可弃的手牌且超出手牌上限时，该角色需展示其手牌。\
	◆例：若指定的是装备牌，此时该角色2点体力，同时手里有两张【闪】和三张装备牌，弃牌阶段，该角色必须把两张【闪】弃掉，然后该角色展示这三张装备牌，结束他的回合。",
	["danlao"] = "啖酪",
	[":danlao"] = "当一个锦囊指定了不止一个目标，且你也是其中之一时，你可以立即摸一张牌，若如此做，跳过该锦囊对你的结算。",
	["jilei:basic"] = "基本牌",
	["jilei:equip"] = "装备牌",
	["jilei:trick"] = "锦囊牌",
	["#Jilei"] = "%from <font color='yellow'><b>【鸡肋】</b></font>了 %to 的 %arg ",
	["#JileiClear"] = "%from 的<font color='yellow'><b>【鸡肋】</b></font>效果消失",
	["#DanlaoAvoid"] = "%from 发动了技能<font color='yellow'><b>【啖酪】</b></font>，跳过了锦囊 %arg 对他的结算",

	--SP关羽
	["sp_guanyu"] = "SP关羽",
	["danji"] = "单骑",
	[":danji"] = "<b>觉醒技</b>，回合开始阶段，若你的手牌数大于你当前的体力值，且本局主公为曹操时，你须减1点体力上限并永久获得技能“马术”。",
	["#DanjiWake"] = "%from 的手牌数（%arg）多于体力值（%arg2）且本局主公为曹操，觉醒技<font color='yellow'><b>【单骑】</b></font>被触发",
	["yuesanshi"] = "约三事",
	[":yuesanshi"] = "<b>限定技</b>，游戏开始时，你可以选择变身为SP关羽，势力为魏",

	--SP庞德
	["sp_pangde"] = "SP庞德",
        ["taichen"] = "抬榇",
	[":taichen"] = "出牌阶段，你可以自减1点体力或弃一张武器牌，弃掉你攻击范围内的一名角色处（手牌、装备区、判定区）的两张牌，每回合中，你可以多次使用抬榇",
	["$taichen"] = "良将不惧死以苟免，烈士不毁节以求生",
	["~sp_pangde"] = "吾宁死于刀下，岂降汝乎",

	--SP贾诩
	["sp_jiaxu"] = "SP贾诩",
	["guiwei"] = "归魏",
	[":guiwei"] = "<b>限定技</b>，游戏开始时，你可以选择变身为SP贾诩，势力为魏。",

	--SP马超
	["sp_machao"] = "SP马超",
	["fanqun"] = "返群",
	[":fanqun"] = "<b>限定技</b>，游戏开始时，你可以选择变身为SP马超，势力为群",

	--SP姜维
	["sp_jiangwei"] = "SP姜维",
	["qiliner"] = "麒麟儿",
	[":qiliner"] = "<b>限定技</b>，游戏开始时，你可以选择变身为SP姜维，势力为魏",

	--SP蔡文姬
	["sp_caiwenji"] = "SP蔡文姬",
	["guixiang"] = "归乡",
	[":guixiang"] = "<b>限定技</b>，游戏开始时，你可以选择变身为SP蔡文姬，势力为魏",

	--SP孙尚香
	["sp_sunshangxiang"] = "SP孙尚香",
	["chujia"] = "出嫁",
	[":chujia"] = "<b>限定技<b>, 游戏开始时，你可以选择变身为SP孙尚香，势力为蜀",

	--公孙瓒
	["gongsunzan"] = "公孙瓒",
	["yicong"] = "义从",
	[":yicong"] = "<b>锁定技</b>，只要你的体力值大于2点，你计算与其他角色的距离时，始终-1；只要你的体力值为2点或更低，其他角色计算与你的距离时，始终+1。",
	["#YicongAttack"] = "%from 的锁定技<font color='yellow'><b>【义从】</b></font>被触发，与其它角色计算距离时始终<font color='yellow'><b> -1</b></font>",--，%arg
	["#YicongDefend"] = "%from 的锁定技<font color='yellow'><b>【义从】</b></font>被触发，其它角色与之计算距离时始终<font color='yellow'><b> +1</b></font>",--，%arg

	--袁术
	["yuanshu"] = "袁术",
	["yongsi"] = "庸肆",
	[":yongsi"] = "<b>锁定技</b>，摸牌阶段，你额外摸X张牌，X为场上现存势力数。弃牌阶段，你需要弃掉至少等同于场上现存势力数的牌（不足则全弃）。",
	["weidi"] = "伪帝",
	[":weidi"] = "<b>锁定技</b>，你视为拥有当前主公的主公技。",
	["#YongsiGood"] = "%from 的锁定技<font color='yellow'><b>【庸肆】</b></font>被触发，额外摸了 %arg 张牌",
	["#YongsiBad"] = "%from 的锁定技<font color='yellow'><b>【庸肆】</b></font>被触发，必须弃掉至少 %arg 张牌",
	["#YongsiWorst"] = "%from 的锁定技<font color='yellow'><b>【庸肆】</b></font>被触发，弃掉了所有的装备和手牌（共 %arg 张）",

	--SP貂蝉
	["sp_diaochan"] = "SP貂蝉",
	["xuwei"] = "续尾",
	[":xuwei"] = "狗尾续貂，变身为原版貂蝉，每回合限一次。",
	["muyu"] = "沐浴",
	[":muyu"] = "<b>限定技</b>，游戏开始时，你可以选择变身为SP貂蝉，势力不改变。",

	--SP司马懿
	["sp_simayi"] = "SP司马懿",
	["zhulu"] = "逐鹿",
	[":zhulu"] = "<b>限定技<b>, 游戏开始时，你可以选择变身为SP司马懿，势力不改变。",

	--sp_card
	["sp_cards"] = "SP卡牌包",
	["sp_moonspear"] = "SP银月枪",
	[":sp_moonspear"] = "你的回合外，若打出了一张黑色的牌，你可以立即指定攻击范围内的一名角色打出一张【闪】，否则受到你对其造成的1点伤害",
	["@moon-spear-jink"] = "受到SP银月枪技能的影响，你必须打出一张【闪】",

	--虎牢关 神·吕布
	["shenlvbu1"] = "神·吕布·最强神话",
	["shenlvbu2"] = "神·吕布·暴怒的战神",
	["xiuluo"] = "修罗",
	[":xiuluo"] = "回合开始阶段，你可以弃一张手牌来弃置你判定区里的一张延时类锦囊（必须花色相同）。",
	["shenwei"] = "神威",
	[":shenwei"] = "<b>锁定技</b>，摸牌阶段，你额外摸两张牌；你的手牌上限+2。",
	["shenji"] = "神戟",
	[":shenji"] = "没装备武器时，你使用的杀可指定至多3名角色为目标。",
	["@xiuluo"] = "请弃掉一张与指定判定牌花色相同的手牌来将此判定牌弃置",

	["#Reforming"] = "%from 进入重整状态",
	["#ReformingRecover"] = "%from 在重整状态中<font color='#98fb98'><b>回复了 1 点体力</b></font>",
	["#ReformingRevive"] = "%from 重整完毕，回到战场",
	["draw_1v3"] = "重整摸牌",
	["weapon_recast"] = "武器重铸",
	["hulaopass"] = "虎牢关模式",

	--杨修
	["$jilei"] = "食之无味，弃之可惜。",
	["$jilei1"] = "食之无肉，弃之有味。",
	["$jilei2"] = "曹公之意，我已了然。",
	["$danlao"] = "一人一口，分而食之。",
	["$danlao1"] = "我喜欢～",
	["$danlao2"] = "来来，一人一口～",

	--SP关羽
	["$danji"] = "",

	--SP庞德（同原庞德）

	--SP孙尚香（同原孙尚香）

	--公孙瓒
	["$yicong1"] = "冲啊！",
	["$yicong2"] = "众将听令，摆好阵势，御敌！",

	--袁术
	["$yongsi1"] = "玉玺在手，天下我有！",
	["$yongsi2"] = "大汉天下已半入我手！",
	["$weidi1"] = "我才是皇帝！",
	["$weidi2"] = "你们都得听我的号令！",

	--SP貂蝉（同原貂蝉）

	--虎牢关 神·吕布
	["$xiuluo"] = "神挡杀神，佛挡杀佛！",
	["$shenwei"] = "挡我者死！",
	["$shenji"] = "神挡杀神，佛挡杀佛！",

	--武将阵亡台词
	["~yangxiu"] = "我故自已死之晚也。",
	["~sp_jiangwei"] = "SP姜维·阵亡",
	["~sp_machao"] = "（马蹄声）",
	["~sp_simayi"] = "难道真是天命难违？",
	["~sp_caiwenji"] = "SP蔡文姬·阵亡",
	["~sp_guanyu"] = "什么？此地名叫麦城？",
	["~sp_pangde"] = "四面都是水，我命休矣……",
	["~sp_sunshangxiang"] = "不，还不可以死……",
	["~gongsunzan"] = "我军将败，我已无颜苟活于世。",
	["~yuanshu"] = "可恶，就差一步了……",
	["~sp_diaochan"] = "父亲大人，对不起……",
	["~shenlvbu1"] = "看我杀你们个片甲不留！",
	["~shenlvbu2"] = "呃，不可能！",

	["designer:sp_jiangwei"] = "非官方出品",
	["designer:sp_simayi"] = "非官方出品",
}
