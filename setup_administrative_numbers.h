#ifndef SETUP_ADMINISTRATIVE_NUMBERS_H
#define SETUP_ADMINISTRATIVE_NUMBERS_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
typedef unsigned short int my_type;

namespace Ui {
class setup_administrative_numbers;
}

class setup_administrative_numbers : public QDialog
{
    Q_OBJECT

public:
    explicit setup_administrative_numbers(QWidget *parent = nullptr);
    ~setup_administrative_numbers();

signals:
    void emitting_my_vars(const my_type & my_v1,const my_type & my_v2, const std::string* my_names);
    void appear_last_wind();

private slots:

    void on_back_btn_clicked();

    void on_cont_btn_clicked();

    void hiding_next_step(const bool & tr);

    void disable_first_step(const bool & tr);

    void on_cancel_btn_clicked();

    void on_next_btn_clicked();

    void on_back_numb_btn_clicked();

private:
    Ui::setup_administrative_numbers *ui;
    std::string* my_names;
    my_type elector_numbers;
    my_type candidats_numbers;
    my_type index;
};

#endif // SETUP_ADMINISTRATIVE_NUMBERS_H
