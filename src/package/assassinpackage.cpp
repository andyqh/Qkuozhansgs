#include "assassinpackage.h"
#include "general.h"
#include "skill.h"
#include "engine.h"
#include "standard.h"
#include "carditem.h"
#include "maneuvering.h"
#include "generaloverview.h"
#include "clientplayer.h"
#include "client.h"
#include "serverplayer.h"
#include "room.h"
#include "standard-skillcards.h"
#include "ai.h"
#include <QCommandLinkButton>


class Ansha:public TriggerSkill{
public:
    Ansha():TriggerSkill("ansha"){
        events << SlashMissed;
    }
    virtual int getPriority() const{
        return 2;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        ServerPlayer *shadowEX = room->findPlayerBySkillName(objectName());
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if(!effect.to||!shadowEX||effect.from!=shadowEX) return false;

            if(effect.to!=shadowEX){
                Room *room = shadowEX->getRoom();
                if(shadowEX->askForSkillInvoke(objectName(), data)){
                    JudgeStruct judge;
                    judge.pattern = QRegExp("(.*):(diamond):(.*)");
                    judge.good = true;
                    judge.reason = objectName();
                    judge.who = shadowEX;
                    room->judge(judge);

                    if(judge.isGood()){
                        JudgeStruct judge2;
                        judge2.pattern = QRegExp("(.*):(diamond):(.*)");
                        judge2.good = true;
                        judge2.reason = objectName();
                        judge2.who = shadowEX;
                        room->judge(judge2);
                        if(judge2.isGood())
                        {
                                 room->setEmotion(shadowEX,"good");
                                 LogMessage log;
                                 log.type = "#ansha";
                                 log.from = shadowEX;
                                 log.to << effect.to;
                                 room->sendLog(log);
                                 room->getThread()->delay(1000);
                                 DamageStruct damage;
                                 damage.from = shadowEX;
                                 damage.to = effect.to;
                                 damage.damage=effect.to->getHp();
                                 room->damage(damage);
                                 return true;
                          }
                    }
                }
           }
        return false;
    }


};

class Shangsan: public FilterSkill{
public:
    Shangsan():FilterSkill("shangsan"){
    }
    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped()&&to_select->getCard()->objectName() == "duel";
    }
    virtual const Card *viewAs(CardItem *card_item) const{
        const Card *c = card_item->getCard();
        Slash *slash=new Slash(c->getSuit(),c->getNumber());
        slash->setSkillName(objectName());
        slash->addSubcard(card_item->getCard());
        return slash;
    }
};


class ShuguangRetrial: public TriggerSkill{
public:
    ShuguangRetrial():TriggerSkill("shuguang"){
        frequency = Compulsory;
        events << FinishJudge;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        JudgeStar judge = data.value<JudgeStar>();
        if(judge->card->getSuit() == Card::Spade){
            LogMessage log;
            log.type = "#ShuguangJudge";
            log.from = player;
            Card *new_card = Card::Clone(judge->card);
            new_card->setSuit(Card::Diamond);
            new_card->setSkillName("shuguang");
            judge->card = new_card;

            player->getRoom()->sendLog(log);
        }

        return false;
    }
};

class Jimie: public PhaseChangeSkill{
public:
    Jimie():PhaseChangeSkill("jimie"){
        frequency = Wake;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return PhaseChangeSkill::triggerable(target)
                && target->getMark("jimie") == 0
                && target->getPhase() == Player::Start
                && target->isWounded();
    }

    virtual bool onPhaseChange(ServerPlayer *shadowEX) const{

        Room *room = shadowEX->getRoom();
        LogMessage log;
        log.type = "#JimieWake";
        log.from = shadowEX;
        room->sendLog(log);
        room->loseMaxHp(shadowEX);
        RecoverStruct recover;
        recover.who = shadowEX;
        room->recover(shadowEX, recover);
        room->acquireSkill(shadowEX,"shuguang");
        room->setPlayerMark(shadowEX, "jimie", 1);
        return false;
    }
};



class Jinghan: public TriggerSkill{
public:
    Jinghan():TriggerSkill("jinghan"){
        events << CardEffected;
        frequency = Compulsory;
    }
    virtual bool triggerable(const ServerPlayer *target) const{
        return TriggerSkill::triggerable(target) && target->getArmor() == NULL;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        const Card *card = NULL;
        if(event == CardEffected)
        {
            CardEffectStruct effect = data.value<CardEffectStruct>();
            card = effect.card;


            if(card == NULL)
            return false;

            if(card->inherits("Duel") || (card->inherits("Slash") && card->isRed()))
            {
                LogMessage log;
                log.from = player;
                log.arg=effect.from->getGeneralName();
                log.arg2=card->objectName();
                log.type="#jinghan";
                player->getRoom()->sendLog(log);
                return true;
            }

        }
        return false;
    }

};

class Qiangzhi: public TriggerSkill{
public:
    Qiangzhi():TriggerSkill("qiangzhi"){
        events  << CardFinished;
        frequency = Frequent;
    }

    virtual int getPriority() const{
        return 2;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return !target->hasSkill(objectName());
    }



    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        ServerPlayer *zhangsong = room->findPlayerBySkillName(objectName());
        QList<const Card *> qiangzhi_cards;

        if(event == CardFinished)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if(use.card->objectName() == "nullification")
                return false;
            if(use.card->isNDTrick()
                &&use.from!=zhangsong)
            {
               qiangzhi_cards << use.card;
            }

        }


        if(qiangzhi_cards.isEmpty())
            return false;


        if(zhangsong && zhangsong->askForSkillInvoke(objectName(), data))
        {

            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(.*):(.*)");
            judge.good = false;
            judge.reason = objectName();
            judge.who = zhangsong;
            room->judge(judge);
            LogMessage log;
            log.from = zhangsong;
            log.type = "#qiangzhi";
            if(judge.card->isRed())
            {
                foreach(const Card *qiangzhi_c, qiangzhi_cards)
                {
                  room->setEmotion(zhangsong,"good");
                  zhangsong->obtainCard(qiangzhi_c);
                  log.arg=qiangzhi_c->objectName();
                  room->sendLog(log);
               }
            }
            else
            {
                room->setEmotion(zhangsong,"bad");
                log.type = "#qiangzhifailed";
                room->sendLog(log);
            }
        }

        return false;
    }
};


class Dusha: public TriggerSkill{
public:
    Dusha():TriggerSkill("dusha"){
        events << CardEffected;        
    }
    virtual bool triggerable(const ServerPlayer *target) const{   
            return true;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        const Card *card = NULL;
        Room *room = player->getRoom();
        ServerPlayer *jiping = room->findPlayerBySkillName(objectName());
        CardEffectStruct effect = data.value<CardEffectStruct>();
        card = effect.card;
        if(effect.to==jiping)
        return false;
        if(card == NULL)
        return false;
        if (effect.to->getHp()<1)
        return false;

            if(card->inherits("Peach")&&room->askForSkillInvoke(jiping, "dusha", data))
            {
              JudgeStruct judge;
              judge.pattern = QRegExp("(.*):(spade|club):(.*)");
              judge.good = false;
              judge.reason = objectName();
              judge.who = jiping;
              LogMessage log;
              log.from = jiping;
              room->judge(judge);

              switch(judge.card->getSuit()){
                case Card::Heart:{
                                room->setEmotion(jiping, "bad");
                                log.type = "#dushafailed";
                                room->sendLog(log);
                                break;
                    }

                 case Card::Diamond:{
                                        room->setEmotion(jiping, "bad");
                                        log.type = "#dushafailed";
                                        room->sendLog(log);
                    break;
                }

                 case Card::Club:{
                    room->setEmotion(jiping, "good");
                    log.type = "#dushaclub";

                    log.arg = effect.to->getGeneralName();
                    room->sendLog(log);
                    return true;
                }

                case Card::Spade:{
                    room->setEmotion(jiping, "good");
                    log.type = "#dushaspade";
                    log.arg = effect.to->getGeneralName();
                    room->sendLog(log);
                    room->loseHp(player);
                    return true;
                }

            default:
                break;}
            }

        return false;
    }
};
class Cuidu: public TriggerSkill{
public:
    Cuidu():TriggerSkill("cuidu"){
        events << Predamage;
        frequency = Compulsory;
    }
    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        ServerPlayer *jiping = room->findPlayerBySkillName(objectName());
        if(!jiping) return false;

        if(event == Predamage){
            DamageStruct damage = data.value<DamageStruct>();
            const Card *reason = damage.card;
            if(!reason || damage.from != jiping)
                return false;

            if(reason->inherits("FireSlash")){
                LogMessage log;
                log.type = "#cuidu";
                log.from = jiping;
                log.to << damage.to;
                log.arg = QString::number(damage.damage);
                log.arg2 = QString::number(damage.damage + 1);
                room->sendLog(log);
                damage.damage ++;
                data = QVariant::fromValue(damage);
            }
        }

        return false;
    }
};

class Yuanxing: public DistanceSkill{
public:
    Yuanxing():DistanceSkill("yuanxing"){

    }

    virtual int getCorrect(const Player *from, const Player *to) const{
        int correct = 0;
        if(from->hasSkill(objectName()))
                correct++;
        if(to->hasSkill(objectName()))
                correct++;
        return correct;
    }
};


