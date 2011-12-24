#include "thunderpackage.h"
#include "standard.h"
#include "skill.h"
#include "wind.h"
#include "client.h"
#include "carditem.h"
#include "engine.h"

class Xianhai:public PhaseChangeSkill{
public:
    Xianhai():PhaseChangeSkill("xianhai"){
        frequency = Frequent;
    }

    virtual bool onPhaseChange(ServerPlayer *zhonghui) const{
        if(zhonghui->getPhase() == Player::Finish &&
           zhonghui->askForSkillInvoke(objectName()))
        {
            Room *room = zhonghui->getRoom();
            room->playSkillEffect("tongmou",2);

            int n = qMin(3, room->alivePlayerCount());
            room->doGuanxing(zhonghui, room->getNCards(n, false), false);
        }

        return false;
    }
};

class Yexin: public PhaseChangeSkill{
  public:
     Yexin():PhaseChangeSkill("yexin"){
        frequency = Wake;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
         return PhaseChangeSkill::triggerable(target)
                 && target->getMark("yexin") == 0
                 && target->getPhase() == Player::Start
                 && target->getHp() <= 2;
    }

   virtual bool onPhaseChange(ServerPlayer *zhonghui) const{
            Room *room = zhonghui->getRoom();

            LogMessage log;
            log.type = "#YexinWake";
            log.from = zhonghui;
            log.arg = QString::number(zhonghui->getHp());
            log.arg2 = QString::number(2);
            room->sendLog(log);

            zhonghui->setMark("yexin", 1);

            RecoverStruct recover;
            recover.who = zhonghui;
            room->recover(zhonghui, recover);

            room->loseMaxHp(zhonghui);

            room->acquireSkill(zhonghui, "xianhai");

              return false;
          }
      };

class Lianyun: public PhaseChangeSkill{
  public:
     Lianyun():PhaseChangeSkill("lianyun"){
        frequency = Wake;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
         return PhaseChangeSkill::triggerable(target)
                 && target->getPhase() == Player::Start;
    }

   virtual bool onPhaseChange(ServerPlayer *mayunlv) const{
          Room *room = mayunlv->getRoom();

          QList<ServerPlayer *> targets;
          foreach(ServerPlayer *p, room->getAlivePlayers())
              if(p->getKingdom() == "shu")
                  targets << p;

          if(mayunlv->getMark("lianyun") == 0 && targets.length() <= 2){
             LogMessage log;
             log.type = "#LianyunWake";
             log.from = mayunlv;
             log.arg = QString::number(2);
             room->sendLog(log);

             mayunlv->setMark("lianyun", 1);

             room->loseMaxHp(mayunlv);
             room->acquireSkill(mayunlv, "longdan");

         }

         return false;
     }
 };

class Jinguo:public SlashBuffSkill{
public:
    Jinguo():SlashBuffSkill("jinguo"){

    }

    virtual bool buff(const SlashEffectStruct &effect) const{
        ServerPlayer *mayunlv = effect.from;

        Room *room = mayunlv->getRoom();
        if(effect.from->askForSkillInvoke("jinguo", QVariant::fromValue(effect))){
            room->playSkillEffect(objectName());

            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(.*):(.*)");
            judge.good = true;
            judge.who = effect.from;
            judge.reason = objectName();

            room->judge(judge);

            switch(judge.card->getSuit()){
            case Card::Heart:{
                    effect.from->drawCards(1);

                    break;
                }

            case Card::Diamond:{
                    room->slashResult(effect, NULL);
                    return true;
                    break;
                }

            case Card::Club:{
                    if(effect.from && effect.from->isAlive() && !effect.to->isNude()){
                        int to_discard = qMin(1, effect.from->getCardCount(true));
                        if(to_discard != 0)
                            room->askForDiscard(effect.from, "jinguo", to_discard, false, true);
                        int to_throw = room->askForCardChosen(mayunlv, effect.to, "he", objectName());
                        room->throwCard(to_throw);
                    }

                    break;
                }

            case Card::Spade:{
                     effect.to->drawCards(2);
                     effect.to->turnOver();

                    break;
                }

            default:
                break;
            }
        }

        return false;
    }
};

