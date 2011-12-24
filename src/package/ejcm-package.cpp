#include "ejcm-package.h"
#include "standard.h"
#include "skill.h"
#include "wind.h"
#include "client.h"
#include "carditem.h"
#include "engine.h"

class Xianming: public PhaseChangeSkill{
public:
    Xianming():PhaseChangeSkill("xianming"){

    }
    virtual bool onPhaseChange(ServerPlayer *player) const{
        if(player->getPhase() == Player::Draw)
            player->tag["card_num"] = player->getHandcardNum();
        else if(player->getPhase() == Player::Play){
            Room *room = player->getRoom();
            int num = player->getHandcardNum() - player->tag.value("card_num").toInt();
            if(num > 0 && player->askForSkillInvoke(objectName())){
                QList<int> cards = player->handCards().mid(player->tag.value("card_num").toInt());
                for(int i = cards.length(); i >0; i--)
                    room->throwCard(cards.at(i-1));
                player->drawCards(num);
            }
        }
        return false;
    }
};

class XiaosiViewAsSkill: public OneCardViewAsSkill{
public:
    XiaosiViewAsSkill():OneCardViewAsSkill("xiaosi"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("XiaosiCard");
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        XiaosiCard *xiaosi_card = new XiaosiCard;
        xiaosi_card->addSubcard(card_item->getCard()->getId());

        return xiaosi_card;
    }
};

XiaosiCard::XiaosiCard(){
    once = true;
}

bool XiaosiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(to_select->getMark("@xiaosi") > 0 || to_select->getMark("xiaosiA") > 0)
        return false;
    return targets.isEmpty() && to_select->getGeneral()->isMale();
}

void XiaosiCard::onEffect(const CardEffectStruct &effect) const{
    Room *room = effect.from->getRoom();
    room->setEmotion(effect.from, "xiaosi");
    QString result = room->askForChoice(effect.to, "xiaosi", "a+b");
    LogMessage log;
    log.from = effect.to;
    log.to << effect.from;
    if(result == "a"){
        log.type = "#XiaosiA";
        room->sendLog(log);
        RecoverStruct recover;
        recover.who = effect.from;
        room->recover(effect.to, recover);
        effect.to->setMark("xiaosiA", 1);
    }
    else{
        log.type = "#XiaosiB";
        room->sendLog(log);
        effect.to->drawCards(2);
        effect.to->gainMark("@xiaosi");
        effect.from->gainMark("@xiaosi");
    }
}

class Xiaosi: public TriggerSkill{
public:
    Xiaosi():TriggerSkill("xiaosi"){
        events << Predamaged << PhaseChange << DrawNCards;
        view_as_skill = new XiaosiViewAsSkill;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill("xiaosi") || target->getMark("@xiaosi") > 0;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        if(event == Predamaged && player->hasSkill("xiaosi")){
            DamageStruct damage = data.value<DamageStruct>();
            if(damage.to != player)
                return false;
            foreach(ServerPlayer *tmp, room->getOtherPlayers(player)){
                if(tmp->getMark("xiaosiA") > 0){
                    damage.to = tmp;
                    tmp->setMark("xiaosiA", 0);
                    //data = QVariant::fromValue();
                    LogMessage log;
                    log.type = "#XiaosiAdamage";
                    log.from = tmp;
                    log.to << player;
                    room->sendLog(log);

                    DamageStruct damage2 = damage;
                    room->damage(damage2);
                    return true;
                }
            }
        }
        else if(event == PhaseChange){
            if(player->getPhase() == Player::Draw && !player->hasSkill("xiaosi") && player->getMark("@xiaosi") > 0){
                player->loseMark("@xiaosi");
                return true;
            }
            else if(player->getPhase() == Player::Start && player->hasSkill("xiaosi")){
                foreach(ServerPlayer *tmp, room->getOtherPlayers(player)){
                    if(tmp->getMark("xiaosiA") > 0)
                        tmp->setMark("xiaosiA", 0);
                    if(tmp->getMark("@xiaosi") > 0)
                        tmp->loseMark("@xiaosi");
                }
            }
        }
        else if(event == DrawNCards){
            if(player->hasSkill("xiaosi") && player->getMark("@xiaosi") > 0){
                LogMessage log;
                log.type = "#XiaosiBdraw";
                log.arg = objectName();
                log.from = player;
                room->sendLog(log);

                player->loseMark("@xiaosi");
                data = data.toInt() + 1;
            }
        }
        return false;
    }
};

