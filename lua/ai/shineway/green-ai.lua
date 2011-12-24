-- GreenPackage's AI by Ubun.

-- yabian
sgs.ai_skill_invoke["yabian"] = function(self, data)
	local damage = data:toDamage()
	return self:isEnemy(damage.to)
end

-- yuanlv
sgs.ai_skill_invoke["yuanlv"] = true
local yuanlv_skill = {}
yuanlv_skill.name = "yuanlv"
table.insert(sgs.ai_skills, yuanlv_skill)
yuanlv_skill.getTurnUseCard = function(self)
	if self.player:hasUsed("YuanlvCard") or self.player:isWounded() then return end
	local yuanlv_card = sgs.Card_Parse("@YuanlvCard=.")
	assert(yuanlv_card)
	return yuanlv_card
end
sgs.ai_skill_use_func["YuanlvCard"] = function(card, use, self)
	if use.to then use.to:append(self.enemies[1]) end
	use.card = card
end

-- zhongjian
sgs.ai_skill_invoke["zhongjian"] = function(self, data)
	return #self.friends_noself ~= 0
end
sgs.ai_skill_playerchosen["zhongjian"] = function(self, targets)
	return self.friends_noself[1]
end

-- shixian&liji
sgs.ai_skill_invoke["shixian"] = function(self, data)
	return self.player:getPhaseString() == "discard" and self.player:getHandcardNum() >= self.player:getHp()
end
sgs.ai_skill_playerchosen["liji"] = function(self, targets)
	self:sort(self.enemies, "hp")
	return self.enemies[1]
end

-- diezhi1
diezhi1_skill={}
diezhi1_skill.name="diezhi1"
table.insert(sgs.ai_skills, diezhi1_skill)
diezhi1_skill.getTurnUseCard=function(self)
	if self.player:getMark("@drig") <= 0 then return end
	local r = math.random(1, 4)
	if r == 2 then return sgs.Card_Parse("@Diezhi1Card=.") end
end
sgs.ai_skill_use_func["Diezhi1Card"]=function(card,use,self)
	use.card = card
end
sgs.ai_skill_playerchosen["diezhi1"] = function(self, targets)
	if #self.enemies > #self.friends then
		for _, target in ipairs(self.enemies) do
			if not target:isLord() then
				return target
			end
		end
	else
		return self.friends[1]
	end
end

-- duizheng
local duizheng_skill={}
duizheng_skill.name="duizheng"
table.insert(sgs.ai_skills,duizheng_skill)
duizheng_skill.getTurnUseCard=function(self)
	if self.player:hasUsed("DuizhengCard") then return nil end
	local max_card = self:getMaxCard()
	if not max_card or max_card:getNumber() <= 11 then return nil end
	for _, enemy in ipairs(self.enemies) do
		if enemy:getHandcardNum() > 3 then
			return sgs.Card_Parse("@DuizhengCard=.")
		end
	end
end
sgs.ai_skill_use_func["DuizhengCard"]=function(card,use,self)
	for _, enemy in ipairs(self.enemies) do
		if enemy:getHandcardNum() > 3 then
			if use.to then use.to:append(enemy)	end
			use.card=card
			return
		end
	end
end

-- qilin
sgs.ai_skill_invoke["qilin"] = true
sgs.ai_skill_playerchosen["qilin"] = function(self, targets)
	local hc = self.player:getHandcardNum()
	self:sort(self.friends_noself, "handcard")
	for _, friend in ipairs(self.friends_noself) do
		if hc > friend:getHandcardNum() then
			return friend
		end
	end
	self:sort(self.enemies, "defense")
	for _, enemy in ipairs(self.enemies) do
		if enemy:getHandcardNum() - hc > 1 then
			return enemy
		end
	end
	return self.enemies[1]
end

-- jinguo1
sgs.ai_skill_use["@@jinguo1"] = function(self, prompt)
	if self.player:isKongcheng() then return end
	local card = self.player:getRandomHandCard()
	self:sort(self.enemies, "hp")
	local enemy = self.enemies[1]
	return "@Jinguo1Card="..card:getEffectiveId().."->"..enemy:objectName()
end

-- wuqi
sgs.ai_skill_invoke["wuqi"] = true
sgs.ai_skill_invoke["zhunsuan"] = true

-- quanyi
sgs.ai_skill_invoke["quanyi"] = true
local quanyi_skill = {}
quanyi_skill.name = "quanyi"
table.insert(sgs.ai_skills, quanyi_skill)
quanyi_skill.getTurnUseCard = function(self)
	if self.player:hasUsed("QuanyiCard") or self.player:isNude() then return end
	local card
	if self.player:isKongcheng() then
		card = self.player:getCards("he")[1]
	else
		card = self.player:getRandomHandCard()
	end
	return sgs.Card_Parse("@QuanyiCard=" .. card:getEffectiveId())
end
sgs.ai_skill_use_func["QuanyiCard"] = function(card, use, self)
	self:sort(self.friends, "handcard")
	local from, to
	for _, player in ipairs (self.friends) do
		if not from then
			from = player
		else
			to = player
		end
		if to then break end
	end
	if not to then to = self.enemies[1] end
	if use.to then
		use.to:append(from)
		use.to:append(to)
	end
	use.card = card
end

-- zhunsuan
sgs.ai_skill_choice["zhunsuan"] = function(self, choices)
	if not self.player:isWounded() then
		return "7"
	elseif self:isWeak(self.player) then
		return "6"
	else
		return "8"
	end
end
