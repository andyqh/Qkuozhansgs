#ifndef GREEN_H
#define GREEN_H

#include "package.h"
#include "card.h"
#include "standard.h"

struct YuanlvStruct{
    YuanlvStruct();
    QString kingdom;
    QString generalA;
    QString generalB;
    int maxhp;
    QStringList skills;
};

Q_DECLARE_METATYPE(YuanlvStruct);

class YuanlvCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE YuanlvCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class DiezhiCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE DiezhiCard();

    virtual void use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const;
};

class JinguoCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE JinguoCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class GreenPackage: public Package{
    Q_OBJECT

public:
    GreenPackage();
};

#endif // GREEN_H
