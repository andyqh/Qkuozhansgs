-- qishe
local qishe_skill={}
qishe_skill.name="qishe"
table.insert(sgs.ai_skills,qishe_skill)
qishe_skill.getTurnUseCard=function(self)
    if self.player:isKongcheng() then return end
	if not self.player:hasUsed("QisheCard") then
		return sgs.Card_Parse("@QisheCard=.")
	end
end

sgs.ai_skill_use_func["QisheCard"]=function(card,use,self)
	for _, enemy in ipairs(self.enemies) do
	if not enemy:isKongcheng() and self.player:inMyAttackRange(enemy) then
			use.card=card
			if use.to then use.to:append(enemy) end
			return
	   end
	end
end

-- xianming
sgs.ai_skill_invoke.xianming= true

-- xiaosi
local xiaosi_skill={}
xiaosi_skill.name="xiaosi"
table.insert(sgs.ai_skills,xiaosi_skill)
xiaosi_skill.getTurnUseCard=function(self)
	if self.player:isKongcheng() then return end
    if self.player:hasUsed("XiaosiCard") then return end

	local cards = self.player:getHandcards()
	cards=sgs.QList2Table(cards)

	self:sortByKeepValue(cards)

	local card_str = ("@XiaosiCard=%d"):format(cards[1]:getId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["XiaosiCard"]=function(card,use,self)
	for _, friend in ipairs(self.friends_noself) do
	if friend:getGeneral():isMale() then
			use.card=card
			if use.to then use.to:append(friend) end
			return
		end
	end
end

sgs.ai_skill_choice.xiaosi = function(self, choices)
	if self.player:isWounded() then return "a" end
	return "b"
end

-- juhun
sgs.ai_skill_invoke.juhun= true

-- chengshi
sgs.ai_skill_invoke.chengshi= true

-- zhenshou
local zhenshou_skill={}
zhenshou_skill.name="zhenshou"
table.insert(sgs.ai_skills,zhenshou_skill)
zhenshou_skill.getTurnUseCard=function(self)
	if not self.player:getPile("shou"):isEmpty() then return end

	local cards = self.player:getHandcards()
	local shous = {}
	for _, card in sgs.qlist(cards) do
		if card:getSuit() ~= sgs.Card_Heart and not card:inherits("Peach") and not card:inherits("Analeptic") then
			table.insert(shous, card)
		end
	end

	if #shous == 0 then return end
	self:sortByUseValue(shous, true)

	local card_str = ("@ZhenshouCard=%d"):format(shous[1]:getEffectiveId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["ZhenshouCard"]=function(card,use,self)
	use.card = card
end

--daoji
daoji_skill={}
daoji_skill.name="daoji"
table.insert(sgs.ai_skills,daoji_skill)
daoji_skill.getTurnUseCard=function(self)
	if not self.player:hasUsed("DaojiCard") then
		return sgs.Card_Parse("@DaojiCard=.")
	end
end

sgs.ai_skill_use_func["DaojiCard"] = function(card, use, self)
	local cards = self.player:getHandcards()
	cards=sgs.QList2Table(cards)
	self:sortByUseValue(cards,true)

	local target
	for _, friend in ipairs(self.friends_noself) do
		if self:hasSkills(sgs.lose_equip_skill, friend) and friend:getWeapon() then
			for _, card in ipairs(cards) do
				if card:getSuit() == sgs.Card_Club and self.player:getHandcardNum() > 1 then
					use.card = sgs.Card_Parse("@DaojiCard=" .. card:getEffectiveId())
					target = friend
					break
				end
			end
		end
		if target then break end
	end
	if not target then
		for _, enemy in ipairs(self.enemies) do
			if enemy:getWeapon() then
				for _, card in ipairs(cards)do
					if card:getSuit() == sgs.Card_Club and self.player:getHandcardNum() > 1 then
						use.card = sgs.Card_Parse("@DaojiCard=" .. card:getEffectiveId())
						target = enemy
						break
					end
				end
			end
			if target then break end
		end
	end

	if target then
		self.room:setPlayerFlag(target, "daoji_target")
		if use.to then
			use.to:append(target)
		end
	end
end

sgs.ai_skill_playerchosen.daoji = function(self, targets)
	for _, player in sgs.qlist(targets) do
		if (player:getHandcardNum() <= 2 or not player:getWeapon()) and self:isFriend(player) and not player:hasFlag("daoji_target") then
			return player
		end
	end
end

--jingjiu
local jingjiu_skill={}
jingjiu_skill.name="jingjiu"
table.insert(sgs.ai_skills,jingjiu_skill)
jingjiu_skill.getTurnUseCard=function(self)
	local cards = self.player:getHandcards()
	local jius = {}
	for _, card in sgs.qlist(cards) do
		if card:inherits("Analeptic") then
			table.insert(jius, card)
		end
	end

	if #jius == 0 then return end
	self:sortByUseValue(jius, true)

	local card_str = ("@JingjiuCard=%d"):format(jius[1]:getEffectiveId())
	return sgs.Card_Parse(card_str)
end

sgs.ai_skill_use_func["JingjiuCard"]=function(card,use,self)
	for _, friend in ipairs(self.friends_noself) do
	if not friend:hasFlag("drank") then
			use.card=card
			if use.to then use.to:append(friend) end
			return
		end
	end
end
