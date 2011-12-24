module("extensions.qhs", package.seeall)
extension = sgs.Package("qhs")

lualajiche = sgs.General(extension, "lualajiche", "god", 0, true, true)
luasimahui = sgs.General(extension, "luasimahui", "qun", 3)
luajiping = sgs.General(extension, "luajiping", "qun", 3)
shenluasimazhongda = sgs.General(extension, "shenluasimazhongda", "god", 3,true,true)
luapanfeng = sgs.General(extension, "luapanfeng", "qun")
lualiuba = sgs.General(extension, "lualiuba", "shu", 3)
luahuaxiong = sgs.General(extension, "luahuaxiong", "qun")
luasimazhao = sgs.General(extension, "luasimazhao", "wei", 3)
lualiru = sgs.General(extension, "lualiru", "qun", 3)
lualengyanju = sgs.General(extension, "lualengyanju", "qun", 3)
luadingfeng = sgs.General(extension, "luadingfeng", "wu", 4)
luazuoci = sgs.General(extension, "luazuoci", "qun", 3)
shenlualvfengxian = sgs.General(extension, "shenlualvfengxian", "god", 5,true,true)

--司马徽
--codeby lycio
luayinshi_buff=sgs.CreateProhibitSkill{
	name = "#luayinshi_buff",
	is_prohibited=function(self,from,to,card)
		return ( card:inherits("DelayedTrick"))
	end,
}
luayinshi = sgs.CreateTriggerSkill{
	name = "luayinshi",
	events = {sgs.CardEffect,sgs.CardEffected},
	frequency = sgs.Skill_Compulsory,
	on_trigger = function(self,event,player,data)
		local room = player:getRoom()
		local smh = room:findPlayerBySkillName(self:objectName())
		if smh == nil then return false end
		if event == sgs.CardEffect then
			local effect = data:toCardEffect()
			local card = effect.card
			if not effect.to then return false end
			if effect.to:distanceTo(smh) > effect.to:getAttackRange() and card:inherits("BasicCard") then
				local log=sgs.LogMessage()
				log.type = "#yinshi"
				log.from = smh
				log.arg = card:objectName()
				room:sendLog(log)
				room:playSkillEffect("luayinshi",1)
				smh:drawCards(1)
				return true
			end
		end
		if event == sgs.CardEffected then
			local effect = data:toCardEffect()
			local card = effect.card
			if not effect.from then return false end
			if smh:distanceTo(effect.from) > smh:getAttackRange() and card:inherits("BasicCard") then 
				local log=sgs.LogMessage()
				log.type = "#yinshi"
				log.from = smh
				log.arg = card:objectName()
				room:sendLog(log)
				room:playSkillEffect("luayinshi",1)
				smh:drawCards(1)
				return true 
			end
		end 
	end
}
luashuijing = sgs.CreateTriggerSkill{
	name = "luashuijing",
	events = {sgs.FinishJudge, sgs.HpLost, sgs.HpRecover, sgs.Predamaged},
	can_trigger = function(self,player)
		return player:getRoom():findPlayerBySkillName("luashuijing")
	end,
	on_trigger = function(self,event,player,data)
		local room = player:getRoom()
		local smh = room:findPlayerBySkillName(self:objectName())
		if smh == nil then return false end
		if event ~= sgs.FinishJudge then
		
			local log = sgs.LogMessage()
			log.type = "#luashuijing"
			log.arg = player:getGeneralName()
			room:sendLog(log)
				
			if (not room:askForSkillInvoke(smh, "luashuijing")) then return false end 
			room:playSkillEffect("luashuijing",1)
			local judge = sgs.JudgeStruct()
			judge.pattern = sgs.QRegExp("(.*):(.*):(.*)")
			judge.reason = "luashuijing"
			judge.who = smh
			room:judge(judge)
			sgs.card_suit = {heart = ".H", spade = ".S", club = ".C", diamond = ".D",}
			local card = room:askForCard(smh, sgs.card_suit[judge.card:getSuitString()], "@luashuijing1:")
			if card then
				if event == sgs.HpRecover then 
					local recover = data:toRecover()
					recover.recover = recover.recover + 1
					data:setValue(recover)
					room:setEmotion(player, "good")
					
					local log = sgs.LogMessage()
					log.type = "$luashuijing2"
					log.card_str = card:toString()
					log.from = smh
					room:sendLog(log)
					
				elseif event == sgs.HpLost then
					local lost = data:toInt() + 1
					data:setValue(lost)
										
					local log = sgs.LogMessage()
					log.type = "$luashuijing1"
					log.card_str = card:toString()
					log.from = smh
					room:sendLog(log)
					
				elseif event == sgs.Predamaged then
					local damage = data:toDamage()
					damage.damage = damage.damage + 1
					data:setValue(damage)
										
					local log = sgs.LogMessage()
					log.type = "$luashuijing3"
					log.card_str = card:toString()
					log.from = smh
					room:sendLog(log)
					
				end
			else
				local log = sgs.LogMessage()
				log.type = "$luashuijing4"
				log.from = smh
				room:sendLog(log)
				room:setEmotion(smh, "bad")
				return false
			end
		end
	end,
}

--吉平
--codeby lycio
luazhenzhi = sgs.CreateTriggerSkill
{
	name = "luazhenzhi",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.Damaged},
	can_trigger = function (self, player)
		return player:hasSkill("luazhenzhi")
	end,
	on_trigger = function (self, event, player, data)
		local room = player:getRoom()
		local damage = data:toDamage()
		local p = damage.to
		local source = damage.from
		local sp = room:getAllPlayers()
		if damage.card ~= nil and damage.card:inherits("SavageAssault") then
			for _,p in sgs.qlist(sp) do
				if p:hasSkill("huoshou") then source = p end
			end
		end
		if damage.damage < 3 then 
			if source then
				if not player:isAlive() then return false end
				if not room:askForSkillInvoke(p, "luazhenzhi", data) then return false end
				local log = sgs.LogMessage()
				log.type = "#luazhenzhi"
				log.from = player
				log.arg = source:getGeneralName()
				room:sendLog(log)
				room:loseHp(source, damage.damage)
				source:drawCards(damage.damage)
				p:drawCards(damage.damage)
			else return false
			end
		end
		if damage.damage >= 3 and p:faceUp() then
			if not player:isAlive() then return false end
			if not room:askForSkillInvoke(p, "luazhenzhi", data) then return false end
			p:drawCards(damage.damage)
			p:turnOver()
			local otherplayers = room:getOtherPlayers(p)
			local target = room:askForPlayerChosen(p, otherplayers, "@luazhenzhi")
			local log = sgs.LogMessage()
			log.type = "#luazhenzhi"
			log.from = player
			log.arg = target:getGeneralName()
			room:sendLog(log)
			room:killPlayer(target)
		end
	end,
}

hh_record={}
luahuanhun_record = sgs.CreateTriggerSkill
{
	name = "#luahuanhun_record",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Death},
	can_trigger = function (self,player)
		return not player:hasSkill("#luahuanhun")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		if event == sgs.Death then 
			local tmp = player:getGeneralName()
			table.insert (hh_record, tmp)
		end
	end,	
}
luahuanhun = sgs.CreateTriggerSkill
{
	name = "#luahuanhun",
	frequency = sgs.Skill_Limited,
	events = {sgs.TurnStart},
	can_trigger = function(self, player)
		return player:hasSkill("#luahuanhun") and player:getMark("limited") == 0 and #hh_record > 0
	end,
	on_trigger = function (self, event, player, data)
		local room = player:getRoom()
		if event == sgs.TurnStart and (not player:faceUp()) then
			if not player:isAlive() then return false end
			if not room:askForSkillInvoke(player, "#luahuanhun") then return false end
			local targets = table.concat(hh_record, "+")
			local choice = room:askForChoice(player, "luayincang", targets)
			local target = room:findPlayer(choice,true)
			room:revivePlayer(target)
			local log = sgs.LogMessage()
			log.type = "#luahuanhun1"
			log.from = player
			log.arg = target:getGeneralName()
			room:sendLog(log)
			local x = target:getMaxHP()
			room:setPlayerProperty(target, "hp", sgs.QVariant(x))
			target:drawCards(x)
			room:setPlayerMark(player, "limited", 1)
			return true 
		end
	end,
}

