#include "shadowpackage.h"
#include "standard.h"
#include "skill.h"
#include "wind.h"
#include "client.h"
#include "carditem.h"
#include "engine.h"

class Huwei: public TriggerSkill{
public:
    Huwei():TriggerSkill("huwei"){
        events <<  Predamaged;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        if(damage.card == NULL || !damage.card->inherits("Slash") || damage.to->isDead())
            return false;

        Room *room = player->getRoom();
        ServerPlayer *caohong = room->findPlayerBySkillName(objectName());
        if(caohong && damage.to != caohong && caohong->askForSkillInvoke(objectName(), data)){
            QString choice = room->askForChoice(caohong, objectName(), "qi+jian+nothing");
            if(choice == "qi" && caohong->getEquips().length() > 0){
                room->playSkillEffect("huwei",1);
            int card_id = room->askForCardChosen(caohong, caohong , "e", "huwei");
            const Card *card = Sanguosha->getCard(card_id);
            room->throwCard(card);

            if(damage.damage > 0){
                LogMessage log;
                log.type = "#Huwei";
                log.from = player;
                log.arg = QString::number(damage.damage);
                log.arg2 = QString::number(damage.damage - 1);
                player->getRoom()->sendLog(log);

                damage.damage --;
                data = QVariant::fromValue(damage);
            }
        }
            if(choice == "jian"){
                room->playSkillEffect("huwei",2);
                room->loseHp(caohong);

                if(damage.damage > 0){
                    LogMessage log;
                    log.type = "#Huwei";
                    log.from = player;
                    log.arg = QString::number(damage.damage);
                    log.arg2 = QString::number(damage.damage - 1);
                    player->getRoom()->sendLog(log);

                    damage.damage --;
                    data = QVariant::fromValue(damage);
                }
            }
        }
            return false;
        }
    };

YuanliangCard::YuanliangCard()
{
    setObjectName("yuanliang");
    once = true;
    mute =true;
    target_fixed = true;
}

void YuanliangCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const
{
    room->playSkillEffect(objectName());
    room->askForDiscard(source, "yuanliang", 1);

    QList<ServerPlayer*> players;

    int min = 100;
    foreach(ServerPlayer *sp,room->getAlivePlayers())if(sp->getHandcardNum() < min)
        min = sp->getHandcardNum();

    foreach(ServerPlayer *sp,room->getAlivePlayers())if(sp->getHandcardNum()== min)
        players << sp;

    ServerPlayer* target = room->askForPlayerChosen(source,players,"yuanliang");
    room->drawCards(target,2);
}

class Yuanliang : public ZeroCardViewAsSkill
{
public:
    Yuanliang():ZeroCardViewAsSkill("yuanliang")
    {

    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        if(player->hasUsed("YuanliangCard")){
            return false;
        }else

        if(player->isKongcheng()){
                return false;

        }else

        return true;
    }

    virtual const Card * viewAs() const
    {
        return new YuanliangCard;
    }
};

class Diezhi: public TriggerSkill{
public:
    Diezhi():TriggerSkill("diezhi"){
        events << PhaseChange;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return !target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();

        if(player->getPhase() != Player::Finish)
            return false;

        if(player->isKongcheng())
            return false;

        ServerPlayer *kanze = room->findPlayerBySkillName(objectName());
        if(kanze && !kanze->isKongcheng() && kanze->askForSkillInvoke(objectName(), data)){

        const Card *card = room->askForCardShow(player, kanze, objectName());
        room->showCard(player, card->getEffectiveId());

        QString suit = card->getSuitString();

        const Card *cardr = room->askForCardShow(kanze, player, objectName());

        if(cardr->getSuitString() != suit){
            room->throwCard(cardr);
            player->drawCards(1);
            kanze->drawCards(1);

          }else{
                DamageStruct damage;
                damage.card = NULL;
                damage.from = player;
                damage.to = kanze;

                room->damage(damage);
                kanze->obtainCard(card);
            }
        }

        return false;
    }
};