class Liwei:public MasochismSkill{
public:
    Liwei():MasochismSkill("liwei"){

    }

    virtual void onDamaged(ServerPlayer *hanlong, const DamageStruct &damage) const{
        ServerPlayer *from = damage.from;
         Room *room = hanlong->getRoom();
        if(!damage.card) return;
        if(!damage.from) return;
        if(hanlong->isKongcheng())return;
        if((damage.card->inherits("ArcheryAttack")||damage.card->inherits("SavageAssault"))&&from && from->isAlive() && room->askForSkillInvoke(hanlong, objectName())){
            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(spade|club):(.*)");
            judge.good = false;
            judge.reason = objectName();
            judge.who = hanlong;
            room->askForDiscard(hanlong,objectName(),1,false,false);
            room->judge(judge);
            switch(judge.card->getSuit()){
            case Card::Heart:{
                                room->setEmotion(hanlong, "bad");
                                break;
                }

            case Card::Diamond:{
                                room->setEmotion(hanlong, "bad");
                                break;
                }

            case Card::Club:{
                    room->setEmotion(hanlong, "good");
                    RecoverStruct recover;
                    recover.card = damage.card;
                    recover.who = hanlong;
                    room->recover(hanlong, recover);
                    hanlong->drawCards(2);
                    break;
                }

            case Card::Spade:{
                    room->setEmotion(hanlong, "good");
                    DamageStruct damage;
                    damage.from = hanlong;
                    damage.to = from;
                    damage.damage=2;
                    room->setEmotion(hanlong, "good");

                    if(!room->askForDiscard(from,this->objectName(),3,true,true))
                           room->damage(damage);
                    break;
                }

            default:
                break;}

            }

       }
};


class Youguai: public TriggerSkill{
public:
    Youguai():TriggerSkill("youguai"){
        events << Damaged;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        if(damage.card == NULL || !damage.card->inherits("Slash") || damage.to->isDead())
            return false;

        Room *room = player->getRoom();
        ServerPlayer *chizhizhe = room->findPlayerBySkillName(objectName());
        if(chizhizhe->isKongcheng())
            return false;
        if(chizhizhe && !chizhizhe->isNude() && chizhizhe->askForSkillInvoke(objectName(), data)){
            room->askForDiscard(chizhizhe, "youguai", 1, false, true);

            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(.*):(.*)");
            judge.good = true;
            judge.who = player;
            judge.reason = objectName();

            room->judge(judge);
            LogMessage log;
            switch(judge.card->getSuit()){
            case Card::Heart:{
                    RecoverStruct recover;
                    recover.who = chizhizhe;
                    recover.recover=1;
                    log.type = "#youguaiheart";
                    log.from = chizhizhe;
                    log.to << player;
                    room->sendLog(log);
                    room->recover(player, recover);
                    player->drawCards(1);
                    chizhizhe->drawCards(1);                    
                    break;
                }

            case Card::Diamond:{

                    log.type = "#youguaidiamond";
                    log.from = chizhizhe;
                    log.to << player;
                    room->sendLog(log);
                    player->drawCards(2);
                    if(!damage.from->isKongcheng())
                    room->askForDiscard(damage.from, "youguai", 1, false, false);
                    break;
                }

            case Card::Club:{
                    if(damage.from && damage.from->isAlive()){


                        log.from = chizhizhe;
                        log.to << damage.from;


                        if(room->askForDiscard(damage.from, "youguai", 2, true, true))
                        {
                            log.type = "#youguaiclub";
                            room->sendLog(log);
                        }
                        else
                        {
                                log.type = "#youguaiclubnodiscard";
                                room->sendLog(log);
                                damage.from->turnOver();
                        }
                    }

                    break;
                }

            case Card::Spade:{
                    if(damage.from && damage.from->isAlive())

                        log.type = "#youguaispade";
                        log.from = chizhizhe;
                        log.to << damage.from;
                        log.arg=player->getGeneralName();
                        room->sendLog(log);
                        DamageStruct damagetmp;
                        damagetmp.from = player;
                        damagetmp.to = damage.from;
                        damagetmp.damage=1;
                        room->damage(damagetmp);
                        damage.from->turnOver();

                    break;
                }

            default:
                break;
            }
        }

        return false;
    }
};

class Bangpiao: public PhaseChangeSkill{
public:
    Bangpiao():PhaseChangeSkill("bangpiao"){

    }
    virtual int getPriority() const{
        return 2;
    }

    virtual bool onPhaseChange(ServerPlayer *chizhizhe) const{


        if(chizhizhe->getPhase() == Player::Play){
            if(chizhizhe->isKongcheng())
                return false;
            if(chizhizhe->getRoom()->alivePlayerCount()<3)
                return false;
            Room *room = chizhizhe->getRoom();
            if(room->askForSkillInvoke(chizhizhe, objectName())){               
                chizhizhe->throwAllHandCards();
                ServerPlayer *target = room->askForPlayerChosen(chizhizhe, room->getOtherPlayers(chizhizhe), objectName());
                LogMessage log;
                log.type = "#bangpiao";
                log.from = chizhizhe;
                log.arg = target->getGeneralName();
                room->sendLog(log);
                target->turnOver();
                return true;
            }
        }

        return false;
    }
};

class Sipiao: public OneCardViewAsSkill{
public:
    Sipiao():OneCardViewAsSkill("sipiao"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("SipiaoCard") && !player->isKongcheng();
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        SipiaoCard *card = new SipiaoCard;
        card->addSubcard(card_item->getFilteredCard());
        return card;
    }
};

SipiaoCard::SipiaoCard(){
    once = true;
    mute = true;
    will_throw = false;
}

bool SipiaoCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(!targets.isEmpty())
        return false;
    if(to_select->isKongcheng())
        return false;
    if(to_select->faceUp())
        return false;

    return true;
}

void SipiaoCard::use(Room *room, ServerPlayer *chizhizhe, const QList<ServerPlayer *> &targets) const{
    ServerPlayer *piao = targets.first();
    bool success = chizhizhe->pindian(piao, "sipiao", this);
    if(success){
        if(piao==NULL){
            return;
        }        
        DamageStruct damage;
        damage.from = chizhizhe;
        damage.to = piao;
        damage.damage=2;
        room->setEmotion(chizhizhe,"good");
        room->setEmotion(piao,"bad");
        LogMessage log;
        log.type = "#sipiao";
        log.from = chizhizhe;
        log.arg = piao->getGeneralName();
        room->sendLog(log);
        room->damage(damage);

    }
}



class Shengyan: public TriggerSkill{
public:
    Shengyan():TriggerSkill("shengyan"){
        events << CardEffected;
        //frequency = Compulsory;
    }
    virtual bool triggerable(const ServerPlayer *target) const{
            return !target->isKongcheng()
                    &&target->getPhase()==Player::NotActive
                    &&target->hasSkill(objectName())
                    &&target->isAlive();
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();        
        CardEffectStruct effect = data.value<CardEffectStruct>();
        ServerPlayer *liuye = room->findPlayerBySkillName(objectName());
        if(effect.to==liuye&&effect.multiple&&effect.card->inherits("TrickCard")){
            //if(!liuye->getPhase()==Player::NotActives)
              //  return false;
            if(room->askForSkillInvoke(liuye, objectName(), data)&&room->askForDiscard(liuye, objectName(), 1, false,false))
            {

                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(heart):(.*)");
                judge.good = false;
                judge.reason = objectName();
                judge.who = liuye;

                room->judge(judge);
                if(judge.isGood())
                {

                        DamageStruct damage;
                        damage.from = liuye;
                        damage.to = effect.from;
                        room->setEmotion(liuye, "good");
                        room->damage(damage);
                        LogMessage log;
                        log.type = "#ShengyanAvoid";
                        log.from = liuye;
                        log.arg = effect.card->objectName();
                        room->sendLog(log);
                        return true;
                }
                else
                {
                     room->setEmotion(liuye, "bad");
                     LogMessage log;
                     log.type = "#ShengyanFailed";
                     log.from = liuye;
                     room->sendLog(log);
                     return false;
                }

            }

      }
        return false;
    }

};
class Shaqie: public TriggerSkill{
public:
    Shaqie():TriggerSkill("shaqie"){
        events << SlashProceed;
        frequency = Compulsory;
    }

    const Card *askForDoubleJink(ServerPlayer *player, const QString &reason) const{
        Room *room = player->getRoom();

        const Card *first_jink = NULL, *second_jink = NULL;
        first_jink = room->askForCard(player, "jink", QString("@%1-jink-1").arg(reason));
        if(first_jink)
            second_jink = room->askForCard(player, "jink", QString("@%1-jink-2").arg(reason));

        Card *jink = NULL;
        if(first_jink && second_jink){
            jink = new DummyCard;
            jink->addSubcard(first_jink);
            jink->addSubcard(second_jink);
        }

        return jink;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *, QVariant &data) const{
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if(effect.from->hasSkill(objectName()) && effect.to->getGeneral()->isFemale()){
            //  liuye slash female
            ServerPlayer *liuye = effect.from;
            ServerPlayer *female = effect.to;
            Room *room = liuye->getRoom();

            //room->playSkillEffect(objectName(), 1);
            LogMessage log;
            log.type = "#shaqie";
            log.from = liuye;
            log.arg =effect.to->getGeneralName();
            room->sendLog(log);
            room->slashResult(effect, askForDoubleJink(female, "Shaqie"));

            return true;
        }
        return false;
    }
};

