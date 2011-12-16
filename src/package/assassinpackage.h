//assassinpackage.h

#ifndef ASS_H
#define ASS_H
#include <math.h>
#include "package.h"
#include "card.h"
#include "generaloverview.h"

class TaichiePackage: public Package{
    Q_OBJECT

public:
    TaichiePackage();
};

class AssassinPackage: public Package{
    Q_OBJECT

public:
    AssassinPackage();
};
class SipiaoCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE SipiaoCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};
class TiaoboCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE TiaoboCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};


class TianleiCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE TianleiCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class MenkeCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE MenkeCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};
class WangniCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE WangniCard();
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};
class DanceCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE DanceCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};
class ZombieCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE ZombieCard();

    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
};

class PoisonCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE PoisonCard();

    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
};

	
#endif // ASS_H
