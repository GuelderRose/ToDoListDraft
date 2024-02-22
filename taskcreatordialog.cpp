#include "taskcreatordialog.h"


TaskCreatorDialog::TaskCreatorDialog(QWidget* parent, Task task):
    default_task(task)
{
    this->move(parent->pos().x()+35,parent->pos().y());

    QVBoxLayout* v_box = new QVBoxLayout(this);

    // Adding calendar

    calendar_widget = new QCalendarWidget(this);
    calendar_widget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar_widget->setSelectedDate(default_task.getDate());
    v_box->addWidget(calendar_widget);
    v_box->addSpacing(5);

    // Adding task name

    task_name_label = new QLabel(this);
    task_name_label->setFrameStyle(QFrame::Sunken);
    task_name_label->setText("Task name:");
    v_box->addWidget(task_name_label);

    task_name_edit = new QLineEdit(this);
    task_name_edit->setText(default_task.getTaskName());
    v_box->addWidget(task_name_edit);
    v_box->addSpacing(5);

    // Adding task description

    task_description_label = new QLabel(this);
    task_description_label->setFrameStyle(QFrame::Sunken);
    task_description_label->setText("Task description:");
    v_box->addWidget(task_description_label);

    task_description_edit = new QLineEdit(this);
    task_description_edit->setText(default_task.getDescription());
    v_box->addWidget(task_description_edit);
    v_box->addSpacing(5);

    // Adding task state

    task_state_label = new QLabel(this);
    task_state_label->setFrameStyle(QFrame::Sunken);
    task_state_label->setText("Task state:");
    v_box->addWidget(task_state_label);

    task_state_edit = new QComboBox(this);
    task_state_edit->addItems({"In Progress", "Done"});
    task_state_edit->setCurrentIndex((int)default_task.getState());
    v_box->addWidget(task_state_edit);
    v_box->addSpacing(10);

    // Adding buttons

    QHBoxLayout* h_bottom = new QHBoxLayout(this);

    ok_button = new QPushButton(this);
    ok_button->setText("OK");
    h_bottom->addWidget(ok_button);

    cancel_button = new QPushButton(this);
    cancel_button->setText("Cancel");
    h_bottom->addWidget(cancel_button);


    v_box->addLayout(h_bottom);
    setLayout(v_box);
    setWindowTitle("Task editor");



    connect(task_name_edit, &QLineEdit::textChanged,
            this,  &TaskCreatorDialog::taskNameChanged);
    connect(task_description_edit, &QLineEdit::textChanged,
            this,  &TaskCreatorDialog::taskDescriptionChanged);
    connect(task_state_edit, &QComboBox::currentIndexChanged,
            this,  &TaskCreatorDialog::taskStateChanged);
    connect(calendar_widget, &QCalendarWidget::clicked,
            this,  &TaskCreatorDialog::taskDateChanged);
    connect(ok_button, &QPushButton::clicked,
            this,  &TaskCreatorDialog::okButtonClicked);
    connect(cancel_button, &QPushButton::clicked,
            this,  &QDialog::reject);
}

QVariant TaskCreatorDialog::getTask(Task task, QWidget *parent)
{
    TaskCreatorDialog dlg = TaskCreatorDialog(parent, task);
    dlg.setModal(true);
    if (dlg.exec())
        return QVariant::fromValue<Task>(dlg.default_task);
    return QVariant{};
}

void TaskCreatorDialog::taskNameChanged(const QString &text)
{
    default_task.setTaskName(text);
}

void TaskCreatorDialog::taskDescriptionChanged(const QString &text)
{
    default_task.setDescription(text);
}

void TaskCreatorDialog::taskStateChanged(int idx)
{
    default_task.setState(State(idx));
}

void TaskCreatorDialog::taskDateChanged(QDate date)
{
    default_task.setDate(date);
}

void TaskCreatorDialog::okButtonClicked()
{
    if (default_task.getTaskName().size())
        this->accept();
    else
    {
        QMessageBox msg_box = QMessageBox(QMessageBox::Warning, "Warning",
                                          "Task name is empty!",QMessageBox::Ok,this);
        QIcon icon = QIcon();
        icon.addPixmap(QPixmap("Warning"), QIcon::Normal);
        msg_box.setWindowIcon(icon);
        msg_box.move(this->pos().x()+62,this->pos().y()+200);
        msg_box.exec();
    }
}
