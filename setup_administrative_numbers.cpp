#include "setup_administrative_numbers.h"
#include "ui_setup_administrative_numbers.h"



setup_administrative_numbers::setup_administrative_numbers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setup_administrative_numbers),
    my_names(nullptr),
  elector_numbers(0), candidats_numbers(0), index(0)
{
    ui->setupUi(this);
    hiding_next_step(false);
}

setup_administrative_numbers::~setup_administrative_numbers()
{
    if(my_names!=nullptr){
        delete [] my_names;
        my_names=nullptr;
    }
    delete ui;
}

void setup_administrative_numbers::on_back_btn_clicked()
{
    if(my_names!=nullptr){
        delete [] my_names;
        my_names=nullptr;
    }
    close();
    emit appear_last_wind();
}


void setup_administrative_numbers::hiding_next_step(const bool & tr){
    ui->next_btn->setVisible(tr);
    ui->back_numb_btn->setVisible(tr);
    ui->Student_label_numbers->setVisible(tr);
    ui->cancel_btn->setVisible(tr);
    ui->enter_std_label->setVisible(tr);
    ui->names_entry->setVisible(tr);
}

void setup_administrative_numbers::disable_first_step(const bool & tr){
    ui->NB_CAND->setEnabled(tr);
    ui->NB_ELECT->setEnabled(tr);
    ui->back_btn->setEnabled(tr);
    ui->cont_btn->setEnabled(tr);
}

void setup_administrative_numbers::on_cont_btn_clicked()
{
    if((ui->NB_CAND->value()==0) || (ui->NB_ELECT->value()==0) || (ui->NB_CAND->value()>ui->NB_ELECT->value())){
        QMessageBox::warning(this, tr("Invalid Inputs"), tr("You have an error in your inputs!"));
    }
    else{
        hiding_next_step(true);
        disable_first_step(false);
        candidats_numbers=ui->NB_CAND->value();
        elector_numbers=ui->NB_ELECT->value();
        index=0;
        my_names=new std::string[candidats_numbers];
    }

}


void setup_administrative_numbers::on_cancel_btn_clicked()
{
    hiding_next_step(false);
    disable_first_step(true);
    if(my_names!=nullptr){
        delete [] my_names;
        my_names=nullptr;
    }
    ui->names_entry->setEnabled(true);
    ui->next_btn->setText("next");
    ui->Student_label_numbers->setText(QString::fromStdString("Student 1"));
}

void setup_administrative_numbers::on_next_btn_clicked()
{

    if(index<candidats_numbers){
    if(ui->names_entry->text()!=""){
        my_names[index++]=(ui->names_entry->text().toStdString());
        ui->Student_label_numbers->setText(QString::fromStdString("Student "+std::to_string(index+1)));
        ui->names_entry->clear();
    }
    else{
        QMessageBox::warning(this, tr("Invalid Inputs"), tr("You left the name empty!"));}

        if(index==candidats_numbers){
            ui->next_btn->setText("Finish");
            ui->Student_label_numbers->setText(QString::fromStdString("All done"));
            ui->names_entry->setEnabled(false);
        }
    }
    else{
        emit emitting_my_vars(elector_numbers, candidats_numbers, my_names);
        if(my_names!=nullptr){
            delete [] my_names;
            my_names=nullptr;
        }
        close();
        QMessageBox::information(this, tr("Success"), tr("You Started an election \n\nP.S. : We created a file named codes.txt that has the codes for the election"));
        emit appear_last_wind();
    }
}

void setup_administrative_numbers::on_back_numb_btn_clicked()
{
    if(index!=0){
        --index;
        ui->next_btn->setText("next");
        ui->Student_label_numbers->setText(QString::fromStdString("Student "+std::to_string(index+1)));
        ui->names_entry->setEnabled(true);
    }
}

