#include "cyan.h"
#include "skill.h"
#include "client.h"
#include "engine.h"
#include "carditem.h"
#include "room.h"

PearCard::PearCard(){
    target_fixed = true;
}

void PearCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &) const{
    ServerPlayer *kongrong = room->getCurrent();
    if(kongrong->hasSkill("rangli")){
        kongrong->obtainCard(this);
    }
}

class RangliViewAsSkill: public ViewAsSkill{
public:
    RangliViewAsSkill():ViewAsSkill("rangli"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const{
        return pattern == "@@rangli!";
    }

    virtual bool viewFilter(const QList<CardItem *> &selected, const CardItem *to_select) const{
        if(selected.length() > 2)
            return false;
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(cards.length() != 2)
            return NULL;
        PearCard *card = new PearCard();
        card->addSubcards(cards);
        return card;
    }
};

class Rangli: public TriggerSkill{
public:
    Rangli():TriggerSkill("rangli"){
        view_as_skill = new RangliViewAsSkill;
        events << PhaseChange << DrawNCards;
    }

    virtual bool triggerable(const ServerPlayer *player) const{;
        return player->hasSkill(objectName()) || player->getMark("@pear") > 0;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        if(event == DrawNCards){
            int pearnum = player->getMark("@pear");
            data = data.toInt() + pearnum * 2;
            player->loseAllMarks("@pear");
            return false;
        }
        if(player->getMark("@pear") > 0 || player->getPhase() != Player::Draw)
            return false;
        if(player->askForSkillInvoke(objectName(), data)){
            QList<ServerPlayer *> players;
            foreach(ServerPlayer *tmp, room->getAlivePlayers()){
                if(tmp->getHandcardNum() < 2){
                    if(tmp->hasSkill("lianying"))
                        players << tmp;
                    else if(tmp->hasSkill("shangshi") && tmp->isWounded())
                        players << tmp;
                    else
                        continue;
                }
                else
                    players << tmp;
            }
            if(players.isEmpty())
                return false;
            ServerPlayer *target = room->askForPlayerChosen(player, players, objectName());
            target->gainMark("@pear");
            if(!room->askForUseCard(target, "@@rangli!", "@rangli-ask:" + player->objectName())){
                int card_id = room->askForCardChosen(player, target, "h", "rangli");
                room->moveCardTo(Sanguosha->getCard(card_id), player, Player::Hand, false);
                card_id = room->askForCardChosen(player, target, "h", "rangli");
                room->moveCardTo(Sanguosha->getCard(card_id), player, Player::Hand, false);
            }
            return true;
        }
        return false;
    }
};

class Baiming: public TriggerSkill{
public:
    Baiming():TriggerSkill("baiming"){
        events << Predamage;
        frequency = Compulsory;
    }

    virtual int getPriority() const{
        return 2;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        DamageStruct damage = data.value<DamageStruct>();
        const Card *reason = damage.card;
        if(reason && reason->inherits("Slash") && player->getMark("baiming") == 0){
            LogMessage log;
            log.type = "#Baiming";
            log.from = player;
            log.to << damage.to;
            log.arg = objectName();

            QList<ServerPlayer *> players;
            foreach(ServerPlayer *tmp, room->getAllPlayers()){
                if(damage.to->inMyAttackRange(tmp) && tmp != damage.to)
                    players << tmp;
            }
            if(players.isEmpty())
                return true;
            room->sendLog(log);
            damage.to = room->askForPlayerChosen(player, players, objectName());
            log.type = "#BaimingRechoose";
            log.to.clear();
            log.to << damage.to;
            room->sendLog(log);

            player->setMark("baiming", 1);
            room->damage(damage);
            player->setMark("baiming", 0);
            return true;
        }
        return false;
    }
};

JunlingCard::JunlingCard(){
    once = true;
}

bool JunlingCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const{
    return targets.length() == 2;
}

bool JunlingCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(targets.isEmpty()){
        return true;
    }else if(targets.length() == 1){
        const Player *first = targets.first();
        return first->inMyAttackRange(to_select);
    }else
        return false;
}

void JunlingCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    ServerPlayer *killer = targets.at(0);
    ServerPlayer *victim = targets.at(1);
    QString prompt = QString("junling-slash:%1:%2")
                         .arg(source->objectName()).arg(victim->objectName());
    const Card *slash = room->askForCard(killer, "slash", prompt);
    if(slash){
        CardUseStruct use;
        use.card = slash;
        use.from = killer;
        use.to << victim;
        room->useCard(use);
    }else{
        if(!killer->isKongcheng()){
            int card_id = room->askForCardChosen(source, killer, "h", "junling");
            room->moveCardTo(Sanguosha->getCard(card_id), source, Player::Hand, false);
        }
    }
}

class Junling:public ZeroCardViewAsSkill{
public:
    Junling():ZeroCardViewAsSkill("junling$"){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return ! player->hasUsed("JunlingCard");
    }

    virtual const Card *viewAs() const{
        return new JunlingCard;
    }
};

class Shuaijin: public TriggerSkill{
public:
    Shuaijin():TriggerSkill("shuaijin"){
        events << Damage;
        frequency = Frequent;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();

        if(damage.card && damage.card->isBlack() && player->askForSkillInvoke(objectName(), data)){
            Room *room = player->getRoom();
            player->drawCards(1);
            QList<int> sj_cards = player->handCards().mid(player->getHandcardNum() - 1);
            room->setPlayerMark(player, "Shuaijin", 1);
            while(room->askForYiji(player, sj_cards));
            room->setPlayerMark(player, "Shuaijin", 0);
        }
        return false;
    }
};

class Liufang: public TriggerSkill{
public:
    Liufang():TriggerSkill("liufang"){
        events << CardLost;
        frequency = Frequent;
    }

    virtual int getPriority() const{
        return -1;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return TriggerSkill::triggerable(target) && target->getPhase() == Player::NotActive;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        CardMoveStar move = data.value<CardMoveStar>();
        if((move->from_place == Player::Hand || move->from_place == Player::Equip)
            && move->to != player && player->getMark("Shuaijin") == 0
            && player->askForSkillInvoke(objectName(), data)){
            JudgeStruct judge;
            judge.reason = objectName();
            judge.who = player;
            player->getRoom()->judge(judge);
            if(judge.card->isBlack() && !judge.card->inherits("EquipCard"))
                player->getRoom()->obtainCard(player, move->card_id);
        }
        return false;
    }
};

class Weighing: public TriggerSkill{
public:
    Weighing():TriggerSkill("weighing"){
        events << HandCardNumChanged << HpChanged;
        frequency = Compulsory;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *cc, QVariant &) const{
        Room *room = cc->getRoom();
        if(room->getCurrent() && room->getCurrent() != cc){
           int handcard = cc->getHandcardNum();
           int hp = cc->getHp();
           if(handcard != hp){
               LogMessage log;
               log.type = "#TriggerSkill";
               log.from = cc;
               log.arg = objectName();
               room->sendLog(log);

               cc->setMark("Exception", 1);
               if(handcard < hp)
                   cc->drawCards(hp - handcard);
               else
                   room->askForDiscard(cc, objectName(), handcard - qMax(hp, 0));
               cc->setMark("Exception", 0);
           }
        }
        return false;
    }
};

class Kuanhou:public MasochismSkill{
public:
    Kuanhou():MasochismSkill("kuanhou"){
    }

    virtual void onDamaged(ServerPlayer *cc, const DamageStruct &damage) const{
        Room *room = cc->getRoom();
        if(!cc->faceUp())
            return;
        QVariant data = QVariant::fromValue(damage);
        if(room->askForSkillInvoke(cc, objectName(), data)){
            cc->turnOver();
            if(damage.from)
                damage.from->setMark("kuanhou", 1);
        }
    }
};

