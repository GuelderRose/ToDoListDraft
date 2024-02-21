#ifndef TASKCREATORDIALOG_H
#define TASKCREATORDIALOG_H

#include <QDialog>
#include <QVariant>
#include "task.h"


class TaskCreatorDialog : public QDialog
{
    Q_OBJECT
public:
    TaskCreatorDialog(QWidget* parent=nullptr, Task task = Task());

    static QVariant getTask(Task task);
public slots:
    void taskNameChanged(const QString &text);
    void taskDescriptionChanged(const QString &text);
    void taskStateChanged(int idx);
    void taskDateChanged(QDate date);
    void okButtonClicked();

private:
    Task default_task;
};

#endif // TASKCREATORDIALOG_H