class Jianru: public TriggerSkill{
public:
    Jianru():TriggerSkill("jianru"){
        events << PhaseChange;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *kanze, QVariant &data) const{
        Room *room = kanze->getRoom();
        if(kanze->getPhase() == Player::Discard){
            int n1 = kanze->getHandcardNum();
            int n2 = kanze->getHp();

            int n = qAbs(n1 - n2);
            QList<int> jianru_cards = kanze->handCards().mid(0, n);
            if(n1 > n2){
              while(room->askForYiji(kanze, jianru_cards));
            }
        }
        return false;
        }
    };

class Xiandeng: public PhaseChangeSkill{
public:
    Xiandeng():PhaseChangeSkill("xiandeng"){

    }
    virtual bool onPhaseChange(ServerPlayer *yuejin) const{
        Room *room = yuejin->getRoom();

        QList<ServerPlayer *> targets;
        foreach(ServerPlayer *p, room->getAlivePlayers())
            if(p->hasEquip() || !p->getJudgingArea().isEmpty())
                targets << p;

        if(targets.length() < 1)
           return false;

        if(yuejin->getPhase() == Player::Start){
            if(room->askForSkillInvoke(yuejin, objectName())){
                yuejin->skip(Player::Judge);
                yuejin->skip(Player::Draw);

                ServerPlayer *from = room->askForPlayerChosen(yuejin, targets, objectName());{

                int card_id = room->askForCardChosen(yuejin, from , "je", "xiandeng");
                const Card *card = Sanguosha->getCard(card_id);
                Player::Place place = room->getCardPlace(card_id);

                int equip_index = -1;
                const DelayedTrick *trick = NULL;
                if(place == Player::Equip){
                    const EquipCard *equip = qobject_cast<const EquipCard *>(card);
                    equip_index = static_cast<int>(equip->location());
                }else{
                    trick = DelayedTrick::CastFrom(card);
                }

                QList<ServerPlayer *> tos;
                foreach(ServerPlayer *p, room->getAlivePlayers()){
                    if(equip_index != -1){
                        if(p->getEquip(equip_index) == NULL)
                            tos << p;
                    }else{
                        if(!yuejin->isProhibited(p, trick) && !p->containsTrick(trick->objectName()))
                            tos << p;
                    }
                }

                if(trick && trick->isVirtualCard())
                    delete trick;

                room->setTag("XiandengTarget", QVariant::fromValue(from));
                ServerPlayer *to = room->askForPlayerChosen(yuejin, tos, "xiandeng");
                if(to)
                    room->moveCardTo(card, to, place);
                room->removeTag("XiandengTarget");
            }
            }
        }

        return false;
    }
};

class Xiaoguo: public TriggerSkill{
public:
    Xiaoguo():TriggerSkill("xiaoguo"){
        events << Predamage;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        ServerPlayer *yuejin = damage.from;
        if(damage.card && damage.card->inherits("Slash") &&
            damage.to->getJudgingArea().length() > 0)
        {
            Room *room = damage.to->getRoom();

            LogMessage log;
            log.type = "#XiaoguoEffect";
            log.from = yuejin;
            log.to << damage.to;
            log.arg = QString::number(damage.damage);
            log.arg2 = QString::number(damage.damage + 1);
            room->sendLog(log);

            damage.damage ++;
            data = QVariant::fromValue(damage);
        }

        return false;
    }
};

class Chizhong:public PhaseChangeSkill{
public:
    Chizhong():PhaseChangeSkill("chizhong"){

    }

    virtual bool onPhaseChange(ServerPlayer *chengpu) const{
        Room *room = chengpu->getRoom();
        int n = chengpu->getCards("h").length();

        if(chengpu->getPhase() == Player::Start && n > 0 &&
           chengpu->askForSkillInvoke(objectName()))
        {
            room->playSkillEffect(objectName());

            if(room->askForDiscard(chengpu, "chizhong", n)){
            chengpu->drawCards(n + 1);
        }
        }

        return false;
    }
};

class Yinxian: public TriggerSkill{
public:
    Yinxian():TriggerSkill("yinxian"){
        events << CardEffected;
    }
    virtual bool triggerable(const ServerPlayer *target) const{

        return true;
    }
    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{

        Room *room = player->getRoom();

        ServerPlayer *sunluban = room->findPlayerBySkillName(objectName());

            if(!sunluban) return false;

            if(event == CardEffected){

            CardEffectStruct effect = data.value<CardEffectStruct>();

            if(!effect.card->inherits("DelayedTrick"))

                return false;

            room->doGuanxing(sunluban, room->getNCards(1, false), false);
        }
        return false;
    }
};

