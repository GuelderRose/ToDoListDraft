#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QListWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QInputDialog>

#include "taskwidget.h"
#include "task.h"
#include "tasklist.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void on_add_task_button_clicked();
private:
    QListWidget *task_widget_list;
    TaskList *task_list;
    QPushButton *add_task_button;
};
#endif // MAINWIDGET_H
