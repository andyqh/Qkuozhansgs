--zhangling
sgs.ai_skill_invoke.zombiemaster = true
local zombiebomb_skill={}
zombiebomb_skill.name="zombiebomb"
table.insert(sgs.ai_skills, zombiebomb_skill)
zombiebomb_skill.getTurnUseCard = function(self)
	local players = self.room:getOtherPlayers(self.player)
	local targets = {}
	for _, p in sgs.qlist(players) do
			if self:isEnemy(p) 
				then table.insert(targets, p) 			
			end
	end
	
	
	if self.player:getPile("zombies"):isEmpty() 
		or #targets == 0
		or self.player:getHandcardNum()>=self.player:getHp() then 
		return 
	end
	return sgs.Card_Parse("@ZombieCard=.")
end
sgs.ai_skill_invoke.zombiepoison = true
local zombiepoison_skill={}
zombiepoison_skill.name="zombiepoison"
table.insert(sgs.ai_skills, zombiepoison_skill)
zombiepoison_skill.getTurnUseCard = function(self)
	if self.player:getHp()<=2 and not self.player:getPile("zombies"):isEmpty() then 
	return sgs.Card_Parse("@PoisonCard=.")
	end
end

sgs.ai_skill_use_func["ZombieCard"] = function(card, use, self)
	use.card = sgs.Card_Parse("@ZombieCard=.")
end

sgs.ai_skill_use_func["PoisonCard"] = function(card, use, self)
	use.card = sgs.Card_Parse("@PoisonCard=.")
end

sgs.ai_skill_playerchosen.zombiebomb = function(self, targets)
	for _, target in sgs.qlist(targets) do
		if  not self:isFriend(target) then
			return target
		end
	end
end

--dancer
sgs.ai_skill_invoke.dance = function(self, data)
	if self.player:getHp()<=4 or self.player:isKongcheng()
	then return true 
	end
