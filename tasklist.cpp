#include "tasklist.h"

TaskList::TaskList(QObject *parent)
    : QObject{parent}
{

}

void TaskList::addTask(Task* new_task)
{
    tasks.push_back(new_task);
}

void TaskList::deleteTask(int task_id)
{
    if (task_id < tasks.size()) {
        tasks.erase(tasks.begin() + task_id);
    }
}

void TaskList::editTask(int task_id, const QString& task_name, const QDate& date, const QString& description, const State state)
{
    tasks[task_id]->setTaskName(task_name);
    tasks[task_id]->setDate(date);
    tasks[task_id]->setDescription(description);
    tasks[task_id]->setState(state);
}

void TaskList::setState(int task_id, const State state)
{
    (*tasks[task_id]).setState(state);
}
