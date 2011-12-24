-- RedPackage's AI by Ubun.

-- tongmoux
sgs.ai_skill_invoke["tongmoux"] = true
sgs.ai_skill_playerchosen["tongmoux_tie"] = function(self, targets)
	for _, player in sgs.qlist(targets) do
		if self:isEnemy(player) and player:getHandcardNum() > 2 then
			return player
		end
	end
	return self.enemies[1]
end
sgs.ai_skill_invoke["tongmoux"] = true
local tongmoux_skill = {}
tongmoux_skill.name = "tongmoux"
table.insert(sgs.ai_skills, tongmoux_skill)
tongmoux_skill.getTurnUseCard = function(self)
	if self.player:hasUsed("TongmouxCard") then return end
	return sgs.Card_Parse("@TongmouxCard=.")
end
sgs.ai_skill_use_func["TongmouxCard"] = function(card, use, self)
	use.card = card
end

-- xianhaix
sgs.ai_skill_invoke["xianhaix"] = true
local xianhaix_skill = {}
xianhaix_skill.name = "xianhaix"
table.insert(sgs.ai_skills, xianhaix_skill)
xianhaix_skill.getTurnUseCard = function(self)
	local cards = self.player:getHandcards()
	cards = sgs.QList2Table(cards)
	for _, card in ipairs(cards) do
		if card:inherits("Disaster") then
			return sgs.Card_Parse("@XianhaixCard=" .. card:getEffectiveId())
		end
	end
end
sgs.ai_skill_use_func["XianhaixCard"] = function(card, use, self)
	use.card = card
	if use.to then use.to:append(self.enemies[1]) end
end

-- baichux
sgs.ai_skill_invoke["baichux"] = true
local baichux_skill = {}
baichux_skill.name = "baichux"
table.insert(sgs.ai_skills, baichux_skill)
baichux_skill.getTurnUseCard = function(self)
	if self.player:hasUsed("BaichuxCard") then return end
	local cards = self.player:getHandcards()
	cards = sgs.QList2Table(cards)
	for _, card in ipairs(cards) do
		if card:getNumber() > 5 and card:getNumber() < 9 then
			return sgs.Card_Parse("@BaichuxCard=" .. card:getEffectiveId())
		end
	end
end
sgs.ai_skill_use_func["BaichuxCard"] = function(card, use, self)
	use.card = card
end

-- tonglu-response
sgs.ai_skill_choice["tonglu"] = function(self, choices)
	local hejin = self.room:findPlayerBySkillName("tonglu")
	if hejin and self:isFriend(hejin) then
		if self.player:getHp() > 2 and self.player:getHandcardNum() > 2 then
			return "agree"
		elseif self:isEquip("Axe", hejin) then
			return "agree"
		else
			return "deny"
		end
	end
end

-- liehou
sgs.ai_skill_choice["liehou"] = function(self, choices)
	for _, player in sgs.qlist(self.room:getAllPlayers()) do
		if not player:faceUp() and self:isFriend(player) then
			if choices == "get+draw+cancel" then return "get" end
			return "draw"
		end
	end
	return "cancel"
end
sgs.ai_skill_playerchosen["liehou"] = function(self, targets)
	for _, player in sgs.qlist(targets) do
		if self:isFriend(player) and player:getHandcardNum() < 2 then
			return player
		end
	end
	return self.friends[1]
end

-- xiefang
sgs.ai_skill_invoke["xiefang"] = true
local xiefang_skill = {}
xiefang_skill.name = "xiefang"
table.insert(sgs.ai_skills, xiefang_skill)
xiefang_skill.getTurnUseCard = function(self)
	if not self:slashIsAvailable(self.player) then return end
	for _, enemy in ipairs(self.enemies) do
		local weapon = enemy:getWeapon()
		if weapon then
			return sgs.Card_Parse("@XiefangCard=.")
		end
	end
end
sgs.ai_skill_use_func["XiefangCard"] = function(card, use, self)
	self:sort(self.enemies, "threat")

	for _, friend in ipairs(self.friends_noself) do
		if friend:getWeapon() and self:hasSkills(sgs.lose_equip_skill, friend) then
			for _, enemy in ipairs(self.enemies) do
				if self.player:canSlash(enemy) then
					use.card = card
					if use.to then
						use.to:append(friend)
						use.to:append(enemy)
					end
					return
				end
			end
		end
	end
	for _, enemy in ipairs(self.enemies) do
		if not self.room:isProhibited(self.player, enemy, card)
			and not self:hasSkill(sgs.lose_equip_skill, enemy)
			and enemy:getWeapon() then

			local enemies = self.enemies
			self:sort(enemies, "handcard")
			for _, enemy2 in ipairs(enemies) do
				if self.player:canSlash(enemy2) then
					use.card = card
					if use.to then
						use.to:append(enemy)
						if enemy ~= enemy2 then
							use.to:append(enemy2)
						end
					end
					return
				end
			end
		end
	end
	return "."
end

-- xiefang-slash&jink
sgs.ai_skill_invoke["xiefang"] = function(self, data)
	local asked = data:toString()
	for _, enemy in ipairs(self.enemies) do
		local weapon = enemy:getWeapon()
		local armor = enemy:getArmor() or enemy:getDefensiveHorse() or enemy:getOffensiveHorse()
		if (asked == "slash" and weapon) or (asked == "jink" and armor) then
			return true
		end
	end
	return false
end
sgs.ai_skill_playerchosen["xiefang"] = function(self, targets)
	for _, player in sgs.qlist(targets) do
		if self:isEnemy(player) and not self:hasSkills(sgs.lose_equip_skill, player) then
			return player
		elseif self:isFriend(player) and self:hasSkills(sgs.lose_equip_skill, player) then
			return player
		end
	end
end
sgs.ai_skill_cardchosen["xiefang"] = function(self, who)
	local ecards = who:getCards("e")
	ecards = sgs.QList2Table(ecards)
	for _, unweapon in ipairs(ecards) do
		if not unweapon:inherits("Weapon") then
			return unweapon
		end
	end
end

-- zhubing
sgs.ai_skill_invoke["zhubing"] = sgs.ai_skill_invoke["zaiqi"]
sgs.ai_skill_invoke["super_zaiqi"] = sgs.ai_skill_invoke["zaiqi"]

-- jielue
sgs.ai_skill_invoke["jielue"] = function(self, data)
	local effect = data:toSlashEffect()
	return self:isEnemy(effect.to)
end

-- xujiu
sgs.ai_skill_invoke["xujiu"] = function(self, data)
	local damage = data:toDamage()
	return self:isEnemy(damage.to)
end

-- goulian
sgs.ai_skill_invoke["goulian"] = true
local goulian_skill = {}
goulian_skill.name = "goulian"
table.insert(sgs.ai_skills, goulian_skill)
goulian_skill.getTurnUseCard = function(self)
	if self.player:hasUsed("GoulianCard") or self.player:isKongcheng() then return end
	local card = self.player:getRandomHandCard()
	return sgs.Card_Parse("@GoulianCard=" .. card:getEffectiveId())
end
sgs.ai_skill_use_func["GoulianCard"] = function(card, use, self)
	for _, player in ipairs (self.friends_noself) do
		if player:getGeneral():isMale() then
			if use.to then use.to:append(player) end
			use.card = card
			return
		end
	end
end
sgs.ai_skill_choice["goulian"] = function(self, choices)
	if self.player:isWounded() then
		return "a"
	end
	local luban = self.room:findPlayerBySkillName("goulian")
	if luban and self:isFriend(luban) then
		return "b"
	end
	return "a"
end

