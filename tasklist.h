#ifndef TASKLIST_H
#define TASKLIST_H

#include <QObject>
#include <QVector>

#include "task.h"

class TaskList : public QObject
{
    Q_OBJECT
public:
    explicit TaskList(QObject *parent = nullptr);

    void addTask(Task* task);
    void deleteTask(int task_id);
    void editTask(int task_id, const QString& task_name, const QDate& date, const QString& description, const State state);
    void setState(int task_id, const State state);
    int size() const { return tasks.size(); }
signals:

private:
    QVector<Task*> tasks;
};

#endif // TASKLIST_H
