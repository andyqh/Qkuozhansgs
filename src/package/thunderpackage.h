#ifndef THUNDERPACKAGE_H
#define THUNDERPACKAGE_H

#include "package.h"
#include "standard.h"

class YuanjunCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE YuanjunCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class TongmouCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE TongmouCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class ZhongyanCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE ZhongyanCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class FujiCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE FujiCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class XianceCard:public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XianceCard();
    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class BaichuCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE BaichuCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class ThunderPackage: public Package{
    Q_OBJECT

public:
    ThunderPackage();
};

#endif // THUNDERPACKAGE_H
