#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), task_list()
{
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

void MainWidget::addTask(Task* task){

    task_list.addTask(task);
    TaskWidget *new_task_widget = new TaskWidget(task,this);
    drawNewTaskWidget(task, new_task_widget);
    showed_tasks.emplace_back(new_task_widget, task);

}

Task* MainWidget::getCorrespondingTask(TaskWidget * task_widget){
    for(int i = 0; i < showed_tasks.size();i++)
        if(showed_tasks[i].first == task_widget)
            return showed_tasks[i].second;
    return nullptr;
}

void MainWidget::on_add_task_button_clicked()
{
    Task* new_task = new Task();
    QVariant updated_task = TaskCreatorDialog::getTask(*new_task);
    if (updated_task.isValid())
    {
        *new_task = updated_task.value<Task>();
        addTask(new_task);
    }
    else
        delete new_task;
}

void MainWidget::on_delete_widget_button_clicked(TaskWidget *task_widget)
{
    removeTask(task_widget);
}

void MainWidget::on_check_box_clicked(TaskWidget *task_widget)
{
    Task* task = getCorrespondingTask(task_widget);
    task->changeState();
}

void MainWidget::on_edit_widget_button_clicked(TaskWidget *task_widget)
{
    Task* task = getCorrespondingTask(task_widget);
    QVariant updated_task = TaskCreatorDialog::getTask(*task);
    if (updated_task.isValid())
    {
        *task = updated_task.value<Task>();
        task_widget->updateView(task);
        updateTaskWidgetList();
    }
}

void MainWidget::removeTask(TaskWidget *task_widget)
{
    Task* task = getCorrespondingTask(task_widget);
    for (int row = 0; row < task_widget_list->count(); row++)
    {
        QListWidgetItem *item = task_widget_list->item(row);
        if(task_widget_list->itemWidget(item) == task_widget)
        {
            for(int i = 0; i < showed_tasks.size();i++)
                if(showed_tasks[i].first == task_widget)
                {
                    showed_tasks.erase(showed_tasks.begin() + i);
                }
            task_widget_list->takeItem(row);
            break;
        }
    }
    task_list.deleteTask(task);
}

void MainWidget::updateTaskWidgetList() // Redraw all tasks from current existing tasks
{
    task_widget_list->clear();
    QVector<std::pair<TaskWidget*, Task*>> new_view;
    for(auto task_item: showed_tasks){
        TaskWidget* new_task_widget = new TaskWidget(task_item.second, this);
        drawNewTaskWidget(task_item.second, new_task_widget);
        new_view.emplace_back(new_task_widget, task_item.second);
    }
    showed_tasks = std::move(new_view);
}

void MainWidget::initTaskWidgetList(TaskList& tasks) //Draw whole list of tasks from TaskList. Use for filtred/loaded view
{
    task_widget_list->clear();
    showed_tasks.clear();
    for(Task* task: tasks)
    {
        TaskWidget* new_task_widget = new TaskWidget(task, this);
        drawNewTaskWidget(task, new_task_widget);
        showed_tasks.emplace_back(new_task_widget, task);
    }
}


void MainWidget::drawNewTaskWidget(Task *task, TaskWidget *task_widget)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(task_widget->sizeHint());

    task_widget_list->addItem(item);
    task_widget_list->setItemWidget(item,task_widget);

    connect(task_widget, &TaskWidget::task_deleted, this, &MainWidget::on_delete_widget_button_clicked);
    connect(task_widget, &TaskWidget::task_edited, this, &MainWidget::on_edit_widget_button_clicked);
    connect(task_widget, &TaskWidget::task_changed, this, &MainWidget::on_check_box_clicked);
}

