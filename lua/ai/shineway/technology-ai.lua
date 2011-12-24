-- Technology's AI by Ubun.

-- tuiyan
sgs.ai_skill_invoke["tuiyan"] = function(self, data)
	local struct= data:toCardUse()
	local card = struct.card
--	if card:inherits("Peach") or card:inherits("ExNihilo") then
	if card:inherits("Peach") then
		return true
	end
	return false
end
sgs.ai_skill_playerchosen["tuiyan"] = function(self, targets)
	targets = sgs.QList2Table(targets)
	self:sort(targets, "hp")
	for _, friend in ipairs(targets) do
		if self:isFriend(friend) and friend:isWounded() then
			return friend
		end
	end
	return self.player
end

-- yueli
sgs.ai_skill_invoke["yueli_h2d"] = function(self, data)
-- recover to drawcard
	local recover = data:toRecover()
	if self.player:getHp() + recover.recover >= self.player:getMaxHP() then
		return self.player:getHandcardNum() < 2
	end
	return false
end
sgs.ai_skill_invoke["yueli_m2t"] = function(self, data)
-- hurt to discard
	local damage = data:toDamage()
	local allcards = self.player:getCards("he")
	allcards = sgs.QList2Table(allcards)
	if self.player:getHp() - damage.damage <= 0 then
		return #allcards > 1
	end
	return false
end
sgs.ai_skill_invoke["yueli_d2h"] = function(self, data)
-- draw to recoverhp
	if self.player:getHandcardNum() > 2 then
		return self.player:isWounded()
	end
	return false
end
sgs.ai_skill_invoke["yueli_t2m"] = function(self, data)
-- discard to losehp
	local card = data:toCard()
	if #card:getSubcards() > 3 then
		return not self.player:isWounded() 
	end
	return false
end

-- mengjie
sgs.ai_skill_invoke["mengjie"] = true
sgs.ai_skill_playerchosen["mengjie"] = function(self, targets)
	targets = sgs.QList2Table(targets)
	self:sort(targets, "handcard")
	for _, target in ipairs(targets) do
		if self:isEnemy(target) and not target:isChained() then
			return target
		end
	end
	return self.enemies[1]
end

-- mengjie2
sgs.ai_skill_invoke["mengJie"] = function(self, data)
	local struct = data:toCardUse()
	local card = struct.card
	local to = struct.to
	to = sgs.QList2Table(to)
	if card:inherits("Peach") or card:inherits("ExNihilo") then
		return to[1] ~= self.player
	end
	if #to == 1 and to[1] == self.player then
		return true
	end
	return false
end