end
sgs.ai_skill_use["@@dance"]=function(self,prompt)
    self:updatePlayers()
	local guests = {}
	local first,second,third		
	local players = self.room:getAllPlayers()
	for _,p in sgs.qlist(players) do		
		if  self:isFriend(p) and p:isWounded() then table.insert(guests, p) end
		if #guests >= 3 then break end
	end	
	if (#guests>=3) then	
			first =guests[1]
			second=guests[2]
			third =guests[3]			
			return ("@DanceCard=.->%s+%s+%s"):format(first:objectName(), second:objectName(),third:objectName())
	end
	if (#guests==2) then	
			first = guests[1]
			second = guests[2]
			return ("@DanceCard=.->%s+%s"):format(first:objectName(), second:objectName())
	end			
	if (#guests==1) then	
			first = guests[1]
			return "@DanceCard=.->"..first:objectName()
	end		
end




--archer
sgs.ai_skill_invoke.archershoot =true
sgs.ai_skill_invoke.spreadingshoot = function(self, data)
	 return self.player:getLostHp() >= 2
end
--gexuan
sgs.ai_skill_invoke.xiuzhen = true
sgs.ai_skill_invoke.xiuzhenlevel5 = true
sgs.ai_skill_invoke.xiuzhenlevel1 = true
sgs.ai_skill_invoke.xiuzhenlevel2 = true
sgs.ai_skill_playerchosen.xiuzhenlevel2 = function(self, targets)
	for _, target in sgs.qlist(targets) do
		if not self:isFriend(target) then
			return target
		end
	end
end
sgs.ai_skill_invoke.xiuzhenlevel3 = true
sgs.ai_skill_invoke.xiuzhenlevel4 = true
sgs.ai_skill_use["@@tianlei"]=function(self,prompt)
    self:updatePlayers()
	local guests = {}
	local first,second,third
	self:sort(self.enemies,"hp")
	for _,enemy in ipairs(self.enemies) do
		if self:objectiveLevel(enemy)>3 and not enemy:hasSkill("hongyan") then table.insert(guests, enemy) end
		if #guests >= 3 then break end	
	end
	if (#guests>=3) then	
			first =guests[1]
			second=guests[2]
			third =guests[3]			
			return ("@TianleiCard=.->%s+%s+%s"):format(first:objectName(), second:objectName(),third:objectName())
	end
	if (#guests==2) then	
			first = guests[1]
			second = guests[2]
			return ("@TianleiCard=.->%s+%s"):format(first:objectName(), second:objectName())
	end			
	if (#guests==1) then	
			first = guests[1]
			return "@TianleiCard=.->"..first:objectName()
	end		
end

sgs.ai_skill_playerchosen.xiuzhenlevel4 = function(self, targets)
	for _, target in sgs.qlist(targets) do
		if not self:isFriend(target) then
			return target
		end
	end
end

--yingzi
sgs.ai_skill_invoke.ansha = true

--zhangsong
sgs.ai_skill_invoke["qiangzhi"] = function(self, data)
	local struct= data:toCardUse()
	return self:isEnemy(struct.from)
end
--jiping
-- when enemy using the peach
sgs.ai_skill_invoke.dusha = function(self, data)
	local struct= data:toCardEffect()
	return self:isEnemy(struct.from)
end
--fanjiangzhangda 
sgs.ai_skill_invoke.fankang = function(self, data)
	if self.player:getHp()<4 or self.player:isKongcheng()
	then return true 
	end
end
--luyi



local mimou_skill={}
mimou_skill.name="mimou"
table.insert(sgs.ai_skills,mimou_skill)
mimou_skill.getTurnUseCard=function(self)
    local cards = self.player:getCards("h")	
    cards=sgs.QList2Table(cards)
	
	local card
	
	self:sortByUseValue(cards,true)
	
	for _,acard in ipairs(cards)  do
		if (acard:getSuit() == sgs.Card_Diamond) then
			card = acard
			break
		end
	end
	
	    if not card then return nil end
		local number = card:getNumberString()
	    local card_id = card:getEffectiveId()
	    local card_str = ("ex_nihilo:mimou[diamond:%s]=%d"):format(number, card_id)
		local skillcard = sgs.Card_Parse(card_str)
		
	    assert(skillcard)
        
        return skillcard
		
end
--hanlong
sgs.ai_skill_invoke.liwei = true


--chizhizhe
--changjue
sgs.ai_skill_invoke.changjue = true
local changjue_skill={}
changjue_skill.name="changjue"
table.insert(sgs.ai_skills, changjue_skill)
changjue_skill.getTurnUseCard = function(self)
	if self.player:getMark("@changjue")==0 then return end
	if self.player:isWounded() then 
	return sgs.Card_Parse("@ChangjueCard=.")
	end
end
sgs.ai_skill_use_func["ChangjueCard"] = function(card, use, self)
	use.card = sgs.Card_Parse("@ChangjueCard=.")
end
sgs.ai_skill_playerchosen.changjue = function(self, targets)
	for _, target in sgs.qlist(targets) do
		if not self:isFriend(target) then
			return target
		end
	end
end
-- youguai
sgs.ai_skill_invoke.youguai = function(self, data)
	local damage = data:toDamage()
	if damage.to:getHp()<=4 then
		return self:isFriend(damage.to) and not self:isFriend(damage.from)
	else if (self.Player==damage.to and self.Player:getHp()<3) then return true end
	end
	return false
end
--bangpiao
sgs.ai_skill_invoke.bangpiao = function(self, data)
	if self.player:getHp() <2 or self.player:isKongcheng() then
		return true
	end
end
sgs.ai_skill_playerchosen.bangpiao = function(self, targets)
	for _, target in sgs.qlist(targets) do
		if not self:isFriend(target) then
			return target
		end
	end
end

-- sipiao





--liuye
--shengyan
sgs.ai_skill_invoke.shengyan = function(self, data)
	local effect = data:toCardEffect()	
	if effect.card:inherits("GodSalvation") and self.player:isWounded() then
		return false
	else return self:isEnemy(effect.from)		
	end
end
local wuhuan_skill={}
wuhuan_skill.name="wuhuan"
table.insert(sgs.ai_skills,wuhuan_skill)
wuhuan_skill.getTurnUseCard=function(self)
    local cards = self.player:getCards("h")	
    cards=sgs.QList2Table(cards)	
	local anal_card	
	self:sortByUseValue(cards,true)	
	for _,card in ipairs(cards)  do
		if card:inherits("Analeptic") then 
			anal_card = card
			break
		end
	end
	if anal_card then		
		local suit = anal_card:getSuitString()
    	local number = anal_card:getNumberString()
		local card_id = anal_card:getEffectiveId()
		local card_str = ("jink:wuhuan[%s:%s]=%d"):format(suit, number, card_id)
		local jink = sgs.Card_Parse(card_str)        
        return jink
	end
end




--wufu
sgs.ai_skill_invoke.bishou = true

--weike
local quanjiu_skill={}
quanjiu_skill.name="quanjiu"
table.insert(sgs.ai_skills,quanjiu_skill)
quanjiu_skill.getTurnUseCard=function(self)
    local cards = self.player:getCards("h")	
    cards=sgs.QList2Table(cards)
	
	local card
	
	self:sortByUseValue(cards,true)
	
	for _,acard in ipairs(cards)  do
		if (acard:getSuit() == sgs.Card_Spade) then--and (self:getUseValue(acard)<sgs.ai_use_value["IronChain"]) then
			card = acard
			break
		end
	end
	
	    if not card then return nil end
		local number = card:getNumberString()
	    local card_id = card:getEffectiveId()
	    local card_str = ("analeptic:quanjiu[spade:%s]=%d"):format(number, card_id)
		local skillcard = sgs.Card_Parse(card_str)
		
	    assert(skillcard)
        
        return skillcard
		
end

sgs.ai_skill_invoke.taolue=true




--yinfan 
--lianzuo
sgs.ai_skill_invoke.lianzuo =  function(self, data)	
	local players = self.room:getOtherPlayers(self.player)
	local x=0
	for _, p in sgs.qlist(players) do
		if self:isEnemy(p) then x=x+1 end
	end
	if x>1 then return true 
	else return false
	end
end

sgs.ai_skill_playerchosen.lianzuo = function(self, targets)
	for _, target in sgs.qlist(targets) do
		if not self:isFriend(target) then
			return target
		end
	end
end
--tiaobo
local tiaobo_skill={}
tiaobo_skill.name="tiaobo"
table.insert(sgs.ai_skills,tiaobo_skill)
tiaobo_skill.getTurnUseCard=function(self)
	if self.tiaobo_used then
		return 
	end
	if not self.player:isNude() then
		local card
		local card_id
		if self.player:getArmor() and self.player:isWounded() and self.player:getArmor():objectName()=="silver_lion" then
			card = sgs.Card_Parse("@TiaoboCard=" .. self.player:getArmor():getId())
		elseif self.player:getHandcardNum() > self.player:getHp() then
			local cards = self.player:getHandcards()
			cards=sgs.QList2Table(cards)
			
			for _, acard in ipairs(cards) do
				if (acard:inherits("BasicCard") or acard:inherits("EquipCard") or acard:inherits("AmazingGrace"))
					and not acard:inherits("Peach") and not acard:inherits("Shit") then 
					card_id = acard:getEffectiveId()
					break
				end
			end
		elseif not self.player:getEquips():isEmpty() then
			local player=self.player
			if player:getWeapon() then card_id=player:getWeapon():getId()
			elseif player:getOffensiveHorse() then card_id=player:getOffensiveHorse():getId()
			elseif player:getDefensiveHorse() then card_id=player:getDefensiveHorse():getId()
			elseif player:getArmor() and player:getHandcardNum()<=1 then card_id=player:getArmor():getId()
			end
		end
		if not card_id then
			cards=sgs.QList2Table(self.player:getHandcards())
			for _, acard in ipairs(cards) do
				if (acard:inherits("BasicCard") or acard:inherits("EquipCard") or acard:inherits("AmazingGrace"))
					and not acard:inherits("Shit")  then 
					card_id = acard:getEffectiveId()
					break
				end
			end
		end
		if not card_id then
			return nil
		else
			card = sgs.Card_Parse("@TiaoboCard=" .. card_id)
			return card
		end
	end
	return nil
end

sgs.ai_skill_use_func["TiaoboCard"]=function(card,use,self)
	local findFriend_maxSlash=function(self,first)
		self:log("Looking for the friend!")
		local maxSlash = 0
		local friend_maxSlash
		for _, friend in ipairs(self.friends_noself) do
			if (self:getSlashNumber(friend)> maxSlash)  then
				maxSlash=self:getSlashNumber(friend)
				friend_maxSlash = friend
			end
		end
		if friend_maxSlash then
			local safe = false
			if (first:hasSkill("ganglie") or first:hasSkill("fankui") or first:hasSkill("enyuan")) then
				if (first:getHp()<=1 and first:getHandcardNum()==0) then safe=true end
			elseif (self:getSlashNumber(friend_maxSlash) >= first:getHandcardNum()) then safe=true end
			if safe then return friend_maxSlash end
		else self:log("unfound")
		end
		return nil
	end

	if not self.tiaobo_used --and not self.player:isNude()
	then
		self:sort(self.enemies, "hp")
		local males = {}
		local first, second
		local zhugeliang_kongcheng
		for _, enemy in ipairs(self.enemies) do
			if zhugeliang_kongcheng and #males==1 then table.insert(males, zhugeliang_kongcheng) end
			if  not enemy:hasSkill("wuyan") then
				if enemy:hasSkill("kongcheng") and enemy:isKongcheng() then	zhugeliang_kongcheng=enemy
				else table.insert(males, enemy)	end
				if #males >= 2 then	break end
			end
		end
		--if (#males==0) then self:log("No real men!") end
		if (#males==1) and #self.friends_noself>0 then
			self:log("Only 1")
			first = males[1]
			if zhugeliang_kongcheng then table.insert(males, zhugeliang_kongcheng)
			else
				local friend_maxSlash = findFriend_maxSlash(self,first)
				if friend_maxSlash then table.insert(males, friend_maxSlash) end
			end
		end
		if (#males >= 2) then
			first = males[2]
			second = males[1]
			local lord = self.room:getLord()
			if (first:getHp()<=1) then
				if self.player:isLord() or isRolePredictable() then 
					local friend_maxSlash = findFriend_maxSlash(self,first)
					if friend_maxSlash then second=friend_maxSlash end
				elseif (not lord:hasSkill("wuyan")) then 
					if (self.role=="rebel") and (not first:isLord()) then
						second = lord
					else
						if ((self.role=="loyalist" or (self.role=="renegade") and not (first:hasSkill("ganglie") and first:hasSkill("enyuan"))))
							and	( self:getSlashNumber(first)<=self:getSlashNumber(second)) then
							--the first male maybe have a "Slash" Card
							second = lord
						end
					end
				end
			end

			if first and second 
					then
				if use.to --and not (self.player:getHandcardNum()<=1 and first:getHp()>1)
					then 
		        use.to:append(first)
		        use.to:append(second)
		        self.tiaobo_used = true
				end
			end
            use.card=card
		end
	end
end

--menke
local menke_skill={}
menke_skill.name="menke"
table.insert(sgs.ai_skills,menke_skill)
menke_skill.getTurnUseCard=function(self)
	if self.menke_used then
		return 
	end
	if not self.player:isNude() then
		local card
		local card_id
	    local cards = self.player:getHandcards()
		cards=sgs.QList2Table(cards)			
			for _, acard in ipairs(cards) do
				if (acard:inherits("BasicCard") or acard:inherits("EquipCard") or acard:inherits("AmazingGrace"))
					and not acard:inherits("Peach") and not acard:inherits("Shit") and acard:isRed() then 
					card_id = acard:getEffectiveId()
					break
				end
			end

		if not card_id then
			cards=sgs.QList2Table(self.player:getHandcards())
			for _, acard in ipairs(cards) do
				if (acard:inherits("BasicCard") or acard:inherits("EquipCard") or acard:inherits("AmazingGrace"))
					and not acard:inherits("Shit")  and acard:isRed() then 
					card_id = acard:getEffectiveId()
					break
				end
			end
		end
		if not card_id then
			return nil
		else
			card = sgs.Card_Parse("@MenkeCard=" .. card_id)
			return card
		end
	end
	return nil
end
sgs.ai_skill_playerchosen.menke = function(self, targets)
	for _, target in sgs.qlist(targets) do
		if  not self:isFriend(target) then
			return target
		end
	end
	return targets:first()
end
sgs.ai_skill_use_func["MenkeCard"]=function(card,use,self)
	if not self.menke_used --and not self.player:isNude()
	then
		self:sort(self.enemies, "hp")
		local guests = {}
		local first, second,third		
		for _, enemy in ipairs(self.enemies) do
			for _, enemy2 in ipairs(self.enemies) do
				for _, enemy3 in ipairs(self.enemies) do
					if not (enemy2:hasSkill("yuanxing") or enemy:hasSkill("yuanxing"))then 
						if  (enemy3:objectName() ~= enemy2:objectName()) 
						    and (enemy2:objectName() ~= enemy:objectName()) 
							and (enemy3:objectName() ~= enemy:objectName())
							and enemy2:inMyAttackRange(enemy) 
							and enemy2:inMyAttackRange(enemy3)							
							then table.insert(guests, enemy) 
				                 table.insert(guests, enemy2)
								 table.insert(guests, enemy3)
     					end						
					end
					if #guests >= 3 then break end	
                end					
			end	
		end
		if(#guests==0) then 
		local players = self.room:getOtherPlayers(self.player)
			for _, p in sgs.qlist(players) do
				for _, p2 in sgs.qlist(players) do
					for _, enemy in ipairs(self.enemies) do
						if not self:isEnemy(p) and not self:isEnemy(p2) then
							if (enemy:objectName() ~= p:objectName()) 
								and (enemy:objectName() ~= p2:objectName()) 
								and (p:objectName() ~= p2:objectName())
								and enemy:inMyAttackRange(p) 
								and enemy:inMyAttackRange(p2) 
								then table.insert(guests, p) 
									 table.insert(guests, p2)
							end		
						end	
					end		
				end
			end
		end

		if (#guests >= 3) then
			first = guests[1]
			second = guests[2]
			third= guests[3]
			if first and second and third
					then
				if use.to --and not (self.player:getHandcardNum()<=1 and first:getHp()>1)
					then 
		        use.to:append(first)
		        use.to:append(second)
				use.to:append(third)
		        self.menke_used = true
				end
			end
            use.card=card
		end
		if (#guests ==2) then
			first = guests[2]
			second = guests[1]			
			if first and second 
					then
				if use.to --and not (self.player:getHandcardNum()<=1 and first:getHp()>1)
					then 
		        use.to:append(first)
		        use.to:append(second)				
		        self.menke_used = true
				end
			end
            use.card=card
		end	
	end
end

--·ï³û
sgs.ai_skill_invoke.buzhen  =  true

sgs.ai_skill_playerchosen.buzhen = function(self, targets)
	if self.player:isLord() then return targets:last() end
	local x=0
	local y=0
	local z=0
	local players=self.room:getAllPlayers()
	for _, p in sgs.qlist(players) do
		if((p:objectName()~=self.player:objectName() and not p:isLord()) and y==0 )then  x=x+1 end
		if p:isLord() then y=y+1 end
		if((p:objectName()~=self.player:objectName() and not p:isLord()) and y==1 )then  z=z+1 end
	end
	if x>z then return targets:at(x-1) end
	if x<=z then return targets:at(x) end
end

sgs.ai_skill_invoke.buzhen4 = function(self, data)
	local damage = data:toDamage()	
	return self:isFriend(damage.to) and not self.Player:isKongcheng()	
end	