class Wuhuan: public FilterSkill{
public:
    Wuhuan():FilterSkill("wuhuan"){
    }
    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped() && to_select->getCard()->objectName() == "analeptic";
    }
    virtual const Card *viewAs(CardItem *card_item) const{
        const Card *c = card_item->getCard();
        Jink *jink=new Jink(c->getSuit(),c->getNumber());
        jink->setSkillName(objectName());
        jink->addSubcard(card_item->getCard());
        return jink;
    }
};

class Tiaobo: public OneCardViewAsSkill{
public:
    Tiaobo():OneCardViewAsSkill("tiaobo"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return !player->hasUsed("TiaoboCard");
    }

    virtual bool viewFilter(const CardItem *) const{
        return true;
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        TiaoboCard *tiaobo_card = new TiaoboCard;
        tiaobo_card->addSubcard(card_item->getCard()->getId());
        return tiaobo_card;
    }
};
TiaoboCard::TiaoboCard(){
    once = true;
}

bool TiaoboCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(targets.length() >= 2)
        return false;
    if(to_select == Self)
        return false;
    return true;
}

bool TiaoboCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const{
    return targets.length() == 2;
}

void TiaoboCard::use(Room *room, ServerPlayer *, const QList<ServerPlayer *> &targets) const{
    room->throwCard(this);
    ServerPlayer *to = targets.at(1);
    ServerPlayer *from = targets.at(0);
      Slash *slash = new Slash(Card::NoSuit, 0);
      slash->setSkillName("tiaobocard");
      CardUseStruct use;
      use.from = from;
      use.to << to;
      use.card = slash;
      room->useCard(use);

      CardUseStruct use2;
      use2.from = to;
      use2.to << from;
      use2.card = slash;
      room->useCard(use2);
}

class Lianzuo: public TriggerSkill{
public:
    Lianzuo():TriggerSkill("lianzuo"){
        events << Predamaged;
        //frequency=Compulsory;
    }


    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        Room *room=player->getRoom();
        ServerPlayer *yinfan = room->findPlayerBySkillName(objectName());
        if (damage.to!=yinfan) return false;
        if(room->askForSkillInvoke(yinfan, objectName(), data))
        {

            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(spade):(.*)");
            judge.good = false;
            judge.reason = objectName();
            judge.who = yinfan;
            room->judge(judge);

            if(judge.isGood())
            {
                    ServerPlayer *target = room->askForPlayerChosen(yinfan, room->getOtherPlayers(damage.from), objectName());
                    DamageStruct damagetmp;
                    if(damage.nature)
                        damagetmp.nature=damage.nature;
                    damagetmp.damage=damage.damage;
                    damagetmp.from = damage.from;
                    damagetmp.to =target;
                    room->setEmotion(yinfan, "good");
                    room->damage(damagetmp);
                    LogMessage log;
                    log.type = "#lianzuo";
                    log.from = yinfan;
                    log.arg  = damagetmp.from->getGeneralName();
                    log.arg2 = damagetmp.to->getGeneralName();
                    room->sendLog(log);
                    return false;
            }
            else
            {
                 room->setEmotion(yinfan, "bad");
                 return false;
            }

        }

        return false;
    }
};


class Bujing: public ProhibitSkill{
public:
    Bujing():ProhibitSkill("bujing"){

    }

    virtual bool isProhibited(const Player *, const Player *, const Card *card) const{
        return card->inherits("SupplyShortage") || card->inherits("Indulgence");
    }
};

class Qingkai: public TriggerSkill{
public:
    Qingkai():TriggerSkill("qingkai"){
        events << Predamaged;
        frequency=Compulsory;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        if(damage.damage >= 2){
            LogMessage log;
            log.type = "#qingkai";
            log.from = player;
            log.arg = QString::number(damage.damage);
            log.arg2 =QString::number(damage.damage-1);
            damage.damage =damage.damage-1;
            player->getRoom()->sendLog(log);
            data = QVariant::fromValue(damage);
            return false;
        }
        return false;
    }
};
class Bishou:public SlashBuffSkill{
public:
    Bishou():SlashBuffSkill("bishou"){

    }

    virtual bool buff(const SlashEffectStruct &effect) const{
        ServerPlayer *wufu = effect.from;

        Room *room = wufu->getRoom();
        if(effect.from->askForSkillInvoke("bishou", QVariant::fromValue(effect))){
            room->playSkillEffect(objectName());

            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(spade):(.*)");
            judge.good = true;
            judge.reason = objectName();
            judge.who = wufu;

            room->judge(judge);
            if(judge.isGood()){
                room->slashResult(effect, NULL);
                return true;
            }
        }

        return false;
    }
};



class Pofuchenzhou: public TriggerSkill{
public:
    Pofuchenzhou():TriggerSkill("pofuchenzhou"){        
        events << Predamaged <<PhaseChange;
        frequency=Compulsory;
    }
    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
            Room *room = player->getRoom();
            ServerPlayer *guoxiu = room->findPlayerBySkillName(objectName());
            DamageStruct damage = data.value<DamageStruct>();
            if(event == Predamaged)
            {
                const Card *reason = damage.card;
                if(!reason)
                   return false;
                if((damage.from!=guoxiu))
                    return false;
                if(reason->inherits("Slash")&&reason->isBlack())
                {
                    damage.damage++;
                    LogMessage log;
                    log.type = "#pofuBuf";
                    log.from = guoxiu;
                    log.arg = reason->objectName();
                    room->sendLog(log);
                    data = QVariant::fromValue(damage);

                }

               if(guoxiu->getMark("@pofu")!=1)
                       guoxiu->gainMark("@pofu",1);


            }
            else if(event == PhaseChange)
            {

                 if(guoxiu->getPhase() == Player::Finish)
                {
                    if(guoxiu->getMark("@pofu")!=1)
                    {
                        LogMessage log;
                        log.type = "#chenzhouLoseHP";
                        log.from = guoxiu;
                        room->sendLog(log);
                        room->loseHp(guoxiu,1);
                    }
                    guoxiu->loseAllMarks("@pofu");
                }


           }


        return false;
    }
};

class Taolue:public MasochismSkill{
public:
    Taolue():MasochismSkill("taolue"){

    }

    virtual void onDamaged(ServerPlayer *weike, const DamageStruct &damage) const{
        ServerPlayer *from = damage.from;
        Room *room = weike->getRoom();
        if(from && from->isAlive() && room->askForSkillInvoke(weike, "taolue")){
            //room->playSkillEffect(objectName());
            room->drawCards(weike,1);
            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(club):(.*)");
            judge.good = false;
            judge.reason = objectName();
            judge.who = weike;

            room->judge(judge);
            if(judge.isGood())
            {
                if(!room->askForDiscard(from, objectName(), 2, true,false)){
                    room->setEmotion(weike, "good");
                    LogMessage log;
                    log.type = "#taolue";
                    log.from = weike;
                    log.arg= from->getGeneralName();
                    room->sendLog(log);
                    room->loseHp(from,1);
                }
            }
            else
                room->setEmotion(weike, "bad");
        }
    }
};

class Quanjiu: public FilterSkill{
public:
    Quanjiu():FilterSkill("quanjiu"){
    }
    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped()&&to_select->getCard()->getSuit()==Card::Spade;
    }
    virtual const Card *viewAs(CardItem *card_item) const{
        const Card *c = card_item->getCard();
        Analeptic *analeptic=new Analeptic(c->getSuit(),c->getNumber());
        analeptic->setSkillName(objectName());
        analeptic->addSubcard(card_item->getCard());
        return analeptic;
    }
};

class Xiulian: public TriggerSkill{
public:

