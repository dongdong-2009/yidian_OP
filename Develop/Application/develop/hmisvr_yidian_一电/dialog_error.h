#ifndef DIALOG_ERROR_H
#define DIALOG_ERROR_H

#include <QDialog>

namespace Ui {
class Dialog_error;
}

class Dialog_error : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_error(QWidget *parent = 0);
    ~Dialog_error();

private:
    Ui::Dialog_error *ui;

private:
        QTimer *timer;

        int lbl_num;
        int lbl_num_2;
        int lbl_num_3;
        int lbl_num_4;
        int lbl_num_5;

        char lbl_txt[50];
        char lbl_txt_2[50];
        char lbl_txt_3[50];
        char lbl_txt_4[50];
        char lbl_txt_5[50];

private slots:
    void init_page_dlg(void);
    void init_page_val(void);
    void start_timer(void);
    void timer_handle(void);
    void exit_page_dlg(void);
    void on_pbtn_err_clicked(void);
    void on_pbtn_set_clicked();
    void on_pbtn_up_clicked(void);
    void on_pbtn_down_clicked(void);
    void on_pbtn_back_2_clicked(void);
    void btn_press(void);

private:
    unsigned char btn_passwd_pos;
    char btn_passwd[9];
    char btn_passwd_disp[9];

private slots:
    void on_pbtn_go_clicked();
    void on_pbtn_ok_clicked();
    void on_pbtn_back_clicked();
    void on_pbtn_dot_clicked();
    void on_pbtn_num0_clicked();
    void on_pbtn_num9_clicked();
    void on_pbtn_num8_clicked();
    void on_pbtn_num7_clicked();
    void on_pbtn_num6_clicked();
    void on_pbtn_num5_clicked();
    void on_pbtn_num4_clicked();
    void on_pbtn_num3_clicked();
    void on_pbtn_num2_clicked();
    void on_pbtn_num1_clicked();

private:
    void update_page_info(void);
    void update_hmi_page_index(void);

signals:

    void signal_exit_errdlg();
    void signal_exit_errdlg_link();
    void signal_exit_errdlg_charging();
    void signal_exit_errdlg_payoff();
    void signal_exit_errdlg_judge();
};

#endif // DIALOG_ERROR_H
