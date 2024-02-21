#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QListWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QInputDialog>
#include<QVector>
#include "taskwidget.h"
#include "task.h"
#include "tasklist.h"
#include "taskcreatordialog.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void on_add_task_button_clicked();
    void on_delete_widget_button_clicked(TaskWidget* task_widget);
    void on_edit_widget_button_clicked(TaskWidget *task_widget);
    void on_check_box_clicked(TaskWidget *task_widget);
private:
    void addTask(Task*);
    QListWidget *task_widget_list;
    TaskList task_list;
    QVector<std::pair<TaskWidget*, Task*>> showed_tasks;
    QPushButton *add_task_button;
    void removeTask(TaskWidget* task);
    void updateTaskWidgetList();
    void initTaskWidgetList(TaskList& tasks);
    void drawNewTaskWidget(Task* task, TaskWidget* task_widget);
    Task *getCorrespondingTask(TaskWidget *task_widget);
};
#endif // MAINWIDGET_H
