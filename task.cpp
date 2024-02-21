#include "task.h"

Task::Task():state(State::InProgress)
{}

Task::Task(QString task_name)
    :task_name(task_name), date(), description(""), state(State::InProgress)
{
}

Task::Task(QString task_name, QDate date) :Task(task_name)
{
    this->date = date;
}

Task::Task(QString task_name, QDate date, QString description) :Task(task_name, date)
{
    this->description = description;
}

Task::Task(QString task_name, QString description) :Task(task_name)
{
    this->description = description;
}

const QString& Task::getTaskName() const
{
    return task_name;
}

const QDate& Task::getDate() const
{
    return date;
}

const QString& Task::getDescription()const
{
    return description;
}

State Task::getState() const
{
    return state;
}

void Task::setTaskName(const QString& task_name)
{
    this->task_name = task_name;
}

void Task::setDate(const QDate& date)
{
    this->date = date;
}

void Task::setDescription(const QString& description)
{
    this->description = description;
}

void Task::setState(State state)
{
    this->state = state;
}

void Task::changeState()
{
    if(this->state == State::Done)
        state = State::InProgress;
    else
        state = State::Done;
}
