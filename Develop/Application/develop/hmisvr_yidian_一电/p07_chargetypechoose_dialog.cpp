#include "p07_chargetypechoose_dialog.h"
#include "ui_p07_chargetypechoose_dialog.h"
#include "globalhmi.h"

p07_chargetypechoose_dialog::p07_chargetypechoose_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p07_chargetypechoose_dialog)
{
    ui->setupUi(this);
}

p07_chargetypechoose_dialog::~p07_chargetypechoose_dialog()
{
    delete ui;
}

void p07_chargetypechoose_dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void p07_chargetypechoose_dialog::init_page_dlg()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_handle()));
    timer->start(PAGE_FLUSH_TIMER);
    init_page_val();
    ui->label_stubnum->setText(QString::fromUtf8("桩编号："));
    ui->label_phone->setText(QString::fromUtf8("客服热线："));
    ui->label_code->setText(code);
    ui->label_num1->setText(phonenum);
    ui->label_num2->setText(phonenum_2);
}

void p07_chargetypechoose_dialog::init_page_val()
{
        UINT8 data = NO_BUTTON;
        API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void p07_chargetypechoose_dialog::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}

void p07_chargetypechoose_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();

}

void p07_chargetypechoose_dialog::update_page_info()
{

       if(language_num == 1)
       {

       }
       else  if(language_num == 2)
       {
          //   ui->label_logo->setText("DC charging pile");
             ui->label_title->setText("Type  Choose");
             ui->label_stubnum->setText("Pile Number :");

             ui->pbtn_cancel->setText("Back");
             ui->pbtn_auto->setText("ChargeByAuto");
             ui->pbtn_byenergy->setText("ChargeByEnergy");
             ui->pbtn_bytime->setText("ChargeByTime");
             ui->pbtn_bymoney->setText("ChargeByMoney");
       }
}

void p07_chargetypechoose_dialog::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));

    if(hmi_page_index != PAGEINDEX_CHARGETYPECHOSE)
    {
        exit_page_dlg();
    }
    else
    {

    }
}
/*
void p07_chargetypechoose_dialog::call_dlg_1()
{
    timer->stop();
    if(dlg_1){
            delete dlg_1;
            dlg_1 = NULL;

    }

    dlg_1 = new dialog_1 ;
    dlg_1->setWindowFlags(Qt::FramelessWindowHint);
    connect(this,SIGNAL(signal_enable_dlg_1_timer()),dlg_1,SLOT(init_page_dlg()));
    connect(dlg_1,SIGNAL(signal_exit_dlg_1()),this,SLOT(exit_page_dlg()));
    emit signal_enable_dlg_1_timer();
    dlg_1->exec();
}
*/
void p07_chargetypechoose_dialog::call_p08_dlg()
{
    timer->stop();
    if(p08_dlg){
            delete p08_dlg;
            p08_dlg = NULL;
            handle_dlg_p08--;
    }
    p08_dlg = new  p08_chargebytime_dialog;
    p08_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p08++;

    connect(this,SIGNAL(signal_enable_p08dlg_timer()),p08_dlg,SLOT(init_page_dlg()));
    connect(p08_dlg,SIGNAL(signal_exit_p08dlg()),this,SLOT(exit_page_dlg()));
    connect(p08_dlg,SIGNAL(signal_timer_p08dlg()),this,SLOT(start_timer()));
    emit signal_enable_p08dlg_timer();
    p08_dlg->exec();
}

/*
void p07_chargetypechoose_dialog::call_p23_dlg()
{
    timer->stop();
    if(p23_dlg){
            delete p23_dlg;
            p23_dlg = NULL;
    }
    p23_dlg = new  p23_chargebymoney;
    p23_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_p23dlg_timer()),p23_dlg,SLOT(init_page_dlg()));
    connect(p23_dlg,SIGNAL(signal_exit_p23dlg()),this,SLOT(exit_page_dlg()));
    connect(p23_dlg,SIGNAL(signal_timer_p23dlg()),this,SLOT(start_timer()));
    emit signal_enable_p23dlg_timer();
    p23_dlg->exec();
}
*/
void p07_chargetypechoose_dialog::call_p09_dlg()
{
    timer->stop();
    if(p09_dlg){
            delete p09_dlg;
            p09_dlg = NULL;
            handle_dlg_p09--;
    }
    p09_dlg = new  p09_chargebyenergy_dialog;
    p09_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p09++;

    connect(this,SIGNAL(signal_enable_p09dlg_timer()),p09_dlg,SLOT(init_page_dlg()));
    connect(p09_dlg,SIGNAL(signal_exit_p09dlg()),this,SLOT(exit_page_dlg()));
    connect(p09_dlg,SIGNAL(signal_timer_p09dlg()),this,SLOT(start_timer()));

    emit signal_enable_p09dlg_timer();
    p09_dlg->exec();
}

/*
void p07_chargetypechoose_dialog::call_p11_dlg()
{
    timer->stop();
    if(p11_dlg){
            delete p11_dlg;
            p11_dlg = NULL;
            handle_dlg_p11--;
    }
    p11_dlg = new  p11_charging_dialog;
    p11_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p11++;

    connect(this,SIGNAL(signal_enable_p11dlg_timer()),p11_dlg,SLOT(init_page_dlg()));
    connect(p11_dlg,SIGNAL(signal_exit_p11dlg()),this,SLOT(exit_page_dlg()));
    emit signal_enable_p11dlg_timer();
    p11_dlg->exec();
}

void p07_chargetypechoose_dialog::call_p10_dlg()
{
    timer->stop();
    if(p10_dlg){
            delete p10_dlg;
            p10_dlg = NULL;
            handle_dlg_p10--;
    }
    p10_dlg = new  p10_chargebyauto_dialog;
    p10_dlg->setWindowFlags(Qt::FramelessWindowHint);
    handle_dlg_p10++;

    connect(this,SIGNAL(signal_enable_p10dlg_timer()),p10_dlg,SLOT(init_page_dlg()));
    connect(p10_dlg,SIGNAL(signal_exit_p10dlg()),this,SLOT(exit_page_dlg()));

    emit signal_enable_p10dlg_timer();
    p10_dlg->exec();
}
*/
void p07_chargetypechoose_dialog::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p07dlg();
    //delete p07_dlg;
    //p07_dlg = NULL;
}

 void p07_chargetypechoose_dialog::on_pbtn_bymoney_clicked()
 {
     hmi_button_dn_num=CHARGEBYMONEY_BUTTON;
     API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
 }

void p07_chargetypechoose_dialog::on_pbtn_cancel_clicked()
{
    hmi_button_dn_num=CANCEL_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void p07_chargetypechoose_dialog::on_pbtn_bytime_clicked()
{
    hmi_button_dn_num=CHARGEBYTIME_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void p07_chargetypechoose_dialog::on_pbtn_byenergy_clicked()
{
    hmi_button_dn_num=CHARGEBYCAPA_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

void p07_chargetypechoose_dialog::on_pbtn_auto_clicked()
{
    hmi_button_dn_num=CHARGEBYAUTO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}

