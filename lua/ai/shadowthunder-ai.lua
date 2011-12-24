
--tongmou
local tongmou_skill={}
tongmou_skill.name="tongmou"
table.insert(sgs.ai_skills,tongmou_skill)
tongmou_skill.getTurnUseCard=function(self)
	if not self.player:hasUsed("TongmouCard") then
		return sgs.Card_Parse("@TongmouCard=.")
	end
end

sgs.ai_skill_use_func["TongmouCard"]=function(card, use, self)
	local targets = self.room:getOtherPlayers(self.player)
	local target
	local target_num = 0
	for _, player in sgs.qlist(targets) do
		if self:isEnemy(player) then
			if player:getHandcardNum() > target_num then
				target = player
				target_num = player:getHandcardNum()
			end
		end
	end

	if target then
		if use.to then
			use.to:append(target)
		end
		use.card = card
	end
end

sgs.ai_skill_invoke.tongmou = function(self, card_ids, refusable)
	local cards = {}
	for _, card_id in ipairs(card_ids) do
		local card = sgs.Sanguosha:getCard(card_id)
		table.insert(cards, card)
	end

	self:sortByUseValue(cards, true)

	return cards[1]:getEffectiveId()
end

-- jinguo
sgs.ai_skill_invoke.jinguo= function(self, data)
	local effect = data:toSlashEffect()
	return not self:isFriend(effect.to)
end

-- madai
sgs.ai_skill_invoke.zhuiji = function(self, data)
	local damage = data:toDamage()
	return self:isEnemy(damage.to)
end

-- lvlingqi
sgs.ai_skill_invoke.jichi = function(self, data)
	local effect = data:toSlashEffect()
	return not self:isFriend(effect.to) or (self:hasSkills(sgs.lose_equip_skill,effect.to) and not effect.to:getEquips():isEmpty())
end

-- caijian
sgs.ai_skill_invoke.caijian= true

-- fuji
local fuji_skill={}
fuji_skill.name="fuji"
table.insert(sgs.ai_skills,fuji_skill)
fuji_skill.getTurnUseCard=function(self)
	local cards = self.player:getHandcards()
	local basics = {}
	for _, card in sgs.qlist(cards) do
		if card:getTypeId() == sgs.Card_Basic then
			table.insert(basics, card)
		end
	end

	if #basics == 0 or self.player:hasUsed("FujiCard") then return end
	self:sortByUseValue(basics, true)

	local card_str = ("@FujiCard=%d"):format(basics[1]:getEffectiveId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["FujiCard"]=function(card,use,self)
	for _, enemy in ipairs(self.enemies) do
			use.card=card
			if use.to then use.to:append(enemy) end
			return
	end
end

-- zhongyan
local zhongyan_skill={}
zhongyan_skill.name="zhongyan"
table.insert(sgs.ai_skills,zhongyan_skill)
zhongyan_skill.getTurnUseCard=function(self)
	local cards = self.player:getHandcards()
	local tricks = {}
	for _, card in sgs.qlist(cards) do
		if card:getTypeId() == sgs.Card_Trick then
			table.insert(tricks, card)
		end
	end

	if #tricks == 0 or self.player:hasUsed("ZhongyanCard") then return end
	self:sortByUseValue(tricks, true)

	local card_str = ("@ZhongyanCard=%d"):format(tricks[1]:getEffectiveId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["ZhongyanCard"]=function(card,use,self)
	for _, enemy in ipairs(self.enemies) do
			use.card=card
			if use.to then use.to:append(enemy) end
			return
	end
end

--xiance
local xiance_skill={}
xiance_skill.name="xiance"
table.insert(sgs.ai_skills, xiance_skill)
xiance_skill.getTurnUseCard = function(self)
	local cards = self.player:getHandcards()
	local tricks = {}
	for _, card in sgs.qlist(cards) do
		if card:getTypeId() == sgs.Card_Trick then
			table.insert(tricks, card)
		end
	end

	if #tricks == 0 then return end
	self:sortByUseValue(tricks, true)

	local card_str = ("@XianceCard=%d"):format(tricks[1]:getEffectiveId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["XianceCard"] = function(card, use, self)
	for _, friend in pairs(self.friends_noself) do
			use.card=card
			if use.to then use.to:append(friend) end
			return
	end
end

-- yuanjun
local yuanjun_skill={}
yuanjun_skill.name="yuanjun"
table.insert(sgs.ai_skills,yuanjun_skill)
yuanjun_skill.getTurnUseCard=function(self)
	if self.player:isKongcheng() then return end
    if self.player:hasUsed("YuanjunCard") then return end

	local cards = self.player:getHandcards()
	cards=sgs.QList2Table(cards)

	self:sortByKeepValue(cards)

	local card_str = ("@YuanjunCard=%d"):format(cards[1]:getId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["YuanjunCard"]=function(card,use,self)
	for _, friend in ipairs(self.friends_noself) do
			use.card=card
			if use.to then use.to:append(friend) end
			return
	end
end

-- baichu
sgs.ai_skill_invoke.baichu= true

sgs.ai_skill_playerchosen.baichu = function(self, targets)
if self.player:hasSkill("wuyan") then return end
	for _, player in sgs.qlist(targets) do
		if (not player:isKongcheng() or not player:getEquips().isEmpty()) and self:isEnemy(player) then
			return player
		end
	end
end

-- baichu
local baichu_skill={}
baichu_skill.name="baichu"
table.insert(sgs.ai_skills,baichu_skill)
baichu_skill.getTurnUseCard=function(self)
	if not self.player:getPile("ji"):isEmpty() then return end

	local cards = self.player:getHandcards()
	local jis = {}
	for _, card in sgs.qlist(cards) do
		if card:getSuit() ~= sgs.Card_Heart and not card:inherits("Peach") and not card:inherits("Analeptic") then
			table.insert(jis, card)
		end
	end

	if #jis == 0 then return end
	self:sortByUseValue(jis, true)

	local card_str = ("@BaichuCard=%d"):format(jis[1]:getEffectiveId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["BaichuCard"]=function(card,use,self)
	use.card = card
end

-- fuhuo
sgs.ai_skill_invoke.fuhuo= true

-- fuhuo
local fuhuo_skill={}
fuhuo_skill.name="fuhuo"
table.insert(sgs.ai_skills,fuhuo_skill)
fuhuo_skill.getTurnUseCard=function(self)
	if not self.player:getPile("xianjing"):isEmpty() then return end

	local cards = self.player:getHandcards()
	local xians = {}
	for _, card in sgs.qlist(cards) do
		if card:getSuit() ~= sgs.Card_Heart and not card:inherits("Peach") and not card:inherits("Analeptic") then
			table.insert(xians, card)
		end
	end

	if #xians == 0 then return end
	self:sortByUseValue(xians, true)

	local card_str = ("@FuhuoCard=%d"):format(xians[1]:getEffectiveId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["FuhuoCard"]=function(card,use,self)
	use.card = card
end