class Jichi: public TriggerSkill{
public:
    Jichi():TriggerSkill("jichi"){
        events << SlashMissed;
    }

    virtual int getPriority() const{
        return 2;
    }

    virtual bool trigger(TriggerEvent, ServerPlayer *lvlingqi, QVariant &data) const{
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if(!effect.to->isNude() && !lvlingqi->isKongcheng() && !effect.to->isKongcheng()){
            Room *room = lvlingqi->getRoom();
           if(lvlingqi->askForSkillInvoke(objectName(), data)){
                room->playSkillEffect(objectName());
            bool success = lvlingqi->pindian(effect.to, "jichi", NULL);
                if(success){
                    room->slashResult(effect, NULL);
                    return true;
                    }
            }
       }
                     return false;
         }
    };

class Hunv: public TriggerSkill{
public:
    Hunv():TriggerSkill("hunv"){
        events << Pindian;
    }

    virtual int getPriority() const{
        return 0;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *lvlingqi, QVariant &data) const{
        PindianStar pindian = data.value<PindianStar>();
         Room *room = lvlingqi->getRoom();
        if(pindian->reason == "jichi"){

            int num = pindian->from_card-> getNumber() + 3 ;
            if (num > 13) num = 13;
            const Card *tmp = pindian->from_card;
            Card *use_card = Sanguosha->cloneCard(tmp->objectName(), tmp->getSuit(), num);
            use_card->setSkillName(objectName());
            use_card->addSubcard(tmp);
            pindian->from_card = use_card;

            LogMessage log;
            log.type = "#Hunv";

            room->sendLog(log);

          if(pindian->reason == "jichi" && pindian->isSuccess()){
                lvlingqi->drawCards(1);
            }
        }
        data = QVariant::fromValue(pindian);
        return false;
    }
};

class Jiangmen: public PhaseChangeSkill{
public:
    Jiangmen():PhaseChangeSkill("jiangmen"){
       frequency = Wake;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
         return PhaseChangeSkill::triggerable(target)
                 && target->getPhase() == Player::Start;
      }

      virtual bool onPhaseChange(ServerPlayer *lvlingqi) const{
         foreach(const Player *player, lvlingqi->getSiblings()){
              if(player->isDead() && player->getGeneral()->isMale()
                 && lvlingqi->getMark("jiangmen") == 0 && !player->isLord() && player != lvlingqi){

          lvlingqi->setMark("jiangmen", 1);

          Room *room = lvlingqi->getRoom();

          LogMessage log;
          log.type = "#JiangmenWake";
          log.from = lvlingqi;
          room->sendLog(log);

          room->loseMaxHp(lvlingqi);
          room->acquireSkill(lvlingqi, "hunv");
      }
          }

          return false;
      }
  };

class Shouming: public PhaseChangeSkill{
public:
    Shouming():PhaseChangeSkill("shouming"){
       frequency = Wake;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
         return PhaseChangeSkill::triggerable(target)
                 && target->getPhase() == Player::Start;
      }

      virtual bool onPhaseChange(ServerPlayer *madai) const{
         foreach(const Player *player, madai->getSiblings()){
             if(player->isDead() && player->getKingdom() == "shu"
                 && madai->getMark("shouming") == 0 && !player->isLord() && player != madai){

          madai->setMark("shouming", 1);

          Room *room = madai->getRoom();

          LogMessage log;
          log.type = "#ShoumingWake";
          log.from = madai;
          room->sendLog(log);

          room->loseMaxHp(madai);
          room->acquireSkill(madai, "yuanjun");
          room->acquireSkill(madai, "qishu");
      }
          }

          return false;
      }
  };

YuanjunCard::YuanjunCard(){
    once = true;
}

