#ifndef TASKLIST_H
#define TASKLIST_H

#include <QObject>
#include <QSet>
#include <QJsonArray>
#include <QJsonObject>

#include "task.h"

class TaskList
{
public:
    explicit TaskList();

    void addTask(Task* task);
    //void deleteTask(int task_id);
    void deleteTask(Task* task);
    //void editTask(int task_id, const QString& task_name, const QDate& date, const QString& description, const State state);
    //void setState(int task_id, const State state);
    int size() const { return tasks.size(); }
    TaskList filterFromDate(QDate start)const;
    TaskList filterToDate(QDate finish)const;
    TaskList filterByState(State state)const;
    TaskList filterByName(QString pattern)const;
    TaskList filterByDescription(QString pattern)const;
    friend QSet<Task*>::iterator begin(TaskList &x);
    friend QSet<Task*>::iterator end(TaskList &x);
    QJsonArray convertToJson() const;
    static TaskList createFromJson(QJsonArray json);
    QDate getMinDate() const;
    QDate getMaxDate() const;
signals:

private:
    QSet<Task*> tasks;
};

// QSet<Task*>::iterator begin(TaskList &x);
// QSet<Task*>::iterator end(TaskList &x);

#endif // TASKLIST_H
