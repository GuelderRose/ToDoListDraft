#include "tasklist.h"

TaskList::TaskList()
{
}

void TaskList::addTask(Task* new_task)
{
    tasks.push_back(new_task);
}

void TaskList::deleteTask(Task *task)
{
    for(int i = 0; i < tasks.size(); i++)
        if(tasks[i] == task)
            tasks.erase(tasks.begin() + i);
    delete task;
}

TaskList TaskList::filterFromDate(QDate start) const
{
    TaskList filtred;
    for(auto task: tasks){
        if(task->getDate().isNull() || task->getDate()>= start)
            filtred.addTask(task);
    }
    return filtred;
}

TaskList TaskList::filterToDate(QDate finish)const
{
    TaskList filtred;
    for(auto task: tasks)
        if(task->getDate().isNull() || task->getDate()<= finish)
            filtred.addTask(task);
    return filtred;
}

TaskList TaskList::filterByState(State state) const
{
    TaskList filtred;
    for(auto task: tasks)
        if(task->getState() == state)
            filtred.addTask(task);
    return filtred;
}

TaskList TaskList::filterByName(QString pattern) const
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

TaskList TaskList::filterByDescription(QString pattern) const
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

QJsonArray TaskList::convertToJson() const
{
    QJsonArray taskListJson;
    for(const auto* task: tasks)
        taskListJson.push_back(task->convertToJson());
    return taskListJson;
}

TaskList TaskList::createFromJson(QJsonArray json)
{
    TaskList result;
    for(auto task_json: json){
        if(!task_json.isObject())
            return TaskList();
        Task* task = Task::createFromJson(task_json.toObject());
        if(task)
            result.addTask(task);
        else
            return TaskList();
    }
    return result;
}

QDate TaskList::getMinDate() const
{
    QDate minDate = QDate();
    for(auto* task: tasks){
        if(task->getDate().isValid()){
            if (minDate.isNull() || task->getDate() < minDate)
                minDate = task->getDate();
        }
    }
    return minDate;
}

QDate TaskList::getMaxDate() const
{
    QDate maxDate = QDate();
    for(auto* task: tasks){
        if(task->getDate().isValid()){
            if (maxDate.isNull() || task->getDate() > maxDate)
                maxDate = task->getDate();
        }
    }
    return maxDate;
}

QVector<Task*>::iterator begin(TaskList &x){return x.tasks.begin();}

QVector<Task*>::iterator end(TaskList &x){return x.tasks.end();}