ZenhuiCard::ZenhuiCard(){
    once = true;
    mute = true;
    will_throw = false;
}

void ZenhuiCard::onEffect(const CardEffectStruct &effect) const{
    effect.to->obtainCard(this);

    Room *room = effect.to->getRoom();
    const Card *slash = room->askForCard(effect.to, ".slash", "@zenhui-answer");
    if(slash){
        room->setEmotion(effect.to, "killer");
        LogMessage log;
        log.type = "#ThrowSlash";
        log.from = effect.to;
        log.arg = "slash";
        room->sendLog(log);
    }
    if(!slash){
        DamageStruct damage;
        damage.from = effect.from;
        damage.to = effect.to;
        damage.damage = 1;

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
}

class Zenhui: public OneCardViewAsSkill{
public:
    Zenhui():OneCardViewAsSkill("zenhui"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("ZenhuiCard") && !player->isKongcheng();
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        ZenhuiCard *card = new ZenhuiCard;
        card->addSubcard(card_item->getFilteredCard());

        return card;
    }
};

FuhuoCard::FuhuoCard(){
    target_fixed = true;
    will_throw = false;
}

void FuhuoCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &) const{
    const QList<int> xian = source->getPile("xianjing");

    if(subcards.isEmpty()){
        foreach(int card_id, xian){
            room->obtainCard(source, card_id);
        }
    }else{
        foreach(int card_id, subcards){
            source->addToPile("xianjing", card_id);
        }
    }
}

class FuhuoViewAsSkill: public ViewAsSkill{
public:
    FuhuoViewAsSkill():ViewAsSkill(""){
        card = new FuhuoCard;
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        if(player->getPile("xianjing").isEmpty())
            return !player->isKongcheng();
        else
            return true;
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        int n = Self->getPile("xianjing").length();
        int x = Self->getLostHp() + 1;
        if(selected.length() + n >= x)
            return false;

        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(Self->getPile("xianjing").isEmpty() && cards.isEmpty())
            return NULL;

        card->clearSubcards();
        card->addSubcards(cards);
        return card;
    }

private:
    FuhuoCard *card;
};

class Fuhuo: public TriggerSkill{
public:
    Fuhuo():TriggerSkill("fuhuo"){
   view_as_skill = new FuhuoViewAsSkill;
        events << CardFinished;
    }

    void throw_xian_card(Room *room, ServerPlayer *huaman, QList<int> &xians) const{

        room->fillAG(xians);
        for(int i = 0; i < 1; i++){
            int card_id = room->askForAG(huaman, xians, false, objectName());
            room->takeAG(NULL, card_id);
            xians.removeOne(card_id);
        }

        huaman->clearPrivatePiles();
        foreach(int id, xians)
            huaman->addToPile("xianjing", id);

        room->broadcastInvoke("clearAG");
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return !target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        CardUseStruct use = data.value<CardUseStruct>();
        if(use.card->getTypeId() == Card::Basic || use.card->isNDTrick()){
            Room *room = player->getRoom();
            if(room->getCardPlace(use.card->getEffectiveId()) == Player::DiscardedPile){
                ServerPlayer *huaman = room->findPlayerBySkillName(objectName());
                if(!huaman) return false;
                QList<int> xians = huaman->getPile("xianjing");

                if(xians.isEmpty())
                    return false;

                    if(room->askForSkillInvoke(huaman, objectName())){
                        throw_xian_card(room, huaman, xians);
                        huaman->obtainCard(use.card);
                        room->playSkillEffect(objectName());
                }
            }
        }

        return false;
    }
    };

class FuhuoEnd:public PhaseChangeSkill{
public:
    FuhuoEnd():PhaseChangeSkill("#fuhuo-end"){
        frequency = Compulsory;
    }