class KuanhouEffect:public PhaseChangeSkill{
public:
    KuanhouEffect():PhaseChangeSkill("#kuanhou_effect"){
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->getMark("kuanhou") > 0;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const{
        Room *room = player->getRoom();
        ServerPlayer *cc = room->findPlayerBySkillName("kuanhou");
        if(cc && player->getPhase() == Player::NotActive){
            ServerPlayer *target = room->askForPlayerChosen(cc, room->getOtherPlayers(player), "kuanhou");
            player->setMark("kuanhou", 0);

            LogMessage log;
            log.type = "#Kuanhou";
            log.from = cc;
            log.to << target;
            room->sendLog(log);

            QList<Player::Phase> phases;
            phases << Player::Play;
            target->play(phases);
        }
        return false;
    }
};

class Hunren: public TriggerSkill{
public:
    Hunren():TriggerSkill("hunren"){
        events << CardLost << CardFinished << FinishJudge;
        frequency = Compulsory;
    }

    virtual int getPriority() const{
        return -1;
    }

    static QString PuyuanBook(QString weapon){
        QMap<QString, QString> map;

        map["crossbow"] = "jizhi";
        map["double_sword"] = "rende";
        map["qinggang_sword"] = "juejing";
        map["guding_blade"] = "yinghun";
        map["ice_sword"] = "tianxiang";
        map["blade"] = "wusheng";
        map["axe"] = "duanliang";
        map["spear"] = "paoxiao";
        map["fan"] = "bazhen";
        map["halberd"] = "wushuang";
        map["kylin_bow"] = "liegong";
        map["moon_spear"] = "longdan";
        map["yitian_sword"] = "jianxiong";
        map["yx_sword"] = "fangzhu";
        map["sp_moonspear"] = "qingguo";

        return map.value(weapon, QString());
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        const Card *weapon;
        if(event == FinishJudge){
            weapon = player->getWeapon();
            if(weapon)
                return false;
            JudgeStar judge = data.value<JudgeStar>();
            CardStar card = judge->card;
            QVariant data_card = QVariant::fromValue(card);
            if(player->askForSkillInvoke("tiandu", data_card)){
                player->obtainCard(judge->card);
                room->playSkillEffect("tiandu");
                return true;
            }
            return false;
        }
        else if(event == CardLost){
            CardMoveStar move = data.value<CardMoveStar>();
            if(move->from_place == Player::Equip){
                weapon = Sanguosha->getCard(move->card_id);
                if(weapon->inherits("Weapon")){
                    LogMessage log;
                    log.type = "#HunrenSkill";
                    log.from = player;
                    log.arg = objectName();
                    log.arg2 = PuyuanBook(weapon->objectName());
                    room->detachSkillFromPlayer(player, log.arg2);
                    room->sendLog(log);
                }
            }
            return false;
        }
        CardUseStruct card_use = data.value<CardUseStruct>();
        if(card_use.card->inherits("Weapon")){
            weapon = player->getWeapon();
            if(weapon){
                LogMessage log;
                log.type = "#TriggerSkill";
                log.from = player;
                log.arg = objectName();
                room->sendLog(log);
                room->acquireSkill(player, PuyuanBook(weapon->objectName()));
            }
        }
        return false;
    }
};

class HunrenNotActive: public TriggerSkill{
public:
    HunrenNotActive():TriggerSkill("#hunren_nat"){
        events << CardFinished;
    }

    virtual int getPriority() const{
        return -2;
    }

