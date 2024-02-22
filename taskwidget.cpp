#include "taskcreatordialog.h"
#include "taskwidget.h"

TaskWidget::TaskWidget(QWidget *parent)
    : QWidget{parent}
{
}

TaskWidget::TaskWidget(const Task *task, QWidget *parent): QWidget{parent}
{
    h_box = new QHBoxLayout(this);

    // Adding options menu

    v_option_box = new QVBoxLayout();
    v_option_box->setSpacing(10);

    check_box = new QCheckBox(this);
    check_box->setStyleSheet("QCheckBox::indicator { width: 15px; height: 20px;}");

    if (task->getState() == State::Done)
        check_box->setCheckState(Qt::CheckState::Checked);
    else
        check_box->setCheckState(Qt::CheckState::Unchecked);

    v_option_box->addWidget(check_box);

    delete_button = new QPushButton(this);
    delete_button->setFixedSize(QSize(25,25));
    delete_icon = QPixmap ("icons/delete.png");
    delete_button->setIcon(delete_icon);
    v_option_box->addWidget(delete_button);

    edit_button = new QPushButton(this);
    edit_button->setFixedSize(QSize(25,25));
    edit_icon = QPixmap("icons/edit.png");
    edit_button->setIcon(edit_icon);
    v_option_box->addWidget(edit_button);

    // Adding task texts and date

    v_label_box = new QVBoxLayout();

    task_name=new QLabel(this);
    task_name->setText(task->getTaskName());
    task_name->setWordWrap(true);
    v_label_box->addWidget(task_name);

    task_date=new QLabel(this);
    task_date->setText(task->getDate().toString("dd.MM.yyyy"));
    v_label_box->addWidget(task_date);

    task_description = new QLabel(this);
    task_description->setWordWrap(true);
    task_description->setText(task->getDescription());
    v_label_box->addWidget(task_description);

    h_box->addLayout(v_option_box);
    h_box->addLayout(v_label_box);
    h_box->setAlignment(Qt::AlignLeft);
    h_box->insertSpacing(1,15);

    // Setting color for task widgets

    if(task->getState()==State::InProgress)
    {
        QPalette pal = QPalette();
        pal.setColor(QPalette::Base, QColor::fromRgb(210,255,255));
        this->setAutoFillBackground(true);
        this->setPalette(pal);

    } else {

        QPalette pal = QPalette();
        pal.setColor(QPalette::Base, QColor::fromRgb(200,255,200));
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    }


    connect(delete_button, &QPushButton::clicked, this, &TaskWidget::onDeleteButtonClicked);
    connect(edit_button, &QPushButton::clicked, this, &TaskWidget::onEditButtonClicked);
    connect(check_box, &QCheckBox::clicked, this, &TaskWidget::onCheckBoxClicked);
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

void TaskWidget::changeTaskState()
{
    if (check_box->isChecked())
        check_box->setCheckState(Qt::CheckState::Unchecked);
    else
        check_box->setCheckState(Qt::CheckState::Checked);
}

void TaskWidget::onDeleteButtonClicked()
{
    emit taskDeleted(this);
}

void TaskWidget::onEditButtonClicked()
{
    emit taskEdited(this);
}

void TaskWidget::onCheckBoxClicked()
{
    emit taskChanged(this);
}
