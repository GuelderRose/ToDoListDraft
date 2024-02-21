#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QListWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QInputDialog>
#include<QVector>
#include <QDateEdit>
#include <QLineEdit>
#include<QPixmap>
#include <QJsonDocument>
#include <QFile>
#include <QFileInfo>

#include "taskwidget.h"
#include "task.h"
#include "tasklist.h"
#include "taskcreatordialog.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_add_task_button_clicked();
    void on_delete_widget_button_clicked(TaskWidget* task_widget);
    void on_edit_widget_button_clicked(TaskWidget *task_widget);
    void on_check_box_clicked(TaskWidget *task_widget);

    void redrawView();
    void resetFilters();
private:
    void saveTasks();
    void addTask(Task*);
    void removeTask(TaskWidget* task);
    void updateTaskWidgetList();
    void initTaskWidgetList(TaskList& tasks);
    void drawNewTaskWidget(Task* task, TaskWidget* task_widget);
    Task *getCorrespondingTask(TaskWidget *task_widget);

    QLabel *filter_label;
    QLabel *state_filter_label;
    QLabel *date_filter_label;
    QLabel *name_filter_label;
    QLabel *desc_filter_label;
    QLineEdit *search_by_name_line;
    QLineEdit *search_by_desc_line;
    QPushButton *reset_all_filters_button;
    QPixmap reset_filters_icon;
    QComboBox *task_state_filter;
    QDateEdit *left_date_edit;
    QDateEdit *right_date_edit;
    TaskList full_task_list;
    TaskList showed_task_list;
    QListWidget *task_widget_list;
    QVector<std::pair<TaskWidget*, Task*>> showed_tasks;
    QPushButton *add_task_button;
    void updateFiltredTaskList();
    std::pair<QDate, QDate> getDefaultDatesForFilterWidget();
    TaskList loadTasks();
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWIDGET_H
