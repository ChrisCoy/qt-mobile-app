#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScrollBar>
#include<QDebug>

int acaoTela = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gerenciadorTelas->setCurrentIndex(this->HOME);
    ui->btnBackEdit->setVisible(false);

    QString styleSheet_string ="QScrollBar:vertical {width:8px;}"
                               "QScrollBar::handle:vertical {background: #D9D9D9;}";

    QScrollBar *vBar = ui->listWidget->QAbstractScrollArea::verticalScrollBar();
    vBar->setStyleSheet(styleSheet_string);


    ui->listWidget->setIconSize(QSize(35,35));
    ui->listWidget->setFont(QFont("Segoe UI", 14, QFont::Thin));
    ui->listWidget->setSpacing(8);
    ui->listWidget->setIconSize(QSize(34,34));

    QListWidgetItem *item2 = new QListWidgetItem(QIcon(":/src/img/iconPerson.png"),"Christopher Lee Gontijo Silva");
    ui->listWidget->addItem(item2);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_btnAddContact_clicked()
{
    setTypeScreen(2);
}


void MainWindow::on_btnBack_clicked()
{
    ui->gerenciadorTelas->setCurrentIndex(this->HOME);
}



void MainWindow::setTypeScreen(int option){
    switch(option){
        case 1:
            acaoTela = 1;
            ui->gerenciadorTelas->setCurrentIndex(this->HOME);
        break;
        case 2:
            acaoTela = 2;
            ui->lblTitulo->setText("<center>Criando Novo Contato");
            ui->btnBackEdit->setVisible(false);
            ui->btnBack->setVisible(true);

            ui->inptNome->setEnabled(true);
            ui->inptDia->setEnabled(true);
            ui->inptMes->setEnabled(true);

            ui->inptNome->setText("");
            ui->inptDia->setText("");
            ui->inptMes->setText("");

            ui->btnEdit->setVisible(false);
            ui->btnRemove->setVisible(false);
            ui->btnOk->setVisible(true);
            ui->gerenciadorTelas->setCurrentIndex(this->CRUD);
        break;
        case 3:
            acaoTela = 3;
            ui->lblTitulo->setText("<center>Detalhes do Contato");
            ui->btnBackEdit->setVisible(false);
            ui->btnBack->setVisible(true);

            ui->inptNome->setEnabled(false);
            ui->inptDia->setEnabled(false);
            ui->inptMes->setEnabled(false);

            ui->inptNome->setText("");
            ui->inptDia->setText("");
            ui->inptMes->setText("");

            ui->btnEdit->setVisible(true);
            ui->btnRemove->setVisible(true);
            ui->btnOk->setVisible(false);
            ui->gerenciadorTelas->setCurrentIndex(this->CRUD);
        break;
        case 4:
            acaoTela = 4;
            ui->lblTitulo->setText("<center>Editando Contato");
            ui->btnBackEdit->setVisible(true);
            ui->btnBack->setVisible(false);

            ui->inptNome->setEnabled(true);
            ui->inptDia->setEnabled(true);
            ui->inptMes->setEnabled(true);

            ui->inptNome->setText("");
            ui->inptDia->setText("");
            ui->inptMes->setText("");

            ui->btnEdit->setVisible(false);
            ui->btnRemove->setVisible(false);
            ui->btnOk->setVisible(true);
            ui->gerenciadorTelas->setCurrentIndex(this->CRUD);
        break;
    }
}


void MainWindow::on_btnBackEdit_clicked()//evento tela edit
{

}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    setTypeScreen(3);
    ui->inptNome->setText(item->text());
    ui->inptDia->setText("01");
    ui->inptMes->setText("06");
}