lualianyu = sgs.CreateTriggerSkill
{
	name = "lualianyu",
	events = {sgs.HpRecover},
	can_trigger = function(self,player)
		return player:hasSkill("lualianyu")
	end,
	on_trigger = function (self, event, player, data)
		local room = player:getRoom()
		local sp = room:getOtherPlayers(player)
		if player:isChained() then 
			if not room:askForSkillInvoke(player, "lualianyu") then return false end
			local targets = sgs.SPlayerList()
			for _,p in sgs.qlist(sp) do 
				if p:isChained() then targets:append(p) end
			end 
			local target = room:askForPlayerChosen(player, targets, "@lualianyu")
			local discard = room:askForCard(target, ".H", "@lianyucard")
			if not discard then 
				local log = sgs.LogMessage()
				log.type = "#lualianyu"
				log.from = target
				room:sendLog(log)
				return false 
			end
			if discard then 
				local log = sgs.LogMessage()
				log.type = "$lualianyu"
				log.from = target
				log.card_str = discard:toString()
				room:sendLog(log)
				local recover = sgs.RecoverStruct()
				recover.who = target
				recover.recover = 1
				room:recover(target,recover)
			end
		end
	end,
}
luayincang = sgs.CreateTriggerSkill
{
	name = "luayincang",
	frequency = sgs.Skill_Limited,
	events = sgs.GameStart,
	on_trigger = function(self, event, player, data)
	end,
}

--司马仲达
--codeby lycio
lualietian = sgs.CreateTriggerSkill
{
	name = "lualietian",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.Damaged},
	can_trigger = function(self, player)
		return player:hasSkill("lualietian")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local damaged = data:toDamage()
		local source = damaged.from
		local targets = room:getAllPlayers()
		if not player:isAlive() then return false end
		if not room:askForSkillInvoke(player, "lualietian") then return false end
		room:playSkillEffect("lualietian", 1)
		local target = room:askForPlayerChosen(player, targets, "@lualietian")
		local judge = sgs.JudgeStruct()
		judge.pattern = sgs.QRegExp("(.*):(spade):([2-9])")
		judge.good = false
		judge.reason = "lualietian"
		judge.who = target
		room:judge(judge)
		if (not judge:isGood()) then
			room:setEmotion(target, "bad")
			local damage = sgs.DamageStruct()
			damage.card = nil
			damage.damage = 3
			damage.from = player
			damage.to = target
			damage.nature = sgs.DamageStruct_Thunder
			room:damage(damage)	
			return true
		else
			room:setEmotion(target, "good")
		end
	end,
}
luazhenlei = sgs.CreateTriggerSkill
{
	name = "luazhenlei",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Predamaged},
	can_trigger = function (self, player)
		return player:hasSkill("luazhenlei")
	end,
	on_trigger = function (self, event, player, data)
		local room = player:getRoom()
		if event == sgs.Predamaged then
			local damage = data:toDamage()
			if (damage.to:isChained() or damage.chain) and damage.nature == sgs.DamageStruct_Thunder  then
				room:playSkillEffect("luazhenlei", 1)
				local log = sgs.LogMessage()
				log.type = "#luazhenlei"
				log.from = damage.to
				room:sendLog(log)
				damage.chain = false
				local recover = sgs.RecoverStruct()
				recover.who = damage.to
				recover.reason = self:objectName()
				recover.recover = damage.damage
				room:recover(damage.to, recover)
				return true
			end
		end
	end,
}
luadaishi_card=sgs.CreateSkillCard
{
	name = "luadaishi_effect",
	target_fixed = true,
	will_throw = false,
}
luadaishivs = sgs.CreateViewAsSkill{
	name = "luadaishivs",
	n = 1,
	view_filter = function(self, selected, to_select)        
			return not to_select:isEquipped()  
	end,
	view_as = function(self, cards)
			if #cards == 1 then 
			local acard = luadaishi_card:clone()        
			acard:addSubcard(cards[1])        
			acard:setSkillName("luadaishi")
			return acard end
	end,
	enabled_at_play = function()
			return false        
	end,
	enabled_at_response = function(self, player, pattern)
			return pattern == "@@luadaishi"       
	end
}
luadaishi = sgs.CreateTriggerSkill
{
	name = "luadaishi",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.AskForRetrial},
	view_as_skill = luadaishivs,
	on_trigger=function(self,event,player,data)
		local room = player:getRoom()
        local ssmy = room:findPlayerBySkillName("luadaishi")
		if ssmy == nil then return false end
        local judge = data:toJudge()
		ssmy:setTag("Judge", data)
        if not room:askForSkillInvoke(ssmy, "luadaishi") then return false end 
		room:playSkillEffect("luadaishi", 1)
        local card = room:askForCard(ssmy,"@@luadaishi","@luadaishi",data)
        if card ~= nil then
			ssmy:obtainCard(judge.card)
			judge.card = sgs.Sanguosha:getCard(card:getEffectiveId())
			room:moveCardTo(judge.card, nil, sgs.Player_Special)
			local log = sgs.LogMessage()
            log.type = "$ChangedJudge"
            log.from = player
            log.to:append(judge.who)
            log.card_str = card:getEffectIdString()
            room:sendLog(log)
			room:sendJudgeResult(judge)
        end
        return false 
    end,
}

--潘凤
--codeby lycio
luajizhan = sgs.CreateTriggerSkill
{
	name = "luajizhan",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.CardEffect, sgs.CardEffected},
	can_trigger = function(self, player)
		return player:hasSkill("luajizhan")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local pf = room:findPlayerBySkillName("luajizhan")
		if pf == nil then return false end
		local effect = data:toCardEffect()
		local card = effect.card

		if card == nil then return false end
		if card:inherits("Slash") then
			local acard = nil
			if card:inherits("ThunderSlash") then 
				acard = sgs.Sanguosha:cloneCard("duel", sgs.Card_Spade, 0)
			elseif card:inherits("FireSlash") then
				acard = sgs.Sanguosha:cloneCard("duel", sgs.Card_Heart, 0)
			else
				acard = sgs.Sanguosha:cloneCard("duel", sgs.Card_NoSuit, 0) 
			end
				
			acard:addSubcard(effect.card:getId())
			acard:setSkillName(self:objectName())
				
			local log = sgs.LogMessage()
			log.type = "$luajizhan"
			log.from = pf
			log.card_str = card:toString()
			room:sendLog(log)
				
			effect.card = acard
			data:setValue(effect)
			room:playSkillEffect("luajizhan", math.random(1,2))
		end
		
		return false
	end,
}
luajizhan_buff = sgs.CreateTriggerSkill
{
	name = "#luajizhan_buff",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Predamage, sgs.Predamaged},
	can_trigger = function (self, player)
		return true
	end,
	on_trigger = function (self, event, player, data)
		local room = player:getRoom()
		local damage = data:toDamage()
		local card = damage.card
		if card:inherits("Duel") and card:getNumber() == 0 then
			if card:getSuit() == sgs.Card_Spade then
				damage.nature = sgs.DamageStruct_Thunder
			elseif card:getSuit() == sgs.Card_Heart then
				damage.nature = sgs.DamageStruct_Fire
			else 
				damage.nature = sgs.DamageStruct_Normal
			end
			data:setValue(damage)
		end
		return false
	end,
}
luazhanma_card = sgs.CreateSkillCard
{
	name = "luazhanma_card",
	target_fixed = true,
	will_throw = true,
	on_use = function(self, room, source, targets)
		source:gainMark("@zmmark", self:subcardsLength())
		room:throwCard(self)
	end,
}

luazhanmavs = sgs.CreateViewAsSkill
{
	name = "luazhanmavs",
	n = 998,
	view_filter = function(self, selected, to_select)
		return true 
	end,
	view_as = function(self, cards)
		if #cards == 0 then return end
		local acard = luazhanma_card:clone()
		for var = 1, #cards, 1 do
			acard:addSubcard(cards[var])
		end
		acard:setSkillName("luazhanma")
		return acard 
	end,
	enabled_at_play = function()
			return false        
	end,
	enabled_at_response = function(self, player, pattern)
			return pattern == "@@luazhanma"       
	end
}
luazhanma = sgs.CreateTriggerSkill
{
	name = "luazhanma",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.PhaseChange},
	view_as_skill = luazhanmavs,
	can_trigger = function(self, player)
		return player:hasSkill("luazhanma")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		if event == sgs.PhaseChange and player:getPhase() == sgs.Player_Start then
			if not room:askForSkillInvoke(player, "luazhanma") then return false end
			room:askForUseCard(player, "@@luazhanma", "@luazhanma:")
			room:playSkillEffect("luazhanma", 1)
			
			if player:getMark("@zmmark") > 0 then 

				room:attachSkillToPlayer(player, "luazhanma_buff")
				
				local log = sgs.LogMessage()
				log.type = "#luazhanma1"
				log.from = player
				room:sendLog(log)
				
			end
		end
		if event == sgs.PhaseChange and player:getPhase() == sgs.Player_Finish then
			if player:hasSkill("luazhanma_buff") then 
				room:detachSkillFromPlayer(player, "luazhanma_buff")
			end
			local x = player:getMark("@zmmark")
			room:setPlayerMark(player, "@zmmark",0)
			
			local log = sgs.LogMessage()
			log.type = "#luazhanma2"
			log.from = player
			log.arg = x
			room:sendLog(log)
			
			return false
		end
	end,
}
luazhanma_buff = sgs.CreateDistanceSkill{
	name = "luazhanma_buff",
	correct_func = function(self,from,to)
		if from:hasSkill("luazhanma") then
			local x = from:getMark("@zmmark")
			return 0-x
		end
	end,
}