    Xiulian():TriggerSkill("xiulian"){
        events << Predamaged <<PhaseChange;
    }
    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
            Room *room = player->getRoom();
            ServerPlayer *gexuan = room->findPlayerBySkillName(objectName());
            if(!gexuan) return false;
            LogMessage log;
            log.from = gexuan;
            if(gexuan->hasSkill("xiulianlevel5"))
                return false;
            int x=gexuan->getMark("@xiulian");            
            if(event == Predamaged)
            {

                DamageStruct damage = data.value<DamageStruct>();
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(.*):(.*)");
                judge.good = true;
                judge.reason = "xiulian";
                judge.who = gexuan;
                if(damage.to== gexuan&&room->askForSkillInvoke(gexuan,"xiulian"))
                {

                    room->judge(judge);
                    if(judge.card->isRed())
                    {
                      log.type = "#xiulianlevelup";
                      room->setEmotion(gexuan, "good");
                      room->sendLog(log);
                      if(x<5)
                      gexuan->gainMark("@xiulian",1);
                    }
                    else
                    {
                      log.type = "#xiulianlevelupfailed";
                      room->setEmotion(gexuan, "bad");
                      room->sendLog(log);
                    }
                }
                if(damage.from == gexuan&&room->askForSkillInvoke(gexuan,"xiulian"))
                {                   
                    room->judge(judge);
                    if(judge.card->isRed())
                    {
                      log.type = "#xiulianlevelup";
                      room->setEmotion(gexuan, "good");
                      room->sendLog(log);
                      if(x<5)
                      gexuan->gainMark("@xiulian",1);
                    }
                    else
                    {
                      log.type = "#xiulianlevelupfailed";
                      room->setEmotion(gexuan, "bad");
                      log.from = gexuan;
                      room->sendLog(log);
                    }
                }
            }
            else if(event == PhaseChange)
            {

                if(gexuan->getPhase() == Player::Start)
                {
                        log.from = gexuan;
                        if(x==0)
                             return false;
                        switch(gexuan->getMark("@xiulian"))
                        {
                           case 1: {  if(!gexuan->hasSkill("xiulianlevel1"))
                                        {
                                        log.type = "#xiulianl1";
                                        room->sendLog(log);
                                        room->acquireSkill(gexuan,"xiulianlevel1");
                                        }
                                   break;}

                           case 2: {
                                      if(!gexuan->hasSkill("xiulianlevel1"))
                                      room->acquireSkill(gexuan,"xiulianlevel1");
                                      if(!gexuan->hasSkill("xiulianlevel2"))
                                      {
                                       room->acquireSkill(gexuan,"xiulianlevel2");
                                       log.type = "#xiulianl2";
                                       room->sendLog(log);

                                      }
                                      break;}
                           case 3: {
                                      if(!gexuan->hasSkill("xiulianlevel1"))
                                      room->acquireSkill(gexuan,"xiulianlevel1");

                                      if(!gexuan->hasSkill("xiulianlevel2"))
                                      room->acquireSkill(gexuan,"xiulianlevel2");

                                      if(!gexuan->hasSkill("xiulianlevel3"))
                                      {
                                       room->acquireSkill(gexuan,"xiulianlevel3");
                                       log.type = "#xiulianl3";
                                       room->sendLog(log);
                                      }
                                      break;}
                           case 4: {
                                      if(!gexuan->hasSkill("xiulianlevel1"))
                                      room->acquireSkill(gexuan,"xiulianlevel1");

                                      if(!gexuan->hasSkill("xiulianlevel2"))
                                      room->acquireSkill(gexuan,"xiulianlevel2");

                                      if(!gexuan->hasSkill("xiulianlevel3"))
                                      room->acquireSkill(gexuan,"xiulianlevel3");

                                      if(!gexuan->hasSkill("xiulianlevel4"))
                                      {
                                        room->acquireSkill(gexuan,"xiulianlevel4");
                                        log.type = "#xiulianl4";
                                        room->sendLog(log);
                                      }
                                      break;}
                           case 5: {
                                      if(!gexuan->hasSkill("xiulianlevel1"))
                                      room->acquireSkill(gexuan,"xiulianlevel1");

                                      if(!gexuan->hasSkill("xiulianlevel2"))
                                      room->acquireSkill(gexuan,"xiulianlevel2");

                                      if(!gexuan->hasSkill("xiulianlevel3"))
                                      room->acquireSkill(gexuan,"xiulianlevel3");

                                      if(!gexuan->hasSkill("xiulianlevel4"))
                                      room->acquireSkill(gexuan,"xiulianlevel4");

                                      if(!gexuan->hasSkill("xiulianlevel5"))
                                      {
                                       room->acquireSkill(gexuan,"xiulianlevel5");
                                       log.type = "#xiulianl5";
                                       room->sendLog(log);
                                       gexuan->loseAllMarks("@xiulian");
                                       room->setPlayerProperty(gexuan, "maxhp", gexuan->getMaxHP() + 2);
                                      }
                                      break;
                                  }
                         }



                }
            }


        return false;
    }
};
class Leifu: public TriggerSkill{
public:
    Leifu():TriggerSkill("xiulianlevel1"){
        events << SlashEffect<< Predamage;
        frequency = Compulsory;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room=player->getRoom();
        ServerPlayer *gexuan = room->findPlayerBySkillName(objectName());
        LogMessage log;
        log.from = gexuan;
        if(!gexuan)
            return false;
        if( event == SlashEffect )
        {
            SlashEffectStruct effect = data.value<SlashEffectStruct>();
            if(effect.nature != DamageStruct::Thunder)
            {
                effect.nature = DamageStruct::Thunder;
                data = QVariant::fromValue(effect);
            }
         }
        else if( event == Predamage )
        {
            DamageStruct damage = data.value<DamageStruct>();
            const Card *reason = damage.card;
            if(!reason || damage.from != gexuan)
                return false;

            if(reason->inherits("Slash"))
            {

                if(gexuan->askForSkillInvoke(objectName(), data)){
                   JudgeStruct judge;
                   judge.pattern = QRegExp("(.*):(.*):(.*)");
                   judge.good = true;
                   judge.reason = objectName();
                   judge.who = gexuan;
                   room->judge(judge);
                   if(judge.card->isBlack())
                   {
                       room->setEmotion(gexuan,"good");
                       log.type = "#xiulianlevel1";
                       damage.damage++;
                       data = QVariant::fromValue(damage);
                   }else log.type="#xiulianlevel1failed";
                   room->sendLog(log);
               }
            }
        }

        return false;
     }

};
class Fentian:public TriggerSkill{
public:
    Fentian():TriggerSkill("xiulianlevel2"){
        events << SlashMissed;
    }
    virtual int getPriority() const{
        return 2;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        LogMessage log;
        ServerPlayer *gexuan = room->findPlayerBySkillName(objectName());
        log.from = gexuan;
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if(!effect.to||!gexuan||effect.from!=gexuan) return false;

            if(effect.to!=gexuan)
               {
                 if(gexuan->askForSkillInvoke(objectName(), data)){
                    JudgeStruct judge;
                    judge.pattern = QRegExp("(.*):(heart):(.*)");
                    judge.good = true;
                    judge.reason = objectName();
                    judge.who = effect.to;
                    room->judge(judge);

                    if(judge.isGood())
                    {
                        room->setEmotion(gexuan,"good");
                        room->setEmotion(effect.to,"bad");
                        log.type = "#xiulianlevel2";                        
                        room->sendLog(log);
                        DamageStruct damage;
                        damage.from = gexuan;
                        ServerPlayer *target = room->askForPlayerChosen(gexuan, room->getOtherPlayers(gexuan), objectName());
                        damage.to=target;
                        damage.nature=DamageStruct::Fire;
                        damage.damage=1;
                        room->damage(damage);
                        return true;
                    }
                    else
                    {
                        room->setEmotion(gexuan,"bad");
                        log.type = "#xiulianlevel2failed";
                        room->sendLog(log);

                    }
                }
           }
        return false;
    }


};

class Xuwu:public MasochismSkill{
public:
    Xuwu():MasochismSkill("xiulianlevel3"){
    }

    virtual void onDamaged(ServerPlayer *gexuan, const DamageStruct &damage) const{
        ServerPlayer *from = damage.from;
        Room *room = gexuan->getRoom();
        LogMessage log;
        log.from = gexuan;        
        if(!damage.card)
            return;
        if(damage.card->isBlack())
        {

            if(from&&room->askForSkillInvoke(gexuan, "xiulianlevel3")){


            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(.*):(.*)");
            judge.good = false;
            judge.reason = objectName();
            judge.who = gexuan;

                room->judge(judge);
                if(judge.card->isBlack())
                {
                    room->setEmotion(gexuan, "good");
                    log.type = "#xiulianlevel3";
                    room->sendLog(log);
                    RecoverStruct recover;
                    recover.who = gexuan;
                    recover.recover=damage.damage;
                    room->recover(gexuan, recover);

                }
                else
                {
                    room->setEmotion(gexuan, "bad");
                    log.type = "#xiulianlevel3failed";
                    room->sendLog(log);
                }
            }

        }
    }
};
TianleiCard::TianleiCard(){
}

bool TianleiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(targets.length() >= 3)
        return false;

    if(to_select == Self)
        return false;

    return true;

}

void TianleiCard::onEffect(const CardEffectStruct &effect) const{
    ServerPlayer *gexuan = effect.from;
    ServerPlayer *target = effect.to;

    Room *room = gexuan->getRoom();
    LogMessage log;
    log.from = gexuan;
    JudgeStruct judge;
    judge.pattern = QRegExp("(.*):(.*):(.*)");
    judge.good = false;
    judge.reason = "xiulianlevel4";
    judge.who = target;

    room->judge(judge);

    if(judge.card->isBlack()){
        room->setEmotion(target, "bad");
        room->setEmotion(gexuan, "good");
        DamageStruct damage;
        damage.card = NULL;
        damage.damage = 1;
        damage.from = gexuan;
        damage.to = target;
        damage.nature = DamageStruct::Thunder;
        log.type = "#xiulianlevel4";
        log.to<<target;
        room->sendLog(log);
        room->damage(damage);
    }else
    {
        room->setEmotion(target, "good");
        room->setEmotion(gexuan, "bad");
        log.type = "#xiulianlevel4failed";
        room->sendLog(log);
    }
}