    virtual bool triggerable(const ServerPlayer *) const{
        return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        ServerPlayer *puyuan = room->findPlayerBySkillName("hunren");
        if(!puyuan)
            return false;
        CardUseStruct card_use = data.value<CardUseStruct>();
        if(card_use.to.contains(puyuan) && card_use.card->getId() < 0 &&
           (card_use.card->getSkillName() == "zhijian" ||
            card_use.card->getSkillName() == "ganlu")){
            const Card *weapon = puyuan->getWeapon();
            if(weapon){
                LogMessage log;
                log.type = "#TriggerSkill";
                log.from = puyuan;
                log.arg = "hunren";
                room->sendLog(log);
                room->acquireSkill(puyuan, Hunren::PuyuanBook(weapon->objectName()));
            }
        }
        return false;
    }
};

class Cuihuo: public TriggerSkill{
public:
    Cuihuo():TriggerSkill("cuihuo"){
        events << CardLost;
        frequency = Compulsory;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        CardMoveStar move = data.value<CardMoveStar>();
        if(move->from_place == Player::Equip){
            Room *room = player->getRoom();
            if(Sanguosha->getCard(move->card_id)->inherits("Weapon")){
                if(player->getPhase() == Player::Play && player->hasFlag("cuihuo"))
                    return false;
                LogMessage log;
                log.type = "#TriggerSkill";
                log.from = player;
                log.arg = objectName();
                room->sendLog(log);

                RecoverStruct recover;
                recover.who = player;
                room->recover(player, recover);
                if(player->getPhase() == Player::Play)
                    player->setFlags("cuihuo");
            }
        }
        return false;
    }
};

RujiCard::RujiCard(){

}

bool RujiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(!targets.isEmpty())
        return false;
    return to_select != Self && !to_select->isKongcheng();
}

void RujiCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    const Card *card = Sanguosha->getCard(this->getSubcards().first());
    ServerPlayer *target = targets.first();
    if(source->pindian(target, "ruji", card)){
        QList<int> card_ids;
        foreach(const Card *card, target->getHandcards()){
            card_ids << card->getEffectiveId();
        }
        if(!card_ids.isEmpty()){
            room->fillAG(card_ids);
            LogMessage log;
            log.type = "#RujiSucc";
            log.from = source;
            log.to << target;
            room->sendLog(log);

            int card_id = room->askForAG(source, card_ids, true, "ruji");
            if(card_id > -1){
                room->throwCard(card_id);
                room->broadcastInvoke("clearAG");
                return;
            }
            else
                room->broadcastInvoke("clearAG");
        }
        if(target->getEquips().length() + target->getJudgingArea().length() == 0)
            return;
        int card_id = room->askForCardChosen(source, target, "ej", "ruji_success");
        room->throwCard(card_id);
    }
    else
        target->drawCards(2);
}

class RujiViewAsSkill: public OneCardViewAsSkill{
public:
    RujiViewAsSkill():OneCardViewAsSkill("ruji"){
    }

    virtual bool isEnabledAtPlay(const Player *) const{
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const{
        return pattern == "@@ruji!";
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        RujiCard *card = new RujiCard;
        card->addSubcard(card_item->getCard()->getId());
        return card;
    }
};

class Ruji: public PhaseChangeSkill{
public:
    Ruji():PhaseChangeSkill("ruji"){
        view_as_skill = new RujiViewAsSkill;
    }

    virtual int getPriority() const{
        return 3;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const{
        if(player->getPhase() != Player::Start)
            return false;
        Room *room = player->getRoom();
        bool fadong = false;
        if(player->askForSkillInvoke(objectName())){
            player->drawCards(1);

            foreach(ServerPlayer *tmp, room->getOtherPlayers(player)){
                if(!tmp->isKongcheng()){
                    fadong = true;
                    break;
                }
            }
            if(!fadong)
                return false;
            if(!room->askForUseCard(player, "@@ruji!", "@ruji-card"))
                room->throwCard(player->getHandcards().last());
        }
        return false;
    }
};

class Caishi:public PhaseChangeSkill{
public:
    Caishi():PhaseChangeSkill("caishi"){
        frequency = Compulsory;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const{
        if(player->getPhase() != Player::NotActive)
            return false;
        Room *room = player->getRoom();
        LogMessage log;
        log.type = "#Caishi";
        log.from = player;
        log.arg = objectName();
        log.arg2 = player->getHandcardNum() > 1 ? QString::number(2) :
                   player->getHandcardNum() == 1 ? QString::number(1) : QString::number(0);
        room->sendLog(log);

        int discardnum = qMin(2, player->getHandcardNum());
        if(player->getHandcardNum() > 2)
            room->askForDiscard(player, objectName(), discardnum);
        else
            player->throwAllHandCards();
        if(player->isAlive())
            player->drawCards(1);
        return false;
    }
};

ZhongshuCard::ZhongshuCard(){
    once = true;
}
bool ZhongshuCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    if(!targets.isEmpty())
        return false;
    if(Self->canSlash(to_select))
        return true;
    return qAbs(to_select->getHandcardNum() - Self->getHp()) == 1;
}
void ZhongshuCard::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    const Card *slash = Sanguosha->getCard(this->getSubcards().first());

