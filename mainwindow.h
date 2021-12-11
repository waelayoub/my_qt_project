#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setup_administrative_numbers.h"
#include "election_students.h"
#include <QDateTime>
#include <string>
#include <QMessageBox>
#include <QDebug>
#include <set>
#include<cstdlib>
#include <fstream>
#include <vector>

typedef unsigned short int my_type ;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_start_btn_clicked();

    void on_Last_results_btn_clicked();

    void on_ending_elect_btn_clicked();

    void on_download_btn_clicked();

public slots:
    void getmyvars(const my_type & my_v1, const my_type & my_v2, const std::string* my_names);

signals:
    void give_my_vars_to_elect(const std::string* my_n, const my_type& cand);

private:
    Ui::MainWindow *ui;
    setup_administrative_numbers * sec_ad_wind;
    Election_Students * elec_std_wind;
    my_type number_of_elect;
    my_type number_of_cand;
    std::string * my_names;
    bool ongoing_election;
    std::set<size_t> codes;
    std::vector<my_type> results;
    bool check_code_exist(const size_t & code);
    void get_the_vote(const my_type& num);
    my_type number_of_voters;
    void end_election();
    std::string results_of_election();
    std::string resulting_strings;
    void show_res();
};
#endif // MAINWINDOW_H