    virtual bool onPhaseChange(ServerPlayer *huaman) const{
        QList<int> xians = huaman->getPile("xianjing");
        if(huaman->getPhase() == Player::Start && !xians.isEmpty()){
            Room *room = huaman->getRoom();

            int card_id;
                room->fillAG(xians, huaman);
                card_id = xians.first();
                huaman->invoke("clearAG");

                foreach(int card_id, xians){
                room->throwCard(card_id);
            }
        }

        return false;
    }
};

class Manxue: public TriggerSkill{
public:
    Manxue():TriggerSkill("manxue"){
        events << CardEffected;
        frequency = Compulsory;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        CardEffectStruct effect = data.value<CardEffectStruct>();
        if(effect.card->inherits("SavageAssault")){
            LogMessage log;
            log.type = "#SkillNullify";
            log.from = player;
            log.arg = "manxue";
            log.arg2 = "savage_assault";
            player->getRoom()->sendLog(log);

            return true;
        }else
            return false;
    }
    };

class Conglang:public TriggerSkill{
public:
    Conglang():TriggerSkill("conglang"){
        frequency = Frequent;
        events << CardUsed << CardResponsed;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *xinxianying, QVariant &data) const{
        CardStar card = NULL;
        if(event == CardUsed){
            CardUseStruct use = data.value<CardUseStruct>();
            card = use.card;
        }else if(event == CardResponsed)
            card = data.value<CardStar>();

        if(card->isNDTrick()){
            Room *room = xinxianying->getRoom();
            if(xinxianying->getPile("zhi").length() < 10 && room->askForSkillInvoke(xinxianying, objectName())){
                room->playSkillEffect(objectName());
                QList<int> card_ids = room->getNCards(1);
                foreach(int card_id, card_ids){
                xinxianying->obtainCard(Sanguosha->getCard(card_id));
                xinxianying->addToPile("zhi", card_id, false);
            }
            }
        }

        return false;
    }
};

class Zhinang: public OneCardViewAsSkill{
public:
    Zhinang():OneCardViewAsSkill("zhinang"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        int card_id = player->getMark("zhinang_mark");
        if(player->getPile("zhi").length() >= 3 && card_id > 0){
            const Card *card = Sanguosha->getCard(card_id);
            return card->isAvailable(player);
        }else
            return false;
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return to_select->getFilteredCard();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        int card_id = Self->getMark("zhinang_mark");
        if(card_id == 0)
            return NULL;

        const Card *card = Sanguosha->getCard(card_id);
        const Card *orign = card_item->getFilteredCard();

        Card *new_card = Sanguosha->cloneCard(card->objectName(), orign->getSuit(), orign->getNumber());
        new_card->addSubcard(card_item->getCard());
        new_card->setSkillName(objectName());
        return new_card;
    }
};

class ZhinangMark: public TriggerSkill{
public:
    ZhinangMark():TriggerSkill("#zhinang_mark"){
        events << CardUsed << PhaseChange;
    }

    void throw_zhi_card(Room *room, ServerPlayer *xinxianying, QList<int> &zhis) const{

        room->fillAG(zhis);
        for(int i = 0; i < 3; i++){
            int card_id = room->askForAG(xinxianying, zhis, false, objectName());
            room->takeAG(NULL, card_id);
            zhis.removeOne(card_id);
        }

        xinxianying->clearPrivatePiles();
        foreach(int id, zhis)
            xinxianying->addToPile("zhi", id);

        room->broadcastInvoke("clearAG");
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *xinxianying, QVariant &data) const{
        Room *room = xinxianying->getRoom();
       QList<int> zhis = xinxianying->getPile("zhi");
        if(event == CardUsed){
            CardUseStruct use = data.value<CardUseStruct>();
            if(use.card){
                if(!use.card->isVirtualCard() && (use.card->getTypeId() == Card::Basic || use.card->isNDTrick())
                   && xinxianying->getPile("zhi").length() >= 3 && room->askForSkillInvoke(xinxianying, objectName(), data)){
                    room->setPlayerMark(xinxianying,"zhinang_mark",use.card->getId());
                }
                if(use.card->getSkillName() == "zhinang"){
                    throw_zhi_card(room, xinxianying, zhis);
                    room->setPlayerMark(xinxianying,"zhinang_mark",0);

                }
            }
        }else if(event == PhaseChange && xinxianying->getPhase() == Player::Finish){
            room->setPlayerMark(xinxianying,"zhinang_mark",0);
        }
        return false ;
    }
};

