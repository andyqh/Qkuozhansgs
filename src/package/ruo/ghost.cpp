#include "ghost.h"
#include "client.h"
#include "engine.h"
#include "carditem.h"
#include "settings.h"
#include "maneuvering.h"

class Longyin:public PhaseChangeSkill{
public:
    Longyin():PhaseChangeSkill("longyin"){
        frequency = Compulsory;
    }

    virtual bool onPhaseChange(ServerPlayer *guizhangfei) const{
        if(guizhangfei->getPhase() == Player::Play)
        {
            Room *room = guizhangfei->getRoom();
            room->playSkillEffect(objectName());
        }

        return false;
    }
};

class Sheji: public SlashBuffSkill{
public:
    Sheji():SlashBuffSkill("sheji"){
        frequency = Compulsory;
    }

    virtual bool buff(const SlashEffectStruct &effect) const{
        ServerPlayer *player = effect.from;
        Room *room = player->getRoom();
        if(player->getPhase() != Player::Play)
            return false;

        if(effect.to->inMyAttackRange(player)){
            room->playSkillEffect(objectName());
            room->slashResult(effect, NULL);

                return true;
        }

        return false;
    }
};

class Wumo: public TriggerSkill{
public:
    Wumo():TriggerSkill("wumo"){
        events << CardUsed << CardResponsed;

        frequency = Frequent;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        const Card *card = NULL;
        if(event == CardUsed){
            CardUseStruct use = data.value<CardUseStruct>();
            card = use.card;
        }else if(event == CardEffected){
            CardEffectStruct effect = data.value<CardEffectStruct>();
            card = effect.card;
        }

        if(card == NULL)
            return false;

        if(card->inherits("Slash") && player->getPhase() == Player::Play){
            if(player->askForSkillInvoke(objectName(), data))
                player->drawCards(1);
        }

        return false;
    }
};

class Tuodao: public TriggerSkill{
public:
    Tuodao():TriggerSkill("tuodao"){
        events << SlashMissed;
    }

    virtual bool triggerable(const ServerPlayer *) const{
        return true;
    }
    virtual bool trigger(TriggerEvent, ServerPlayer *player, QVariant &data) const{
        SlashEffectStruct effect = data.value<SlashEffectStruct>();

        if(effect.to->hasSkill("tuodao") && effect.to->getPhase() == Player::NotActive)
            effect.to->getRoom()->askForUseCard(effect.to, "slash", "@askforslash");

        return false;
    }
};

GhostPackage::GhostPackage()
    :Package("ghost")
{
    General *guizhangfei = new General(this, "guizhangfei", "shu", 4);
    guizhangfei->addSkill(new Longyin);
    guizhangfei->addSkill(new Skill("huxiao", Skill::Compulsory));

    General *guilvbu = new General(this, "guilvbu", "qun", 4);
    guilvbu->addSkill(new Sheji);
    guilvbu->addSkill(new Skill("juelu", Skill::Compulsory));

    General *guiguanyu = new General(this, "guiguanyu", "shu", 4);
    guiguanyu->addSkill(new Wumo);
    guiguanyu->addSkill(new Tuodao);
}

ADD_PACKAGE(Ghost)