DaojiCard::DaojiCard(){
    once = true;
}

bool DaojiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.isEmpty() && to_select->getWeapon() != NULL;
}

void DaojiCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    room->throwCard(this);

    ServerPlayer *target = targets.value(0, source);

    CardEffectStruct effect;
    effect.card = this;
    effect.from = source;
    effect.to = target;

    room->cardEffect(effect);
}

void DaojiCard::onEffect(const CardEffectStruct &effect) const{
    Room *room = effect.from->getRoom();
    room->setEmotion(effect.from, "daoji");

    int card_id = effect.to->getWeapon()->getId();
    const Card *card = Sanguosha->getCard(card_id);
    bool is_public = room->getCardPlace(card_id) != Player::Hand;
    room->moveCardTo(card, effect.from, Player::Hand, is_public ? true : false);

    QList<ServerPlayer *> targets = room->getOtherPlayers(effect.to);
    ServerPlayer *target = room->askForPlayerChosen(effect.from, targets, "daoji");
    if(target != effect.from)
        room->moveCardTo(card, target, Player::Hand, false);
}

class Daoji: public OneCardViewAsSkill{
public:
    Daoji():OneCardViewAsSkill("daoji"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("DaojiCard");
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return to_select->getCard()->getSuit() == Card::Club && !to_select->isEquipped();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        DaojiCard *card = new DaojiCard;
        card->addSubcard(card_item->getFilteredCard());
        return card;
    }
};

JingjiuCard::JingjiuCard(){
}

bool JingjiuCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.isEmpty() && to_select != Self && !to_select->hasFlag("drank");
}

void JingjiuCard::onEffect(const CardEffectStruct &effect) const{
    Room *room = effect.to->getRoom();
    room->setEmotion(effect.from, "jingjiu");

    QString who = effect.to->objectName();
    QString animation_str = QString("analeptic:%1:%2").arg(who).arg(who);
    room->broadcastInvoke("animate", animation_str);

        LogMessage log;
        log.type = "#Drank";
        log.from = effect.to;
        room->sendLog(log);

        room->setPlayerFlag(effect.to, "drank");
}

class Jingjiu: public OneCardViewAsSkill{
public:
    Jingjiu():OneCardViewAsSkill("jingjiu"){

    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return to_select->getCard()->inherits("Analeptic");
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        JingjiuCard *card = new JingjiuCard;
        card->addSubcard(card_item->getCard()->getId());

        return card;
    }
};

class Juhun:public PhaseChangeSkill{
public:
    Juhun():PhaseChangeSkill("juhun"){
    }

    virtual bool onPhaseChange(ServerPlayer *xiahounv) const{
        Room *room = xiahounv->getRoom();
        int n = xiahounv->getHp();
        int m = xiahounv->getLostHp();

        if(n <= 3 && m >0 && xiahounv->getPhase() == Player::Finish && xiahounv->askForSkillInvoke(objectName())){
            room->playSkillEffect(objectName());
            room->setEmotion(xiahounv, "juhun");
            xiahounv->drawCards(m);
        }

        return false;
    }
};

class JuhunMid:public TriggerSkill{
public:
    JuhunMid():TriggerSkill("#juhun1"){
        frequency = Frequent;
        events << CardUsed << CardResponsed;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *xiahounv, QVariant &data) const{
        CardStar card = NULL;
        int n = xiahounv->getHp();
        int m = xiahounv->getLostHp();

        if(event == CardUsed){
            CardUseStruct use = data.value<CardUseStruct>();
            card = use.card;
        }else if(event == CardResponsed)
            card = data.value<CardStar>();

        if(n <= 2 && card->getSuit() == Card::Spade){
            Room *room = xiahounv->getRoom();
            if(room->askForSkillInvoke(xiahounv, "juhun")){
                room->playSkillEffect("juhun");
                room->setEmotion(xiahounv, "juhun");
                xiahounv->drawCards(m);
            }
        }

        return false;
    }
};

