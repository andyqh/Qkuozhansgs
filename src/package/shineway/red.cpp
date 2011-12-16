#include "red.h"
#include "skill.h"
#include "client.h"
#include "engine.h"
#include "carditem.h"
#include "room.h"

class TongluViewAsSkill: public ZeroCardViewAsSkill{
public:
    TongluViewAsSkill():ZeroCardViewAsSkill("tonglu"){}
    virtual const Card *viewAs() const{
        return new TongluCard;
    }
};

class Tonglu: public TriggerSkill{
public:
    Tonglu():TriggerSkill("tonglu"){
        events << CardFinished << Predamage;
        view_as_skill = new TongluViewAsSkill;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(event == CardFinished){
            CardUseStruct card_use = data.value<CardUseStruct>();
            if(!card_use.card->inherits("Slash"))
                return false;
            player->loseAllMarks("@wocao");
            return false;
        }
        DamageStruct damage = data.value<DamageStruct>();
        int x = player->getMark("@wocao");
        if(damage.card && damage.card->inherits("Slash") && x > 0){
            damage.damage += x;
            player->loseAllMarks("@wocao");
            data = QVariant::fromValue(damage);

            LogMessage log;
            log.type = "#TongluBuff";
            log.from = player;
            log.arg = QString::number(x);
            log.arg2 = QString::number(damage.damage);
            player->getRoom()->sendLog(log);
        }

        return false;
    }
};

TongluCard::TongluCard(){
    target_fixed = true;
}

void TongluCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &) const{
    QList<ServerPlayer *> players;
    foreach(ServerPlayer *tmp, room->getOtherPlayers(source)){
        if(tmp->faceUp())
            players << tmp;
    }
    if(players.isEmpty())
        return;
    source->setMark("@wocao", 0);
    foreach(ServerPlayer *tmp, players){
        QString result = room->askForChoice(tmp, "tonglu", "agree+deny");
        if(result != "deny"){
            tmp->turnOver();
            source->gainMark("@wocao", 1);
        }
    }
}

class Liehou: public TriggerSkill{
public:
    Liehou():TriggerSkill("liehou"){
        events << CardDiscarded << PhaseChange;
        default_choice = "draw";
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        QList<ServerPlayer *> sbmen;
        foreach(ServerPlayer *tmp, room->getAllPlayers()){
            if(!tmp->faceUp())
                sbmen << tmp;
        }
        if(event == PhaseChange){
            if(player->getPhase() == Player::Finish && !player->hasFlag("liehou_on") && !sbmen.isEmpty()){
                QString result = room->askForChoice(player, objectName(), "draw+cancel");
                if(result == "cancel")
                    return false;
                LogMessage log;
                log.type = "#InvokeSkill";
                log.arg = objectName();
                log.from = player;
                room->sendLog(log);
                ServerPlayer *target = room->askForPlayerChosen(player, sbmen, "liehou");
                target->drawCards(1);
            }
            return false;
        }
        if(player->getPhase() == Player::Discard && !sbmen.isEmpty()){

            CardStar card = data.value<CardStar>();
            DummyCard *dummy = new DummyCard;
            foreach(int card_id, card->getSubcards()){
                dummy->addSubcard(Sanguosha->getCard(card_id));
            }

            QString result = room->askForChoice(player, objectName(), "get+draw+cancel");
            player->setFlags("liehou_on");
            if(result == "cancel")
                return false;
            LogMessage log;
            log.type = "#InvokeSkill";
            log.arg = objectName();
            log.from = player;
            room->sendLog(log);

            ServerPlayer *target = room->askForPlayerChosen(player, sbmen, "liehou");
            if(result == "draw")
                target->drawCards(1);
            else{
                log.type = "#Liehou";
                log.arg = QString::number(dummy->subcardsLength());
                log.to << target;
                room->sendLog(log);

                target->obtainCard(dummy);
                delete dummy;
            }
        }
        return false;
    }
};

