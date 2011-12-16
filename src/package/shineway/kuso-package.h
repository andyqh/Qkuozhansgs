#ifndef KUSO_H
#define KUSO_H

#include "package.h"
#include "card.h"
#include "standard.h"

class LiaotingCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE LiaotingCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class KusoPackage: public Package{
    Q_OBJECT

public:
    KusoPackage();
};

//cards
class Sacrifice: public SingleTargetTrick{
    Q_OBJECT

public:
    Q_INVOKABLE Sacrifice(Card::Suit suit, int number);

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class ClearShirt:public Armor{
    Q_OBJECT

public:
    Q_INVOKABLE ClearShirt(Card::Suit suit, int number);

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &) const;
};

class KawaiiDress: public Armor{
    Q_OBJECT

public:
    Q_INVOKABLE KawaiiDress(Card::Suit suit, int number);

    virtual void onInstall(ServerPlayer *player) const;
    virtual void onUninstall(ServerPlayer *player) const;
};

class Fiveline: public Armor{
    Q_OBJECT

public:
    Q_INVOKABLE Fiveline(Card::Suit suit, int number);

    virtual void onInstall(ServerPlayer *player) const;
    virtual void onUninstall(ServerPlayer *player) const;
};

class Emigration:public DelayedTrick{
    Q_OBJECT

public:
    Q_INVOKABLE Emigration(Card::Suit suit, int number);

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void takeEffect(ServerPlayer *target) const;
};

class UFO:public Armor{
    Q_OBJECT

public:
    Q_INVOKABLE UFO(Card::Suit suit, int number);
};
/*
class Castrate: public BasicCard{
    Q_OBJECT

public:
    Q_INVOKABLE Castrate(Card::Suit suit, int number);
    virtual QString getSubtype() const;
    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
};
*/
class KusoCardPackage: public Package{
    Q_OBJECT

public:
    KusoCardPackage();
};

#endif // KUSO_H
