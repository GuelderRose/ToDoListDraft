#include "taskwidget.h"

TaskWidget::TaskWidget(QWidget *parent)
    : QWidget{parent}
{
    QLabel *label=new QLabel(this);
    label->setText("Hi from TaskWidget");
    label->setGeometry(10,10,300,20);

    QPushButton *but=new QPushButton(this);
    but->setText("button from TaskWidget");
    but->setGeometry(10,40,300,30);

    Task *new_task = new Task("Task name");
    QLabel *task_name=new QLabel(this);
    task_name->setText(new_task->getTaskName());

}

TaskWidget::TaskWidget(const Task *task, QWidget *parent)
{
    QHBoxLayout *h_box = new QHBoxLayout(this);
    h_box->setContentsMargins(20,0,0,0);

    QCheckBox *check_box = new QCheckBox(this);
    check_box->setFixedSize(QSize(15,15));
    h_box->addWidget(check_box);


    QVBoxLayout *v_label_box = new QVBoxLayout();
    v_label_box->setSpacing(5);

    QLabel *task_name=new QLabel(this);
    task_name->setText(task->getTaskName());
    task_name->setWordWrap(true);
    v_label_box->addWidget(task_name);

    QLabel *task_date=new QLabel(this);
    //task_date->setText(task->getDate().toString());
    task_date->setText("15.05.2015");
    v_label_box->addWidget(task_date);

    QLabel *task_description = new QLabel(this);
    task_description->setWordWrap(true);
    task_description->setText(task->getDescription());
    v_label_box->addWidget(task_description);




    h_box->addLayout(v_label_box);
    h_box->insertSpacing(1,15);

    setLayout(h_box);

    //adjustSize();
}

QSize TaskWidget::sizeHint() const
{
    auto res = this->QWidget::sizeHint();
    return res;
}