class TianleiViewAsSkill: public ZeroCardViewAsSkill{
public:
    TianleiViewAsSkill():ZeroCardViewAsSkill("xiulianlevel4"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const{
        return  pattern == "@@tianlei";
    }

    virtual const Card *viewAs() const{
        return new TianleiCard;
    }
};

class Tianlei: public TriggerSkill{
public:
    Tianlei():TriggerSkill("xiulianlevel4"){
        events << CardResponsed;
        view_as_skill = new TianleiViewAsSkill;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *gexuan, QVariant &data) const{
        CardStar card_star = data.value<CardStar>();
        if(!(card_star->inherits("Jink")||card_star->inherits("Slash")))
            return false;
        Room *room = gexuan->getRoom();
        room->askForUseCard(gexuan, "@@tianlei", "@tianlei");
        return false;
    }
};

class Dujie: public TriggerSkill{
public:
    Dujie():TriggerSkill("xiulianlevel5"){
        frequency = Compulsory;
        events << CardAsked;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return TriggerSkill::triggerable(target)&& !target->getArmor();
    }

    virtual bool trigger(TriggerEvent, ServerPlayer *gexuan, QVariant &data) const{
        QString pattern = data.toString();
        Room *room = gexuan->getRoom();
        LogMessage log;
        log.from=gexuan;



        if(pattern=="jink"&&gexuan->askForSkillInvoke(objectName())){
            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(heart):(.*)");
            judge.good = false;
            judge.reason = objectName();
            judge.who = gexuan;

            room->judge(judge);

            if(judge.isGood()){
                Jink *jink = new Jink(Card::NoSuit, 0);
                jink->setSkillName(objectName());
                room->provide(jink);
                room->setEmotion(gexuan, "good");
                log.type = "#xiulianlevel5";
                room->sendLog(log);
                return true;
            }
            else
            {
                room->setEmotion(gexuan, "bad");
                log.type = "#xiulianlevel5failed";
                room->sendLog(log);
            }
        }
            if(pattern=="slash"&&gexuan->askForSkillInvoke(objectName())){
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(heart):(.*)");
                judge.good = false;
                judge.reason = objectName();
                judge.who = gexuan;

                room->judge(judge);

                if(judge.isGood()){
                    Slash *slash = new Slash(Card::NoSuit, 0);
                    slash->setSkillName(objectName());
                    room->provide(slash);
                    room->setEmotion(gexuan, "good");
                    log.type = "#xiulianlevel5";
                    room->sendLog(log);
                    return true;
                }
                else
                {
                    room->setEmotion(gexuan, "bad");
                    log.type = "#xiulianlevel5failed";
                    room->sendLog(log);
                }
        }

        return false;
    }
};


class Fankang:public MasochismSkill{
public:
    Fankang():MasochismSkill("fankang")
    {
    }

    virtual void onDamaged(ServerPlayer *fanjiangzhangda, const DamageStruct &damage) const{
        ServerPlayer *from = damage.from;
        if (damage.card==NULL)
            return;
        Room *room = fanjiangzhangda->getRoom();
        LogMessage log;
        log.from = fanjiangzhangda;
        log.arg=from->getGeneralName();      
        if (damage.card->inherits("Slash")||damage.card->inherits("Duel"))
        {
            if(from && from->isAlive() && room->askForSkillInvoke(fanjiangzhangda, "fankang"))
            {
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(.*):(A|4|7)");
                judge.good = true;
                judge.reason = objectName();
                judge.who = fanjiangzhangda;
                room->judge(judge);
                if(judge.isGood())
                {
                    room->setEmotion(fanjiangzhangda, "good");
                    DamageStruct damagetmp;
                    damagetmp.from = fanjiangzhangda;
                    damagetmp.to = damage.from;
                    damagetmp.damage=damage.damage+1;
                    room->damage(damagetmp);
                    log.type = "#fankang174";
                    room->sendLog(log);
                }
                else if(judge.card->getNumber()==2||judge.card->getNumber()==5||judge.card->getNumber()==8)
                {
                    fanjiangzhangda->drawCards(2,true);
                    log.type = "#fankang258";
                    room->sendLog(log);
                }
                else
                {
                    room->setEmotion(fanjiangzhangda, "bad");
                    log.type = "#fankangfailed";
                    room->sendLog(log);
                }
            }
        }
    }
};

MenkeCard::MenkeCard(){
    once = true;
}

bool MenkeCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(targets.length() >= 3)
        return false;

    if(to_select == Self)
        return false;
    return true;
}

void MenkeCard::onEffect(const CardEffectStruct &effect) const{     
     ServerPlayer *xugong = effect.from;
     Room *room = xugong->getRoom();
     if(!xugong->isKongcheng())
     {

            QList<ServerPlayer *> players = room->getOtherPlayers(effect.to), targets;
            foreach(ServerPlayer *player, players){
            if(effect.to->inMyAttackRange(player))
             targets << player;
            }
         LogMessage log;
         log.from = xugong;
         JudgeStruct judge;
         judge.pattern = QRegExp("(.*):(.*):(.*)");
         judge.good = true;
         judge.reason = "menke";
         judge.who = effect.to;
         DamageStruct damage;
         damage.card = NULL;
         damage.damage = 1;
         room->judge(judge);
         if(judge.card->isRed())
         {           
            room->setEmotion(effect.to,"good");
            room->setEmotion(xugong, "good");
            ServerPlayer *target=room->askForPlayerChosen(xugong,targets,"menke");
            damage.from = effect.to;
            damage.to =target;
            log.type = "#menke";
            log.to<<effect.to;
            log.arg=target->getGeneralName();
            room->sendLog(log);
            room->damage(damage);
          }
         else
         {
            room->setEmotion(effect.to,"bad");
            room->setEmotion(xugong, "bad");
            effect.to->drawCards(1);
            log.type = "#menkefailed";
            log.to<<effect.to;
            room->sendLog(log);
            room->damage(damage);
         }
     }


}

class Menke: public OneCardViewAsSkill{
public:
    Menke():OneCardViewAsSkill("menke"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        if(player->hasUsed("MenkeCard")) return false;
        else
            return true;
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped() && to_select->getFilteredCard()->isRed();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        MenkeCard *menke_card = new MenkeCard;
        menke_card->addSubcard(card_item->getCard()->getId());
        return menke_card;
    }
};


WangniCard::WangniCard(){
    once = true;
}

void WangniCard::onEffect(const CardEffectStruct &effect) const{
    ServerPlayer *xugong = effect.from;
    LogMessage log;
    log.from = xugong;
    log.to << effect.to;
    log.type = "#wangni";
    xugong->getRoom()->sendLog(log);
    xugong->getRoom()->swapSeat(xugong, effect.to);
}

bool WangniCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(!targets.isEmpty())
        return false;
    if(!to_select->isAlive())
        return false;
    if(to_select->getKingdom()!="wu")
        return false;

    return true;
}
class Wangni: public ViewAsSkill{
public:
    Wangni():ViewAsSkill("wangni"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("WangniCard");
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        if(to_select->isEquipped())
            return false;

        if(selected.isEmpty())
            return to_select->getFilteredCard()->isBlack();
        else if(selected.length() == 1)
        {
            return to_select->getFilteredCard()->isBlack() ;
        }else
            return false;


    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(cards.length() != 2)
            return NULL;

        WangniCard *card = new WangniCard;
        card->addSubcards(cards);
        return card;
    }
};

class Mimou: public OneCardViewAsSkill{
public:
    Mimou():OneCardViewAsSkill("mimou"){
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped() && to_select->getCard()->getSuit() == Card::Diamond;
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        const Card *card = card_item->getFilteredCard();
        ExNihilo *mimoucard = new ExNihilo(card->getSuit(), card->getNumber());
        mimoucard->addSubcard(card);
        mimoucard->setSkillName(objectName());
        return mimoucard;
    }
};

class Weisui: public TriggerSkill{
public:
    Weisui():TriggerSkill("weisui"){
        events << Predamage;
        frequency = Compulsory;
    }
    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        ServerPlayer *luyi = room->findPlayerBySkillName(objectName());
        if(!luyi) return false;
        LogMessage log;
        log.from = luyi;
        if(event == Predamage){
            DamageStruct damage = data.value<DamageStruct>();
            const Card *reason = damage.card;
            if(!reason )
                return false;
            if(damage.from != luyi)
                return false;

            if(reason->inherits("Slash")||reason->inherits("Duel"))
            {
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(spade):(.*)");
                judge.good = false;
                judge.reason = "weisui";
                judge.who = luyi;
                room->judge(judge);
                if(judge.isGood())
                {
                    log.to << damage.to;
                    log.type = "#weisuifailed";
                    log.arg=reason->objectName();
                    room->sendLog(log);
                    return true;
                }
            }
        }

        return false;
    }
};
DanceCard::DanceCard(){
}

bool DanceCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(targets.length() >= 3)
        return false;
    if(!to_select->isWounded())
        return false;
    return true;

}

void DanceCard::onEffect(const CardEffectStruct &effect) const{

    ServerPlayer *dancer = effect.from;
    ServerPlayer *target = effect.to;
    Room *room = dancer->getRoom();
    LogMessage log;
    log.from = dancer;
    RecoverStruct recover;
    recover.who = dancer;
    room->recover(target, recover);
    log.type = "#dancediamond";
    log.to<<target;
    room->sendLog(log);

}

