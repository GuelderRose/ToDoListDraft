#ifndef TASKLIST_H
#define TASKLIST_H

#include <QObject>
#include <QSet>

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
    TaskList filterFromDate(QDate start);
    TaskList filterToDate(QDate finish);
    TaskList filterByState(State state);
    TaskList filterByName(QString pattern);
    TaskList filterByDescription(QString pattern);
    friend QSet<Task*>::iterator begin(TaskList &x);
    friend QSet<Task*>::iterator end(TaskList &x);

signals:

private:
    QSet<Task*> tasks;
};

// QSet<Task*>::iterator begin(TaskList &x);
// QSet<Task*>::iterator end(TaskList &x);

#endif // TASKLIST_H
