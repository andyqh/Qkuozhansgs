#ifndef SHADOWPACKAGE_H
#define SHADOWPACKAGE_H

#include "package.h"
#include "standard.h"

class YuanliangCard:public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE YuanliangCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class ZenhuiCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE ZenhuiCard();

    virtual void onEffect(const CardEffectStruct &effect) const;
};

class FuhuoCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE FuhuoCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class ShadowPackage: public Package{
    Q_OBJECT

public:
    ShadowPackage();
};

#endif // SHADOWPACKAGE_H