--liuba
--codeby lycio
luacaiao = sgs.CreateTriggerSkill
{
	name = "luacaiao",
	events = sgs.SlashEffected,
	can_trigger = function(self,player)
		return player:hasSkill("luacaiao")
	end,
	on_trigger = function(self,event,player,data)
		local room = player:getRoom()
		local source = data:toSlashEffect().from
		if player:isKongcheng() then return false end
		if not room:askForSkillInvoke(player, "luacaiao") then return false end
		local cac = room:askForCardShow(player, source, "@luacaiao")
		
		local log = sgs.LogMessage()
		log.type ="$luacaiao"
		log.from = player
		log.card_str = cac:toString()
		room:sendLog(log)

		room:moveCardTo( cac, source, sgs.Player_Hand, true)
		local x = player:getLostHp()+1
		player:drawCards(x)
		return false
	end,
}
luagushang = sgs.CreateTriggerSkill
{
	name = "luagushang",
	frequency = sgs.Skill_Compulsory,
	events = sgs.Damaged,
	can_trigger = function (self,player)
		return player:hasSkill("luagushang")
	end,
	on_trigger = function (self, event, player, data)
		local room = player:getRoom()
		if not player:isAlive() then return false end
		local damage = data:toDamage()
		local hpmax = player:getMaxHP()
		local hcnum = player:getHandcardNum()
		if hcnum > hpmax then 
			local discard_num = hcnum-hpmax
			local log=sgs.LogMessage()
			log.type ="#gushang1"
			log.from =player
			log.arg = discard_num
			room:sendLog(log)
			room:askForDiscard(player, "luagushang", discard_num)
		end
		if hcnum < hpmax then
			local drawcard_num = hpmax-hcnum
			local log=sgs.LogMessage()
			log.type ="#gushang2"
			log.from =player
			log.arg = drawcard_num
			room:sendLog(log)
			player:drawCards(drawcard_num)
		end
	end,		
}

--华雄
--codeby lycio
luawenjiu = sgs.CreateTriggerSkill
{
	name = "luawenjiu",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Predamage,sgs.Predamaged},
	can_trigger = function (self, player)
		return player:hasSkill("luawenjiu")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local hx = room:findPlayerBySkillName("luawenjiu")
		if hx == nil then return false end
		local damage = data:toDamage()
		local card = damage.card
		if card == nil then return false end
		if card:inherits("Slash") and card:isRed() then
			if damage.from:objectName() == hx:objectName() then
				room:playSkillEffect("luawenjiu", 1)
			elseif damage.to:objectName() == hx:objectName() then
				room:playSkillEffect("luawenjiu", 2)
			end
			
			local log = sgs.LogMessage()
			log.type = "#luawenjiu"
			log.from = hx
			room:sendLog(log)
				
			damage.damage = damage.damage + 1
			data:setValue(damage)
		end
		
		return false
	end,
}
luazhanjiang = sgs.CreateTriggerSkill
{
	name = "luazhanjiang",
	frequency = sgs.Skill_Wake,
	events = {sgs.Death},
	can_trigger = function(self, player)
		return true 
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local damage = data:toDamageStar()
		local hx = room:findPlayerBySkillName("luazhanjiang")
		if hx == nil then return false end
		if (damage.from:getGeneralName() == hx:getGeneralName() and hx:getMark("@waked") == 0) then 
			room:playSkillEffect("luazhanjiang", 1)
			
			local log = sgs.LogMessage()
			log.type = "#luazhanjiang"
			log.from = hx
			room:sendLog(log)
				
			room:loseMaxHp(hx, 1)	
			room:acquireSkill(hx, "luaxuexing")
			room:acquireSkill(hx, "paoxiao")

			hx:gainMark("@waked", 1)
			return false
		end
	end,
}
luaxuexing = sgs.CreateViewAsSkill
{
	name = "luaxuexing",
	n = 1,
	view_filter = function(self, selected, to_select)
        return to_select:isBlack() and to_select:isEquipped()
	end,
	view_as=function(self, cards)
        if #cards==0 then return nil end
		if #cards==1 then         
                local card = cards[1]
				local acard=sgs.Sanguosha:cloneCard("slash", sgs.Card_Heart, card:getNumber()) 
                acard:addSubcard(card:getId())
                acard:setSkillName(self:objectName())
        return acard
        end
	end,
	enabled_at_play=function() 
        return true
	end,
	enabled_at_response=function(self, player, pattern)
		return false
	end,
}

--司马昭
--codeby lycio
luabaiquan = sgs.CreateTriggerSkill
{
	name = "luabaiquan",
	frequency = sgs.Skill_Frequent,
	events = {sgs.CardLost},
	can_trigger = function(self, player)
		return player:hasSkill("luabaiquan")
	end,
	on_trigger = function (self, event, player, data)
		local room = player:getRoom()
		local smz = room:findPlayerBySkillName("luabaiquan")
		if smz == nil then return false end
		local move = data:toCardMove()
		if smz:isKongcheng() then
			if move.from_place == sgs.Player_Hand then 
				if not room:askForSkillInvoke(smz, "luabaiquan") then return false end
				local judge = sgs.JudgeStruct()
				judge.pattern = sgs.QRegExp("(.*):(heart):(.*)")
				judge.good = true
				judge.reason = "luabaiquan"
				judge.who = smz
				room:judge(judge)
				if(judge:isGood()) then                            
					room:setEmotion(smz, "bad")
				else
					room:setEmotion(smz, "good")
					smz:drawCards(smz:getMaxHP())
				end
			end
		end
	end,
}
luamouwei = sgs.CreateTriggerSkill
{
	name = "luamouwei",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.Predamage},
	can_trigger = function(self, player)
		return not player:hasSkill("luamouwei")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local smz = room:findPlayerBySkillName("luamouwei")
		if smz == nil then return false end
		local damage = data:toDamage()
		local source = damage.from 
		local target = damage.to
		local sp = room:getAllPlayers()
		if damage.card ~= nil and damage.card:inherits("SavageAssault") then
			for _,p in sgs.qlist(sp) do
				if p:hasSkill("huoshou") then source = p end
			end
		end		
		if (not source:isKongcheng()) and smz:isAlive() and (not smz:isKongcheng()) then
			if not room:askForSkillInvoke(smz, "luamouwei") then return false end
			local success = smz:pindian(source, "luamouwei", nil)
			if (success) then
				room:loseHp(target, damage.damage)
				return true
			end
		end
	end,
}