bool YuanjunCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.length() < 1  && to_select != Self;
}

void YuanjunCard::onEffect(const CardEffectStruct &effect) const{
    effect.to->gainMark("@yuanjun");
}

class YuanjunViewAsSkill: public ViewAsSkill{
public:
    YuanjunViewAsSkill():ViewAsSkill("yuanjun"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("YuanjunCard");
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        if(selected.isEmpty())
            return !to_select->isEquipped();
        else
        return false;
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(cards.length() == 1){
            YuanjunCard *card = new YuanjunCard;
            card->addSubcards(cards);
            return card;
        }else
            return NULL;
    }
};

class Yuanjun: public DrawCardsSkill{
public:
    Yuanjun():DrawCardsSkill("yuanjun"){
        view_as_skill = new YuanjunViewAsSkill;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->getMark("@yuanjun") > 0;
    }

    virtual int getDrawNum(ServerPlayer *player, int n) const{
        Room *room = player->getRoom();
        player->loseMark("@yuanjun");

        // find madai
        ServerPlayer *madai = room->findPlayerBySkillName(objectName());
        if(!madai){
            return n;
        }else
        if(madai){
            madai->drawCards(1);
        }

        return n + 1;
    }
};


class YuanjunClear: public PhaseChangeSkill{
public:
    YuanjunClear():PhaseChangeSkill("#yuanjun-clear"){

    }

    virtual bool onPhaseChange(ServerPlayer *madai) const{
        if(madai->getPhase() == Player::Start){
            Room *room = madai->getRoom();
            room->playSkillEffect(objectName());
            QList<ServerPlayer *> players = room->getOtherPlayers(madai);
            foreach(ServerPlayer *player, players){
                if(player->getMark("@yuanjun") > 0){
                    player->loseMark("@yuanjun");
                }
            }
        }

        return false;
    }
};

class Qishu: public DistanceSkill{
public:
    Qishu():DistanceSkill("qishu"){

    }

    virtual int getCorrect(const Player *from, const Player *to) const{
        int correct = 0;
        if(from->hasSkill(objectName())){
            correct --;
            if(from->getOffensiveHorse() != NULL)
                correct -= from->getOffensiveHorse()->getCorrect() ;
        }
        if(to->hasSkill(objectName())){
            correct ++;
            if(to->getDefensiveHorse() != NULL)
                correct -= to->getDefensiveHorse()->getCorrect() ;
        }

        return correct;
    }
};

class Zhuiji: public TriggerSkill{
public:
    Zhuiji():TriggerSkill("zhuiji"){
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
        ServerPlayer *madai = room->findPlayerBySkillName(objectName());
        if(madai && madai->getPhase() == Player::Play && madai->canSlash(damage.to) && damage.from == madai && damage.to != madai  )
        if(madai && madai->askForSkillInvoke(objectName(), data)){
            room->playSkillEffect(objectName());

          JudgeStruct judge;
          judge.pattern = QRegExp("(.*):(.*)");
          judge.good = true;
          judge.who = madai;
          judge.reason = objectName();

          room->judge(judge);

          switch(judge.card->getSuit()){
          case Card::Club:{
                  const Card *slash = room->askForCard(madai, "slash", "zhuijislash");
                  if(slash){
                      room->playSkillEffect(objectName());
                      CardUseStruct use;
                      use.card = slash;
                      use.to << damage.to;
                      use.from = madai;
                      room->useCard(use);
              }
                  break;


              }
          case Card::Diamond:{
                  madai->drawCards(1);

                  break;

              }
          default:
              break;
          }
          }
      return false;
  }
};

class Xuezhan: public TriggerSkill{
public:
    Xuezhan():TriggerSkill("xuezhan"){
        events << SlashProceed;

    }

