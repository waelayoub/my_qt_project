#ifndef ELECTION_STUDENTS_H
#define ELECTION_STUDENTS_H

#include <QDialog>
#include <vector>
#include <QDebug>

typedef unsigned short int my_type ;
namespace Ui {
class Election_Students;
}

class Election_Students : public QDialog
{
    Q_OBJECT

public:
    explicit Election_Students(QWidget *parent = nullptr);
    ~Election_Students();

private slots:

    void on_voting_btn_clicked();

public slots:
    void change_combo_values(const std::string* my_s, const my_type & number_of_can);

signals:
    void send_my_number(const my_type & numb);

private:
    Ui::Election_Students *ui;
    my_type num_of_cand;
    std::vector<my_type> results;

};

#endif // ELECTION_STUDENTS_H
