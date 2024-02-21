#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPixmap>
#include <QCoreApplication>
#include <QListWidgetItem>


#include "task.h"


class TaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr);
    TaskWidget(const Task* task, QWidget *parent = nullptr);
    //QSize sizeHint() const override;
    void updateView(const Task * task);
    void changeTaskState();
signals:
    void task_deleted(TaskWidget* task);
    void task_changed(TaskWidget* task);
    void task_edited(TaskWidget* task);
private slots:
    void on_delete_button_clicked();
    void on_edit_button_clicked();
    void on_check_box_clicked();

private:
    QHBoxLayout *h_box;

    QVBoxLayout *v_option_box;
    QCheckBox *check_box;
    QPushButton *delete_button;
    QPushButton *edit_button;
    QPixmap icon;

    QVBoxLayout *v_label_box;
    QLabel *task_name;
    QLabel *task_date;
    QLabel *task_description;

};

#endif // TASKWIDGET_H
