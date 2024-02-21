#include "mainwidget.h"

namespace {
const QString TASKS_JSON_PATH = "tasks.json";
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), full_task_list(loadTasks()), showed_task_list()
{
    QVBoxLayout *v_box = new QVBoxLayout(this);

    filter_label=new QLabel(this);
    filter_label->setText("Filters:");


    // Adding filters

    QHBoxLayout *h_filter_box = new QHBoxLayout();

    QHBoxLayout *h_state_date_box = new QHBoxLayout();

    // ----- Adding state filter

    QVBoxLayout *v_state_box = new QVBoxLayout();

    state_filter_label=new QLabel("State:");
    v_state_box->addWidget(state_filter_label);

    task_state_filter = new QComboBox();
    task_state_filter->addItems({"In Progress", "Done", "All"});
    task_state_filter->setCurrentIndex(0);
    v_state_box->addWidget(task_state_filter);
    v_state_box->setAlignment(Qt::AlignTop);

    // ----- Adding date filter

    QVBoxLayout *v_date_box = new QVBoxLayout();

    date_filter_label=new QLabel("Dates:");
    v_date_box->addWidget(date_filter_label);

    QHBoxLayout *h_dates_box = new QHBoxLayout();
    auto dates = getDefaultDatesForFilterWidget();
    left_date_edit = new QDateEdit(QDate());
    left_date_edit->setCalendarPopup(true);
    left_date_edit->setDate(dates.first);
    left_date_edit->setMinimumWidth(90);
    h_dates_box->addWidget(left_date_edit);

    right_date_edit = new QDateEdit(QDate());
    right_date_edit->setCalendarPopup(true);
    right_date_edit->setDate(dates.second);
    right_date_edit->setMinimumWidth(90);
    connect(left_date_edit,&QDateEdit::dateChanged,[&](const QDate &date){
        right_date_edit->setMinimumDate(date);
    });
    connect(right_date_edit,&QDateEdit::dateChanged,[&](const QDate &date){
        left_date_edit->setMaximumDate(date);
    });
    h_dates_box->addWidget(right_date_edit);

    v_date_box->addLayout(h_dates_box);
    v_date_box->setAlignment(Qt::AlignTop);

    h_state_date_box->addLayout(v_state_box);
    h_state_date_box->addLayout(v_date_box);

    // ----- Adding by name filter

    QHBoxLayout *h_name_desc_box = new QHBoxLayout();

    QVBoxLayout *v_name_box = new QVBoxLayout();

    name_filter_label = new QLabel("By name:");
    v_name_box->addWidget(name_filter_label);

    search_by_name_line = new QLineEdit();
    search_by_name_line->setMaximumWidth(150);
    v_name_box->addWidget(search_by_name_line);

    // ----- Adding by description filter

    QVBoxLayout *v_desc_box = new QVBoxLayout();

    desc_filter_label = new QLabel("By description:");
    v_desc_box->addWidget(desc_filter_label);

    search_by_desc_line = new QLineEdit();
    search_by_desc_line->setMaximumWidth(180);
    v_desc_box->addWidget(search_by_desc_line);


    h_name_desc_box->addLayout(v_name_box);
    h_name_desc_box->addLayout(v_desc_box);


    QVBoxLayout *v_filter_box = new QVBoxLayout();
    v_filter_box->addLayout(h_state_date_box);
    v_filter_box->addLayout(h_name_desc_box);
    v_filter_box->setAlignment(Qt::AlignLeft);


    // ----- Adding reset button

    reset_all_filters_button = new QPushButton(this);
    reset_filters_icon = QPixmap("icons/reset_filters.png");
    reset_all_filters_button->setIcon(reset_filters_icon);


    h_filter_box->addLayout(v_filter_box);
    h_filter_box->addWidget(reset_all_filters_button);


    // Adding task widget list

    task_widget_list = new QListWidget(this);
    task_widget_list->setMinimumSize(QSize(300,420));
    task_widget_list->setSpacing(10);
    initTaskWidgetList(showed_task_list);
    // Adding add task button

    add_task_button = new QPushButton("Add task",this);
    //add_task_button->setMinimumSize(QSize(340,50));

    v_box->addWidget(filter_label);
    v_box->addLayout(h_filter_box);
    v_box->addWidget(task_widget_list);
    v_box->addWidget(add_task_button);

    setLayout(v_box);

    connect(add_task_button, &QPushButton::clicked, this,&MainWidget::on_add_task_button_clicked);

    connect(search_by_name_line, &QLineEdit::textChanged, this, &MainWidget::redrawView);
    connect(search_by_desc_line, &QLineEdit::textChanged, this, &MainWidget::redrawView);
    connect(task_state_filter, &QComboBox::currentIndexChanged, this, &MainWidget::redrawView);
    connect(left_date_edit, &QDateEdit::dateChanged, this, &MainWidget::redrawView);
    connect(right_date_edit, &QDateEdit::dateChanged, this, &MainWidget::redrawView);

    connect(reset_all_filters_button, &QPushButton::clicked, this, &MainWidget::resetFilters);

    redrawView();
}