class Zide: public PhaseChangeSkill{
public:
    Zide():PhaseChangeSkill("zide"){
        frequency = Compulsory;
    }
    virtual bool onPhaseChange(ServerPlayer *player) const{
        if(player->getPhase() == Player::Finish && !player->hasUsed("TongluCard")){
            LogMessage log;
            log.type = "#TriggerSkill";
            log.arg = objectName();
            log.from = player;
            player->getRoom()->sendLog(log);

            player->drawCards(1);
        }
        return false;
    }
};

XiefangCard::XiefangCard(){
}

bool XiefangCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const{
    if(targets.length() == 2)
        return true;
    return targets.length() == 1 && Self->canSlash(targets.first());
}

bool XiefangCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(targets.isEmpty()){
        return to_select->getWeapon() && to_select != Self;
    }else if(targets.length() == 1){
        const Player *first = targets.first();
        return first != Self && first->getWeapon() && Self->canSlash(to_select);
    }else
        return false;
}

void XiefangCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    const Card *weapon = targets.at(0)->getWeapon();
    ServerPlayer *target;
    if(targets.length() == 1){
        if(!Self->canSlash(targets.first()))
            return;
        else
            target = targets.first();
    }
    else
        target = targets.at(1);

    if(weapon){
        room->throwCard(weapon->getId());
        Slash *slash = new Slash(weapon->getSuit(), weapon->getNumber());
        slash->setSkillName("xiefang");
        slash->addSubcard(weapon);
        CardUseStruct use;
        //room->throwCard(slash->getId());
        use.card = slash;
        use.from = source;
        use.to << target;
        room->useCard(use);
    }
}

class XiefangViewAsSkill:public ZeroCardViewAsSkill{
public:
    XiefangViewAsSkill():ZeroCardViewAsSkill("xiefang"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return Slash::IsAvailable(player);
    }

    virtual const Card *viewAs() const{
        return new XiefangCard;
    }
};

class Xiefang: public TriggerSkill{
public:
    Xiefang():TriggerSkill("xiefang"){
        events << CardAsked;
        view_as_skill = new XiefangViewAsSkill;
    }

    virtual int getPriority() const{
        return 1;
    }

    virtual bool trigger(TriggerEvent, ServerPlayer *player, QVariant &data) const{
        QString asked = data.toString();
        if(asked != "slash" && asked != "jink")
            return false;
        if(asked == "slash" && player->getMark("yany") > 0)
            return false;
        Room *room = player->getRoom();
        QList<ServerPlayer *> playerAs, playerBs;
        foreach(ServerPlayer *tmp, room->getOtherPlayers(player)){
            if(asked == "slash" && tmp->getWeapon())
                playerAs << tmp;
            if(asked == "jink" &&
                    (tmp->getArmor() || tmp->getOffensiveHorse() || tmp->getDefensiveHorse()))
                playerBs << tmp;
        }
        if((asked == "slash" && playerAs.isEmpty()) || (asked == "jink" && playerBs.isEmpty()))
            return false;
        if(room->askForSkillInvoke(player, "xiefang", data)){
            ServerPlayer *target = asked == "slash" ?
                                   room->askForPlayerChosen(player, playerAs, objectName()) :
                                   room->askForPlayerChosen(player, playerBs, objectName());
            int card_id = asked == "slash" ?
                          target->getWeapon()->getId() :
                          room->askForCardChosen(player, target, "e", objectName());
            if(asked == "jink" && target->getWeapon() && target->getWeapon()->getId() == card_id)
                return false;
            const Card *card = Sanguosha->getCard(card_id);
            if(asked == "slash"){
                Slash *xiefang_card = new Slash(card->getSuit(), card->getNumber());
                xiefang_card->setSkillName(objectName());
                xiefang_card->addSubcard(card);
                room->provide(xiefang_card);
            }
            else if(asked == "jink"){
                Jink *xiefang_card = new Jink(card->getSuit(), card->getNumber());
                xiefang_card->setSkillName(objectName());
                xiefang_card->addSubcard(card);
                room->provide(xiefang_card);
            }
        }
        return false;
    }
};