--李儒
--codeby lycio
luajiusha_card = sgs.CreateSkillCard
{
	name = "luajiusha_card",
	target_fixed = true,
	will_throw = true,
	on_use = function(self, room, source, targets)
		room:throwCard(self)
	end,
}
luajiushavs = sgs.CreateViewAsSkill
{
	name = "luajiushavs",
	n = 1,
	view_filter = function(self, selected, to_select)
		return to_select:getSuit() == sgs.Card_Spade and (not to_select:inherits("TrickCard") )
	end,
	view_as = function(self, cards)
		if #cards == 0 then return false end
		if #cards == 1 then
			local card = cards[1]
			local acard = luajiusha_card:clone()
			acard:addSubcard(cards[1])
			acard:setSkillName("luajiusha")
			return acard 
		end
	end,
	enabled_at_play = function()
		return false        
	end,
	enabled_at_response = function(self, player, pattern)
		return pattern == "@@luajiusha"       
	end,
}
luajiusha = sgs.CreateTriggerSkill
{
	name = "luajiusha",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.HpRecover},
	view_as_skill = luajiushavs,	
	can_trigger = function(self, player)
		return true
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local recover = data:toRecover()
		local lr = room:findPlayerBySkillName("luajiusha")
		if lr == nil then return false end
		if recover.card == nil then return false end
		if recover.card:inherits("Peach") or recover.card:inherits("Analeptic") then
			if not lr:isNude() then 
				if not room:askForSkillInvoke(lr, "luajiusha") then return false end
				local discard = room:askForUseCard(lr, "@@luajiusha", "@luajiusha:")
				if discard then
					room:playSkillEffect("luajiusha", math.random(1,2))
					if room:askForSkillInvoke(lr, "luafuhei") then 
						room:playSkillEffect("luafuhei", 1)
						local judge = sgs.JudgeStruct()
						judge.pattern = sgs.QRegExp("(.*):(spade):(.*)")
						judge.who = lr
						judge.good = true
						judge.reason = "luabaiquan"
						room:judge(judge)
						if(judge:isGood()) then                            
							room:setEmotion(lr, "good")
							local recover = sgs.RecoverStruct()
							recover.reason = "luafuhei"
							recover.who = lr
							recover.recover = 1
							room:recover(lr, recover)
						else
							room:setEmotion(lr, "bad")
						end
						lr:obtainCard(judge.card)
					end
					return true
				else 
					return false
				end
			end
		end
	end,		
}
luafuhei = sgs.CreateTriggerSkill
{
	name = "luafuhei",
	frequency = sgs.Skill_Frequent,
	events = {sgs.Damaged},
	can_trigger = function(self, player)
		return player:hasSkill("luafuhei")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		if player:isAlive() then
			local damage = data:toDamage()
			for var = 1, damage.damage, 1 do
				if not room:askForSkillInvoke(player, "luafuhei") then return false end
				room:playSkillEffect("luafuhei", 2)
				local judge = sgs.JudgeStruct()
				judge.pattern = sgs.QRegExp("(.*):(spade):(.*)")
				judge.who = player
				judge.good = true
				judge.reason = "luabaiquan"
				room:judge(judge)
				if(judge:isGood()) then                            
					room:setEmotion(player, "good")
					local recover = sgs.RecoverStruct()
					recover.reason = "luafuhei"
					recover.who = player
					recover.recover = 1
					room:recover(player, recover)
				else
					room:setEmotion(player, "bad")
				end
				player:obtainCard(judge.card)
			end
		end
	end,
}
luayihen = sgs.CreateTriggerSkill
{
	name = "luayihen",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Death},
	can_trigger = function(self, player)
		return player:hasSkill("luayihen")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local damage = data:toDamageStar()
		local source = damage.from
		local sp = room:getAllPlayers()
		if damage.card ~= nil and damage.card:inherits("SavageAssault") then
			for _,p in sgs.qlist(sp) do
				if p:hasSkill("huoshou") then source = p end
			end
		end
		
		local log = sgs.LogMessage()
		log.type = "#luayihen"
		log.from = player 
		log.to:append(source)
		room:sendLog(log)
			
		room:acquireSkill(source, "luayihen_buff")
	end,
}
luayihen_buff = sgs.CreateTriggerSkill
{
	name = "luayihen_buff",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.PhaseChange},
	can_tigger = function(self, player)
		return player:hasSkill("luayihen_buff") 
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		if event == sgs.PhaseChange and player:getPhase() == sgs.Player_Discard then 
			local hcnum = player:getHandcardNum()
			local hp = player:getHp()
			local discard_num = hcnum - hp
			local sp = room:getAllPlayers()
			for _,p in sgs.qlist(sp) do
				if p:hasSkill("juejing") then discard_num = discard_num - 2 end
			end
			room:askForDiscard(player, "luayihen_buff", math.min(discard_num + 1,hcnum), true, false)
			return true
		end
	end,
}
--冷艳锯
--codeby lycio
luahuixuan_card = sgs.CreateSkillCard
{
	name = "luahuixuan_card",
	target_fixed = true,
	will_throw = true,
	on_use = function(self, room, source, targets)
		room:throwCard(self)
	end,
}
luahuixuanvs = sgs.CreateViewAsSkill
{
	name = "luahuixuanvs",
	n = 1,
	view_filter = function(self, selected, to_select)
		return to_select:isRed()
	end,
	view_as = function(self, cards)
		if #cards == 0 then return false end
		if #cards == 1 then
			local card = cards[1]
			local acard = luajiusha_card:clone()
			acard:addSubcard(cards[1])
			acard:setSkillName("luahuixuan")
			return acard 
		end
	end,
	enabled_at_play = function()
		return false        
	end,
	enabled_at_response = function(self, player, pattern)
		return pattern == "@@luahuixuan"       
	end,
}
luahuixuan = sgs.CreateTriggerSkill
{
	name = "luahuixuan",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.PhaseChange,sgs.CardResponsed,sgs.SlashMissed},
	view_as_skill = luahuixuanvs,	
	can_trigger = function(self, player)
		return true
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local lyj = room:findPlayerBySkillName("luahuixuan")
		if lyj == nil then return false end
		if event == sgs.PhaseChange and lyj:getPhase() == sgs.Player_Start then
			lyj:setFlags("luahuixuan_canuse")
			room:setPlayerMark(lyj, "@hxbuff", 0)
			
			local log = sgs.LogMessage()
			log.type = "#luahuixuan1"
			log.from = lyj
			room:sendLog(log)
			
		end
		if event == sgs.CardResponsed and lyj:getPhase() == sgs.Player_Play then
			local card = data:toCard()
			if card:inherits("Slash") then lyj:setFlags("-luahuixuan_canuse") end
		end
		if event == sgs.PhaseChange and lyj:getPhase() == sgs.Player_Discard then
			if lyj:hasFlag("luahuixuan_canuse") and lyj:getSlashCount() == 0 and room:askForSkillInvoke(lyj, "luahuixuan") then 
				room:askForDiscard(lyj, "luahuixuan", 1, true, true)
				lyj:gainMark("@hxbuff",1)
				
				local log = sgs.LogMessage()
				log.type = "#luahuixuan2"
				log.from = lyj
				room:sendLog(log)
				
				return true
			end
		end
		if event == sgs.SlashMissed then
			local effect = data:toSlashEffect()
			local to = effect.to
			local from = effect.from
			
			if lyj == nil then return false end
			if lyj:getMark("@hxbuff") > 0 and to:getGeneralName() ~= lyj:getGeneralName() and from:getGeneralName() ~= lyj:getGeneralName() then
				if not room:askForSkillInvoke(lyj, "luahuixuan") then return false end
				local card = room:askForUseCard(lyj, "@@luahuixuan", "@luahuixuan_slash:")
				if card then
					local slash = sgs.Sanguosha:cloneCard("slash", sgs.Card_NoSuit, 0)
					
					local log = sgs.LogMessage()
					log.type = "#luahuixuan3"
					log.from = lyj 
					log.to:append(to) 
					log.arg = from:getGeneralName()
					room:sendLog(log)
					
					room:cardEffect(slash, from, to)
	--				room:setPlayerMark(lyj, "@hxbuff", 0)
				else 
					return false
				end
			end
		end
	end,		
}
luadaohun = sgs.CreateTriggerSkill
{
	name = "luadaohun",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.CardLost,sgs.FinishJudge},
	priority = -1,
	can_trigger = function(self, player)
		return not player:hasSkill("luadaohun")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local lyj = room:findPlayerBySkillName("luadaohun")
		if lyj == nil then return false end
		local blade = nil
		local from = nil
		if event == sgs.CardLost then
			local move = data:toCardMove()
			local card = sgs.Sanguosha:getCard(move.card_id)
			if room:getCardPlace(card:getEffectiveId()) == sgs.Player_DiscardedPile and card:inherits("Blade") then 
				blade = card
				from = move.from
			else 
				return false
			end
		end
		if event == sgs.FinishJudge then 
			local judge = data:toJudge()
			if room:getCardPlace(judge.card:getEffectiveId()) == sgs.Player_DiscardedPile and judge.card:inherits("Blade") then
				blade = judge.card
			else 
				return false
			end
		end

			if not room:askForSkillInvoke(lyj, "luadaohun") then return false end
			local sp = {}
			if from then 
				sp = room:getOtherPlayers(from)
			else	
				sp = room:getAllPlayers()
			end
			local tos = sgs.SPlayerList()
			for _,p in sgs.qlist(sp) do
				if not p:getWeapon() then tos:append(p) end
			end
			if not tos:isEmpty() then 
				local to = room:askForPlayerChosen(lyj, tos, "@luadaohun")
				room:moveCardTo(blade, to, sgs.Player_Equip)
			
				local log = sgs.LogMessage()
				log.type = "$luadaohun"
				log.from = to 
				log.card_str = blade:toString()
				room:sendLog(log)		
				
			else
				lyj:obtainCard(blade) 
			end
			return false	

	end,
}
lualongyin = sgs.CreateTriggerSkill
{
	name = "lualongyin",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.Predamage},
	can_trigger = function(self, player)
		return player:getGeneralName() == "guanyu" or player:getGeneralName() == "sp_guanyu" or player:getGeneralName() == "shenguanyu" or player:getGeneralName() == "luaguanyu" or (player:getWeapon() and player:getWeapon():className()=="Blade")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local lyj = room:findPlayerBySkillName("lualongyin")
		if lyj == nil then return false end
		local damage = data:toDamage()
		local card = damage.card
		if card:inherits("Slash") and card:isRed() then
			if not room:askForSkillInvoke(lyj, "lualongyin") then return false end
			local judge = sgs.JudgeStruct()
			judge.pattern = sgs.QRegExp("(.*):(heart):(.*)")
			judge.good = true
			judge.reason = "lualongyin"
			judge.who = lyj
			room:judge(judge)
			if (judge:isGood()) then
				room:setEmotion(lyj, "good")
				damage.damage = damage.damage + 1
				data:setValue(damage)
				
				local log = sgs.LogMessage()
				log.type = "#lualongyin_good"
				log.from = lyj
				log.to:append(damage.to)
				room:sendLog(log)
						
				return false
			else
				
				room:setEmotion(lyj, "bad")
				
				local log = sgs.LogMessage()
				log.type = "#lualongyin_bad"
				log.from = lyj
				log.to:append(damage.to)
				room:sendLog(log)
				
				lyj:obtainCard(judge.card)
				return false
			end
		end
	end,
}
luaguiling = sgs.CreateTriggerSkill
{
	name = "luaguiling",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Death},
	can_trigger = function(self, player)
		return player:hasSkill("luaguiling")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local damage = data:toDamageStar()
		local source = damage.from
		local sp = room:getAllPlayers()
		if damage.card ~= nil and damage.card:inherits("SavageAssault") then
			for _,p in sgs.qlist(sp) do
				if p:hasSkill("huoshou") then source = p end
			end
		end
				
		local log = sgs.LogMessage()
		log.type = "#luaguiling"
		log.from = player 
		log.to:append(source)
		room:sendLog(log)
			
		room:acquireSkill(source, "luaguiling_buff")
		if source:getWeapon() then 
			room:throwCard(source:getWeapon())
			return false
		end

	end,
}
luaguiling_buff = sgs.CreateTriggerSkill
{
	name = "luaguiling_buff",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.CardUsed,sgs.SlashMissed},
	can_trigger = function(self, player)
		return player:hasSkill("luaguiling_buff")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()

		if event == sgs.CardUsed and player:getPhase() == sgs.Player_Play then
			local use = data:toCardUse()
			if use.card:inherits("Weapon") then 
				
				local log = sgs.LogMessage()
				log.type = "$luaguiling_buff"
				log.from = player 
				log.card_str = use.card:toString()
				room:sendLog(log)
				
				room:throwCard(use.card)
				return true
			end
		end
		if event == sgs.SlashMissed then 
			local effect = data:toSlashEffect()
			if effect.to:hasSkill("kongcheng") and effect.to:isKongcheng() then return false end
			if not room:askForSkillInvoke(player, "luaguiling_buff") then return false end
			local slash = room:askForCard(player, "slash", "@blade-slash")
			if slash == nil then return false end
			local use = sgs.CardUseStruct()
			use.from = effect.from
			use.to:append(effect.to)
			use.card = slash
			room:useCard(use, false)
		end
	end,			
}

