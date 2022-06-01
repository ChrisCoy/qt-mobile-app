#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    const int HOME = 0;
    const int CRUD = 1;
    void setTypeScreen(int option);
    void reset_list();
private slots:


    void on_btnAddContact_clicked();

    void on_btnBack_clicked();

    void on_btnBackEdit_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_btnOk_clicked();

    void on_btnEdit_clicked();

    void on_btnRemove_clicked();

    void on_btnSearchContact_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
