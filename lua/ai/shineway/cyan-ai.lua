-- CyanPackage's AI by Ubun.

-- rangli
sgs.ai_skill_invoke["rangli"] = function(self, data)
	local players = sgs.QList2Table(self.room:getAllPlayers())
	for _, player in ipairs(players) do
		if not player:isKongcheng() then
			return true
		end
	end
	return false
end
sgs.ai_skill_playerchosen["rangli"] = function(self, targets)
	local next_player = self.player:getNextAlive()
	targets = sgs.QList2Table(targets)
	self:sort(targets, "hp")
	for _, target in ipairs(targets) do
		if next_player == target and self:isFriend(target) and target:getHandcardNum() > 1 then
			return target
		elseif self:isEnemy(target) and target:getHp() < 2 and target:getHandcardNum() > 1 and
			not target:hasSkill("lianying") and
			not target:hasSkill("shangshi") and
			not target:hasSkill("tuntian") then
			return target
		end
	end
	return targets[1]
end

-- kuanhou
sgs.ai_skill_invoke["kuanhou"] = true
sgs.ai_skill_playerchosen["kuanhou"] = function(self, targets)
	targets = sgs.QList2Table(targets)
	for _, target in ipairs(targets) do
		if self:isFriend(target) and target:containsTrick("indulgence") and target:getHandcardNum() > 2 then
			return target
		end
	end
	for _, target in ipairs(targets) do
		if self:isFriend(target) and target:getHandcardNum() > 2 then return target end
	end
	for _, target in ipairs(targets) do
		if self:isFriend(target) then return target	end
	end
	return targets[1]
end

-- guolie
sgs.ai_skill_invoke["guolie"] = function(self, data)
	local damage = data:toDamage()
	if self:isFriend(damage.to) then 
		if damage.from:getHandcardNum() - damage.to:getHandcardNum() > 1 then
			return true
		end
	else
		if damage.to:getHandcardNum() - damage.from:getHandcardNum() > 1 then
			return true
		end
	end
end

-- ruji
sgs.ai_skill_invoke["ruji"] = true
sgs.ai_skill_use["@@ruji!"] = function(self, prompt)
	local max_card = self:getMaxCard()
	if not max_card or max_card:getNumber() < 11 then return end
	self:sort(self.enemies, "threat")
	for _, enemy in ipairs(self.enemies) do
		if not enemy:isKongcheng() then
			return "@RujiCard="..max_card:getEffectiveId().."->"..enemy:objectName()
		end
	end
end

-- jiaozei
sgs.ai_skill_invoke["jiaozei"] = function(self, data)
	local zhb_enable = false
	if self.player:hasLordSkill("zhaobing") then
		for _, player in sgs.qlist(self.room:getAlivePlayers()) do
			if player:getKingdom() == "qun" and player ~= self.player and self:isFriend(player) and not player:isKongcheng() then
				zhb_enable = true
				break
			end
		end
	end
	if zhb_enable then
		return true
	else
		local max_card = self:getMaxCard()
		return max_card and max_card:getNumber() > 11
	end
end
sgs.ai_skill_invoke["zhaobing"] = function(self, data)
	local max_card = self:getMaxCard()
	if max_card and max_card:getNumber() > 11 then
		return false
	else
		return true
	end
end
