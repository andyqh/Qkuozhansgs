#ifndef RED_H
#define RED_H

#include "package.h"
#include "card.h"
#include "standard.h"

/*
class Jiehuo: public TriggerSkill{
public:
    Jiehuo():TriggerSkill("jiehuo"){
        events << CardUsed << CardEffected;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        ServerPlayer *shuijing = room->findPlayerBySkillName(objectName());
        if(event == CardEffected){
            CardEffectStruct effect = data.value<CardEffectStruct>();

            if(!(effect.multiple &&
                (effect.card->inherits("GlobalEffect") ||
                 effect.card->inherits("AOE"))))
                return false;
            foreach(ServerPlayer *p,room->getAlivePlayers())
                if(p->getMark("jiehuo") > 0)
                    return false;
            if(shuijing->getMark("jiehuoover")<1){
                ServerPlayer *target = room->askForPlayerChosen(shuijing, room->getAlivePlayers(), objectName());
                if(target){
                    target->addMark("jiehuo");
                    shuijing->addMark("jiehuoover");
                }
            }
            else if(shuijing->getMark("jiehuoover")>0 && player->getMark("jiehuo")>0){
                player->loseAllMarks("juehuo");
                shuijing->loseAllMarks("jiehuoover");
                return true;
            }
        }
        else if(event == CardUsed){
            CardUseStruct effect = data.value<CardUseStruct>();

            if(effect.card->inherits("TrickCard") &&
               !effect.card->inherits("Collateral") &&
               effect.to.contains(shuijing) && effect.to.length() > 1){
                Room *room = player->getRoom();
                if(room->askForSkillInvoke(shuijing, objectName(), data)){
                    ServerPlayer *target = room->askForPlayerChosen(shuijing, effect.to, objectName());
                    if(target)
                        effect.to.removeOne(target);
                    data = QVariant::fromValue(effect);
                    return false;
                }
            }
        }
        return false;
    }
};
*/

class TongmouxCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE TongmouxCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class XianhaixCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XianhaixCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class BaichuxCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE BaichuxCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class TongluCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE TongluCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class XiefangCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XiefangCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class GoulianCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE GoulianCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class AmaterasuCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE AmaterasuCard();

    virtual void onEffect(const CardEffectStruct &effect) const;
};

class SusaCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE SusaCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class RedPackage: public Package{
    Q_OBJECT

public:
    RedPackage();
};

#endif // RED_H