class DanceViewAsSkill: public ZeroCardViewAsSkill{
public:
    DanceViewAsSkill():ZeroCardViewAsSkill("dancediamond"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const{
        return  pattern == "@@dance";
    }

    virtual const Card *viewAs() const{
        return new DanceCard;
    }
};

class Dance: public PhaseChangeSkill{
public:
    Dance():PhaseChangeSkill("dance"){
        view_as_skill = new DanceViewAsSkill;
    }
    virtual int getPriority() const{
        return 2;
    }


    virtual bool onPhaseChange(ServerPlayer *dancer) const{


        if(dancer->getPhase() == Player::Play){

            Room *room = dancer->getRoom();           
            if(room->askForSkillInvoke(dancer, objectName()))
            {
                if(!room->askForDiscard(dancer,"@dancereason",2,true,false))
                      dancer->turnOver();

                //QList<ServerPlayer *> all_players = room->getOtherPlayers(dancer);
                //QList<ServerPlayer *> all_players = room->getAlivePlayers();                
                LogMessage log;
                log.from = dancer;
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(.*):(.*)");
                judge.good = false;
                judge.reason = objectName();
                judge.who = dancer;
                room->judge(judge);

                switch(judge.card->getSuit())
                //switch(Card::Diamond)
                {
                case Card::Heart:{
                                    room->setEmotion(dancer, "bad");
                                    QString victim=Sanguosha->getRandomGeneralName();
                                    ServerPlayer *victimplayer;
                                    while(!room->findPlayer(victim,false))
                                    {
                                        victim = Sanguosha->getRandomGeneralName();
                                        /*log.type="#dancedebug";
                                        log.arg=victim;
                                        room->sendLog(log);*/
                                    }
                                    victimplayer=room->findPlayer(victim,false);
                                    log.arg=victimplayer->getGeneralName();
                                    if(victimplayer==dancer)
                                        log.type="#danceheartself";
                                    else
                                        log.type="#danceheart";
                                    room->sendLog(log);
                                    room->loseHp(victimplayer,1);
                                    break;
                                }

                case Card::Diamond:{
                                    room->setEmotion(dancer, "good");
                                    room->askForUseCard(dancer, "@@dance", "@dance");

                                    break;
                                }

                case Card::Club:{
                                 room->setEmotion(dancer, "bad");
                                 QString bombername=Sanguosha->getRandomGeneralName();
                                 ServerPlayer *bomber;
                                 while(!room->findPlayer(bombername,false))
                                 {                                     
                                     bombername = Sanguosha->getRandomGeneralName();
                                 }
                                 bomber=room->findPlayer(bombername,false);
                                 log.arg=bomber->getGeneralName();
                                 if(bomber==dancer)
                                     log.type="#dancebombself";
                                 else
                                     log.type="#dancebomb";
                                 DamageStruct reason;
                                 reason.from = bomber;
                                 reason.to = bomber;
                                 room->sendLog(log);
                                 room->getThread()->delay(2000);
                                 room->killPlayer(bomber,&reason);
                                 room->getThread()->delay(2000);
                                    foreach(ServerPlayer *victim, room->getAlivePlayers())
                                    {                                       
                                         room->getThread()->delay(1500);
                                         DamageStruct bombdamage;
                                         bombdamage.card = NULL;
                                         if(bomber->getMaxHP()<4)
                                           bombdamage.damage = bomber->getMaxHP()-1;
                                         else
                                           bombdamage.damage = bomber->getMaxHP()-2;
                                         bombdamage.from=bomber;
                                         bombdamage.to=victim;
                                         log.type="#dancebombing";
                                         log.arg2=victim->getGeneralName();
                                         room->sendLog(log);
                                         room->damage(bombdamage);                                        
                                    }
                                    break;
                                }
                case Card::Spade:{
                        room->setEmotion(dancer, "good");
                        foreach(ServerPlayer *player, room->getOtherPlayers(dancer))
                        {
                                log.type="#dancespade";
                                log.arg=player->getGeneralName();
                                room->getThread()->delay(1000);
                                DamageStruct damage;
                                damage.card = NULL;
                                damage.damage = 1;
                                damage.from=player;
                                damage.to=player;
                                room->sendLog(log);
                                room->damage(damage);

                        }

                        break;
                    }
                default:
                    break;}
            }
        }
        return false;
    }
};

class Archershoot: public TriggerSkill{
public:
    Archershoot():TriggerSkill("archershoot"){
        events <<CardFinished;
        //<< CardUsed
    }
    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *archer, QVariant &data) const{
        const Card *card = NULL;
        CardUseStruct use = data.value<CardUseStruct>();
        card = use.card;
        Room *room = archer->getRoom();
        if(card == NULL)
            return false;
        if(card->inherits("ArcheryAttack"))
        {
            if(archer->askForSkillInvoke(objectName()))
            {
                LogMessage log;
                log.from = archer;
                int x=room->getAlivePlayers().count();
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(.*):(.*)");
                judge.good = false;
                judge.reason = objectName();
                judge.who = archer;
                room->judge(judge);
                if(judge.card->isRed())
                {
                    room->setEmotion(archer, "good");
                    int y;
                    if(x>4) y=4;
                    else y=x-1;
                    for(int z=1;z<y;z++)
                    {
                        QString victim=Sanguosha->getRandomGeneralName();
                        ServerPlayer *victimplayer;
                        while((!room->findPlayer(victim,false))||room->findPlayer(victim,false)==archer)
                        {
                             victim = Sanguosha->getRandomGeneralName();                            
                         }
                         victimplayer=room->findPlayer(victim,false);
                         room->setEmotion(victimplayer, "bad");
                         log.arg=victimplayer->getGeneralName();
                         log.type="#archershoot";
                         room->sendLog(log);
                         Slash *slash = new Slash(Card::NoSuit, 0);
                         slash->setSkillName("archershoot");
                         CardUseStruct usetmp;
                         usetmp.from = archer;
                         usetmp.to << victimplayer;
                         usetmp.card = slash;
                         room->useCard(usetmp);

                    }
                }
                else
                {
                    room->setEmotion(archer, "bad");
                    log.type="#archershootfailed";
                    room->sendLog(log);
                }
            }

        }

        return false;
    }
};
class Archerskill: public TriggerSkill{
public:
    Archerskill():TriggerSkill("archerskill"){
        events << CardFinished;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return !target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        CardUseStruct use = data.value<CardUseStruct>();
        if(use.card->inherits("ArcheryAttack")){
            Room *room = player->getRoom();
            if(room->getCardPlace(use.card->getEffectiveId()) == Player::DiscardedPile){
                // finding archer;
                QList<ServerPlayer *> players = room->getAllPlayers();
                foreach(ServerPlayer *p, players)
                {
                    if(p->hasSkill(objectName()))
                    {
                        p->obtainCard(use.card);

                        break;
                    }
                }
            }
        }

        return false;
    }
};

class ArcheryAttackAvoid: public TriggerSkill{
public:
    ArcheryAttackAvoid(const QString &avoid_skill)
        :TriggerSkill("#sa_avoid_" + avoid_skill), avoid_skill(avoid_skill)
    {
        events << CardEffected;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        CardEffectStruct effect = data.value<CardEffectStruct>();
        if(effect.card->inherits("ArcheryAttack")){
            LogMessage log;
            log.type = "#SkillNullify";
            log.from = player;
            log.arg = avoid_skill;
            log.arg2 = "archery_attack";
            player->getRoom()->sendLog(log);

            return true;
        }else
            return false;
    }

private:
    QString avoid_skill;
};


class Spreadingshoot: public PhaseChangeSkill{
public:
    Spreadingshoot():PhaseChangeSkill("spreadingshoot$"){
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->isWounded()&&target->hasSkill(objectName());
    }
    virtual bool onPhaseChange(ServerPlayer *archer) const{
        if(archer->getPhase() == Player::Draw){
            Room *room = archer->getRoom();
            if(room->askForSkillInvoke(archer, objectName())){
                int x = archer->getLostHp(), i;

                for(i=0; i<x; i++){
                    int card_id = room->drawCard();
                    room->moveCardTo(Sanguosha->getCard(card_id), NULL, Player::Special, true);

                    room->getThread()->delay();
                    const Card *card = Sanguosha->getCard(card_id);
                    if(card->getSuit() == Card::Diamond){
                        ArcheryAttack *wanjian = new ArcheryAttack(Card::Diamond, card->getNumber());
                        wanjian->setSkillName("spreadingshoot");
                        wanjian->addSubcard(card);
                        CardUseStruct card_use;
                        card_use.card = wanjian;
                        card_use.from = archer;
                        room->useCard(card_use);

                    }else
                        room->obtainCard(archer, card_id);
                }

                return true;
            }
        }
        return false;
    }
};


