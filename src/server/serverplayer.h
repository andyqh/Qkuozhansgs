#ifndef SERVERPLAYER_H
#define SERVERPLAYER_H

class Room;
struct CardMoveStruct;
class AI;
class Recorder;

#include "player.h"
#include "socket.h"

#include <QMutex>

class ServerPlayer : public Player
{
    Q_OBJECT

    Q_PROPERTY(QString ip READ getIp)

public:
    explicit ServerPlayer(Room *room);

    void setSocket(ClientSocket *socket);
    void invoke(const char *method, const QString &arg = ".");
    QString reportHeader() const;
    void sendProperty(const char *property_name, const Player *player = NULL) const;
    void unicast(const QString &message) const;
    void drawCard(const Card *card);
    Room *getRoom() const;
    void playCardEffect(const Card *card);
    int getRandomHandCardId() const;
    const Card *getRandomHandCard() const;
    void obtainCard(const Card *card);
    void throwAllEquips();
    void throwAllHandCards();
    void throwAllCards();
    void bury();
    void throwAllMarks();
    void clearPrivatePiles();
    void drawCards(int n, bool set_emotion = true);
    bool askForSkillInvoke(const QString &skill_name, const QVariant &data = QVariant());
    QList<int> forceToDiscard(int discard_num, bool include_equip);
    QList<int> handCards() const;
    QList<const Card *> getHandcards() const;
    QList<const Card *> getCards(const QString &flags) const;
    DummyCard *wholeHandCards() const;
    bool hasNullification() const;
    void kick();
    bool pindian(ServerPlayer *target, const QString &reason, const Card *card1 = NULL);
    void turnOver();
    void play();
    void play(QList<Player::Phase> &set_phases);

    QList<Player::Phase> &getPhases();
    void skip(Player::Phase phase);

    void gainMark(const QString &mark, int n = 1);
    void loseMark(const QString &mark, int n = 1);
    void loseAllMarks(const QString &mark_name);

    void setAI(AI *ai);
    AI *getAI() const;
    AI *getSmartAI() const;

    virtual int aliveCount() const;
    virtual int getHandcardNum() const;
    virtual void removeCard(const Card *card, Place place);
    virtual void addCard(const Card *card, Place place);
    virtual bool isLastHandCard(const Card *card) const;

    void addVictim(ServerPlayer *victim);
    QList<ServerPlayer *> getVictims() const;

    void startRecord();
    void saveRecord(const QString &filename);

    void setNext(ServerPlayer *next);
    ServerPlayer *getNext() const;
    ServerPlayer *getNextAlive() const;

    // 3v3 methods
    void addToSelected(const QString &general);
    QStringList getSelected() const;
    QString findReasonable(const QStringList &generals);
    void clearSelected();

    int getGeneralMaxHP() const;
    virtual QString getGameMode() const;

    QString getIp() const;
    void introduceTo(ServerPlayer *player);
    void marshal(ServerPlayer *player) const;

    void addToPile(const QString &pile_name, int card_id, bool open = true);
    void gainAnExtraTurn();

    void copyFrom(ServerPlayer* sp);

private:
    ClientSocket *socket;
    QList<const Card *> handcards;
    Room *room;
    AI *ai;
    AI *trust_ai;
    QList<ServerPlayer *> victims;
    Recorder *recorder;
    QList<Phase> phases;
    ServerPlayer *next;
    QStringList selected; // 3v3 mode use only

private slots:
    void getMessage(char *message);
    void castMessage(const QString &message);

signals:
    void disconnected();
    void request_got(const QString &request);
    void message_cast(const QString &message) const;
};

#endif // SERVERPLAYER_H
