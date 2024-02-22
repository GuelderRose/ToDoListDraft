#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QCheckBox>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <QPalette>

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
    void taskDeleted(TaskWidget* task);
    void taskChanged(TaskWidget* task);
    void taskEdited(TaskWidget* task);

private slots:
    void onDeleteButtonClicked();
    void onEditButtonClicked();
    void onCheckBoxClicked();

private:
    QFrame *task_frame;
    QHBoxLayout *h_box;

    QVBoxLayout *v_option_box;
    QCheckBox *check_box;
    QPushButton *delete_button;
    QPushButton *edit_button;
    QPixmap delete_icon;
    QPixmap edit_icon;

    QVBoxLayout *v_label_box;
    QLabel *task_name;
    QLabel *task_date;
    QLabel *task_description;
};

#endif // TASKWIDGET_H