class JuhunEnd: public ProhibitSkill{
public:
    JuhunEnd():ProhibitSkill("#juhun2"){

    }

    virtual bool isProhibited(const Player *from, const Player *to, const Card *card) const{
        if(to->getHp() <= 1 && from->getGeneral()->isMale()){
        return card->isRed();
    }
       return false;
    }
};

class Chengshi: public TriggerSkill{
public:
    Chengshi():TriggerSkill("chengshi"){
        events << PhaseChange << FinishJudge;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *baosanniang, QVariant &data) const{
        Room *room = baosanniang->getRoom();

        if(event == PhaseChange){
            if(baosanniang->getPhase() == Player::Start && baosanniang->askForSkillInvoke(objectName())){
                if(baosanniang->getMark("chengshimark") == 1){
                    room->detachSkillFromPlayer(baosanniang, "jizhi");
                    baosanniang->loseSkill("jizhi");
                }else
                    if(baosanniang->getMark("chengshimark") == 2){
                        room->detachSkillFromPlayer(baosanniang, "wusheng");
                        baosanniang->loseSkill("wusheng");
                    }else
                        if(baosanniang->getMark("chengshimark") == 3){
                            room->detachSkillFromPlayer(baosanniang, "xiaoji");
                            baosanniang->loseSkill("xiaoji");
                        }

                room->setPlayerMark(baosanniang, "chengshimark", 0);

                    baosanniang->setFlags("chengshi");

                    JudgeStruct judge;
                    judge.pattern = QRegExp("(.*)");
                    judge.good = true;
                    judge.reason = objectName();
                    judge.who = baosanniang;

                    room->judge(judge);

                    if(judge.card->inherits("TrickCard")){
                        room->setPlayerMark(baosanniang, "chengshimark", 1);
                        room->acquireSkill(baosanniang, "jizhi");
                    }else
                    if(judge.card->inherits("BasicCard")){
                        room->setPlayerMark(baosanniang, "chengshimark", 2);
                        room->acquireSkill(baosanniang, "wusheng");
                    }else{
                        room->setPlayerMark(baosanniang, "chengshimark", 3);
                        room->acquireSkill(baosanniang, "xiaoji");
                    }
                    baosanniang->setFlags("-chengshi");

                    return true;
                }

        }else if(event == FinishJudge){
            JudgeStar judge = data.value<JudgeStar>();
            if(judge->reason == "chengshi"){
                baosanniang->obtainCard(judge->card);
                return true;
            }
        }

        return false;
    }
};

ZhenshouCard::ZhenshouCard(){
    target_fixed = true;
    will_throw = false;
}

void ZhenshouCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &) const{
    const QList<int> shou = source->getPile("shou");

    if(subcards.isEmpty()){
        foreach(int card_id, shou){
            room->obtainCard(source, card_id);
        }
    }else{
        foreach(int card_id, subcards){
            source->addToPile("shou", card_id);
        }
    }
}

class ZhenshouViewAsSkill: public ViewAsSkill{
public:
    ZhenshouViewAsSkill():ViewAsSkill(""){
        card = new ZhenshouCard;
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        if(player->getPile("shou").isEmpty())
            return !player->isKongcheng();
        else
            return true;
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        int n = Self->getPile("shou").length();
        if(selected.length() + n >= 1)
            return false;

        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(Self->getPile("shou").isEmpty() && cards.isEmpty())
            return NULL;

        card->clearSubcards();
        card->addSubcards(cards);
        return card;
    }

private:
    ZhenshouCard *card;
};

