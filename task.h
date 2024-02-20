#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QString>
#include <QDate>

enum class State {
    InProgress,
    Done,
    Overdue
};



class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);

    Task(QString task_name);
    Task(QString task_name, QDate date);
    Task(QString task_name, QDate date, QString description);
    Task(QString task_name, QString description);
    const QString& getTaskName() const;
    const QDate& getDate() const; //maybe return string instead?
    const QString& getDescription() const;
    State getState() const;
    void setTaskName(const QString& task_name);
    void setDate(const QDate& date);
    void setDescription(const QString& description);
    void setState(State state);
signals:

private:
    QString task_name;
    QDate date;
    QString description;
    State state;
};

#endif // TASK_H
