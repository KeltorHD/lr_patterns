#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <vector>
#include <QFile>

#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct user
{
    QString name;
    QString email;
    QString passw;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_to_registration_clicked();

    void on_to_login_clicked();

    void on_register_2_clicked();

    void on_login_2_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_del_clicked();

    void on_edit_clicked();

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
    QValidator *fio_validator;
    QValidator *email_validator;
    Dialog* dialog;
    std::vector<user> users;
    int cur_item;
    int edit_item;

    enum class screen
    {
        registration = 0,
        login = 1,
        user = 2,
        admin = 3
    };

    void update_list();
    void enable_right(bool enable);
    void enable_down(bool enable);
};
#endif // MAINWINDOW_H