class Yanyun: public TriggerSkill{
public:
    Yanyun():TriggerSkill("yanyun"){
        events << SlashMissed;
        frequency = Frequent;
    }

    virtual int getPriority() const{
        return -1;
    }

    virtual bool trigger(TriggerEvent, ServerPlayer *player, QVariant &data) const{
        SlashEffectStruct effect = data.value<SlashEffectStruct>();

        if(effect.slash->getSkillName() != "xiefang")
            return false;
        if(effect.to->hasSkill("kongcheng") && effect.to->isKongcheng())
            return false;

        Room *room = player->getRoom();
        player->setMark("yany", 1);
        if(room->askForSkillInvoke(player, objectName(), data)){
            const Card *card = room->askForCard(player, "slash", "@yanyun-slash");
            player->setMark("yany", 0);
            if(card && card->getSkillName() != "xiefang"){
                if(player->hasFlag("drank"))
                    room->setPlayerFlag(player, "-drank");

                CardUseStruct use;
                use.card = card;
                use.from = player;
                use.to << effect.to;
                room->useCard(use, false);
            }
        }
        player->setMark("yany", 0);
        return false;
    }
};

class Jielue: public TriggerSkill{
public:
    Jielue():TriggerSkill("jielue"){
        events << SlashEffect << Pindian;
        frequency = Frequent;
    }

    virtual int getPriority() const{
        return -1;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(event == Pindian){
            PindianStar pindian = data.value<PindianStar>();
            if(pindian->reason == objectName() && pindian->isSuccess())
                pindian->from->obtainCard(pindian->to_card);
            return false;
        }
        if(player->getPhase() != Player::Play)
            return false;
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if(effect.slash->getNumber() == 0)
            return false;
        if(effect.slash && !effect.to->isKongcheng() && effect.from->askForSkillInvoke(objectName(), data))
            effect.from->pindian(effect.to, objectName(), effect.slash);
        return false;
    }
};

class Chuzhen: public PhaseChangeSkill{
public:
    Chuzhen():PhaseChangeSkill("chuzhen"){
        frequency = Wake;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return PhaseChangeSkill::triggerable(target)
                && target->getMark("chuzhen") == 0
                && target->getPhase() == Player::Start
                && target->isWounded();
    }

    virtual bool onPhaseChange(ServerPlayer *pai) const{
        Room *room = pai->getRoom();

        LogMessage log;
        log.type = "#ChuzhenWake";
        log.from = pai;
        room->sendLog(log);

        room->setPlayerProperty(pai, "maxhp", pai->getMaxHP() + 1);
        room->acquireSkill(pai, "linjia");
        room->acquireSkill(pai, "zhubing");
        room->setPlayerMark(pai, "chuzhen", 1);
        return false;
    }
};

class Linjia: public TriggerSkill{
public:
    Linjia():TriggerSkill("linjia"){
        events << Predamaged << SlashEffected << CardEffected;
        frequency = Compulsory;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(event == SlashEffected){
            SlashEffectStruct effect = data.value<SlashEffectStruct>();
            if(effect.nature == DamageStruct::Normal){
                LogMessage log;
                log.from = player;
                log.type = "#LinjiaNullify";
                log.arg = objectName();
                log.arg2 = effect.slash->objectName();
                player->getRoom()->sendLog(log);

                return true;
            }
        }else if(event == CardEffected){
            CardEffectStruct effect = data.value<CardEffectStruct>();
            if(effect.card->inherits("SavageAssault")){
                LogMessage log;
                log.from = player;
                log.type = "#LinjiaNullify";
                log.arg = objectName();
                log.arg2 = effect.card->objectName();
                player->getRoom()->sendLog(log);

                return true;
            }
        }else if(event == Predamaged){
            DamageStruct damage = data.value<DamageStruct>();
            if(damage.nature == DamageStruct::Fire){
                LogMessage log;
                log.type = "#LinjiaDamage";
                log.from = player;
                log.arg = QString::number(damage.damage);
                log.arg2 = QString::number(damage.damage + 1);
                player->getRoom()->sendLog(log);

                damage.damage ++;
                data = QVariant::fromValue(damage);
            }
        }

        return false;
    }
};