--丁奉
--codeby lycio
luaxuexi = sgs.CreateTriggerSkill
{
	name = "luaxuexi",
	frequency = sgs.Skill_NotFrequent,
	events ={sgs.CardLost,sgs.TurnStart},
	can_trigger = function(self, player)
		return true
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local df = room:findPlayerBySkillName("luaxuexi")
		local current = room:getCurrent()
		if df == nil then return false end
		if event == sgs.CardLost and df:getPhase() == sgs.Player_NotActive then
			local move = data:toCardMove()
			
			if (move.from_place == sgs.Player_Hand or move.from_place == sgs.Player_Equip) and move.from:getGeneralName() == df:getGeneralName() then 
				if current:getHp() > df:getHp() then
					room:setPlayerMark(df, "xuexi_canuse", 1)
				end
			end
			return false
		end
		if event == sgs.TurnStart and df:getMark("xuexi_canuse") == 1 then
			room:setPlayerMark(df, "xuexi_canuse", 0)
			if not room:askForSkillInvoke(df, "luaxuexi") then return false end
				
			local log = sgs.LogMessage()
			log.type = "#luaxuexi1"
			log.from = df
			room:sendLog(log)
		
			local current = room:getCurrent()
			room:setCurrent(df)
			room:getThread():trigger(sgs.TurnStart, df)
			
			local log = sgs.LogMessage()
			log.type = "#luaxuexi2"
			log.from = df
			room:sendLog(log)
			
			room:setCurrent(current)
			return false
		end
	end,
}
luashuangleng = sgs.CreateTriggerSkill
{
	name = "luashuangleng",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Damage},
	can_trigger = function(self, player)
		return player:hasSkill("luashuangleng")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local choice = room:askForChoice(player, "luashuangleng", "turnover+losehp")
		
		local log = sgs.LogMessage()
		log.type = "#luashuangleng"
		log.from = player
		log.arg = choice
		room:sendLog(log)
		
		if choice == "losehp" then
			room:loseHp(player,1)
		end
		if choice == "turnover" then
			player:turnOver()
		end
	end,
}

--左慈
--codeby lycio
luafenbei = sgs.CreateTriggerSkill
{
	name = "luafenbei",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.PhaseChange},
	can_trigger = function(self, player)
		return player:hasSkill("luafenbei")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		if player:getPhase() == sgs.Player_Draw then
			if not room:askForSkillInvoke(player, "luafenbei") then return false end
			room:playSkillEffect("luafenbei", math.random(1,2))
			local to = room:askForPlayerChosen(player, room:getOtherPlayers(player), "luafenbei")
			to:drawCards(2)
			local x = math.abs((to:getHandcardNum()+1)/2)
			for v=1, x, 1 do
				local card_id = room:askForCardChosen(player, to, "h", "luafenbei")
				room:moveCardTo(sgs.Sanguosha:getCard(card_id), player, sgs.Player_Hand, false)
			end
			room:setEmotion(to, "bad")
			
			local log = sgs.LogMessage()
			log.type = "#luafenbei"
			log.from = player
			room:sendLog(log)
			
			return true
		end
	end,
}

luayindun_buff = sgs.CreateProhibitSkill{
	name = "#luayindun_buff",
	is_prohibited = function(self, from, to, card)
		local suit = sgs.Sanguosha:getCard(to:getPile("yd_pile"):at(0)):getSuitString()
		return card:getSuitString() == suit and to:getMark("yd_buff") == 1
	end,
}
luayindun = sgs.CreateTriggerSkill
{
	name = "luayindun",
	frequency = sgs.Skill_NotFrequent,
	events = {sgs.CardEffected,sgs.CardDiscarded,sgs.PhaseChange},
	can_trigger = function(self, player)
		return true
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local zc = room:findPlayerBySkillName("luayindun")
		if zc == nil then return false end
		
		if (event == sgs.CardDiscarded and zc:getPhase() == sgs.Player_Discard) then
			local card = data:toCard()
			if(card:subcardsLength() == 0) then return false end
			if not room:askForSkillInvoke(zc, "luayindun")then return false end
			room:playSkillEffect("luayindun", math.random(1,3))
			room:setPlayerMark(zc, "yd_buff", 1)
			local discards = sgs.IntList()
			for _,cdid in sgs.qlist(card:getSubcards()) do
				if room:getCardPlace(cdid)==sgs.Player_DiscardedPile then
					discards:append(cdid)
				end
			end
			room:fillAG(discards, zc);
			local ydid = room:askForAG(zc, discards, true, "luayindun")

			zc:addToPile("yd_pile", ydid, true)
			zc:invoke("clearAG")
			local log = sgs.LogMessage()
			log.type = "#luayindun"
			log.from = zc
			log.arg = sgs.Sanguosha:getCard(ydid):getSuitString()
			room:sendLog(log)
			return false
		end

		if event == sgs.PhaseChange and zc:getPhase() == sgs.Player_Start then
			room:setPlayerMark(zc, "yd_buff", 0)
			zc:clearPrivatePiles()
			return false
		end
	end,
}