class Caijian: public TriggerSkill{
public:
    Caijian():TriggerSkill("caijian"){
        events << CardAsked;
    }
    void throw_zhi_card(Room *room, ServerPlayer *xinxianying, QList<int> &zhis) const{

        room->fillAG(zhis);
        for(int i = 0; i < 1; i++){
            int card_id = room->askForAG(xinxianying, zhis, false, objectName());
            room->takeAG(NULL, card_id);
            zhis.removeOne(card_id);
        }

        xinxianying->clearPrivatePiles();
        foreach(int id, zhis)
            xinxianying->addToPile("zhi", id);

        room->broadcastInvoke("clearAG");
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return TriggerSkill::triggerable(target);
    }

    virtual bool trigger(TriggerEvent, ServerPlayer *xinxianying, QVariant &data) const{
        QString pattern = data.toString();
        QList<int> zhis = xinxianying->getPile("zhi");
        Room *room = xinxianying->getRoom();

        if(zhis.isEmpty())
            return false;

        if(pattern == "jink"){
        if(xinxianying->askForSkillInvoke(objectName())){
            throw_zhi_card(room, xinxianying, zhis);
            JudgeStruct judge;
            judge.pattern = QRegExp("(.*):(heart|diamond):(.*)");
            judge.good = true;
            judge.reason = objectName();
            judge.who = xinxianying;

            room->judge(judge);

            if(judge.isGood()){
                Jink *jink = new Jink(Card::NoSuit, 0);
                jink->setSkillName(objectName());
                room->provide(jink);
                room->setEmotion(xinxianying, "good");
                return true;
            }else
                room->setEmotion(xinxianying, "bad");
        }
    }
          if(pattern == "slash"){
              if(xinxianying->askForSkillInvoke(objectName())){
                 throw_zhi_card(room, xinxianying, zhis);
                 JudgeStruct judge;
                 judge.pattern = QRegExp("(.*):(club|spade):(.*)");
                 judge.good = true;
                 judge.reason = objectName();
                 judge.who = xinxianying;

                 room->judge(judge);
                 if(judge.isGood()){
                     Slash *slash = new Slash(Card::NoSuit, 0);
                     slash->setSkillName(objectName());
                     room->provide(slash);
                     room->setEmotion(xinxianying, "good");

                     return true;
                 }else
                     room->setEmotion(xinxianying, "bad");
             }
              }
        return false;
    }
};

ShadowPackage::ShadowPackage()
    :Package("shadow")
{
    General *caohong = new General(this, "caohong", "wei");
    caohong->addSkill(new Huwei);

    General *lidian = new General(this, "lidian", "wei");
    lidian->addSkill(new Yuanliang);

    General *kanze = new General(this, "kanze", "wu", 3);
    kanze->addSkill(new Diezhi);
    kanze->addSkill(new Jianru);

    General *yuejin = new General(this, "yuejin", "wei");
    yuejin->addSkill(new Xiandeng);
    yuejin->addSkill(new Xiaoguo);

    General *chengpu = new General(this, "chengpu", "wu");
    chengpu->addSkill(new Chizhong);

    General *sunluban = new General(this, "sunluban", "wu", 3, false);
    sunluban->addSkill(new Yinxian);
    sunluban->addSkill(new Zenhui);

    General *xinxianying = new General(this, "xinxianying", "wei", 3, false);
    xinxianying->addSkill(new Conglang);
    xinxianying->addSkill(new Zhinang);
    xinxianying->addSkill(new ZhinangMark);
    xinxianying->addSkill(new Caijian);

    related_skills.insertMulti("zhinang", "#zhinang_mark");

    General *huaman = new General(this, "huaman", "shu", 4, false);
    huaman->addSkill(new Fuhuo);
    huaman->addSkill(new FuhuoEnd);
    huaman->addSkill(new Manxue);

    related_skills.insertMulti("fuhuo", "#fuhuo-end");

    addMetaObject<YuanliangCard>();
    addMetaObject<ZenhuiCard>();
    addMetaObject<FuhuoCard>();
}

ADD_PACKAGE(Shadow);