class ZombieBody: public TriggerSkill{
public:
    ZombieBody():TriggerSkill("#zombiebody"){
        events << CardEffected;
        frequency = Compulsory;
    }
    virtual bool triggerable(const ServerPlayer *target) const{
            return true;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        const Card *card = NULL;
        Room *room = player->getRoom();
        ServerPlayer *zhangling = room->findPlayerBySkillName("zombiemaster");
        CardEffectStruct effect = data.value<CardEffectStruct>();
        card = effect.card;
        if(effect.to!=zhangling)
            return false;
        int x=zhangling->getPile("zombies").length();
        if (x==0) return false;
        if(x!=0&&x>2) x=2;
        if(event == CardEffected)
        {

            if(card == NULL)
            return false;
            if(card->inherits("Peach"))
            {
                LogMessage log;
                log.from=zhangling;
                log.type="#zombieskill";               
                RecoverStruct recover;
                recover.recover=x;
                recover.who = zhangling;
                room->sendLog(log);
                room->recover(zhangling, recover);

            }
        }
        return false;
    }
};

class ZombieMaster: public TriggerSkill{
public:
    ZombieMaster():TriggerSkill("zombiemaster"){
        events << CardLost << CardLostDone << FinishJudge;
        frequency = NotFrequent;
    }


    virtual bool triggerable(const ServerPlayer *target) const{
        return TriggerSkill::triggerable(target) && target->getPhase() == Player::NotActive;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        ServerPlayer *zhangling=player;
        if(event == CardLost){
            CardMoveStar move = data.value<CardMoveStar>();

            if(move->from_place == Player::Hand || move->from_place == Player::Equip)
                player->tag["Invokezombiemaster"] = true;
        }else if(event == CardLostDone){
            if(!player->tag.value("Invokezombiemaster", false).toBool())
                return false;
            player->tag.remove("Invokezombiemaster");

            if(player->askForSkillInvoke("zombiemaster", data)){
                Room *room = player->getRoom();
                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(heart):(.*)");
                judge.good = false;
                judge.reason = "zombiemaster";
                judge.who = player;

                room->judge(judge);
            }
        }else if(event == FinishJudge){
            JudgeStar judge = data.value<JudgeStar>();
            if(judge->reason == "zombiemaster" && judge->isGood())
            {
                player->addToPile("zombies", judge->card->getEffectiveId());
                LogMessage log;
                log.from=zhangling;
                log.arg=judge->card->objectName();
                log.type="#zombiemaster";
                player->getRoom()->sendLog(log);
                return true;
            }
        }

        return false;
    }
};

ZombieCard::ZombieCard(){
    target_fixed = true;
}

void ZombieCard::onUse(Room *room, const CardUseStruct &card_use) const{
    ServerPlayer *zhangling = card_use.from;
    LogMessage log;
    log.from=zhangling;
    QList<int> zombies = zhangling->getPile("zombies");
    if(zombies.isEmpty())
        return;

    int card_id;
    if(zombies.length() == 1)
        card_id = zombies.first();
    else
    {
        room->fillAG(zombies,zhangling);
        card_id = room->askForAG(zhangling, zombies, false,"zombiebomb");
        zhangling->invoke("clearAG");
        if(card_id == -1) return;
    }

    ServerPlayer *target = room->askForPlayerChosen(zhangling,room->getOtherPlayers(zhangling),"zombiebomb");

    log.arg=target->getGeneralName();
    JudgeStruct judge;
    judge.pattern = QRegExp("(.*):(.*):(.*)");
    judge.good = true;
    judge.reason = "zombiebomb";
    judge.who = zhangling;
    room->judge(judge);
    switch(judge.card->getSuit()){
      case Card::Heart:{
                           room->setEmotion(target, "bad");
                           room->setEmotion(zhangling, "good");
                           log.type="#zbHeart";
                           DamageStruct damage;
                           damage.card = NULL;
                           damage.nature=DamageStruct::Fire;
                           damage.damage = 1;
                           damage.from=NULL;
                           damage.to=target;
                           room->sendLog(log);
                           room->damage(damage);
                           target->turnOver();
                           break;}

     case Card::Diamond:{room->setEmotion(zhangling, "bad");
                        log.type="#zbfailed";
                        room->sendLog(log);

             break;}

     case Card::Club:{  room->setEmotion(zhangling, "bad");
                        log.type="#zbfailed";
                        room->sendLog(log);

             break;}

     case Card::Spade:{
                           room->setEmotion(target, "good");
                           room->setEmotion(zhangling, "bad");
                           log.type="#zbSpade";
                           room->sendLog(log);
                           zhangling->turnOver();
                           break;}

        default:break;}

    room->throwCard(card_id);
}

class ZombieBomb:public ZeroCardViewAsSkill{
public:
    ZombieBomb():ZeroCardViewAsSkill("zombiebomb"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return !player->getPile("zombies").isEmpty();
    }

    virtual const Card *viewAs() const{
        return new ZombieCard;
    }
};

class ZombiePoison:public ZeroCardViewAsSkill{
public:
    ZombiePoison():ZeroCardViewAsSkill("zombiepoison"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return !player->getPile("zombies").isEmpty();
    }

    virtual const Card *viewAs() const{
        return new PoisonCard;
    }
};

PoisonCard::PoisonCard(){
    target_fixed = true;
}

void PoisonCard::onUse(Room *room, const CardUseStruct &card_use) const{
    ServerPlayer *zhangling = card_use.from;
    QList<int> zombies = zhangling->getPile("zombies");
    int x=zombies.count();
    if(x>3) x=3;
    if(zombies.isEmpty())
    return;
    if(room->askForSkillInvoke(zhangling,"zombiepoison"))
    {
        LogMessage log;
        log.from=zhangling;


        int card_id;
        if(zombies.length() == 1)
        {
            card_id = zombies.first();
            room->throwCard(card_id);
        }
        else
        {
            foreach(int cid,zhangling->getPile("zombies"))
            {
                room->throwCard(cid);
            }

        }


    JudgeStruct judge;
    judge.pattern = QRegExp("(.*):(.*):(.*)");
    judge.good = true;
    judge.reason = "zombiepoison";
    judge.who = zhangling;
    room->judge(judge);
    switch(judge.card->getSuit()){
      case Card::Heart:{   room->setEmotion(zhangling, "bad");
                           log.type="#zpfailed";
                           room->sendLog(log);
                           break;}

     case Card::Diamond:{
                    room->setEmotion(zhangling, "good");
                    log.type="#zpDiamond";
                    DamageStruct damage;
                    damage.card = NULL;
                    damage.nature=DamageStruct::Fire;
                    damage.damage = x;
                    damage.from=NULL;
                    foreach(ServerPlayer *player,room->getOtherPlayers(zhangling))
                    {
                            room->setEmotion(player, "bad");
                            log.arg=player->getGeneralName();
                            room->sendLog(log);
                            damage.to=player;
                            room->damage(damage);
                    }

                           break;}

     case Card::Club:{

             log.type="#zpClub";
             foreach(ServerPlayer *player,room->getAlivePlayers())
             {
                    room->setEmotion(player, "bad");
                    log.arg=player->getGeneralName();
                    room->loseHp(player);
                    room->sendLog(log);
             }



                           break;}

     case Card::Spade:{room->setEmotion(zhangling, "bad");
                       log.type="#zpfailed";
                       room->sendLog(log);
                           break;}

        default:break;}


  }else return;

}
class Buzhen: public TriggerSkill{
public:
    Buzhen():TriggerSkill("buzhen"){
        events << PhaseChange ;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room=player->getRoom();
        ServerPlayer *fengchu=player->getRoom()->findPlayerBySkillName(objectName());
        if(event==PhaseChange)
        {
            if(fengchu->getPhase() == Player::Play)
            {
                if(fengchu->getHandcardNum()>=2 && room->askForSkillInvoke(fengchu,objectName()))
                {
                    foreach(ServerPlayer *tmp, player->getRoom()->getAlivePlayers())
                    {
                        if(tmp->getMark("@zhenyan")>0) tmp->loseAllMarks("@zhenyan");
                        if(tmp->getMark("@zhenzhong")>0) tmp->loseAllMarks("@zhenzhong");
                    }
                    for(int i = 1; i <= 4; i++)
                    {
                      QString mark_name = "@buzhen" + QString::number(i);
                      if(fengchu->getMark(mark_name)>0)
                      fengchu->loseAllMarks(mark_name);
                    }
                    room->askForDiscard(fengchu,"buzhen",2,false,false);
                    ServerPlayer *zhenyan,*zhenyan2;
                    zhenyan=room->askForPlayerChosen(fengchu,room->getOtherPlayers(fengchu),"buzhen");
                    zhenyan->gainMark("@zhenyan",1);
                    zhenyan2=room->askForPlayerChosen(fengchu,room->getOtherPlayers(fengchu),"buzhen");
                    while(zhenyan2==zhenyan)
                    {
                      zhenyan2=room->askForPlayerChosen(fengchu,room->getOtherPlayers(zhenyan),"buzhen");
                    }
                    zhenyan2->gainMark("@zhenyan",1);
                    int x=0;
                    foreach(ServerPlayer *tmp, player->getRoom()->getAlivePlayers())
                    {
                        if(tmp->getMark("@zhenyan")==1)
                        {
                            x++;
                        }
                        if(x==1&&tmp->getMark("@zhenyan")<1)
                        {
                            tmp->gainMark("@zhenzhong",1);
                        }
                        if(x==2)
                            break;
                    }

                    JudgeStruct judge;
                    judge.pattern = QRegExp("(.*):(.*):(.*)");
                    judge.good = false;
                    judge.reason = objectName();
                    judge.who = fengchu;
                    room->judge(judge);

                    switch(judge.card->getSuit())
                   // switch(Card::Heart)
                    {
                    case Card::Heart:{
                                        room->broadcastInvoke("animate", "lightbox:$buzhen1");
                                        fengchu->gainMark("@buzhen1");
                                        break;
                                    }

                    case Card::Diamond:{
                                        room->broadcastInvoke("animate", "lightbox:$buzhen2");
                                        fengchu->gainMark("@buzhen2");
                                        break;
                                    }

                    case Card::Club:{
                                        room->broadcastInvoke("animate", "lightbox:$buzhen3");
                                        fengchu->gainMark("@buzhen3");
                                        break;
                                    }
                    case Card::Spade:{
                                        room->broadcastInvoke("animate", "lightbox:$buzhen4");
                                        fengchu->gainMark("@buzhen4");
                            break;
                        }
                    default:
                        break;}

                }
            }
        }
        return false;
    }
};

