#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "not open to read!";
    while(!file.atEnd())
    {
        QString name{file.readLine()};
        name = name.simplified();
        QString email{file.readLine()};
        email = email.simplified();
        QString passw{file.readLine()};
        passw = passw.simplified();
        this->users.push_back({name,email,passw});
    }
    file.close();

    this->ui->stackedWidget->setCurrentIndex((int)screen::registration);
    this->dialog = new Dialog(this);

    this->fio_validator = new QRegularExpressionValidator(QRegularExpression("[а-яА-я]+ [А-я]\\.[А-я]\\."), this);
    this->email_validator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+"), this);
    this->ui->fio->setValidator(this->fio_validator);
    this->ui->email->setValidator(this->email_validator);
}

MainWindow::~MainWindow()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "not open to write!";
    for (size_t i = 0; i < this->users.size(); i++)
    {
        file.write(QString(this->users[i].name + "\n").toUtf8());
        file.write(QString(this->users[i].email + "\n").toUtf8());
        file.write(QString(this->users[i].passw + "\n").toUtf8());
    }
    file.close();

    delete ui;
}

QString generate_password()
{
    QString res;
    for (size_t i = 0; i < 10; i++)
    {
        res+= QChar(rand() % (122 - 65 + 1) + 65);
    }
    return res;
}

void MainWindow::on_to_registration_clicked()
{
    this->ui->stackedWidget->setCurrentIndex((int)screen::registration);
}

void MainWindow::on_to_login_clicked()
{
    this->ui->stackedWidget->setCurrentIndex((int)screen::login);
}

void MainWindow::on_register_2_clicked()
{
    if (!this->ui->fio->text().size() || !this->ui->email->text().size())
    {
        this->dialog->set_text("Введите данные!");
        this->dialog->exec();
        return;
    }

    QRegularExpression fio("[а-яА-я]+ [А-я]\\.[А-я]\\.");
    QRegularExpression email("[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+");
    if (!fio.match(this->ui->fio->text()).hasMatch() || !email.match(this->ui->email->text()).hasMatch())
    {
        this->dialog->set_text("Некорректные данные!");
        this->dialog->exec();
        return;
    }

    for (size_t i = 0; i < this->users.size(); i++)
    {
        if (this->users[i].email == this->ui->email->text())
        {
            this->dialog->set_text("Такой пользователь уже существует!");
            this->dialog->exec();
            return;
        }
    }

    QString passw{generate_password()};
    this->dialog->set_text("Вы успешно зарегистрировались, ваш пароль:" + passw);
    this->dialog->exec();

    this->users.push_back({this->ui->fio->text(), this->ui->email->text(), passw});

    this->ui->stackedWidget->setCurrentIndex((int)screen::user);
}

void MainWindow::on_login_2_clicked()
{
    if (!this->ui->login_email->text().size() || !this->ui->login_password->text().size())
    {
        this->dialog->set_text("Введите данные!");
        this->dialog->exec();
        return;
    }

    if (this->ui->login_email->text() == "admin" && this->ui->login_password->text() == "admin")
    {
        this->update_list();
        this->ui->stackedWidget->setCurrentIndex((int)screen::admin);
        this->enable_down(false);
        this->enable_right(false);
        return;
    }

    QRegularExpression email("[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+");
    if (!email.match(this->ui->login_email->text()).hasMatch())
    {
        this->dialog->set_text("Некорректно введен email!");
        this->dialog->exec();
        return;
    }

    if (this->ui->login_password->text().size() != 10)
    {
        this->dialog->set_text("Некорректно введен пароль!");
        this->dialog->exec();
        return;
    }

    for (size_t i = 0; i < this->users.size(); i++)
    {
        if (this->users[i].email == this->ui->login_email->text())
        {
            if (this->users[i].passw == this->ui->login_password->text())
            {
                this->ui->stackedWidget->setCurrentIndex((int)screen::user);
                return;
            }
            else
            {
                this->dialog->set_text("Неправильный пароль!");
                this->dialog->exec();
                return;
            }
        }
    }


    this->dialog->set_text("Неправильная почта!");
    this->dialog->exec();
    return;
}

void MainWindow::update_list()
{
    this->ui->listWidget->clear();
    for (size_t i = 0; i < this->users.size(); i++)
    {
        this->ui->listWidget->addItem(this->users[i].email);
    }
}

void MainWindow::enable_right(bool enable)
{
    this->ui->edit_email->setEnabled(enable);
    this->ui->edit_name->setEnabled(enable);
    this->ui->edit_passw->setEnabled(enable);
    this->ui->save->setEnabled(enable);
}

void MainWindow::enable_down(bool enable)
{
    this->ui->edit->setEnabled(enable);
    this->ui->del->setEnabled(enable);
}

void MainWindow::on_listWidget_currentRowChanged(int item)
{
    this->cur_item = item;

    this->enable_down(true);
    this->enable_right(false);
}

void MainWindow::on_del_clicked()
{
    this->users.erase(this->users.begin() + this->cur_item);
    this->cur_item = -1;
    this->edit_item = -1;
    this->update_list();
    this->enable_down(false);
    this->enable_right(false);
}

void MainWindow::on_edit_clicked()
{
    this->edit_item = this->cur_item;
    this->ui->edit_name->setText(this->users[this->cur_item].name);
    this->ui->edit_email->setText(this->users[this->cur_item].email);
    this->ui->edit_passw->setText(this->users[this->cur_item].passw);

    this->enable_down(false);
    this->enable_right(true);
}

void MainWindow::on_save_clicked()
{
    QRegularExpression name("[а-яА-я]+ [А-я]\\.[А-я]\\.");
    QRegularExpression email("[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+");

    auto m_name{name.match(this->ui->edit_name->text())};
    if (!m_name.hasMatch() || m_name.captured() != this->ui->edit_name->text())
    {
        this->dialog->set_text("Неправильный формат Имени!");
        this->dialog->exec();
        return;
    }
    auto m_email{email.match(this->ui->edit_email->text())};
    if (!m_email.hasMatch() || m_email.captured() != this->ui->edit_email->text())
    {
        this->dialog->set_text("Неправильный формат Почты!");
        this->dialog->exec();
        return;
    }
    if (this->ui->edit_passw->text().size() != 10)
    {
        this->dialog->set_text("Неправильный формат Пароля!");
        this->dialog->exec();
        return;
    }

    this->users[this->edit_item].name = this->ui->edit_name->text();
    this->users[this->edit_item].email = this->ui->edit_email->text();
    this->users[this->edit_item].passw = this->ui->edit_passw->text();
    this->edit_item = -1;

    this->enable_down(false);
    this->enable_right(false);
}