class Zhubing: public PhaseChangeSkill{
public:
    Zhubing():PhaseChangeSkill("zhubing"){
    }
    virtual bool onPhaseChange(ServerPlayer *pai) const{
        if(pai->getPhase() == Player::Draw){
            Room *room = pai->getRoom();
            if(room->askForSkillInvoke(pai, objectName())){
                int x = pai->getLostHp(), i;
                room->playSkillEffect(objectName(), 1);
                bool has_spade = false;

                for(i=0; i<x; i++){
                    int card_id = room->drawCard();
                    room->moveCardTo(Sanguosha->getCard(card_id), NULL, Player::Special, true);

                    room->getThread()->delay();
                    const Card *card = Sanguosha->getCard(card_id);
                    if(card->getSuit() == Card::Spade){
                        SavageAssault *nanmam = new SavageAssault(Card::Spade, card->getNumber());
                        nanmam->setSkillName("zhubing");
                        nanmam->addSubcard(card);
                        CardUseStruct card_use;
                        card_use.card = nanmam;
                        card_use.from = pai;
                        room->useCard(card_use);
                        has_spade = true;
                    }else
                        room->obtainCard(pai, card_id);
                }
/*
                if(has_spade)
                    room->playSkillEffect(objectName(), 2);
                else
                    room->playSkillEffect(objectName(), 3);
*/
                return true;
            }
        }
        return false;
    }
};

class Xujiu: public PhaseChangeSkill{
public:
    Xujiu():PhaseChangeSkill("xujiu"){
    }
    virtual bool onPhaseChange(ServerPlayer *qiong) const{
        if(qiong->getPhase() != Player::Start)
            return false;
        Room *room = qiong->getRoom();
        const Card *card = room->askForCard(qiong, ".black", "@xujiu-ask");
        if(card){
            qiong->addToPile("niangA", card->getId());
        }
        return false;
    }
};

class BlackPattern: public CardPattern{
public:
    virtual bool match(const Player *player, const Card *card) const{
        return card->isBlack();
    }
    virtual bool willThrow() const{
        return false;
    }
};