class BuzhenEffect:public TriggerSkill{
public:
    BuzhenEffect():TriggerSkill("#buzhen_eft"){
        events<<HpRecover<<Damaged<<DamageDone<<Predamaged<<TurnStart;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        for(int i = 1; i <= 4; i++){
            QString mark_name = "@buzhen" + QString::number(i);
            if(target->getMark(mark_name) > 0)
                return true;
        }
        if(target->getMark("@zhenyan") > 0)return true;
        if(target->getMark("@zhenzhong") > 0)return true;
        return false;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room=player->getRoom();
        ServerPlayer *fengchu=player->getRoom()->findPlayerBySkillName("buzhen");
        LogMessage log;
        if(event==HpRecover )
        {
            RecoverStruct recover = data.value<RecoverStruct>();
            if(player->getMark("@zhenzhong")>0 && fengchu->getMark("@buzhen1")>0)
            {
                log.from=fengchu;
                log.type="#buzhen1";
                log.arg=player->getGeneralName();
                room->sendLog(log);
                int x = recover.recover, i;
                for(i=0; i<x; i++){
                    RecoverStruct r;
                    r.recover=1;
                    r.who = fengchu;
                    room->recover(fengchu, r);
                }
            }
        }
        else if(event==Damaged)
        {
                DamageStruct damage = data.value<DamageStruct>();
                if(damage.to==fengchu && fengchu->getMark("@buzhen2")>0)
                {
                    foreach(ServerPlayer *tmp, room->getAlivePlayers())
                    {

                        if(tmp->getMark("@zhenzhong") > 0&&room->askForSkillInvoke(fengchu,"buzhen2"))
                        {
                            log.from=fengchu;
                            log.type="#buzhen2";
                            log.arg=tmp->getGeneralName();
                            room->sendLog(log);
                            if(!tmp->isKongcheng())
                            room->askForDiscard(tmp,"buzhen",1,false,false);
                        }
                     }
                }

        }
        else if(event==DamageDone)
        {
            DamageStruct damage = data.value<DamageStruct>();
            if(damage.to==player && player->getMark("@zhenyan")>0 && fengchu->getMark("@buzhen3")>0)
            {
                log.from=fengchu;
                log.type="#buzhen3";
                log.arg=player->getGeneralName();
                room->sendLog(log);
                int x = damage.damage, i;
                 for(i=0; i<x; i++)
                {
                    fengchu->drawCards(2);
                }
             }
        }
        else if(event==Predamaged)
        {
            DamageStruct damage = data.value<DamageStruct>();

            if(damage.to==player&&player->getMark("@zhenzhong")>0)
            {
                if(!fengchu->getMark("@buzhen4")>0)
                    return false;
                if((!fengchu->isKongcheng())&& room->askForSkillInvoke(fengchu,"buzhen4"))
                {
                     if(room->askForDiscard(fengchu,"buzhen4",1,true,false))
                    {
                         log.from=fengchu;
                         log.type="#buzhen4";
                         log.arg=player->getGeneralName();
                         room->sendLog(log);
                        return true;
                    }
                }
            }
        }
        else if(event == TurnStart)
        {
                   int mks=0;
                   foreach(ServerPlayer *tmp, player->getRoom()->getAlivePlayers())
                   {
                     if(tmp->getMark("@zhenyan") > 0)
                     mks++;
                   }
                   if(mks<2 ||fengchu->isDead())
                   {
                       foreach(ServerPlayer *tmp, player->getRoom()->getAlivePlayers())
                       {
                             if(tmp->getMark("@zhenyan")>0) tmp->loseAllMarks("@zhenyan");
                             if(tmp->getMark("@zhenzhong")>0)tmp->loseAllMarks("@zhenzhong");
                             for(int i = 1; i <= 4; i++)
                             {
                               QString mark_name = "@buzhen" + QString::number(i);
                               if(tmp->getMark(mark_name) > 0)
                               tmp->loseAllMarks(mark_name);
                             }
                       }
                   }

                   return false;
        }

        return false;
    }
};
AssassinPackage::AssassinPackage()
    :Package("Assassin")
{

    General *chizhizhe=new General(this, "chizhizhe$", "qun",4);
    chizhizhe->addSkill(new Youguai);
    chizhizhe->addSkill(new Bangpiao);
    chizhizhe->addSkill(new Sipiao);



    General *jiping=new General(this, "jiping", "qun",3);
    jiping->addSkill(new Dusha);
    jiping->addSkill(new Cuidu);

    General *liuye=new General(this, "liuye", "wei",3);
    liuye->addSkill(new Shaqie);
    liuye->addSkill(new Shengyan);
    liuye->addSkill(new Wuhuan);

    General *hanlong=new General(this, "hanlong", "wei",3);
    hanlong->addSkill(new Yuanxing);
    hanlong->addSkill(new Liwei);




    General *yinfan=new General(this, "yinfan", "wu",3);
    yinfan->addSkill(new Tiaobo);
    yinfan->addSkill(new Lianzuo);

    General *wufu=new General(this, "wufu", "qun",3);
    wufu->addSkill(new Bujing);
    wufu->addSkill(new Qingkai);
    wufu->addSkill(new Bishou);

    General *guoxiu=new General(this, "guoxiu", "wei",4);
    guoxiu->addSkill(new Pofuchenzhou);

    General *weike=new General(this, "weike", "wei",3);
    weike->addSkill(new Taolue);
    weike->addSkill(new Quanjiu);

    General *fanjiangzhangda=new General(this, "fanjiangzhangda", "shu",3);
    fanjiangzhangda->addSkill(new Fankang);

    General *xugong=new General(this, "xugong", "wu",4);
    xugong->addSkill(new Menke);
    xugong->addSkill(new Wangni);

    General *luyi=new General(this, "luyi", "wei",3);
    luyi->addSkill(new Mimou);
    luyi->addSkill(new Weisui);


    // for skill cards

    addMetaObject<SipiaoCard>();    
    addMetaObject<TiaoboCard>();
    addMetaObject<TianleiCard>();
    addMetaObject<MenkeCard>();
    addMetaObject<WangniCard>();
    
}

TaichiePackage::TaichiePackage()
    :Package("Taichie")
{
    General *zhangsong=new General(this, "zhangsong", "shu",3);
    zhangsong->addSkill(new Jinghan);
    zhangsong->addSkill(new Qiangzhi);

    General *shadowEX=new General(this, "shadowEX", "shu",4,false);
    shadowEX->addSkill(new Ansha);
    shadowEX->addSkill(new Shangsan);
    shadowEX->addSkill(new Jimie);

    General *gexuan=new General(this, "gexuan", "qun",3);
    gexuan->addSkill(new Xiulian);

    General *dancer=new General(this, "dancer", "qun",4,false);
    dancer->addSkill(new Dance);

    General *archer=new General(this, "archer$", "qun",3,false);
    archer->addSkill(new Spreadingshoot);
    archer->addSkill(new Archershoot);
    archer->addSkill(new Archerskill);
    archer->addSkill(new ArcheryAttackAvoid("archerskill"));

    related_skills.insertMulti("archerskill", "#sa_avoid_archerskill");

    General *zhangling=new General(this, "zhangling", "qun",4);
    zhangling->addSkill(new ZombieMaster);
    zhangling->addSkill(new ZombieBomb);
    zhangling->addSkill(new ZombiePoison);
    related_skills.insertMulti("zombiemaster", "#zombiebody");

    General *fengchu=new General(this, "fengchu", "shu",3);
    fengchu->addSkill(new Buzhen);
    fengchu->addSkill(new BuzhenEffect);
    related_skills.insertMulti("buzhen", "#buzhen_eft");

    // for skill cards
    addMetaObject<DanceCard>();
    addMetaObject<ZombieCard>();
    addMetaObject<PoisonCard>();

    skills << new ShuguangRetrial<<new Leifu<<new Fentian<<new Xuwu<<new Tianlei<<new Dujie<<new ZombieBody;
    //related_skills.insertMulti("heimu", "#heimu-retrial");

}

ADD_PACKAGE(Assassin)
ADD_PACKAGE(Taichie)
