#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QScrollBar>
#include <string>

using namespace std;

int acaoTela = 0;
int contactToEdit;

typedef struct {
  QString name;
  int month;
  int day;
} Contacts;

Contacts contacts[300];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /*******        ESTILIZAÇÃO     *******/
  ui->gerenciadorTelas->setCurrentIndex(this->HOME);
  ui->btnBackEdit->setVisible(false);

  QString styleSheet_string =
      "QScrollBar:vertical {width:8px;}"
      "QScrollBar::handle:vertical {background: #D9D9D9;}";

  QScrollBar *vBar = ui->listWidget->QAbstractScrollArea::verticalScrollBar();
  vBar->setStyleSheet(styleSheet_string);

  ui->listWidget->setIconSize(QSize(35, 35));
  ui->listWidget->setFont(QFont("Segoe UI", 14, QFont::Thin));
  ui->listWidget->setSpacing(8);
  ui->listWidget->setIconSize(QSize(34, 34));
  /*******        ESTILIZAÇÃO     *******/

  ui->inptDia->setValidator( new QIntValidator(0, 100, this) );
  ui->inptMes->setValidator( new QIntValidator(0, 100, this) );
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnAddContact_clicked() { setTypeScreen(2); }

void MainWindow::on_btnBack_clicked() {
  ui->gerenciadorTelas->setCurrentIndex(this->HOME);
  reset_list();
}

void MainWindow::setTypeScreen(int option) {
  switch (option) {
  case 1:
    acaoTela = 1;
    reset_list();
    ui->gerenciadorTelas->setCurrentIndex(this->HOME);
    break;
  case 2:
    acaoTela = 2;
    ui->lblTitulo->setText("<center>Criando Novo Contato");
    ui->btnBackEdit->setVisible(false);
    ui->btnBack->setVisible(true);

    ui->inptNome->setClearButtonEnabled(true);
    ui->inptDia->setClearButtonEnabled(true);
    ui->inptMes->setClearButtonEnabled(true);
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

    ui->inptNome->setClearButtonEnabled(false);
    ui->inptDia->setClearButtonEnabled(false);
    ui->inptMes->setClearButtonEnabled(false);
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

    ui->inptNome->setClearButtonEnabled(true);
    ui->inptDia->setClearButtonEnabled(true);
    ui->inptMes->setClearButtonEnabled(true);
    ui->inptNome->setEnabled(true);
    ui->inptDia->setEnabled(true);
    ui->inptMes->setEnabled(true);

    ui->btnEdit->setVisible(false);
    ui->btnRemove->setVisible(false);
    ui->btnOk->setVisible(true);

    ui->gerenciadorTelas->setCurrentIndex(this->CRUD);
    break;
  }
}

void MainWindow::on_btnBackEdit_clicked() // evento tela edit
{
  acaoTela = 3;
  ui->lblTitulo->setText("<center>Detalhes do Contato");
  ui->btnBackEdit->setVisible(false);
  ui->btnBack->setVisible(true);

  ui->inptNome->setClearButtonEnabled(false);
  ui->inptDia->setClearButtonEnabled(false);
  ui->inptMes->setClearButtonEnabled(false);
  ui->inptNome->setEnabled(false);
  ui->inptDia->setEnabled(false);
  ui->inptMes->setEnabled(false);

  ui->btnEdit->setVisible(true);
  ui->btnRemove->setVisible(true);
  ui->btnOk->setVisible(false);

  reset_list();
}

void MainWindow::on_listWidget_itemDoubleClicked(
    QListWidgetItem *item) // fazer o dado aparecer na tela
{
  setTypeScreen(3);
  for (int i = 0; i < 300; i++) {
    if (contacts[i].name == item->text()) {
      ui->inptNome->setText(contacts[i].name);
      ui->inptMes->setText(QString::number(contacts[i].month));
      ui->inptDia->setText(QString::number(contacts[i].day));
      contactToEdit = i;
      break;
    }
  }
}

void MainWindow::on_btnOk_clicked() {
  if (acaoTela == 4) {                                                  // editando
    for (int i = 0; i < 300; i++) {

      contacts[contactToEdit].name = ui->inptNome->text();
      contacts[contactToEdit].month = ui->inptMes->text().toInt();
      contacts[contactToEdit].day = ui->inptDia->text().toInt();

      setTypeScreen(3);

      ui->inptNome->setText(contacts[contactToEdit].name);
      ui->inptMes->setText(QString::number(contacts[contactToEdit].month));
      ui->inptDia->setText(QString::number(contacts[contactToEdit].day));
      break;
    }
  } else {                                                              // criando
    for (int i = 0; i < 300; i++) {
      if (contacts[i].name == "") {
        contacts[i].name = ui->inptNome->text();
        contacts[i].month = ui->inptMes->text().toInt();
        contacts[i].day = ui->inptDia->text().toInt();
        setTypeScreen(1);
        break;
      }
    }
  }
}

void MainWindow::reset_list() {
  ui->listWidget->clear();

  for (int i = 0; i < 300; i++) {
    if (contacts[i].name != "") {
      QListWidgetItem *item = new QListWidgetItem(
          QIcon(":/src/img/iconPerson.png"), contacts[i].name);
      ui->listWidget->addItem(item);
    }
  }
}

void MainWindow::on_btnEdit_clicked() { setTypeScreen(4); }

void MainWindow::on_btnRemove_clicked() {
  //QMessageBox *messageBox = new QMessageBox();

  QMessageBox::StandardButton response = QMessageBox::question(
      this, "Excluir contato", "Tem certeza que deseja excluir esse contato?",
      QMessageBox::Yes | QMessageBox::No);

  if (response == QMessageBox::Yes) {
      contacts[contactToEdit].name = "";
      setTypeScreen(1);
  }
}

void MainWindow::on_btnSearchContact_clicked()
{
    if (ui->inptSearchInput->text().isEmpty()){
        reset_list();
    }else{
        ui->listWidget->clear();
        for (int i = 0; i < 300; i++) {
          if (contacts[i].name.startsWith(ui->inptSearchInput->text())) {
            QListWidgetItem *item = new QListWidgetItem(
                QIcon(":/src/img/iconPerson.png"), contacts[i].name);
            ui->listWidget->addItem(item);
          }
        }
    }
}

