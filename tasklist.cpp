#include "tasklist.h"

TaskList::TaskList()
{

}

void TaskList::addTask(Task* new_task)
{
    tasks.insert(new_task);
}

// void TaskList::deleteTask(int task_id)
// {
//     // if (task_id < tasks.size()) {
//     //     tasks.erase(tasks.begin() + task_id);
//     // }
// }

void TaskList::deleteTask(Task *task)
{
    tasks.remove(task);
    delete task;
}

TaskList TaskList::filterFromDate(QDate start)
{
    TaskList filtred;
    for(auto task: tasks){
        if(!task->getDate().isNull() || task->getDate()>= start)
            filtred.addTask(task);
    }
    return filtred;
}

TaskList TaskList::filterToDate(QDate finish)
{
    TaskList filtred;
    for(auto task: tasks)
        if(!task->getDate().isNull() || task->getDate()<= finish)
            filtred.addTask(task);
    return filtred;
}

TaskList TaskList::filterByState(State state)
{
    TaskList filtred;
    for(auto task: tasks)
        if(task->getState() == state)
            filtred.addTask(task);
    return filtred;
}

TaskList TaskList::filterByName(QString pattern)
{
    QStringList words = pattern.split(' ');
    TaskList filtred;
    for(auto task: tasks){
        bool accepted = true;
        for(auto word: words)
            accepted &= task->getTaskName().contains(word,Qt::CaseInsensitive);
        if(accepted)
            filtred.addTask(task);
    }
    return filtred;
}

TaskList TaskList::filterByDescription(QString pattern)
{
    QStringList words = pattern.split(' ');
    TaskList filtred;
    for(auto task: tasks){
        bool accepted = true;
        for(auto word: words)
            accepted &= task->getDescription().contains(word,Qt::CaseInsensitive);
        if(accepted)
            filtred.addTask(task);
    }
    return filtred;
}



// void TaskList::editTask(int task_id, const QString& task_name, const QDate& date, const QString& description, const State state)
// {
//     tasks[task_id]->setTaskName(task_name);
//     tasks[task_id]->setDate(date);
//     tasks[task_id]->setDescription(description);
//     tasks[task_id]->setState(state);
// }

// void TaskList::setState(int task_id, const State state)
// {
//     (*tasks[task_id]).setState(state);
// }

QSet<Task*>::iterator begin(TaskList &x){return x.tasks.begin();}

QSet<Task*>::iterator end(TaskList &x){return x.tasks.end();}
