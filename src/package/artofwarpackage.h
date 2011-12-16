#ifndef ARTOFWARPACKAGE_H
#define ARTOFWARPACKAGE_H

#include "standard.h"

class Wangmei: public SingleTargetTrick{
    Q_OBJECT

public:
    Q_INVOKABLE Wangmei(Card::Suit suit, int number);

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class Tiechui:public Weapon{
    Q_OBJECT

public:
    Q_INVOKABLE Tiechui(Card::Suit suit = Heart, int number = 5);
};

class Qixingdao:public Weapon{
    Q_OBJECT

public:
    Q_INVOKABLE Qixingdao(Card::Suit suit = Spade, int number = 1);
};

class Muniuliuma: public Armor{
    Q_OBJECT

public:
    Q_INVOKABLE Muniuliuma(Card::Suit suit, int number);
};

class Yuxi: public Armor{
    Q_OBJECT

public:
    Q_INVOKABLE Yuxi(Card::Suit suit, int number);
};

class Nanmanxiang: public DefensiveHorse{
    Q_OBJECT

public:
    Q_INVOKABLE Nanmanxiang(Card::Suit suit, int number);

    virtual QString getEffectPath(bool is_male) const;
};

class ArtofwarPackage: public Package{
    Q_OBJECT

public:
    ArtofwarPackage();
};

#endif // ARTOFWARPACKAGE_H