MainWidget::~MainWidget() {}

std::pair<QDate, QDate> MainWidget::getDefaultDatesForFilterWidget(){
    std::pair<QDate, QDate> res = {full_task_list.getMinDate(), full_task_list.getMaxDate()};
    if(res.first.isValid())
        return res;
    return {QDate::currentDate(), QDate::currentDate()};
}

void MainWidget::redrawView(){
    updateFiltredTaskList();
    initTaskWidgetList(showed_task_list);
}

void MainWidget::resetFilters(){
    task_state_filter->setCurrentIndex(2);
    auto dates = getDefaultDatesForFilterWidget();
    left_date_edit->blockSignals(true);
    right_date_edit->blockSignals(true);
    left_date_edit->setDate(dates.first);
    right_date_edit->setDate(dates.second);
    left_date_edit->blockSignals(false);
    right_date_edit->blockSignals(false);
    search_by_name_line->clear();
    search_by_desc_line->clear();
    redrawView();
}

void MainWidget::saveTasks()
{
    QJsonArray tasksJson = full_task_list.convertToJson();
    QJsonDocument doc(tasksJson);
    QFile jsonFile(TASKS_JSON_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(doc.toJson());
}

TaskList MainWidget::loadTasks()
{
    if (QFileInfo::exists(TASKS_JSON_PATH) && QFileInfo(TASKS_JSON_PATH).isFile())
    {
        QFile jsonFile(TASKS_JSON_PATH);
        jsonFile.open(QFile::ReadOnly);
        QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
        if(doc.isArray())
            return TaskList::createFromJson(doc.array());
        return TaskList();
    }
    return TaskList();
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    saveTasks();
    QWidget::closeEvent(event);
}

void MainWidget::updateFiltredTaskList() {
    showed_task_list = full_task_list;
    showed_task_list = showed_task_list.filterByName(search_by_name_line->text());
    showed_task_list = showed_task_list.filterByDescription(search_by_desc_line->text());
    showed_task_list = showed_task_list.filterFromDate(left_date_edit->date());
    showed_task_list = showed_task_list.filterToDate(right_date_edit->date());
    if(task_state_filter->currentText() != "All")
        showed_task_list = showed_task_list.filterByState(State(task_state_filter->currentIndex()));
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
    QVariant updated_task = TaskCreatorDialog::getTask(*new_task, this);
    if (updated_task.isValid())
    {
        *new_task = updated_task.value<Task>();
        full_task_list.addTask(new_task);
        new_task->convertToJson();
        resetFilters();
        redrawView();
    }
    else
        delete new_task;
}

void MainWidget::on_delete_widget_button_clicked(TaskWidget *task_widget)
{
    Task* task = getCorrespondingTask(task_widget);
    full_task_list.deleteTask(task);
    redrawView();
}

void MainWidget::on_check_box_clicked(TaskWidget *task_widget)
{
    Task* task = getCorrespondingTask(task_widget);
    task->changeState();
    resetFilters();
    redrawView();
}

void MainWidget::on_edit_widget_button_clicked(TaskWidget *task_widget)
{
    Task* task = getCorrespondingTask(task_widget);
    QVariant updated_task = TaskCreatorDialog::getTask(*task, this);
    if (updated_task.isValid())
    {
        *task = updated_task.value<Task>();
        task->convertToJson();
        task_widget->updateView(task);
        redrawView();
    }
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