    virtual bool trigger(TriggerEvent , ServerPlayer *huaxiong, QVariant &data) const{
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        Room *room = huaxiong->getRoom();
        room->playSkillEffect(objectName());

        QString slasher = huaxiong->objectName();

        const Card *first_jink = NULL, *second_jink = NULL;
        first_jink = room->askForCard(effect.to, "jink", "@xuezhan-jink-1:" + slasher);
        if(first_jink){
        second_jink = room->askForCard(effect.to, "jink", "@xuezhan-jink-2:" + slasher);
         room->loseHp(huaxiong);
        }

        Card *jink = NULL;
        if(first_jink && second_jink){
            jink = new DummyCard;
            jink->addSubcard(first_jink);
            jink->addSubcard(second_jink);
        }

        if(!first_jink && !second_jink){
            int to_discard = qMin(1, huaxiong->getCardCount(true));
            if(to_discard != 0)
                room->askForDiscard(huaxiong, "xuezhan", to_discard, false, true);
            DamageStruct damage;
            damage.card = NULL;
            damage.damage = 1;
            damage.from = huaxiong;
            damage.to = effect.to;
            damage.nature = DamageStruct::Normal;

            if(damage.from->hasSkill("jueqing")){
                LogMessage log;
                log.type = "#Jueqing";
                log.from = damage.from;
                log.to << damage.to;
                log.arg = QString::number(1);
                room->sendLog(log);
                room->loseHp(damage.to, 1);
            }else{
                room->damage(damage);
        }
        }
        room->slashResult(effect, jink);


        return true;
    }
};

TongmouCard::TongmouCard(){
    once = true;
}

bool TongmouCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.isEmpty() && to_select->getHandcardNum()>0;
}

void TongmouCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    ServerPlayer *target = source, *player = targets.first();

    LogMessage log;
    log.type = "#Tongmou";
    log.from = target;
    log.to << player;
    room->sendLog(log);

    int n = player->getHandcardNum();

    foreach(const Card *card, player->getHandcards()){
        room->moveCardTo(card, target, Player::Hand, false);
    }

    QList<int> cards_id;
    foreach(const Card *card, target->getHandcards()){
        cards_id << card->getEffectiveId();
    }

    while(n-- > 0){
        room->fillAG(cards_id, target);
        int card_id = room->askForAG(target, cards_id, false, "tongmou");
        room->moveCardTo(Sanguosha->getCard(card_id), player, Player::Hand, false);
        cards_id.removeOne(card_id);
        room->broadcastInvoke("clearAG");
    }

}

class Tongmou: public ZeroCardViewAsSkill{
public:
    Tongmou():ZeroCardViewAsSkill("tongmou"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return !player->hasUsed("TongmouCard");
    }

    virtual const Card *viewAs() const{
        Card *card = new TongmouCard;
        card->setSkillName(objectName());
        return card;
    }

};

ZhongyanCard::ZhongyanCard(){
    once = true;
}

bool ZhongyanCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.length() < 1;
}

void ZhongyanCard::onEffect(const CardEffectStruct &effect) const{
    effect.to->gainMark("@zhongyan");
}

class ZhongyanViewAsSkill: public ViewAsSkill{
public:
    ZhongyanViewAsSkill():ViewAsSkill("zhongyan"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("ZhongyanCard");
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        if(selected.isEmpty() && to_select->getCard()->inherits("TrickCard"))
            return true;
         return false;
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(cards.length() == 1){
            ZhongyanCard *card = new ZhongyanCard;
            card->addSubcards(cards);
            return card;
        }else
            return NULL;
    }
};

