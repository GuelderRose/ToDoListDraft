#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    task_list = new TaskList();

    QVBoxLayout *v_box = new QVBoxLayout(this);

    task_widget_list = new QListWidget(this);
    task_widget_list->setMinimumSize(QSize(300,460));
    task_widget_list->setSpacing(10);

    add_task_button = new QPushButton("Добавить задачу",this);
    add_task_button->setMinimumSize(QSize(340,50));

    v_box->addWidget(task_widget_list);
    v_box->addWidget(add_task_button);


    connect(add_task_button, &QPushButton::clicked, this,&MainWidget::on_add_task_button_clicked);
}

MainWidget::~MainWidget() {}

void MainWidget::on_add_task_button_clicked()
{
    //auto newTaskWindow = new NewTaskWindow(parent, task_ptr)
    //connect(signal from window after closing)
    //OR
    //Task updTask = new CustomInputDialog::getTask(this, task_ptr)
    QString c_text = QInputDialog::getText(this,"Item","Enter new item");
    //Task* returned_task = new Task();

    //task_widget_list->addItem("New String");
    QString huy = "";
    int task_list_size=task_list->size();
    for(int i = 0; i < 2 + task_list_size; i++)
        huy += "kjasfk jdsaksf jsdhfk jsjkfd jsdjh kjsfk ksjdhfks djhfjks kdhfkjs dhfkjsd jkdfhsk jdfhskjdf kjsdfhj sdhfksd kdfhkjs dhfksjdf kdfhskjd fhkjsf";

    Task *new_task=new Task("Task Name" + QString::number(task_list_size), QDate(), huy);
    task_list->addTask(new_task);

    QListWidgetItem *item = new QListWidgetItem;

    TaskWidget *new_task_widget = new TaskWidget(new_task);
    item->setSizeHint(new_task_widget->sizeHint());
    task_widget_list->addItem(item);
    //item->setSizeHint(QSize(0,80));
    task_widget_list->setItemWidget(item,new_task_widget);
}