    CardUseStruct use;
    use.card = slash;
    use.from = source;
    use.to = targets;

    room->useCard(use);
}

class Zhongshu: public OneCardViewAsSkill{
public:
    Zhongshu():OneCardViewAsSkill("zhongshu"){
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return Slash::IsAvailable(player) && player->getPhase() == Player::Play;
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return to_select->getCard()->inherits("Slash");
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        ZhongshuCard *card = new ZhongshuCard;
        card->addSubcard(card_item->getFilteredCard());
        return card;
    }
};

class Guolie: public TriggerSkill{
public:
    Guolie():TriggerSkill("guolie"){
        events << Predamage;
    }

    virtual int getPriority() const{
        return 2;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        DamageStruct damage = data.value<DamageStruct>();
        if(player->askForSkillInvoke(objectName(), data)){
            DummyCard *card1 = damage.to->wholeHandCards();
            DummyCard *card2 = damage.from->wholeHandCards();

            if(card1){
                room->moveCardTo(card1, damage.from, Player::Hand, false);
                delete card1;
            }
            if(card2){
                room->moveCardTo(card2, damage.to, Player::Hand, false);
                delete card2;
            }

            LogMessage log;
            log.type = "#Guolie";
            log.from = damage.from;
            log.to << damage.to;
            room->sendLog(log);
            return true;
        }
        return false;
    }
};

class Qianpan: public TriggerSkill{
public:
    Qianpan():TriggerSkill("qianpan"){
        events << CardEffected << Damaged << HpRecover;
        frequency = Compulsory;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        if(event == Damaged || event == HpRecover){
            QString kingdom;
            if(event == HpRecover){
                RecoverStruct recover = data.value<RecoverStruct>();
                if(!recover.who || recover.who == player)
                    return false;
                kingdom = recover.who->getKingdom();
            }
            else
                kingdom = player->getKingdom() == "shu" ? "wu" : "shu";
            LogMessage log;
            log.type = "#Qianpan";
            log.from = player;
            log.arg = kingdom;
            log.arg2 = objectName();
            room->sendLog(log);

            room->setPlayerProperty(player, "kingdom", kingdom);
            return false;
        }
        CardEffectStruct effect = data.value<CardEffectStruct>();
        if(effect.card->isNDTrick() && effect.from->getKingdom() != effect.to->getKingdom()){

            LogMessage log;
            log.type = "#QianpanProtect";
            log.from = effect.to;
            log.to << effect.from;
            log.arg = effect.card->objectName();
            log.arg2 = objectName();
            room->sendLog(log);

            return true;
        }
        return false;
    }
};

class Anshi: public TriggerSkill{
public:
    Anshi():TriggerSkill("anshi"){
        events << Dying << PhaseChange;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        ServerPlayer *fanzhang = room->findPlayerBySkillName(objectName());
        if(!fanzhang)
            return false;
        if(event == PhaseChange && fanzhang->hasFlag("Anshi") && fanzhang->getPhase() == Player::NotActive){
            room->detachSkillFromPlayer(fanzhang, "wansha");
            LogMessage log;
            log.type = "#AnshiSuicide";
            log.from = fanzhang;
            log.arg = objectName();
            room->sendLog(log);

            room->loseHp(fanzhang, fanzhang->getHp());
            return false;
        }
        if(room->getCurrent() != fanzhang)
            return false;
        if(event == Dying && fanzhang->getPhase() == Player::Play){
            DyingStruct dying = data.value<DyingStruct>();
            if(dying.who != fanzhang && fanzhang->askForSkillInvoke(objectName(), data)){
                fanzhang->acquireSkill("wansha");
                room->setPlayerFlag(fanzhang, "Anshi");
            }
        }
        return false;
    }
};

class Jiaozei: public TriggerSkill{
public:
    Jiaozei():TriggerSkill("jiaozei"){
        events << SlashMissed;
    }

