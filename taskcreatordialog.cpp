#include "taskcreatordialog.h"


TaskCreatorDialog::TaskCreatorDialog(QWidget* parent, Task task):
    default_task(task) {

    this->move(parent->pos().x()+35,parent->pos().y());

    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);


    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->setSelectedDate(default_task.getDate());
    vBoxLayout->addWidget(calendarWidget);
    vBoxLayout->addSpacing(5);


    taskNameLabel = new QLabel(this);
    taskNameLabel->setFrameStyle(QFrame::Sunken);
    taskNameLabel->setText("Task name:");
    vBoxLayout->addWidget(taskNameLabel);

    taskNameEdit = new QLineEdit(this);
    taskNameEdit->setText(default_task.getTaskName());
    vBoxLayout->addWidget(taskNameEdit);
    vBoxLayout->addSpacing(5);


    taskDescriptionLabel = new QLabel(this);
    taskDescriptionLabel->setFrameStyle(QFrame::Sunken);
    taskDescriptionLabel->setText("Task description:");
    vBoxLayout->addWidget(taskDescriptionLabel);

    taskDescriptionEdit = new QLineEdit(this);
    taskDescriptionEdit->setText(default_task.getDescription());
    vBoxLayout->addWidget(taskDescriptionEdit);
    vBoxLayout->addSpacing(5);


    taskStateLabel = new QLabel(this);
    taskStateLabel->setFrameStyle(QFrame::Sunken);
    taskStateLabel->setText("Task state:");
    vBoxLayout->addWidget(taskStateLabel);

    taskStateEdit = new QComboBox(this);
    taskStateEdit->addItems({"In Progress", "Done"});
    taskStateEdit->setCurrentIndex((int)default_task.getState());
    vBoxLayout->addWidget(taskStateEdit);
    vBoxLayout->addSpacing(10);


    QHBoxLayout* bottomSection = new QHBoxLayout(this);

    QPushButton* okButton = new QPushButton(this);
    okButton->setText("OK");
    bottomSection->addWidget(okButton);

    QPushButton* cancelButton = new QPushButton(this);
    cancelButton->setText("Cancel");
    bottomSection->addWidget(cancelButton);


    vBoxLayout->addLayout(bottomSection);
    setLayout(vBoxLayout);
    setWindowTitle("Task editor");




    connect(taskNameEdit, &QLineEdit::textChanged,
            this,  &TaskCreatorDialog::taskNameChanged);
    connect(taskDescriptionEdit, &QLineEdit::textChanged,
            this,  &TaskCreatorDialog::taskDescriptionChanged);
    connect(taskStateEdit, &QComboBox::currentIndexChanged,
            this,  &TaskCreatorDialog::taskStateChanged);
    connect(calendarWidget, &QCalendarWidget::clicked,
            this,  &TaskCreatorDialog::taskDateChanged);
    connect(okButton, &QPushButton::clicked,
            this,  &TaskCreatorDialog::okButtonClicked);
    connect(cancelButton, &QPushButton::clicked,
            this,  &QDialog::reject);
}

QVariant TaskCreatorDialog::getTask(Task task, QWidget *parent){
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
        QMessageBox msgBox = QMessageBox(QMessageBox::Warning, "Warning",  "Task name is empty!",QMessageBox::Ok,this);
        QIcon icon = QIcon();
        icon.addPixmap(QPixmap("Warning"), QIcon::Normal);
        msgBox.setWindowIcon(icon);
        msgBox.move(this->pos().x()+62,this->pos().y()+200);
        msgBox.exec();
    }
}
