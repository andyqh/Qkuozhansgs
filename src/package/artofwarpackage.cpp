#include "artofwarpackage.h"
#include "client.h"
#include "engine.h"
#include "carditem.h"

//基本牌

//延时锦囊牌

//单体锦囊牌
Wangmei::Wangmei(Suit suit, int number)
    :SingleTargetTrick(suit, number, false) {
    setObjectName("wangmei");
}

bool Wangmei::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(!targets.isEmpty())
        return false;

    if(to_select == Self)
        return false;

    return true;
}

void Wangmei::onEffect(const CardEffectStruct &effect) const{
    Room *room = effect.to->getRoom();
    room->setEmotion(effect.to, "draw-card");
    JudgeStruct judge;
    judge.pattern = QRegExp("(.*):(club):(.*)");
    judge.good = true;
    judge.reason = objectName();
    judge.who = effect.to;

    room->judge(judge);
    if(judge.isGood()){
        RecoverStruct recover;
        recover.card = NULL;
        recover.who = effect.to;
        room->recover(effect.to, recover);
      }else
          effect.to->drawCards(1);
}

//装备牌·武器
class TiechuiSkill: public WeaponSkill{
public:
    TiechuiSkill():WeaponSkill("tiechui"){
        events << SlashHit;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        SlashEffectStruct effect = data.value<SlashEffectStruct>();

        QStringList armors;
        if(effect.to->getArmor())
            armors << "armor";

        if(armors.isEmpty())
            return false;

        Room *room = player->getRoom();
        if(!player->askForSkillInvoke(objectName(), data))
            return false;

        QString armor_type;
        if(armors.length() == 2)
            armor_type = room->askForChoice(player, objectName(), armors.join("+"));
        else
            armor_type = armors.first();

        if(armor_type == "armor")
            room->throwCard(effect.to->getArmor());
        else if(armor_type == "armor")
            room->throwCard(effect.to->getArmor());

        return false;
    }
};

Tiechui::Tiechui(Suit suit, int number)
    :Weapon(suit, number, 1)
{
    setObjectName("tiechui");
    skill = new TiechuiSkill;
}

class QixingdaoSkill: public WeaponSkill{
public:
    QixingdaoSkill():WeaponSkill("qixingdao"){
        events << CardAsked;
    }

    virtual int getPriority() const{
        return 2;
    }
    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        QString asked = data.toString();
        if(asked == "slash"){
            Room *room = player->getRoom();
            if(room->askForSkillInvoke(player, objectName())){
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(club|spade):(.*)");
                judge.good = true;
                judge.reason = objectName();
                judge.who = player;

                room->judge(judge);
                if(judge.isGood()){
                    Slash *slash = new Slash(Card::NoSuit, 0);
                    slash->setSkillName(objectName());
                    room->provide(slash);
                    room->setEmotion(player, "good");

                    return true;
                }else
                    room->setEmotion(player, "bad");
            }
        }
        return false;
    }
};

Qixingdao::Qixingdao(Suit suit, int number)
    :Weapon(suit, number, 1)
{
    setObjectName("qixingdao");
    skill = new QixingdaoSkill;
}

//装备牌·防具

class MuniuliumaSkill: public ArmorSkill{
public:
    MuniuliumaSkill():ArmorSkill("muniuliuma"){
        events << PhaseChange;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(player->getPhase() == Player::Start){
            Room *room = player->getRoom();
            LogMessage log;
            log.type = "#Muniu";
            log.from = player;
            log.arg = objectName();
            player->getRoom()->sendLog(log);

            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(heart|diamond):(.*)");
            judge.good = true;
            judge.reason = objectName();
            judge.who = player;

            room->judge(judge);
            if(judge.isGood()){
                player->drawCards(1);
                room->setEmotion(player, "good");
                return true;
        }
        }
        return false;
    }
};

Muniuliuma::Muniuliuma(Suit suit, int number)
    :Armor(suit, number)
{
    setObjectName("muniuliuma");
    skill = new MuniuliumaSkill;
}

class YuxiSkill: public ArmorSkill{
public:
    YuxiSkill():ArmorSkill("yuxi"){
        events << PhaseChange;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(player->getPhase() == Player::Finish){
            Room *room = player->getRoom();
            LogMessage log;
            log.type = "#Yuxi";
            log.from = player;
            log.arg = objectName();
            player->getRoom()->sendLog(log);

            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(heart):(.*)");
            judge.good = true;
            judge.reason = objectName();
            judge.who = player;

            room->judge(judge);
            if(judge.isGood()){
                RecoverStruct recover;
                recover.card = NULL;
                recover.who = player;
                room->recover(player, recover);
                room->setEmotion(player, "good");
                return true;
        }else
            player->drawCards(1);
        }
        return false;
    }
};

Yuxi::Yuxi(Suit suit, int number)
    :Armor(suit, number)
{
    setObjectName("yuxi");
    skill = new YuxiSkill;
}

//装备牌·马
Nanmanxiang::Nanmanxiang(Card::Suit suit, int number)
    :DefensiveHorse(suit, number)
{
  setObjectName("nanmanxiang");
}

QString Nanmanxiang::getEffectPath(bool ) const{
    return "audio/card/common/nanmanxiang.ogg";
}

ArtofwarPackage::ArtofwarPackage()
        :Package("artofwar")
{
 QList<Card *> cards;

 cards << new Wangmei(Card::Heart, 1)
       << new Wangmei(Card::Club, 3)
       << new Wangmei(Card::Diamond, 12);

 cards<< new Qixingdao(Card::Spade, 1);

 cards<< new Tiechui(Card::Heart, 2);

 cards << new Muniuliuma(Card::Diamond, 8);

 cards << new Yuxi(Card::Club, 1);

 OffensiveHorse *hanxue = new OffensiveHorse(Card::Club, 5);
 hanxue->setObjectName("hanxue");

 cards << hanxue;

 foreach(Card *card, cards)
     card->setParent(this);

 (new Nanmanxiang(Card::Spade, 5))->setParent(this);

 type = CardPack;
}

ADD_PACKAGE(Artofwar)