    virtual bool trigger(TriggerEvent, ServerPlayer *player, QVariant &data) const{
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if(!effect.to->isKongcheng() && !player->isKongcheng() && player->askForSkillInvoke(objectName(), data)){
            Room *room = player->getRoom();
            const Card *from_card = NULL;
            if(player->hasLordSkill("zhaobing") && player->askForSkillInvoke("zhaobing", data)){
                foreach(ServerPlayer *tmp, room->getOtherPlayers(player)){
                    if(tmp->getKingdom() != "qun")
                        continue;
                    from_card = room->askForCard(tmp, ".", "@zhaobing-pindian:" + player->objectName(), QVariant::fromValue(player));
                    if(from_card){
                        LogMessage log;
                        log.type = "$Zhaobing";
                        log.from = tmp;
                        log.to << player;
                        log.card_str = from_card->getEffectIdString();
                        room->sendLog(log);
                        break;
                    }
                }
            }
            if(player->pindian(effect.to, objectName(), from_card)){
                LogMessage log;
                log.type = "#Jiaozei";
                log.from = player;
                log.to << effect.to;
                log.arg = objectName();
                room->sendLog(log);

                room->slashResult(effect, NULL);
                return true;
            }
        }

        return false;
    }
};

CyanPackage::CyanPackage()
    :Package("cyan")
{
    General *cyankongrong = new General(this, "cyankongrong", "qun");
    cyankongrong->addSkill(new Rangli);

    General *cyancaochong = new General(this, "cyancaochong", "wei", 3);
    cyancaochong->addSkill(new Weighing);
    cyancaochong->addSkill(new Kuanhou);
    cyancaochong->addSkill(new KuanhouEffect);
    related_skills.insertMulti("kuanhou", "#kuanhou_effect");

    General *cyanliaohua = new General(this, "cyanliaohua", "shu");
    cyanliaohua->addSkill(new Zhongshu);
    cyanliaohua->addSkill(new Guolie);

    General *cyanyufan = new General(this, "cyanyufan", "wu", 3);
    cyanyufan->addSkill(new Shuaijin);
    cyanyufan->addSkill(new Liufang);

    General *cyanlidian = new General(this, "cyanlidian", "wei");
    cyanlidian->addSkill(new Ruji);
    cyanlidian->addSkill(new Caishi);

    General *cyanzhangxiu = new General(this, "cyanzhangxiu$", "qun", 4, true, true);
    cyanzhangxiu->addSkill(new Baiming);
    cyanzhangxiu->addSkill(new Junling);

    General *cyanpuyuan = new General(this, "cyanpuyuan", "shu");
    cyanpuyuan->addSkill(new Hunren);
    cyanpuyuan->addSkill(new HunrenNotActive);
    related_skills.insertMulti("hunren", "#hunren_nat");
    cyanpuyuan->addSkill(new Cuihuo);

    General *cyanfanqiangzhangda = new General(this, "cyanfanqiangzhangda", "shu");
    cyanfanqiangzhangda->addSkill(new Qianpan);
    cyanfanqiangzhangda->addSkill(new Anshi);

    General *cyanmateng = new General(this, "cyanmateng$", "qun");
    cyanmateng->addSkill(new Jiaozei);
    cyanmateng->addSkill(new Skill("zhaobing$"));

    addMetaObject<PearCard>();
    addMetaObject<ZhongshuCard>();
    addMetaObject<RujiCard>();
    addMetaObject<JunlingCard>();
}

ADD_PACKAGE(Cyan)