class Zhongyan: public TriggerSkill{
public:
    Zhongyan():TriggerSkill("zhongyan"){
        events << CardUsed;
        view_as_skill = new ZhongyanViewAsSkill;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->getMark("@zhongyan") > 0;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        CardUseStruct use = data.value<CardUseStruct>();
        if(player->getMark("@zhongyan") > 0){
                if(use.card->inherits("Slash")){
                    Room *room = player->getRoom();
                    ServerPlayer *maliang = room->findPlayerBySkillName(objectName());
                    if(!maliang){
                        player->loseMark("@zhongyan");
                        room->loseHp(player, 1);
                 }else{
                    DamageStruct damage;
                    damage.card = NULL;
                    damage.from = maliang;
                    damage.to = player;

                    if(damage.from->hasSkill("jueqing")){
                        LogMessage log;
                        log.type = "#Jueqing";
                        log.from = damage.from;
                        log.to << damage.to;
                        log.arg = QString::number(1);
                        room->sendLog(log);
                        room->loseHp(damage.to, 1);
                    }else{
                        room->playSkillEffect("zhongyan",3);
                        room->damage(damage);
                    }
                    }
                }
            }

            return false;
        }
    };

class ZhongyanClear: public PhaseChangeSkill{
public:
    ZhongyanClear():PhaseChangeSkill("#zhongyan-clear"){

    }

    virtual bool onPhaseChange(ServerPlayer *maliang) const{
        if(maliang->getPhase() == Player::Start){
            Room *room = maliang->getRoom();
            room->playSkillEffect(objectName());
            QList<ServerPlayer *> players = room->getOtherPlayers(maliang);
            foreach(ServerPlayer *player, players){
                if(player->getMark("@zhongyan") > 0){
                    player->loseMark("@zhongyan");
                }
            }
        }

        return false;
    }
};

class Baimei: public ProhibitSkill{
public:
    Baimei():ProhibitSkill("baimei"){

    }

    virtual bool isProhibited(const Player *, const Player *maliang, const Card *card) const{
        if(maliang->getHandcardNum() + maliang->getEquips().length() > 5){
        return card->inherits("Dismantlement");
    }else
        if(maliang->getHandcardNum() + maliang->getEquips().length() == 5){
        return card->inherits("Snatch");
    }else
        if(maliang->getHandcardNum() + maliang->getEquips().length() < 5){
        return card->inherits("Indulgence") || card->inherits("SupplyShortage");
    }
    return false;
}

    };

FujiCard::FujiCard(){
    once = true;
}

bool FujiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.length() < 1;
}

void FujiCard::onEffect(const CardEffectStruct &effect) const{
    effect.to->gainMark("@fuji");
}

class FujiViewAsSkill: public ViewAsSkill{
public:
    FujiViewAsSkill():ViewAsSkill("fuji"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("FujiCard");
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        if(selected.isEmpty() && to_select->getCard()->inherits("BasicCard"))
            return true;
         return false;
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(cards.length() == 1){
            FujiCard *card = new FujiCard;
            card->addSubcards(cards);
            return card;
        }else
            return NULL;
    }
};

class Fuji: public TriggerSkill{
public:
    Fuji():TriggerSkill("fuji"){
        events << PhaseChange;
        view_as_skill = new FujiViewAsSkill;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->getMark("@fuji") > 0;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(player->getMark("@fuji") > 0){
                if(player->getPhase() == Player::Start){
                    JudgeStruct judge;
                    judge.pattern = QRegExp("(.*):(spade|club):(.*)");
                    judge.good = true;
                    judge.reason = objectName();
                    judge.who = player;

                    Room *room = player->getRoom();
                    room->judge(judge);
                    if(judge.isGood()){
                        room->playSkillEffect("fuji",2);
                        ServerPlayer *zhangren = room->findPlayerBySkillName(objectName());
                        if(!zhangren){
                            player->loseMark("@fuji");
                            room->loseHp(player, 1);
                     }else{
                        DamageStruct damage;
                        damage.card = NULL;
                        damage.from = zhangren;
                        damage.to = player;

                        if(damage.from->hasSkill("jueqing")){
                            LogMessage log;
                            log.type = "#Jueqing";
                            log.from = damage.from;
                            log.to << damage.to;
                            log.arg = QString::number(1);
                            room->sendLog(log);
                            room->loseHp(damage.to, 1);
                            player->loseMark("@fuji");
                        }else{
                            player->loseMark("@fuji");
                            room->damage(damage);
                        }
                    }
                 }else{
                     player->loseMark("@fuji");
                 }
                }

                }
                return false;
            }
        };

