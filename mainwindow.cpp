#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),sec_ad_wind(nullptr),  elec_std_wind(nullptr), number_of_elect(0), number_of_cand(0), my_names(nullptr), ongoing_election(false), number_of_voters(0)

{
    ui->setupUi(this);
    ui->welcome_label->setText( QString::fromStdString("Welcome to the Delegate Elections "+std::to_string(QDate::currentDate().year())));
    ui->Last_results_btn->setEnabled(false);
    ui->download_btn->setEnabled(false);
    ui->option_cbb->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    if(my_names!=nullptr){
        delete[] my_names;
        my_names = nullptr;
    }
    delete ui;
}

bool MainWindow::check_code_exist(const size_t & code){
    for(auto const& elem :codes){
       if(elem==code){
           codes.erase(elem);
           return true;
       }
    }
    return false;
}

void MainWindow::get_the_vote(const my_type& num){
    results[num]++;
    number_of_voters++;
    if(number_of_voters==number_of_elect){
        ui->download_btn->setEnabled(true);
        ui->Last_results_btn->setEnabled(true);
        resulting_strings=results_of_election();
        end_election();
        show_res();
    }
}

void MainWindow::show_res(){
    if(ongoing_election){
        QMessageBox::warning(this, tr("Election already on-going"), tr("You should end the previous election before getting results"));
    }
    else{
        QMessageBox::information(this, tr("Results"), tr(resulting_strings.c_str()));
    }
}

std::string MainWindow::results_of_election(){
    string results_str="";

    my_type max1=results[1];
    my_type max2=0;
    my_type index=1;

    results_str+="White votes        "+to_string(results[0])+"\n";
    for(my_type i=0; i<number_of_cand; ++i){
        results_str+=my_names[i]+"        "+to_string(results[i+1])+'\n';
    }
    for(my_type i=2; i<number_of_cand+1; ++i){

        if(results[i]>=max1){
            max2=max1;
            max1=results[i];
            index=i;
        }
        else if(results[i]>=max2){
            max2=results[i];
        }
    }

    results_str+="\n";
    if(number_of_cand==1){
        results_str+="Winner is : "+ my_names[index-1]+"\n";
        results_str+="The winner has : "+to_string(results[index])+" votes!";
    }
    else if(number_of_voters==0){
        results_str+="No winner ";
        results_str+="\nNo one came and voted!";
    }
    else if(max1==max2){
        results_str+="No winner we have a TIE ";
        results_str+="\nMany got : "+to_string(results[index])+" votes!";
    }
    else{
        results_str+="Winner is : "+ my_names[index-1]+"\n";
        results_str+="The winner has : "+to_string(results[index])+" votes!";
    }
    results_str+="\n\nStatistics: \n\n";
    double whvotes=0;
    if(number_of_voters!=0){
        whvotes=(results[0]*100)/(number_of_voters);
    }
    results_str+="Number of electors: "+to_string(number_of_elect)+"\n";
    results_str+="Number of voters : "+to_string(number_of_voters)+"\n";
    results_str+="Percentage of white votes: "+to_string(whvotes)+"%";
    return results_str;
}

void MainWindow::end_election(){
    if(ongoing_election){
        ui->code_entry->clear();
        number_of_cand=0;
        number_of_elect=0;
        number_of_voters=0;
        ongoing_election=false;
        results.clear();
        codes.clear();
        delete [] my_names;
        my_names=nullptr;

    }
}

void MainWindow::on_start_btn_clicked()
{
    if(ui->option_cbb->currentText()=="Administrative" && ongoing_election==false && ui->code_entry->text()=="admin"){
        hide();
        ui->code_entry->clear();
        sec_ad_wind = new setup_administrative_numbers(this);
        sec_ad_wind->show();
        QObject::connect(sec_ad_wind, &setup_administrative_numbers::emitting_my_vars ,this, &MainWindow::getmyvars);
        QObject::connect(sec_ad_wind, &setup_administrative_numbers::appear_last_wind ,this, &MainWindow::show);
    }
    else if(ui->option_cbb->currentText()=="Administrative" && ongoing_election==true){
        ui->code_entry->clear();
        QMessageBox::warning(this, tr("Election already on-going"), tr("You should end the previous election before moving to another"));
    }
    else if(ui->option_cbb->currentText()=="Student" && ongoing_election==true && check_code_exist(ui->code_entry->text().toInt())){
        ui->code_entry->clear();
        hide();
        elec_std_wind=new Election_Students(this);
        elec_std_wind->show();
        QObject::connect(this, &MainWindow::give_my_vars_to_elect,elec_std_wind, &Election_Students::change_combo_values);
        QObject::connect(elec_std_wind, &Election_Students::send_my_number,this, &MainWindow::get_the_vote);
        QObject::connect(elec_std_wind, &Election_Students::send_my_number,this, &MainWindow::show);
        emit give_my_vars_to_elect(my_names, number_of_cand);

    }
    else if(ui->option_cbb->currentText()=="Student" && ongoing_election==false){
        QMessageBox::warning(this, tr("No Election"), tr("Your administration hasen't started an election yet"));
    }
    else{
        ui->code_entry->clear();
        QMessageBox::warning(this, tr("Wrong Input"), tr("Wrong Password or Code"));
    }
}

void MainWindow::getmyvars(const my_type & my_v1, const my_type & my_v2, const std::string* my_names1){
    ui->option_cbb->setCurrentIndex(0);
    number_of_elect=my_v1;
    number_of_cand=my_v2;
    my_names=new string[number_of_cand];
    results.push_back(0);
    for(my_type i=0; i<number_of_cand;++i){
        my_names[i]=my_names1[i];
        results.push_back(0);
    }
    ongoing_election=true;
    std::srand((unsigned) std::time(NULL));
    ofstream my_code_file;
    my_code_file.open("codes.txt");

    while(codes.size()!=number_of_elect){
        size_t random = 1000 + (rand() % (number_of_elect*1000));
        codes.insert(random);
        my_code_file<<random<<endl;
        qDebug()<<random;
    }
    my_code_file.close();
}

void MainWindow::on_Last_results_btn_clicked()
{
    show_res();
}


void MainWindow::on_ending_elect_btn_clicked()
{
    if(ui->option_cbb->currentText()=="Administrative" && ui->code_entry->text()=="admin" && ongoing_election){
        ui->download_btn->setEnabled(true);
        ui->Last_results_btn->setEnabled(true);
        resulting_strings=results_of_election();
        end_election();
        show_res();
    }
    else{
        QMessageBox::warning(this, tr("Not Elligible"), tr("Enter your password in mode administration and make sure there is an election on going"));
    }
}


void MainWindow::on_download_btn_clicked()
{
    ofstream my_down_file;
    my_down_file.open("results.txt");
    my_down_file<<resulting_strings;
    my_down_file.close();
    QMessageBox::information(this, tr("All finished"), tr("Your results have been added to a file called results.txt"));
}

