sgs.ai_skill_invoke.qixingdao=true

sgs.ai_skill_invoke.tiechui = function(self, data)
		local effect = data:toSlashEffect()

		if self:hasSkills(sgs.lose_equip_skill, effect.to) then
			return self:isFriend(effect.to)
		end

		return self:isEnemy(effect.to)
end