class FujiClear: public PhaseChangeSkill{
public:
    FujiClear():PhaseChangeSkill("#fuji-clear"){

    }

    virtual bool onPhaseChange(ServerPlayer *zhangren) const{
        if(zhangren->getPhase() == Player::Start){
            Room *room = zhangren->getRoom();
            room->playSkillEffect(objectName());
            QList<ServerPlayer *> players = room->getOtherPlayers(zhangren);
            foreach(ServerPlayer *player, players){
                if(player->getMark("@fuji") > 0){
                    player->loseMark("@fuji");
                }
            }
        }

        return false;
    }
};

XianceCard::XianceCard(){
    will_throw = false;
}

void XianceCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    if(targets.isEmpty())
        return;

    ServerPlayer *target = targets.first();
    room->moveCardTo(this, target, Player::Hand, false);

    int n = subcardsLength();
    source->drawCards(n);
}

class XianceViewAsSkill:public ViewAsSkill{
public:
    XianceViewAsSkill():ViewAsSkill("xiance"){
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        return to_select->getCard()->inherits("TrickCard");
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(cards.isEmpty())
            return NULL;

        XianceCard *Xiance_card = new XianceCard;
        Xiance_card->addSubcards(cards);
        return Xiance_card;
    }
};

class Xiance: public PhaseChangeSkill{
public:
    Xiance():PhaseChangeSkill("xiance"){
        view_as_skill = new XianceViewAsSkill;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return PhaseChangeSkill::triggerable(target)
                && target->getPhase() == Player::NotActive
                && target->hasUsed("XianceCard");
    }

    virtual bool onPhaseChange(ServerPlayer *target) const{
        target->getRoom()->setPlayerMark(target, "xiance", 0);

        return false;
    }
};

BaichuCard::BaichuCard(){
    target_fixed = true;
    will_throw = false;
}

void BaichuCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &) const{
    const QList<int> ji = source->getPile("ji");

    if(subcards.isEmpty()){
        foreach(int card_id, ji){
            room->obtainCard(source, card_id);
        }
    }else{
        foreach(int card_id, subcards){
            source->addToPile("ji", card_id);
        }
    }
}

class BaichuViewAsSkill: public ViewAsSkill{
public:
    BaichuViewAsSkill():ViewAsSkill(""){
        card = new BaichuCard;
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        if(player->getPile("ji").isEmpty())
            return !player->isKongcheng();
        else
            return true;
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        int n = Self->getPile("ji").length();
        if(selected.length() + n >= 3)
            return false;

        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(Self->getPile("ji").isEmpty() && cards.isEmpty())
            return NULL;

        card->clearSubcards();
        card->addSubcards(cards);
        return card;
    }

private:
    BaichuCard *card;
};

