-- translation for StandardPackage

local t = {
	["standard_cards"] = "标准卡牌包",
	["standard_ex_cards"] = "标准EX卡牌包",
	["attack_card"] = "进攻牌", 
	["defense_card"] = "防御牌", 
	["recover_card"] = "恢复牌", 
	["disgusting_card"] = "恶心牌", 
	["global_effect"] = "全局效果", 
	["aoe"] = "范围效果", 
	["single_target_trick"] = "单体锦囊", 
	["delayed_trick"] = "延时锦囊", 
	["weapon"] = "武器", 
	["armor"] = "防具", 
	["defensive_horse"] = "防御马", 
	["offensive_horse"] = "进攻马", 
	["slash"] = "杀", 
	["jink"] = "闪", 
	["peach"] = "桃", 
	["crossbow"] = "诸葛连弩", 
	["double_sword"] = "雌雄双股剑", 
	["qinggang_sword"] = "青釭剑", 
	["blade"] = "青龙偃月刀", 
	["spear"] = "丈八蛇矛", 
	["axe"] = "贯石斧", 
	["halberd"] = "方天画戟", 
	["kylin_bow"] = "麒麟弓", 
	["eight_diagram"] = "八卦阵", 
	["renwang_shield"] = "仁王盾", 
	["horse"] = "马",
	["ice_sword"] = "寒冰剑", 
	["jueying"] = "绝影", 
	["dilu"] = "的卢", 
	["zhuahuangfeidian"] = "爪黄飞电", 
	["chitu"] = "赤兔", 
	["dayuan"] = "大宛", 
	["zixing"] = "紫骍", 
	["amazing_grace"] = "五谷丰登", 
	["god_salvation"] = "桃园结义", 
	["savage_assault"] = "南蛮入侵", 
	["archery_attack"] = "万箭齐发", 
	["collateral"] = "借刀杀人", 
	["duel"] = "决斗", 
	["ex_nihilo"] = "无中生有", 
	["snatch"] = "顺手牵羊", 
	["dismantlement"] = "过河拆桥", 
	["nullification"] = "无懈可击", 
	["indulgence"] = "乐不思蜀", 
	["lightning"] = "闪电", 
	["eight_diagram:yes"] = "进行一次判定，若判定结果为红色，则视为你打出了一张【闪】", 
	["slash-jink"] = "%src 使用了【杀】，请打出一张【闪】", 
	["duel-slash"] = "%src 向您决斗，您需要打出一张【杀】", 
	["savage-assault-slash"] = "%src 使用了【南蛮入侵】，请打出一张【杀】来响应", 
	["archery-attack-jink"] = "%src 使用了【万箭齐发】，请打出一张【闪】以响应", 
	["collateral-slash"] = "%src 使用了【借刀杀人】，目标是 %dest，请打出一张【杀】以响应", 
	["blade-slash"] = "您可以再打出一张【杀】发动青龙偃月刀的追杀效果", 
	["double-sword-card"] = "%src 发动了雌雄双股剑特效，您必须弃一张手牌或让 %src 摸一张牌", 
	["@axe"] = "你可再弃两张牌（包括装备）使此杀强制命中", 
	["double_sword:yes"] = "您可以让对方选择自弃一牌或让您摸一张牌", 
	["ice_sword:yes"] = "您可以弃掉其两张牌", 
	["kylin_bow:yes"] = "弃置对方的一匹马", 
	["kylin_bow:dhorse"] = "防御马(+1马)", 
	["kylin_bow:ohorse"] = "进攻马(-1马)", 
	["#Slash"] = "%from 对 %to 使用了【杀】", 
	["#Jink"] = "%from 使用了【闪】", 
	["#AxeSkill"] = "%from 使用了贯石斧的技能，弃掉了2张牌以对 %to 强制命中", 
	[":slash"] = "出牌时机：出牌阶段\
使用目标：除你外，你攻击范围内的一名角色\
作用效果：【杀】对目标角色造成1点伤害", 
	[":jink"] = "出牌时机：以你为目标的【杀】开始结算时\
使用目标：以你为目标的【杀】\
作用效果：抵消目标【杀】的效果", 
	[":peach"] = "出牌时机：1、出牌阶段。2、有角色处于濒死状态时\
使用目标：1、你。2、处于濒死状态的一名角色\
作用效果：目标角色回复1点体力", 
	[":duel"] = "出牌时机：出牌阶段\
使用目标：除你以外，任意一名角色\
作用效果：由目标角色先开始，你和他（她）轮流打出一张【杀】，【决斗】对首先不出【杀】的一方造成1点伤害；另一方成为此伤害的来源", 
	[":dismantlement"] = "出牌时机：出牌阶段。\
使用目标：除你以外，任意一名角色。\
作用效果：你选择并弃掉目标角色手牌（随机选择）、装备区或判定区里的一张牌", 
	[":snatch"] = "出牌时机：出牌阶段。\
使用目标：除你以外，与你距离1以内的一名角色。\
作用效果：你选择并获得目标角色手牌（随机选择）、装备区或判定区里的一张牌", 
	[":archery_attack"] = "出牌时机：出牌阶段。\
使用目标：除你以外的所有角色。\
作用效果：按行动顺序结算，除非目标角色打出1张【闪】，否则该角色受到【万箭齐发】对其造成的1点伤害", 
	[":savage_assault"] = "出牌时机：出牌阶段。\
使用目标：除你以外的所有角色。\
作用效果：按行动顺序结算，除非目标角色打出1张【杀】，否则该角色受到【南蛮入侵】对其造成的1点伤害", 
	[":god_salvation"] = "出牌时机：出牌阶段。\
使用目标：所有角色。\
作用效果：按行动顺序结算，目标角色回复1点体力", 
	[":ex_nihilo"] = "出牌时机：出牌阶段。\
使用目标：你。\
作用效果：摸两张牌", 
	[":amazing_grace"] = "出牌时机：出牌阶段。\
使用目标：所有角色。\
作用效果：按你从牌堆顶亮出等同于现存角色数量的牌，然后按行动顺序结算，目标角色选择并获得这些牌中的一张", 
	[":collateral"] = "出牌时机：出牌阶段。\
使用目标：除你以外，装备区里有武器牌的一名角色A。（你需要在此阶段选择另一个A使用【杀】能攻击到的角色B）。\
作用效果：A需对B使用一张【杀】，否则A必须将其装备的武器牌交给你", 
	[":indulgence"] = "出牌时机：出牌阶段。\
使用目标：除你以外，任意一名角色。\
作用效果：将【乐不思蜀】横置于目标角色判定区里，目标角色回合判定阶段，进行判定；若判定结果不为红桃，则跳过目标角色的出牌结算，将【乐不思蜀】弃置", 
	[":lightning"] = "【闪电】出牌时机：出牌阶段。\
使用目标：你。\
作用效果：将【闪电】横置于目标角色判定区里，目标角色回合判定阶段，进行判定；若判定结果为黑桃2-9之间（包括黑桃2和9），则【闪电】对目标角色造成3点伤害，将闪电弃置。若判定结果不为黑桃2-9之间（包括黑桃2和9），将【闪电】移动到当前目标角色下家（【闪电】的目标变为该角色）的判定区", 
	[":nullification"] = "出牌时机：目标锦囊对目标角色生效前。\
使用目标：目标锦囊。\
作用效果：抵消该锦囊对其指定的一名目标角色产生的效果", 
	[":crossbow"] = "攻击范围：１\
武器特效：出牌阶段，你可以使用任意张【杀】", 
	[":double_sword"] = "攻击范围：２\
武器特效：你使用【杀】时，指定了一名异性角色后，在【杀】结算前，你可以令对方选择一项：自己弃一张手牌或者让你从牌堆摸一张牌", 
	[":ice_sword"] = "攻击范围：２\
武器特效：当你使用【杀】造成伤害时，你可以防止此伤害，改为弃置该目标角色的两张牌（弃完第一张再弃第二张）", 
	[":qinggang_sword"] = "【青釭剑】攻击范围：２\
武器特效：锁定技，每当你使用【杀】时，无视目标角色的防具", 
	[":blade"] = "攻击范围：３\
武器特效：当你使用的【杀】被【闪】抵消时，你可以立即对相同的目标再使用一张【杀】直到【杀】生效或你不愿意出了为止", 
	[":spear"] = "攻击范围：３\
武器特效：当你需要使用（或打出）一张【杀】时，你可以将两张手牌当一张【杀】使用（或打出）", 
	[":axe"] = "攻击范围：３\
武器特效：目标角色使用【闪】抵消你使用【杀】的效果时，你可以弃两张牌，则【杀】依然造成伤害", 
	[":halberd"] = "【方天画戟】攻击范围：４\
武器特效：当你使用的【杀】是你的最后一张手牌时，你可以为这张【杀】指定至多三名目标角色，然后按行动顺序依次结算之", 
	[":kylin_bow"] = "攻击范围：５\
武器特效：你使用【杀】对目标角色造成伤害时，你可以将其装备区里的一匹马弃置", 
	[":eight_diagram"] = "防具效果：每当你需要使用（或打出）一张【闪】时，你可以进行一次判定：若结果为红色，则视为你使用（或打出）了一张【闪】；若为黑色，则你仍可从手牌里使用（或打出）。\
★由八卦使用或打出的【闪】，并非从你的手牌中使用或打出", 
	[":renwang_shield"] = "防具效果：锁定技，黑色的【杀】对你无效", 
	[":-1 horse"] = "你计算与其他角色的距离时，始终-1。（你可以理解为一种进攻上的优势）不同名称的-1马，其效果是相同的", 
	[":+1 horse"] = "其他角色计算与你的距离时，始终+1。（你可以理解为一种防御上的优势）不同名称的+1马，其效果是相同的",

	["standard"] = "标准版", 

	["caocao"] = "曹操",
	["jianxiong"] = "奸雄",
	[":jianxiong"] = "你可以立即获得对你造成伤害的牌。",
	["jianxiong:yes"] = "立即获得使你受到伤害的那张牌",
	["hujia"] = "护驾",
	[":hujia"] = "<b>主公技</b>，当你需要使用（或打出）一张【闪】时，你可以发动护驾。所有魏势力角色按行动顺序依次选择是否打出一张【闪】提供给你（视为由你使用或打出），直到有一名角色或没有任何角色决定如此做时为止。",
	["hujia:yes"] = "所有魏势力角色按行动顺序依次选择是否打出一张【闪】提供给你（视为由你使用或打出），直到有一名角色或没有任何角色决定如此做时为止",
	[":hujia:"] = "%from 想让你帮他出一张【闪】：",
	["hujia:accept"] = "帮他护驾",
	["hujia:ignore"] = "拒绝护驾",
	["@hujia-jink"] = "请打出一张【闪】以响应【护驾】",

	["zhangliao"] = "张辽",
	["tuxi"] = "突袭",
	[":tuxi"] = "摸牌阶段，你可以放弃摸牌，然后从至多两名（至少一名）角色的手牌里各抽取一张牌。",
	["@tuxi-card"] = "你是否想发动【突袭】技能",

	["guojia"] = "郭嘉",
	["tiandu"] = "天妒",
	[":tiandu"] = "在你的判定牌生效后，你可以立即获得它。",
	["yiji"] = "遗计",
	[":yiji"] = "你每受到1点伤害，可摸两张牌，将其中的一张交给任意一名角色，然后将另一张交给任意一名角色。",
	["tiandu:yes"] = "拿屎",
	["tiandu:no"] = "不拿屎",

	["xiahoudun"] = "夏侯惇",
	["ganglie"] = "刚烈",
	[":ganglie"] = "你每受到一次伤害，可进行一次判定：若结果不为红桃，则伤害来源必须进行二选一：弃两张手牌或受到你对其造成的1点伤害。",
	["ganglie:yes"] = "进行一次判定，如判定结果不为红桃，可令伤害来源受到你对其的一点无属性伤害或弃两张手牌",

	["simayi"] = "司马懿",
	["fankui"] = "反馈",
	[":fankui"] = "你可以立即从对你造成伤害的来源处获得一张牌。\	◆一次无论受到多少点伤害，只能获得一张牌，若选择手牌则从对方手里随机抽取，选择面前的装备则由你任选。",
	["guicai"] = "鬼才",
	[":guicai"] = "在任意角色的判定牌生效前，你可以打出一张手牌代替之。",
	["fankui:yes"] = "你将获得伤害来源的一张手牌或装备牌。",
	["@guicai-card"] = "请使用【鬼才】修改 %src 的 %arg 判定",

	["xuchu"] = "许褚",
	["luoyi"] = "裸衣",
	[":luoyi"] = "摸牌阶段，你可以少摸一张牌；若如此做，该回合的出牌阶段，你使用【杀】或【决斗】（你为伤害来源时）造成的伤害+1。",
	["luoyi:yes"] = "本回合你的【杀】和【决斗】对别人造成的伤害都+1",
	["#LuoyiBuff"] = "%from 的<font color='yellow'><b>【裸衣】</b></font>效果被触发，伤害从 %arg 点上升至 %arg2 点",

	["zhenji"] = "甄姬",
	["luoshen"] = "洛神",
	[":luoshen"] = "回合开始阶段，你可以进行判定：若为黑色，立即获得此生效后的判定牌，并可以再次使用洛神――如此反复，直到出现红色或你不愿意判定了为止。",
	["qingguo"] = "倾国",
	[":qingguo"] = "你可以将你的黑色手牌当【闪】使用（或打出）。\
	◆使用【倾国】时，仅改变牌的类别（名称）和作用，而牌的花色和点数不变。",

	["liubei"] = "刘备",
	["rende"] = "仁德",
	[":rende"] = "出牌阶段，你可以将任意数量的手牌以任意分配方式交给其他角色，若你给出的牌张数不少于两张时，你回复1点体力。\
	◆使用【仁德】分出的牌，对方无法拒绝。",
	["jijiang"] = "激将",
	[":jijiang"] = "<b>主公技</b>，当你需要使用（或打出）一张【杀】时，你可以发动激将。所有蜀势力角色按行动顺序依次选择是否打出一张【杀】提供给你（视为由你使用或打出），直到有一名角色或没有任何角色决定如此作时为止。",
	[":jijiang:"] = "%from 想让你帮其出一张【杀】：",
	["jijiang:accept"] = "响应激将",
	["jijiang:ignore"] = "拒绝响应",
	["@jijiang-slash"] = "请打出一张【杀】以响应【激将】",

	["guanyu"] = "关羽",
	["wusheng"] = "武圣",
	[":wusheng"] = "你可以将你的任意一张红色牌当【杀】使用或打出。\
	◆若同时用到当前装备的红色装备效果时，不可把这张装备牌当【杀】来使用或打出。\
	◆使用【武圣】时，仅改变牌的类别（名称）和作用，而牌的花色和点数不变。",

	["zhangfei"] = "张飞",
	["paoxiao"] = "咆哮",
	[":paoxiao"] = "出牌阶段，你可以使用任意数量的【杀】。",

	["zhaoyun"] = "赵云",
	["longdan"] = "龙胆",
	[":longdan"] = "你可以将你手牌的【杀】当【闪】、【闪】当【杀】使用或打出。\
	◆使用【龙胆】时，仅改变牌的类别（名称）和作用，而牌的花色和点数不变。",

	["machao"] = "马超",
	["tieji"] = "铁骑",
	[":tieji"] = "当你使用【杀】指定一名角色为目标后，你可以进行判定，若结果为红色，此【杀】不可被闪避。",
	["mashu"] = "马术",
	[":mashu"] = "<b>锁定技</b>，当你计算与其他角色的距离时，始终-1。\
	◆【马术】的效果与装备-1马时效果一样，但你仍然可以装备一匹-1马，此时二者效果叠加。",
	["tieji:yes"] = "可以进行一次判定，若判定结果为红色，则此【杀】不可被闪避",

	["zhugeliang"] = "诸葛亮",
	["guanxing"] = "观星",
	[":guanxing"] = "回合开始阶段，你可以观看牌堆顶的X张牌（X为存活角色的数量且最多为5），将其中任意数量的牌以任意顺序置于牌堆顶，其余以任意顺序置于牌堆底。",
	["kongcheng"] = "空城",
	[":kongcheng"] = "<b>锁定技</b>，当你没有手牌时，你不能成为【杀】或【决斗】的目标。",
	["#GuanxingResult"] = "%from 的<font color='yellow'><b>【观星】</b></font>结果：%arg 张置于牌堆顶，%arg2 张置于牌堆底",

	["huangyueying"] = "黄月英",
	["jizhi"] = "集智",
	[":jizhi"] = "每当你使用一张非延时类锦囊时，（在它结算之前）你可以立即摸一张牌。",
	["qicai"] = "奇才",
	[":qicai"] = "你使用任何锦囊无距离限制。",

	["sunquan"] = "孙权",
	["zhiheng"] = "制衡",
	[":zhiheng"] = "出牌阶段，你可以弃掉任意数量的牌，然后摸取等量的牌，每回合限一次。",
	["jiuyuan"] = "救援",
	[":jiuyuan"] = "<b>主公技</b>，<b>锁定技</b>，其他吴势力角色在你濒死状态下对你使用【桃】时，你额外回复1点体力。",
	["#JiuyuanExtraRecover"] = "%from 的锁定技<font color='yellow'><b>【救援】</b></font>被触发，额外回复 <font color='#98fb98'>１</font> 点体力",

	["zhouyu"] = "周瑜",
	["yingzi"] = "英姿",
	[":yingzi"] = "摸牌阶段，你可以额外摸一张牌。",
	["fanjian"] = "反间",
	[":fanjian"] = "出牌阶段，你可以指定一名其他角色，该角色选择一种花色后获得你的一张手牌并展示之，若此牌与所选花色不同，则你对该角色造成1点伤害。每阶段限一次。",
	["yingzi:yes"] = "你可以多摸一张牌",

	["lumeng"] = "吕蒙",
	["keji"] = "克己",
	[":keji"] = "若你于出牌阶段未使用或打出过任何一张【杀】，你可以跳过此回合的弃牌阶段。",

	["luxun"] = "陆逊",
	["qianxun"] = "谦逊",
	[":qianxun"] = "<b>锁定技</b>，你不能成为【顺手牵羊】和【乐不思蜀】的目标。",
	["lianying"] = "连营",
	[":lianying"] = "每当你失去最后一张手牌时，可立即摸一张牌。",

	["ganning"] = "甘宁",
	["qixi"] = "奇袭",
	[":qixi"] = "出牌阶段，你可以将你的任意黑色牌当【过河拆桥】使用。\
	◆可以使用自己已装备的牌。\
	◆使用【奇袭】时，仅改变牌的类别（名称）和作用，而牌的花色和点数不变。",

	["huanggai"] = "黄盖",
	["kurou"] = "苦肉",
	[":kurou"] = "出牌阶段，你可以失去一点体力，然后摸两张牌。回合内，你可以多次使用苦肉。\
	◆当你失去最后一点体力时，优先结算濒死事件，当你被救活后，你才可以摸两张牌。换言之，你可以用此技能自杀。",

	["daqiao"] = "大乔",
	["guose"] = "国色",
	[":guose"] = "出牌阶段，你可以将你的任意方块花色的牌当【乐不思蜀】使用。",
	["liuli"] = "流离",
	[":liuli"] = "当你成为【杀】的目标时，你可以弃一张牌，并将此【杀】转移给你攻击范围内的另一名角色（该角色不得是【杀】的使用者）。",
	["@liuli"] = "%src 对你出【杀】，你可以发动【流离】弃一张牌将其转给你能攻击到的另一名角色（除了%src）",

	["sunshangxiang"] = "孙尚香",
	["jieyin"] = "结姻",
	[":jieyin"] = "出牌阶段，你可以弃两张手牌并选择一名受伤的男性角色：你和目标角色各回复1点体力。每回合限用一次。\
	◆使用【结姻】的条件是场上有受伤的男性角色，与你自己是否受伤无关。",
	["xiaoji"] = "枭姬",
	[":xiaoji"] = "当你失去一张装备区里的牌时，你可以立即摸两张牌。",

	["lubu"] = "吕布",
	["wushuang"] = "无双",
	[":wushuang"] = "<b>锁定技</b>，你使用【杀】时，目标角色需连续使用两张【闪】才能抵消；与你进行【决斗】的角色每次需连续打出两张【杀】。\
	◆若对方只有一张【闪】或【杀】则即便使用（打出）了也无效。",
	["@wushuang-slash-1"] = "%src 向你决斗，由于他有【无双】技能，你必须打出两张【杀】",
	["@wushuang-slash-2"] = "%src 的决斗有【无双】效果，请再打出一张【杀】",
	["@wushuang-jink-1"] = "%src 拥有【无双】技能，你必须连续出两张【闪】",
	["@wushuang-jink-2"] = "%src 拥有【无双】技能，你还需出一张【闪】",

	["huatuo"] = "华佗",
	["qingnang"] = "青囊",
	[":qingnang"] = "出牌阶段，你可以主动弃掉一张手牌，令任一目标角色回复1点体力。每回合限用一次。",
	["jijiu"] = "急救",
	[":jijiu"] = "你的回合外，你可以将你的任意红色牌当【桃】使用。",

	["diaochan"] = "貂蝉",
	["tuoqiao"] = "脱壳",
	[":tuoqiao"] = "金蝉脱壳，变身为SP貂蝉，每回合限一次。",
	["lijian"] = "离间",
	[":lijian"] = "出牌阶段，你可以弃一张牌并选择两名男性角色。若如此作，视为其中一名男性角色对另一名男性角色使用一张【决斗】（此【决斗】不能被【无懈可击】响应），每回合限用一次。",
	["biyue"] = "闭月",
	[":biyue"] = "回合结束阶段，可以摸一张牌。",
	["biyue:yes"] = "你可以摸一张牌",

	["zhibasunquan"] = "制霸孙权",
	["wuxingzhuge"] = "五星诸葛",
	["zhiba"] = "制霸",
	[":zhiba"] = "出牌阶段，你可以弃置任意数量的牌，然后摸取等量的牌。每回合可用X+1次，X为你已损失的体力值。",
	["super_guanxing"] = "超级观星",
	[":super_guanxing"] = "回合开始阶段，你可以观看牌堆顶的5张牌，将其中任意数量的牌以任意顺序置于牌堆顶，其余则以任意顺序置于牌堆底。",

	["$jianxiong"] = "宁教我负天下人，休教天下人负我！",
	["$jianxiong1"] = "宁教我负天下人，休教天下人负我！",
	["$jianxiong2"] = "吾好梦中杀人！",
	["$hujia1"] = "魏将何在？",
	["$hujia2"] = "来人，护驾！",

	["$tuxi"] = "没想到吧！",
	["$tuxi1"] = "没想到吧！",
	["$tuxi2"] = "拿来吧！",

	["$tiandu"] = "就这样吧。",
	["$tiandu1"] = "就这样吧。",
	["$tiandu2"] = "哦？",
	["$yiji"] = "也好。",
	["$yiji1"] = "也好。",
	["$yiji2"] = "罢了。",

	["$ganglie"] = "鼠辈，竟敢伤我！",
	["$ganglie1"] = "鼠辈，竟敢伤我！",
	["$ganglie2"] = "以彼之道，还施彼身！",

	["$fankui"] = "下次注意点～",
	["$fankui1"] = "下次注意点～",
	["$fankui2"] = "出来混，早晚要还的。",
	["$guicai"] = "天命？哈哈哈哈～",
	["$guicai1"] = "天命？哈哈哈哈～",
	["$guicai2"] = "吾乃天命之子！",

	["$luoyi1"] = "破！",
	["$luoyi2"] = "谁来与我大战三百回合！",

	["$luoshen"] = "仿佛兮若轻云之蔽月，飘飘兮若流风之回雪。",
	["$luoshen1"] = "仿佛兮若轻云之蔽月。",
	["$luoshen2"] = "飘摇兮若流风之回雪。",
	["$qingguo"] = "凌波微步，罗袜生尘。",
	["$qingguo1"] = "凌波微步，罗袜生尘。",
	["$qingguo2"] = "休迅飞凫，飘忽若神。",

	["$rende1"] = "以德服人。",
	["$rende2"] = "惟贤惟德，能服于人。",
	["$jijiang1"] = "蜀将何在？",
	["$jijiang2"] = "尔等敢应战否？",

	["$wusheng1"] = "关羽在此，尔等受死！",
	["$wusheng2"] = "看尔乃插标卖首！",

    ["$paoxiao"] = "啊～",
	["$paoxiao1"] = "啊～",
	["$paoxiao2"] = "燕人张飞在此！",

	["$longdan1"] = "能进能退乃真正法器！",
	--["$longdan2"] = "喝！",
	["$longdan2"] = "吾乃常山赵子龙也！",

	["$tieji"] = "全军突击！",
	["$tieji1"] = "全军突击！",
	["$tieji2"] = "（马蹄声）",

	["$guanxing1"] = "观今夜天象，知天下大事。",
	["$guanxing2"] = "知天易，逆天难。",
	["$super_guanxing1"] = "观今夜天象，知天下大事。",
	["$super_guanxing2"] = "知天易，逆天难。",
	["$kongcheng1"] = "（抚琴声）",
	["$kongcheng2"] = "（抚琴声）",

	["$jizhi"] = "（集智）",
	["$jizhi1"] = "哼哼～",
	["$jizhi2"] = "哼～",

	["$zhiheng"] = "容我三思。",
	["$zhiheng1"] = "容我三思。",
	["$zhiheng2"] = "且慢。",
	["$jiuyuan"] = "吴将何在！",
	["$jiuyuan1"] = "有汝辅佐，甚好！",
	["$jiuyuan2"] = "好舒服啊～",

	["$yingzi1"] = "哈哈哈～",
	["$yingzi2"] = "汝等看好了！",
	["$fanjian"] = "挣扎吧，在血和暗的深渊里！",
	["$fanjian1"] = "挣扎吧，在血和暗的深渊里！",
	["$fanjian2"] = "痛苦吧，在仇与恨的地狱中！",

	["$keji1"] = "不是不报，时候未到！",
	["$keji2"] = "留得青山在，不怕没柴烧！",

	["$lianying"] = "牌不是万能的，但是没牌是万万不能的。",
	["$lianying1"] = "牌不是万能的，但是没牌是万万不能的。",
	["$lianying2"] = "旧的不去，新的不来。",

	["$qixi1"] = "接招吧。",
	["$qixi2"] = "你的牌太多啦～",

	["$kurou"] = "请鞭挞我吧 ，公瑾！",
	["$kurou1"] = "请鞭挞我吧 ，公瑾！",
	["$kurou2"] = "赴汤蹈火，在所不辞！",

	["$guose"] = "请休息吧～",
	["$guose1"] = "请休息吧～",
	["$guose2"] = "你累了～",
	["$liuli"] = "交给你了～",
	["$liuli1"] = "交给你了～",
	["$liuli1"] = "嗯哼，交给你了～",
	["$liuli2"] = "你来嘛～",

	["$jieyin"] = "夫君，身体要紧～",
	["$jieyin1"] = "夫君，身体要紧～",
	["$jieyin2"] = "他好，我也好～",
	["$xiaoji"] = "哼～",
	["$xiaoji1"] = "哼～",
	["$xiaoji2"] = "看我的厉害！",

	["$wushuang"] = "谁能挡我！",
	["$wushuang1"] = "谁能挡我！",
	["$wushuang2"] = "神挡杀神，佛挡杀佛！",

	["$qingnang1"] = "早睡早起，方能养生。",
	["$qingnang2"] = "越老越要补啊～",
	["$jijiu1"] = "别紧张，有老夫呢～",
	["$jijiu2"] = "救人一命，胜造七级浮屠。",

	["$lijian"] = "嗯哼～",
	["$lijian1"] = "嗯呵呵～呵呵～",
	["$lijian2"] = "夫君，你要替妾身做主啊～",
	["$biyue"] = "失礼了～",
	["$biyue1"] = "失礼了～",
	["$biyue2"] = "羡慕吧～",

	--武将阵亡台词
	["~caocao"] = "霸业未成，未成啊……",
	["~zhangliao"] = "真的没想到……",
	["~guojia"] = "咳，咳……",
	["~xiahoudun"] = "两边都看不见啦……",
	["~simayi"] = "难道真是天命难违？",
	["~xuchu"] = "冷，好冷啊……",
	["~zhenji"] = "悼良会之永绝兮，哀一逝而异乡。",

	["~liubei"] = "这就是桃园吗？",
	["~guanyu"] = "什么？此地名叫麦城？",
	["~zhangfei"] = "实在是杀不动啦……",
	["~zhaoyun"] = "这就是失败的滋味吗？",
	["~machao"] = "（马蹄声）",
	["~zhugeliang"] = "将星陨落，天命难违。",
	["~huangyueying"] = "亮……",

	["~sunquan"] = "父亲，大哥，仲谋愧矣……",
	["~zhouyu"] = "既生瑜，何生……",
	["~lumeng"] = "呃，被看穿了吗？",
	["~luxun"] = "我还是太年轻了……",
	["~ganning"] = "二十年后，又是一条好汉。",
	["~huanggai"] = "啊！失血过多了……",
	["~daqiao"] = "伯符，我去了……",
	["~sunshangxiang"] = "不！还不可以死！",

	["~lubu"] = "不可能！",
	["~huatuo"] = "医者不能自医啊。",
	["~diaochan"] = "父亲大人，对不起……",

	["$Dismantlement"] = "%from 被拆掉了 %card",
}

local ohorses = {"chitu", "dayuan", "zixing"}
local dhorses = {"zhuahuangfeidian", "dilu", "jueying", "hualiu"}

for _, horse in ipairs(ohorses) do
	t[":" .. horse] = t[":-1 horse"]
end

for _, horse in ipairs(dhorses) do
	t[":" .. horse] = t[":+1 horse"]
end

return t