class Zhenshou: public TriggerSkill{
public:
    Zhenshou():TriggerSkill("zhenshou"){
  view_as_skill = new ZhenshouViewAsSkill;
        events << CardEffect << CardEffected;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        QList<int> shous = target->getPile("shou");
        return TriggerSkill::triggerable(target) && !shous.isEmpty();
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        CardEffectStruct effect = data.value<CardEffectStruct>();
        Room *room = player->getRoom();

        QList<int> shous = player->getPile("shou");
        int card_id;
            card_id = shous.first();

            const Card *card = Sanguosha->getCard(card_id);
            QString suit = card->getSuitString();

        if(effect.from !=player && effect.card->getSuitString() == suit && !effect.card->inherits("DelayedTrick")){
            room->playSkillEffect(objectName());
            room->setEmotion(player, "zhenshou");

            LogMessage log;
            log.type = "#Zhenshou";
            log.from = player;
            log.to << effect.from;
            log.arg = objectName();
            log.arg2 = effect.card->objectName();

            room->sendLog(log);

            return true;
        }

        return false;
    }
};

QisheCard::QisheCard(){
    once = true;
}

bool QisheCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.isEmpty() && !to_select->isKongcheng() && to_select != Self && Self->inMyAttackRange(to_select);
}

void QisheCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    ServerPlayer *target = source, *player = targets.first();
    room->setEmotion(source, "qishe");

    const Card *card = room->askForCardShow(target, player, objectName());
    room->showCard(target, card->getEffectiveId());
    room->throwCard(card);

    LogMessage log;
    log.type = "$Qishe";
    log.from = target;
    room->sendLog(log);

    QString suit = card->getSuitString();

    int card_id = room->askForCardChosen(target, player, "h", "qishe");
    const Card *cardr = Sanguosha->getCard(card_id);

    if(cardr->getSuitString() == suit){

        LogMessage log;
        log.type = "#Qishe";
        log.from = target;
        log.to << player;
        room->sendLog(log);

        DamageStruct damage;
        damage.card = NULL;
        damage.from = target;
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
            room->damage(damage);

            LogMessage log;
            log.type = "$Dismantlement";
            log.from = player;
            log.card_str = QString::number(card_id);
            room->sendLog(log);

            room->throwCard(card_id);
    }
    }else{
        LogMessage log;
        log.type = "$Dismantlement";
        log.from = player;
        log.card_str = QString::number(card_id);
        room->sendLog(log);

        room->throwCard(card_id);
    }
}

class Qishe: public ZeroCardViewAsSkill{
public:
    Qishe():ZeroCardViewAsSkill("qishe"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return !player->hasUsed("QisheCard") && !player->isKongcheng();
    }

    virtual const Card *viewAs() const{
        Card *card = new QisheCard;
        card->setSkillName(objectName());
        return card;
    }

};

EJCMPackage::EJCMPackage()
    :Package("EJCM")
{
    General *wangyuanji = new General(this, "wangyuanji", "wei", 3, false);
    wangyuanji->addSkill(new Xianming);
    wangyuanji->addSkill(new Xiaosi);

    General *xiahounv = new General(this, "xiahounv", "wei", 3, false);
    xiahounv->addSkill(new Skill("baojie", Skill::Compulsory));
    xiahounv->addSkill(new Juhun);
    xiahounv->addSkill(new JuhunMid);
    xiahounv->addSkill(new JuhunEnd);

    related_skills.insertMulti("juhun", "#juhun1");
    related_skills.insertMulti("junhun", "#juhun2");

    General *baosanniang = new General(this, "baosanniang", "shu", 3, false);
    baosanniang->addSkill(new Chengshi);
    baosanniang->addSkill(new Zhenshou);

    General *handang = new General(this, "handang", "wu", 4);
    handang->addSkill(new Qishe);

    General *hucheer = new General(this, "hucheer", "qun", 4);
    hucheer->addSkill(new Daoji);
    hucheer->addSkill(new Jingjiu);

    addMetaObject<XiaosiCard>();
    addMetaObject<ZhenshouCard>();
    addMetaObject<QisheCard>();
    addMetaObject<DaojiCard>();
    addMetaObject<JingjiuCard>();

}

ADD_PACKAGE(EJCM)