class XujiuSlash: public TriggerSkill{
public:
    XujiuSlash():TriggerSkill("#xujiu_slash"){
        events << Predamage;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        if(!damage.card->inherits("Slash") || damage.from != player)
            return false;
        Room *room = player->getRoom();
        if(!player->getPile("niangA").isEmpty() && room->askForSkillInvoke(player, "xujiu", data)){
            int card_id = player->getPile("niangA").first();
            room->obtainCard(player, card_id);
            player->addToPile("niangB", card_id);

            LogMessage log;
            log.type = "#XujiuBuff";
            log.from = player;
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

class Xuebi: public PhaseChangeSkill{
public:
    Xuebi():PhaseChangeSkill("xuebi"){
        frequency = Compulsory;
    }
    virtual bool onPhaseChange(ServerPlayer *qiong) const{
        if(qiong->getPhase() != Player::Finish)
            return false;
        int x = qiong->getPile("niangA").length();
        int y = qiong->getPile("niangB").length();
        if(x + y > 3){
            Room *room = qiong->getRoom();
            for(int i = qMax(x, y); i > 0 ;i--){
                if(!qiong->getPile("niangA").isEmpty())
                    room->throwCard(qiong->getPile("niangA").first());
                if(!qiong->getPile("niangB").isEmpty())
                    room->throwCard(qiong->getPile("niangB").first());
            }
            qiong->loseSkill("niangA");
            qiong->loseSkill("niangB");
            LogMessage log;
            log.from = qiong;
            log.type = "#Xuebi";
            log.arg = objectName();
            log.arg2 = "niangA";
            room->sendLog(log);
            room->loseMaxHp(qiong);
        }
        return false;
    }
};

class Jiaochong: public PhaseChangeSkill{
public:
    Jiaochong():PhaseChangeSkill("jiaochong"){

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

GoulianCard::GoulianCard(){
    once = true;
}

bool GoulianCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(!targets.isEmpty())
        return false;

    if(to_select->getMark("@goulian") > 0 || to_select->getMark("goulianA") > 0)
        return false;
    return to_select->getGeneral()->isMale();
}

void GoulianCard::onEffect(const CardEffectStruct &effect) const{
    Room *room = effect.from->getRoom();
    QString result = room->askForChoice(effect.to, "goulian", "a+b");
    LogMessage log;
    log.from = effect.to;
    log.to << effect.from;
    if(result == "a"){
        log.type = "#GoulianA";
        room->sendLog(log);
        RecoverStruct recover;
        recover.who = effect.from;
        room->recover(effect.to, recover);
        effect.to->setMark("goulianA", 1);
    }
    else{
        log.type = "#GoulianB";
        room->sendLog(log);
        effect.to->drawCards(2);
        effect.to->gainMark("@goulian");
        effect.from->gainMark("@goulian");
    }
}

class GoulianViewAsSkill: public OneCardViewAsSkill{
public:
    GoulianViewAsSkill():OneCardViewAsSkill("goulian"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("GoulianCard");
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        GoulianCard *goulian_card = new GoulianCard;
        goulian_card->addSubcard(card_item->getCard()->getId());

        return goulian_card;
    }
};

class Goulian: public TriggerSkill{
public:
    Goulian():TriggerSkill("goulian"){
        events << Predamaged << PhaseChange << DrawNCards;
        view_as_skill = new GoulianViewAsSkill;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill("goulian") || target->getMark("@goulian") > 0;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        if(event == Predamaged && player->hasSkill("goulian")){
            DamageStruct damage = data.value<DamageStruct>();
            if(damage.to != player)
                return false;
            foreach(ServerPlayer *tmp, room->getOtherPlayers(player)){
                if(tmp->getMark("goulianA") > 0){
                    damage.to = tmp;
                    tmp->setMark("goulianA", 0);
                    LogMessage log;
                    log.type = "#GoulianAdamage";
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
            if(player->getPhase() == Player::Draw && !player->hasSkill("goulian") && player->getMark("@goulian") > 0){
                player->loseMark("@goulian");
                return true;
            }
            else if(player->getPhase() == Player::Start && player->hasSkill("goulian")){
                foreach(ServerPlayer *tmp, room->getOtherPlayers(player)){
                    if(tmp->getMark("goulianA") > 0)
                        tmp->setMark("goulianA", 0);
                    if(tmp->getMark("@goulian") > 0)
                        tmp->loseMark("@goulian");
                }
            }
        }
        else if(event == DrawNCards){
            if(player->hasSkill("goulian") && player->getMark("@goulian") > 0){
                LogMessage log;
                log.type = "#GoulianBdraw";
                log.arg = objectName();
                log.from = player;
                room->sendLog(log);

                player->loseMark("@goulian");
                data = data.toInt() + 1;
            }
        }
        return false;
    }
};

//fortest
class SuperZaiqi: public PhaseChangeSkill{
public:
    SuperZaiqi():PhaseChangeSkill("super_zaiqi"){
    }
    virtual bool onPhaseChange(ServerPlayer *menghuo) const{
        if(menghuo->getPhase() == Player::Draw){
            Room *room = menghuo->getRoom();
            if(room->askForSkillInvoke(menghuo, objectName())){
                int x = menghuo->getLostHp() + 1;
                room->playSkillEffect("zaiqi", 1);
                bool has_heart = false;
                int spade = 0, heart = 0;

                for(int i=0; i<x; i++){
                    int card_id = room->drawCard();
                    room->moveCardTo(Sanguosha->getCard(card_id), NULL, Player::Special, true);

                    room->getThread()->delay();
                    const Card *card = Sanguosha->getCard(card_id);
                    if(card->getSuit() == Card::Spade){
                        spade ++;
                        SavageAssault *nanmam = new SavageAssault(Card::Spade, card->getNumber());
                        nanmam->setSkillName(objectName());
                        nanmam->addSubcard(card);
                        CardUseStruct card_use;
                        card_use.card = nanmam;
                        card_use.from = menghuo;
                        room->useCard(card_use);
                        has_heart = true;
                    }
                    else if(card->getSuit() == Card::Heart){
                        heart ++;
                        RecoverStruct recover;
                        recover.card = card;
                        recover.who = menghuo;
                        room->recover(menghuo, recover);
                        room->throwCard(card_id);
                        has_heart = true;
                    }
                    else
                        room->obtainCard(menghuo, card_id);
                }

                if(has_heart)
                    room->playSkillEffect("zaiqi", 2);
                else
                    room->playSkillEffect("zaiqi", 3);
                if(heart > spade)
                    room->setPlayerProperty(menghuo, "kingdom", "shu");
                else
                    room->setPlayerProperty(menghuo, "kingdom", "qun");

                return true;
            }
        }
        return false;
    }
};

// itachi
class Tsukuyomi: public TriggerSkill{
public:
    Tsukuyomi():TriggerSkill("tsukuyomi"){
        events << Damaged << PhaseChange << Death;
    }

    static void Losttsuku(Room *room, ServerPlayer *itachi){
        foreach(ServerPlayer *tmp, room->getOtherPlayers(itachi)){
            if(tmp->getMark("Tsuku") > 0)
                tmp->setMark("Tsuku", 0);
        }
        room->detachSkillFromPlayer(itachi, itachi->tag.value("Tsuku").toString());
        itachi->tag.remove("Tsuku");
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *itachi, QVariant &data) const{
        Room *room = itachi->getRoom();
        if(event == Death){
            Losttsuku(room, itachi);
            return false;
        }
        if(event == PhaseChange){
            if(itachi->getPhase() == Player::Finish)
                Losttsuku(room, itachi);
            return false;
        }
        if(room->getCurrent() != itachi && room->askForSkillInvoke(itachi, objectName(), data)){
            ServerPlayer *target = room->askForPlayerChosen(itachi, room->getOtherPlayers(itachi), objectName());
            QList<const Skill *> skills = target->getVisibleSkillList();
            QStringList skill_list;
            foreach(const Skill *skill, skills){
                if(skill->parent())
                    skill_list << skill->objectName();
            }
            if(!skill_list.isEmpty()){
                QString choice = room->askForChoice(itachi, objectName(), skill_list.join("+"));
                Losttsuku(room, itachi);
                itachi->tag["Tsuku"] = choice;
                room->acquireSkill(itachi, choice);
                target->setMark("Tsuku", 1); //connect to trigger SkillCut
            }
        }
        return false;
    }
};

class TsukuEffect: public TriggerSkill{
public:
    TsukuEffect(): TriggerSkill("#tsuku_eft"){
        events << CardUsed;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->getMark("Tsuku") > 0;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *uchiha, QVariant &data) const{
        Room *room = uchiha->getRoom();
        CardUseStruct use = data.value<CardUseStruct>();
        room->throwCard(use.card);
        return true;
    }
};

AmaterasuCard::AmaterasuCard(){
}

void AmaterasuCard::onEffect(const CardEffectStruct &effect) const{
    effect.from->getRoom()->loseMaxHp(effect.from);
    if(effect.from->hasSkill("wansha"))
        effect.from->setFlags("isJiaxu");
    else
        effect.from->acquireSkill("wansha");
    DamageStruct damage;
    damage.nature = DamageStruct::Fire;
    damage.from = effect.from;
    damage.to = effect.to;
    effect.from->getRoom()->damage(damage);
    if(!effect.from->hasFlag("isJiaxu"))
        effect.from->getRoom()->detachSkillFromPlayer(effect.from, "wansha");
}

class Amaterasu:public ZeroCardViewAsSkill{
public:
    Amaterasu():ZeroCardViewAsSkill("amaterasu"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return player->isWounded();
    }

    virtual const Card *viewAs() const{
        return new AmaterasuCard;
    }
};

SusaCard::SusaCard(){
    target_fixed = true;
}

void SusaCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &) const{
    foreach(ServerPlayer *target, room->getOtherPlayers(source)){
        if(target && target->getMark("Tsuku") > 0){
            source->loseMark("@susa");
            target->setMark("Tsuku", 0);
            int maxhp = ceil(target->getMaxHP() / 2 * 3);
            room->transfigure(target, "sujiang", false, false);
            room->setPlayerProperty(target, "maxhp", maxhp);
            room->broadcastInvoke("animate", "lightbox:$susa:2500");
            room->getThread()->delay(2500);
            source->setMark("Susa", 1);
            break;
        }
    }
}

class SusaViewAsSkill:public ZeroCardViewAsSkill{
public:
    SusaViewAsSkill():ZeroCardViewAsSkill("susa"){
        frequency = Limited;
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return player->getMark("@susa") > 0;
    }

    virtual const Card *viewAs() const{
        return new SusaCard;
    }
};

class Susa: public PhaseChangeSkill{
public:
    Susa():PhaseChangeSkill("susa"){
        frequency = Limited;
        view_as_skill = new SusaViewAsSkill;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const{
        if(player->getPhase() == Player::NotActive && player->getMark("Susa") > 0){
            player->setMark("Susa", 0);
            player->getRoom()->killPlayer(player);
        }
        return false;
    }
};

RedPackage::RedPackage()
    :Package("red")
{
    General *redhejin = new General(this, "redhejin", "qun", 4);
    redhejin->addSkill(new Tonglu);
    redhejin->addSkill(new Liehou);
    redhejin->addSkill(new Zide);

    General *redguansuo = new General(this, "redguansuo", "shu", 3);
    redguansuo->addSkill(new Xiefang);
    redguansuo->addSkill(new Yanyun);

    General *redyanbaihu = new General(this, "redyanbaihu", "wu");
    redyanbaihu->addSkill(new Jielue);

    General *redwutugu = new General(this, "redwutugu", "shu", 3);
    redwutugu->addSkill(new Chuzhen);
    skills << new Linjia << new Zhubing;

    General *rednanmanwang = new General(this, "rednanmanwang", "shu", 4, true, true);
    rednanmanwang->addSkill("huoshou");
    rednanmanwang->addSkill("#sa_avoid_huoshou");
    rednanmanwang->addSkill(new SuperZaiqi);

    General *redchunyuqiong = new General(this, "redchunyuqiong", "qun");
    redchunyuqiong->addSkill(new Xujiu);
    redchunyuqiong->addSkill(new XujiuSlash);
    redchunyuqiong->addSkill(new Xuebi);
    related_skills.insertMulti("xujiu", "#xujiu_slash");
    patterns[".black"] = new BlackPattern;

    General *redsunluban = new General(this, "redsunluban", "wu", 3, false);
    redsunluban->addSkill(new Jiaochong);
    redsunluban->addSkill(new Goulian);

    //itachi

    General *uchihaitachi = new General(this, "uchihaitachi", "god", 4, true, true);
    uchihaitachi->addSkill(new Tsukuyomi);
    uchihaitachi->addSkill(new TsukuEffect);
    related_skills.insertMulti("tsukuyomi", "#tsuku_eft");
    uchihaitachi->addSkill(new Amaterasu);
    uchihaitachi->addSkill(new Susa);
    uchihaitachi->addSkill(new MarkAssignSkill("@susa", 1));
    related_skills.insertMulti("Susa", "#@susa");

    addMetaObject<TongluCard>();
    addMetaObject<XiefangCard>();
    addMetaObject<GoulianCard>();

    addMetaObject<AmaterasuCard>();
    addMetaObject<SusaCard>();
}

ADD_PACKAGE(Red)