--吕布
--codeby lycio
luabisha = sgs.CreateTriggerSkill
{
	name = "luabisha",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Predamage},
	can_trigger = function(self, player)
		return player:hasSkill("luabisha")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local damage = data:toDamage()
		if damage.to:getWeapon() ~= nil then return false end
		if damage.to:getArmor() ~= nil then return false end
		if damage.to:getOffensiveHorse() ~= nil then return false end
		if damage.to:getDefensiveHorse() ~= nil then return false end
		if not damage.card:inherits("Slash") then return false end
		
		local log = sgs.LogMessage()
		log.type = "#luabisha"
		log.from = player
		log.to:append(damage.to)
		log.arg = damage.to:getHp()
		room:sendLog(log)
		
		damage.damage = damage.to:getHp()
		data:setValue(damage)
		room:playSkillEffect("luabisha",1)
	end,
}
luakongju = sgs.CreateTriggerSkill
{
	name = "luakongju",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.SlashMissed},
	can_trigger = function(self, player)
		return not player:hasSkill("luakongju")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local lfx = room:findPlayerBySkillName("luakongju")
		if lfx == nil then return false end
		local effect = data:toSlashEffect()
		if effect.to:objectName() ~= lfx:objectName() then return false end
		
		local log = sgs.LogMessage()
		log.type = "#luakongju"
		log.from = player
		room:sendLog(log)
		
		effect.from:turnOver()
		room:playSkillEffect("luakongju",1)
		return false
	end,
}
luayuanmie = sgs.CreateTriggerSkill
{
	name = "luayuanmie",
	frequency = sgs.Skill_Compulsory,
	events = {sgs.Predamaged},
	can_trigger = function(self, player)
		return player:hasSkill("luayuanmie")
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		local damage = data:toDamage()
		room:loseMaxHp(player, damage.damage)
		
		local log = sgs.LogMessage()
		log.type = "#luayuanmie"
		log.from = player
		log.arg = damage.damage
		room:sendLog(log)
		
		room:playSkillEffect("luayuanmie",1)
		return true
	end,
}
luahuijin = sgs.CreateTriggerSkill
{
	name = "luahuijin",
	frequency = sgs.Skill_Limited,
	events = {sgs.GameStart},
	can_trigger = function(self, player)
		return player:hasSkill("luahuijin") 
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		if event == sgs.GameStart then player:gainMark("hjlmt", 1) end
		return false
	end,
}
luahuijin_use = sgs.CreateTriggerSkill
{
	name = "#luahuijin_use",
	frequency = sgs.Skill_Limited,
	events = {sgs.PhaseChange},
	can_trigger = function(self, player)
		return player:getMark("hjlmt") == 1
	end,
	on_trigger = function(self, event, player, data)
		local room = player:getRoom()
		if event == sgs.PhaseChange and player:getPhase() == sgs.Player_Discard and player:getMaxHP() == 1 then
			room:playSkillEffect("luahuijin",1)
			player:throwAllCards()
			room:killPlayer(player)
			local sp = room:getOtherPlayers(player)
			room:killPlayer(player:getNextAlive())
			room:killPlayer(sp:last())
			room:setPlayerMark(player, "hjlmt", 0)
			return false
		end
	end,
}



lualajiche:addSkill(luayihen_buff)
lualajiche:addSkill(luaxuexing)
lualajiche:addSkill(luazhanma_buff)
lualajiche:addSkill(luaguiling_buff)

luasimahui:addSkill(luayinshi_buff)
luasimahui:addSkill(luayinshi)
luasimahui:addSkill(luashuijing)

luajiping:addSkill(luazhenzhi)
luajiping:addSkill(luahuanhun_record)
luajiping:addSkill(luahuanhun)
luajiping:addSkill(lualianyu)
luajiping:addSkill(luayincang)

shenluasimazhongda:addSkill(luadaishi)
shenluasimazhongda:addSkill(lualietian)
shenluasimazhongda:addSkill(luazhenlei)

luapanfeng:addSkill(luajizhan)
luapanfeng:addSkill(luajizhan_buff)
luapanfeng:addSkill(luazhanma)

lualiuba:addSkill(luacaiao)
lualiuba:addSkill(luagushang)

luahuaxiong:addSkill(luawenjiu)
luahuaxiong:addSkill(luazhanjiang)

luasimazhao:addSkill(luabaiquan)
luasimazhao:addSkill(luamouwei)

lualiru:addSkill(luajiusha)
lualiru:addSkill(luafuhei)
lualiru:addSkill(luayihen)

lualengyanju:addSkill(luahuixuan)
lualengyanju:addSkill(luadaohun)
lualengyanju:addSkill(lualongyin)
lualengyanju:addSkill(luaguiling)

luadingfeng:addSkill(luaxuexi)
luadingfeng:addSkill(luashuangleng)

luazuoci:addSkill(luafenbei)
luazuoci:addSkill(luayindun)
luazuoci:addSkill(luayindun_buff)

shenlualvfengxian:addSkill(luabisha)
shenlualvfengxian:addSkill(luakongju)
shenlualvfengxian:addSkill(luayuanmie)
shenlualvfengxian:addSkill(luahuijin)
shenlualvfengxian:addSkill(luahuijin_use)

