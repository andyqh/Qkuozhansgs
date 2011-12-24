-- KusoPackage's AI by Ubun.

-- huaxu
sgs.ai_skill_invoke["huaxu"] = function(self, data)
	local damage = data:toDamage()
	return self:isEnemy(damage.to)
end

-- eatdeath
sgs.ai_skill_invoke["eatdeath"] = function(self, data)
	local damage = data:toDamage()
	local target = damage.to
	if self.player:getMaxHP() < 4 then
		return false
	end
	return true
end

-- clearShirt
function SmartAI:useClearShirt(card, use)
	local next_player = self.player:getNextAlive()
	if self:isFriend(next_player) then
		if self:isEquip("GaleShell", next_player) or
			(self:isEquip("SilverLion", next_player) and next_player:isWounded()) then
			use.card = card
		end
	elseif self:isEnemy(next_player) then
		if not self:isEquip("GaleShell", next_player) then
			use.card = card
		end
	end
	return
end

-- kawaii_dress
function SmartAI:useKawaiiDress(card, use)
	if self.player:getGeneral():isFemale() then
		use.card = card
	elseif self.player:getHp() > 1 then
		use.card = card
	end
	return
end

-- sacrifice
function SmartAI:useCardSacrifice(sacrifice, use)
	if self.player:hasSkill("wuyan") then return end
    if self.player:getHp() <= 2 then return end
	self:sort(self.friends_noself, "hp")
	for _, friend in ipairs(self.friends_noself) do
		if friend:isWounded() then
			use.card = sacrifice
			if use.to then
				use.to:append(friend)
			end
			break
		end
	end
end