class Baichu: public PhaseChangeSkill{
public:
    Baichu():PhaseChangeSkill("baichu"){
        view_as_skill = new BaichuViewAsSkill;
    }
    virtual bool onPhaseChange(ServerPlayer *player) const{
        Room *room = player->getRoom();
        if(player->getPhase() == Player::Finish && player->getPile("ji").length() >= 1 && player->askForSkillInvoke("baichu")){
        if(player->getPile("ji").length() == 3){
            room->playSkillEffect(objectName());
            RecoverStruct recover;
            recover.card = NULL;
            recover.who = player;
            room->recover(player, recover);
            QList<int> jis = player->getPile("ji");
            foreach(int card_id, jis){
            room->throwCard(card_id);
        }
        }
        if(player->getPile("ji").length() == 2){
            room->playSkillEffect(objectName());
            QList<int> jis = player->getPile("ji");

            int card_id;
                room->fillAG(jis, player);
                card_id = jis.first();
                player->invoke("clearAG");

            Snatch *snatch = new Snatch(Card::NoSuit, 0);
            snatch->setSkillName("baichu");
            snatch->addSubcard(card_id);

            QList<ServerPlayer *> targets;
            QList<const Player *> empty_list;
            foreach(ServerPlayer *p, room->getAlivePlayers()){
                if(!snatch->targetFilter(empty_list, p, player))
                    continue;

                if(player->isProhibited(p, snatch))
                    continue;

                targets << p;
            }
            if(targets.isEmpty())
                return false;

            ServerPlayer *target = room->askForPlayerChosen(player, targets, "baichu");

            CardUseStruct use;
            use.card = snatch;
            use.from = player;
            use.to << target;
            room->useCard(use);

            foreach(int card_id, jis){
            room->throwCard(card_id);
        }
        }
        if(player->getPile("ji").length() == 1){
            room->playSkillEffect(objectName());
            QList<int> jis = player->getPile("ji");

            int card_id;
                room->fillAG(jis, player);
                card_id = jis.first();
                player->invoke("clearAG");

            Dismantlement *dismantlement = new Dismantlement(Card::NoSuit, 0);
            dismantlement->setSkillName("baichu");
            dismantlement->addSubcard(card_id);

            QList<ServerPlayer *> targets;
            QList<const Player *> empty_list;
            foreach(ServerPlayer *p, room->getAlivePlayers()){
                if(!dismantlement->targetFilter(empty_list, p, player))
                    continue;

                if(player->isProhibited(p, dismantlement))
                    continue;

                targets << p;
            }
            if(targets.isEmpty())
                return false;

            ServerPlayer *target = room->askForPlayerChosen(player, targets, "baichu");

            CardUseStruct use;
            use.card = dismantlement;
            use.from = player;
            use.to << target;
            room->useCard(use);

            foreach(int card_id, jis){
            room->throwCard(card_id);
        }
        }
    }
        return false;
    }
};

ThunderPackage::ThunderPackage()
    :Package("thunder")
{
    General *maliang = new General(this, "maliang", "shu", 3);
    maliang->addSkill(new Zhongyan);
    maliang->addSkill(new ZhongyanClear);
    maliang->addSkill(new Baimei);

    related_skills.insertMulti("zhongyan", "#zhongyan-clear");

    General *xunyou = new General(this, "xunyou", "wei", 3);
    xunyou->addSkill(new Xiance);
    xunyou->addSkill(new Baichu);

    General *zhangren = new General(this, "zhangren", "qun");
    zhangren->addSkill(new Fuji);
    zhangren->addSkill(new FujiClear);

    related_skills.insertMulti("fuji", "#fuji-clear");

    General *zhonghui = new General(this, "zhonghui", "wei");
    zhonghui->addSkill(new Tongmou);
    zhonghui->addSkill(new Yexin);

    General *mayunlv = new General(this, "mayunlv", "shu", 4, false);
    mayunlv->addSkill(new Jinguo);
    mayunlv->addSkill(new Lianyun);

    General *lvlingqi = new General(this, "lvlingqi", "qun", 4, false);
    lvlingqi->addSkill(new Jichi);
    lvlingqi->addSkill(new Jiangmen);

    General *madai = new General(this, "madai", "shu");
    madai->addSkill(new Zhuiji);
    madai->addSkill(new Shouming);

    General *huaxiong = new General(this, "huaxiong", "qun");
    huaxiong->addSkill(new Xuezhan);

    skills << new Xianhai << new Hunv << new Qishu << new Yuanjun << new YuanjunClear;

    related_skills.insertMulti("yuanjun", "#yuanjun-clear");

    addMetaObject<TongmouCard>();
    addMetaObject<YuanjunCard>();
    addMetaObject<ZhongyanCard>();
    addMetaObject<FujiCard>();
    addMetaObject<XianceCard>();
    addMetaObject<BaichuCard>();
}

ADD_PACKAGE(Thunder);
