#ifndef TASKCREATORDIALOG_H
#define TASKCREATORDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

#include "task.h"


class TaskCreatorDialog : public QDialog
{
    Q_OBJECT
public:
    TaskCreatorDialog(QWidget* parent=nullptr, Task task = Task());

    static QVariant getTask(Task task, QWidget *parent);

public slots:
    void taskNameChanged(const QString &text);
    void taskDescriptionChanged(const QString &text);
    void taskStateChanged(int idx);
    void taskDateChanged(QDate date);
    void okButtonClicked();

private:
    Task default_task;
    QCalendarWidget* calendarWidget;
    QLabel *taskNameLabel;
    QLineEdit* taskNameEdit;
    QLabel *taskDescriptionLabel;
    QLineEdit* taskDescriptionEdit;
    QLabel *taskStateLabel;
    QComboBox* taskStateEdit;
};

#endif // TASKCREATORDIALOG_H
