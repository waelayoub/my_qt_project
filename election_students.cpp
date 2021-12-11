#include "election_students.h"
#include "ui_election_students.h"

Election_Students::Election_Students(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Election_Students)
{
    ui->setupUi(this);
}

Election_Students::~Election_Students()
{
    delete ui;
}

void Election_Students::change_combo_values(const std::string* my_s, const my_type& numb_of_cand){
    for(my_type i=0; i<numb_of_cand;++i){
        ui->cand_combo->addItem(QString::fromStdString(my_s[i]));
    }
}


void Election_Students::on_voting_btn_clicked()
{
    emit send_my_number(ui->cand_combo->currentIndex());
    close();
}