sgs.LoadTranslationTable{
	["qhs"] = "皇包",
	
	["luasimahui"] = "司马徽",
	["~luasimahui"] = "我，还是太嫩了吗？",
	["luayinshi"] = "隐士",
	[":luayinshi"] = "<b>锁定技，</b>你不能成为所有延时性锦囊的目标；你对其他角色使用基本牌时，若你不在其攻击范围内，则该牌无效且你摸一张牌；其他角色对你使用基本牌时，若其不在你的攻击范围内，则该牌无效且你摸一张牌。",
	["#yinshi"] = "%from 的锁定技<font color='yellow'><b>【隐士】</b></font>被触发，<font color='yellow'><b>【%arg】</b></font>无效 ",
	["$luayinshi"] = "有道则显，无道则隐",
	["luashuijing"] = "水镜",
	[":luashuijing"] = "当有角色体力值发生变动时，你可进行一次判定，若你弃置一张与判定牌花色相同的手牌，则该角色体力值的变动量+1。",
	["$luashuijing"] = "上善若水，镜鉴才俊",
	["#luashuijing"] = "%arg 的体力值即将变动",
	["$luashuijing1"] = "%from 弃掉了一张 <b><font color='yellow'>%card</font></b> 此体力流失量将 <b><font color='#98fb98'>+1</font></b> ！",
	["$luashuijing2"] = "%from 弃掉了一张 <b><font color='yellow'>%card</font></b> 此体力回复量将 <b><font color='#98fb98'>+1</font></b> ！",
	["$luashuijing3"] = "%from 弃掉了一张 <b><font color='yellow'>%card</font></b> 此伤害量将 <b><font color='#98fb98'>+1</font></b> ！",
	["$luashuijing4"] = "%from 放弃了弃牌，此变动量 <b><font color='yellow'>不变</font></b> ",
	["@luashuijing1"] = "你可以弃掉一张与此判定牌花色相同的手牌，令此体力变化量+1",
	["@luashuijing2"] = "你可以弃掉一张与此判定牌花色相同的手牌，令此体力变化量-1",
	
	["luajiping"] = "吉平",
	["~luajiping"] = "我，恨啊……",
	["luazhenzhi"] = "针炙",
	[":luazhenzhi"] = "当你受到伤害时，若伤害值小于3，你可指定伤害来源流失X点体力值，然后你与该角色各摸X张牌，若伤害值等于3或更多且你的武将牌正面朝上，你可摸X张牌后将武将牌翻面，然后指定其他任意一名角色立即死亡，X为你受到的伤害值。",
	["@luazhenzhi"] = "请选择一名角色，其将立即死亡",
	["#luazhenzhi"] = "<font color='red'><b>一个人的时候~不是不可以~~</b></font> %from 拿起银针念起咒语， %arg 感到浑身不自在…",
	["#luahuanhun"] = "隐藏技能",
	[":#luahuanhun"] = "选择一名已死亡的角色立即回复所有体力并将手牌补至体力上限，若如此做，你本回合武将牌不可翻回正面朝上。",
	["#luahuanhun1"] = "<font color='red'><b>信我者~得永生~~</b></font> %from 发动了史前秘技，令 %arg 借尸还魂满状态复活了！",
	["lualianyu"] = "链愈",
	[":lualianyu"] = "当你回复体力时，若你处于连环状态，你可令任意一名同处于连环状态的角色弃一张红桃牌，若其如此做，该角色可回复1点体力。",
	["@lualianyu"] = "请选择一名角色作为【链愈】的目标",
	["@lianyucard"] = "请选择一张红桃牌弃置，然后你可以回复1点体力",
	["#lualianyu"] = "%from 放弃了弃牌 ",
	["$lualianyu"] = "%from 弃掉了一张 <b><font color='yellow'>%card</font></b> ",
	["luayincang"] = "隐藏技能",
	[":luayincang"] = "隐藏技能，自己摸索吧",
	
	["shenluasimazhongda"] = "神·司马仲达",
	["~shenluasimazhongda"] = "难道，真是天命难违？",
	["luadaishi"] = "待时",
	[":luadaishi"] = "任意角色判定牌生效前，你可以用任意一张手牌替代之。",
	["@luadaishi"] = "请选择一张手牌",
	["$luadaishi"] = "天命，哈哈哈~",
	["lualietian"] = "裂天",
	[":lualietian"] = "你每受到一次伤害，可令任意一名角色判定，若为黑桃2~9，你对该角色造成3点雷电伤害。",
	["@lualietian"] = "请选择一名角色",
	["$lualietian"] = "出来混，迟早要还的！",
	["luazhenlei"] = "震雷",
	[":luazhenlei"] = "<b>锁定技，</b>当你处于连环状态时，你受到的雷电伤害转化为回复体力。",
	["$luazhenlei"] = "吾乃天命之子~~",
	["#luazhenlei"] = "%from 的技能 <font color='yellow'><b>【震雷】</b></font> 被触发，伤害将转化为体力回复",
	
	["luapanfeng"] = "潘凤",
	["~luapanfeng"] = "我是无双上将！！啊！！！",
	["luajizhan"] = "激战",
	["$luajizhan1"] = "区区华雄，不足挂齿。",
	["$luajizhan2"] = "激斗无双，战意高昂。",
	[":luajizhan"] = "<b>锁定技，</b>你使用的【杀】或指定你为目标的【杀】，均视为【决斗】的结算过程，此决斗造成的伤害属性与杀的属性一致。（此杀计入回合使用杀的限制）",
	["$luajizhan"] = "%from 的锁定技 <font color='yellow'><b>【激战】</b></font> 被触发，<font color='yellow'><b>%card</b></font> 将执行 <font color='yellow'><b>【决斗】</b></font> 的流程",
	["luazhanma"] = "战马",
	["$luazhanma"] = "驰骋千里，杀敌万千。",
	[":luazhanma"] = "回合开始阶段，你可以弃掉任意张牌，若如此做，直到本回合结束前，你与其他角色计算距离时，始终-X（X为你所弃的牌数）",
	["#luazhanma1"] = "%from 获得了技能 <font color='yellow'><b>【战马状态】</b></font> ",
	["#luazhanma2"] = "%from 失去了 <b><font color='#98fb98'>%arg</font></b> 枚 <font color='yellow'><b>战马标记</b></font> 和技能 <font color='yellow'><b>【战马状态】</b></font> ",
	["luazhanma_buff"] = "战马状态",
	[":luazhanma_buff"] = "锁定技，你与其他角色计算距离时始终-X（X为你获得的战马标记数）",
	["@luazhanma"] = "请选择需要弃置的卡牌",
	
	["lualiuba"] = "刘巴",	
	["luacaiao"] = "才傲",	
	[":luacaiao"] = "当你成为杀的目标时（结算之前），你可展示一张手牌后将该牌交给杀的来源，然后你摸X+1张牌，X为你损失的体力值。",	
	["@luacaiao"] = "请选择一张牌",
	["$luacaiao"] = "%from 展示了 <font color='yellow'><b>%card</b></font> ",
	["luagushang"] = "孤尚",	
	[":luagushang"] = "<b>锁定技，</b>当你受到伤害后，你需要摸牌或弃牌，使手牌数量等于你的体力上限",	
	["#gushang1"] = "%from 的锁定技 <font color='yellow'><b>【孤尚】</b></font> 被触发，必须弃掉 <font color='#98fb98'><b>%arg</b></font> 张牌 ",
	["#gushang2"] = "%from 的锁定技 <font color='yellow'><b>【孤尚】</b></font> 被触发，必须摸 <font color='#98fb98'><b>%arg</b></font> 张牌 ",
	
	["luahuaxiong"] = "华雄",
	["~luahuaxiong"] = "敌将太猛了！",
	["luawenjiu"] = "温酒",
	["$luawenjiu1"] = "知道厉害了吧！",
	["$luawenjiu2"] = "厉害！",
	[":luawenjiu"] = "<b>锁定技，</b>你对其他角色使用的红色杀或其他角色对你使用的红色杀造成的伤害+1。",
	["#luawenjiu"] = "%from 的锁定技 <font color='yellow'><b>【温酒】</b></font> 被触发，红色杀造成的伤害将 <b><font color='#98fb98'>+1</font></b> ",
	["luazhanjiang"] = "斩将",
	["$luazhanjiang"] = "杀敌斩将，万夫莫挡。",
	[":luazhanjiang"] = "<b>觉醒技，</b>当你杀死一名角色时，你须自减1点体力上限并永久获得技能【咆哮】和【血性】（出牌阶段，你可以将装备区里的一张黑色牌当做红桃【杀】使用）。",
	["#luazhanjiang"] = "%from 的觉醒技 <font color='yellow'><b>【斩将】</b></font> 被触发，减少了 1 点体力上限",
	["luaxuexing"] = "血性",
	["$luaxuexing"] = "吃我一刀。",
	[":luaxuexing"] = "出牌阶段，你可以将装备区里的一张黑色牌当做红桃【杀】使用。",
	
	["luasimazhao"] = "司马昭",
	["~luasimazhao"] = "命丧铁笼，天不佑我！",
	["luabaiquan"] = "拜泉",
	["$luabaiquan"] = "拜泉求甘露，解吾铁笼围。",
	[":luabaiquan"] = "每当你失去最后一张手牌时，可进行一次判定，若不为<font color='red'><b>♥</b></font>，则你将手牌补至体力上限的张数。",
	["luamouwei"] = "谋魏",
	["$luamouwei1"] = "曹魏已衰，司马必兴。",
	["$luamouwei2"] = "我是老大我怕谁？",
	["$luamouwei3"] = "曹髦小儿，自不量力。",
	[":luamouwei"] = "每当其他角色造成伤害时，你可以与该角色拼点，若你赢，则该伤害视为体力流失。",
		
	["lualiru"] = "李儒",
	["luajiusha"] = "鸩杀",
	[":luajiusha"] = "每当有角色使用(或被使用)一张【桃】或【酒】回复体力时，你可弃置一张黑桃的基本牌（或黑桃的装备牌）抵消该效果。",
	["$luajiusha1"] = "汝休想活命!",
	["$luajiusha2"] = "比三鹿好喝吧。",
	["@luajiusha"] = "请选中一张黑桃基本牌或一张黑桃装备牌",
	["luafuhei"] = "腹黑",
	[":luafuhei"] = "每当你受到1点伤害或发动一次“鸩杀”时，可进行一次判定，若为黑桃则你回复1点体力。无论判定结果如何，获得该判定牌。",
	["$luafuhei1"] = "算无遗露，洞悉先机。",
	["$luafuhei2"] = "低调，低调！",
	["luayihen"] = "遗恨",
	[":luayihen"] = "<b>锁定技，</b>杀死你的角色弃牌阶段须额外弃一张手牌。",
	["$luayihen"] = "早知如此，何必当初？",
	["#luayihen"] = "%from 的锁定技 <font color='yellow'><b>【遗恨】</b></font> 被触发",
	["luayihen_buff"] = "遗恨状态",
	[":luayihen_buff"] = "<b>锁定技，</b>你的弃牌阶段须额外弃一张手牌。",
	
	["lualengyanju"] = "冷艳锯",
	["~lualengyanju"] = "主人，我终于找到你了！",
	["luahuixuan"] = "回旋",
	[":luahuixuan"] = "若你在出牌阶段没有使用或打出一张【杀】，则你可以弃一张牌跳过弃牌阶段，若如此做，直到你的下个回合开始前，获得“回旋状态”。（其他角色使用的【杀】被闪避时，你可弃掉一张红色牌视为该角色再次对同一目标使用了一张【杀】）",
	["#luahuixuan1"] = "%from 失去了 <b><font color='#98fb98'>1</font></b> 枚 <font color='yellow'><b>回旋标记</b></font> 和 <font color='yellow'><b>【回旋状态】</b></font> ",
	["#luahuixuan2"] = "%from 获得了 <font color='yellow'><b>【回旋状态】</b></font> ",	
	["@luahuixuan_slash"] = "请选择一张红色牌来发动【回旋】",
	["#luahuixuan3"] = "%from 弃置了一张 红色牌 视为 %arg 对 %to 使用了一张 <font color='yellow'><b>杀[无色]</b></font>",
	["luadaohun"] = "刀魂",
	[":luadaohun"] = "你可以直接获得其他角色因弃置或判定而进入弃牌堆的【青龙偃月刀】，并将其置于任意一名未装备武器的角色的装备区内。",
	["$luadaohun"] = "%from 装备了 <font color='yellow'><b>%card</b></font> ",
	["lualongyin"] = "龙吟",
	[":lualongyin"] = "当关羽或已装备【青龙偃月刀】的角色使用红色杀造成伤害时，你可以进行一次判定，若结果为<font color='red'><b>♥</b></font>，则该伤害+1，若不为<font color='red'><b>♥</b></font>，你获得该判定牌。",
	["#lualongyin_good"] = "%from 判定成功，%to 受到的伤害将 <b><font color='#98fb98'>+1</font></b> ", 
	["#lualongyin_bad"] = "%from 判定失败，%to 受到的伤害 <b><font color='#98fb98'>不变</font></b> ", 
	["luaguiling"] = "归灵",
	[":luaguiling"] = "<b>锁定技，</b>当你死亡时，杀死你的角色立即弃置已装备的武器并且不可装备任何武器，永久获得【青龙偃月刀】的效果。",
	["#luaguiling"] = "%from 的锁定技 <font color='yellow'><b>【归灵】</b></font> 被触发",
	["luaguiling_buff"] = "归灵状态",
	[":luaguiling_buff"] = "锁定技，你不可装备任何武器且永久获得【青龙偃月刀】的效果（不包括攻击范围）。",
	["$luaguiling_buff"] = "%from 的锁定技 <font color='yellow'><b>【归灵状态】</b></font> 被触发，不可装备武器， <font color='yellow'><b>%card</b></font> 直接进入弃牌堆",
	["@blade-slash"] = "你可以再使用一张【杀】发动青龙偃月刀的追杀效果",
	
	["luadingfeng"] = "丁奉",
	["luaxuexi"] = "雪袭",
	[":luaxuexi"] = "当你在回合外失去牌时，若当前回合角色的体力值大于你的当前体力值，你可在该回合结束时进行一个额外的回合。",
	["#luaxuexi1"] = "%from 将进行一个额外的回合",
	["#luaxuexi2"] = "%from 的额外的回合结束",
	["luashuangleng"] = "霜冷",
	[":luashuangleng"] = "<b>锁定技，</b>你每造成一次伤害，你须流失1点体力或将你的武将牌翻面。",
	["losehp"] = "流失1点体力",
	["turnover"] = "将武将牌翻面",
	["#luashuangleng"] = "%from 的锁定技 <font color='yellow'><b>【霜冷】</b></font> 被触发， %from 选择了 <b><font color='#98fb98'>%arg</font></b> ",
	
	["luazuoci"] = "左慈",
	["~luazuoci"] = "驾鹤西行，成仙而去。",
	["luafenbei"] = "分杯",
	["$luafenbei1"] = "分杯共饮，不偏不倚。",
	["$luafenbei2"] = "玉簪分酒，你有我有。",
	[":luafenbei"] = "摸牌阶段，你可以放弃摸牌令一名角色摸两张牌，然后你从其手牌里抽取一半的牌（向上取整）。",
	["#luafenbei"] = "%from 跳过了 <font color='yellow'><b>摸牌</b></font> 阶段",
	["luafangshu"] = "方术",
	[":luafangshu"] = "出牌阶段，你可以将一张非<font color='red'><b>♥</b></font>的基本牌置于其他一名角色武将牌之上，称为“方术牌”，直到该角色回合结束前，其手牌均视为方术牌，该角色回合结束后，方术牌进入弃牌堆。",
	["luafangshucard"] = "方术",
	["luafangshu_buff"] = "方术状态",
	["luayindun"] = "隐遁",
	["$luayindun1"] = "若隐若现，你看不见。",
	["$luayindun2"] = "猜猜我在哪？",
	["$luayindun3"] = "镜花水月，千奇百变。",
	[":luayindun"] = "你可以在弃牌阶段从所弃牌中选定一种花色，直到你的下回合开始前，你无法成为该花色的卡牌的目标。",
	["#luayindun"] = "直到 %from 的下个回合开始，%from 不能成为花色为 %arg 牌的目标",
	["yd_pile"] = "隐遁",
	["fs_pile"] = "方术",
	
	["shenlualvfengxian"] = "神·吕奉先",
	["~shenlualvfengxian"] = "一切都结束了吗？",
	["luabisha"] = "必杀",
	["$luabisha"] = "拿命来！！！",
	[":luabisha"] = "<b>锁定技，</b>若你对无任何装备的角色使用【杀】成功时，该角色立即濒死。",
	["#luabisha"] = "%to 无任何装备， %from 的锁定技 <font color='yellow'><b>【必杀】</b></font> 被触发， %from 对 %to 造成了 <b><font color='#98fb98'>%arg</font></b> 点伤害",
	["luakongju"] = "恐惧",
	["$luakongju"] = "除了颤抖你还能做什么？",
	[":luakongju"] = "<b>锁定技，</b>其他角色对你使用【杀】被你闪避时，该【杀】来源立即将武将牌翻面。",
	["#luakongju"] = "%from 的锁定技 <font color='yellow'><b>【恐惧】</b></font> 被触发",	
	["luayuanmie"] = "元灭",
	["$luayuanmie"] = "元神还没恢复吗？",
	[":luayuanmie"] = "<b>锁定技，</b>对你所造成的伤害均视为减少一点体力上限。",
	["#luayuanmie"] = "%from 的锁定技 <font color='yellow'><b>【元灭】</b></font> 被触发， %from 失去了 <b><font color='#98fb98'>%arg</font></b> 点体力上限",
	["luahuijin"] = "灰烬",
	["$luahuijin"] = "修罗一震怒，万物皆尘土。",
	[":luahuijin"] = "隐藏技能",
	["#luahuijin_use"] = "灰烬",	
	[":#luahuijin_use"] = "回合结束阶段，若你体力值为1，你可以弃置所有手牌与装备则与你距离为1的角色立即死亡",
	
		
	["cv:luasimahui"] = "制图:皇叔|codeby:皇叔",
	["designer:luasimahui"] = "皇叔",
	["cv:luajiping"] = "制图:天命|codeby:皇叔",
	["designer:luajiping"] = "皇叔",
	["cv:shenluasimazhongda"] = "制图:天命|codeby:皇叔",
	["designer:shenluasimazhongda"] = "天命",
	["cv:luapanfeng"] = "制图:皇叔|codeby:皇叔",
	["designer:luapanfeng"] = "皇叔",
	["cv:lualiuba"] = "制图:daoxian|codeby:皇叔",
	["designer:lualiuba"] = "daoxian",
	["cv:luahuaxiong"] = "制图:gameweare|codeby:皇叔",
	["designer:luahuaxiong"] = "yipjenxen",
	["cv:luasimazhao"] = "制图:gameweare|codeby:皇叔",
	["designer:luasimazhao"] = "gameweare",
	["cv:lualiru"] = "制图:gameweare|codeby:皇叔",
	["designer:lualiru"] = "gameweare",
	["cv:lualengyanju"] = "制图:皇叔|codeby:皇叔",
	["designer:lualengyanju"] = "皇叔",
	["cv:luadingfeng"] = "制图:春哥姨妈|codeby:皇叔",
	["designer:luadingfeng"] = "春哥姨妈",	
	["cv:luazuoci"] = "制图:皇叔|codeby:皇叔",
	["designer:luazuoci"] = "皇叔",	
	["cv:shenlualvfengxian"] = "制图:司马子上|codeby:皇叔",
	["designer:shenlualvfengxian"] = "司马子上",		
	
	["@waked"] = "已觉醒",
	["@zmmark"] = "战马",
	["@hxbuff"] = "回旋",
	[""] = "",
	["lualajiche"] = "测试",
}