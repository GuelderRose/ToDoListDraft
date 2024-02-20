#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>

#include "task.h"

class TaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr);
    TaskWidget(const Task* task, QWidget *parent = nullptr);
    QSize sizeHint() const override;
signals:

private slots:
    //void on_checkBox_selected();
};

#endif // TASKWIDGET_H
