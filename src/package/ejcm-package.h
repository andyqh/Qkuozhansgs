#ifndef EJCMPACKAGE_H
#define EJCMPACKAGE_H

#include "package.h"
#include "card.h"

class XiaosiCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE XiaosiCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class ZhenshouCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE ZhenshouCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class QisheCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE QisheCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class DaojiCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE DaojiCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class JingjiuCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE JingjiuCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class EJCMPackage: public Package{
    Q_OBJECT

public:
    EJCMPackage();
};

#endif // EJCMPACKAGE_H
