#include "taskwidget.h"
#include "taskcreatordialog.h"

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

TaskWidget::TaskWidget(const Task *task, QWidget *parent): QWidget{parent}
{
    h_box = new QHBoxLayout(this);
    h_box->setContentsMargins(20,0,0,0);



    v_option_box = new QVBoxLayout();
    v_option_box->setSpacing(10);

    check_box = new QCheckBox(this);
    if(task->getState() == State::Done)
        check_box->setCheckState(Qt::CheckState::Checked);
    else
        check_box->setCheckState(Qt::CheckState::Unchecked);
    v_option_box->addWidget(check_box);

    delete_button = new QPushButton(this);
    delete_button->setFixedSize(QSize(25,25));
    //icon = QPixmap(QCoreApplication::applicationDirPath()+"/delete.png");
    icon = QPixmap ("C:/qt projects/ToDoList2/delete.png");
    delete_button->setIcon(icon);
    v_option_box->addWidget(delete_button);

    edit_button = new QPushButton(this);
    edit_button->setFixedSize(QSize(25,25));
    //icon = QPixmap(QCoreApplication::applicationDirPath()+"/delete.png");
    //icon = QPixmap ("C:/qt projects/ToDoList2/delete.png");
    //edit_button->setIcon(icon);
    edit_button->setText("X");
    v_option_box->addWidget(edit_button);

    v_label_box = new QVBoxLayout();
    v_label_box->setSpacing(5);

    task_name=new QLabel(this);
    task_name->setText(task->getTaskName());
    task_name->setWordWrap(true);
    v_label_box->addWidget(task_name);

    task_date=new QLabel(this);
    task_date->setText(task->getDate().toString());
    v_label_box->addWidget(task_date);

    task_description = new QLabel(this);
    task_description->setWordWrap(true);
    task_description->setText(task->getDescription());
    v_label_box->addWidget(task_description);


    h_box->addLayout(v_option_box);
    h_box->addLayout(v_label_box);
    h_box->insertSpacing(1,15);

    setLayout(h_box);

    connect(delete_button, &QPushButton::clicked, this, &TaskWidget::on_delete_button_clicked);
    connect(edit_button, &QPushButton::clicked, this, &TaskWidget::on_edit_button_clicked);
    connect(check_box, &QCheckBox::clicked, this, &TaskWidget::on_check_box_clicked);
}


void TaskWidget::updateView(const Task *task)
{
    task_date->setText(task->getDate().toString());
    task_name->setText(task->getTaskName());
    task_description->setText(task->getDescription());
    if(task->getState() == State::Done)
        check_box->setCheckState(Qt::CheckState::Checked);
    else
        check_box->setCheckState(Qt::CheckState::Unchecked);
}

void TaskWidget::changeTaskState(){
    if (check_box->isChecked())
        check_box->setCheckState(Qt::CheckState::Unchecked);
    else
        check_box->setCheckState(Qt::CheckState::Checked);
}

void TaskWidget::on_delete_button_clicked()
{
    emit task_deleted(this);
}

void TaskWidget::on_edit_button_clicked()
{
    emit task_edited(this);
}

void TaskWidget::on_check_box_clicked()
{
    emit task_changed(this);
}
