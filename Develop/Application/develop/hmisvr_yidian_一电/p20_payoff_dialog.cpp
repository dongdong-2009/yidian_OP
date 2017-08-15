#include "p20_payoff_dialog.h"
#include "ui_p20_payoff_dialog.h"
#include "globalhmi.h"

p20_payoff_dialog::p20_payoff_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::p20_payoff_dialog)
{
    ui->setupUi(this);
}

p20_payoff_dialog::~p20_payoff_dialog()
{
    delete ui;
}

void p20_payoff_dialog::changeEvent(QEvent *e)
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

static int add_numb;
static int Timer;

void p20_payoff_dialog::on_pbtn_cancel_clicked()
{
    Timer = 0;
    hmi_button_dn_num=PRINTCANCEL_ACBUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
}


void p20_payoff_dialog::init_page_dlg()
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
    ui->label_piccode->setPixmap(QPixmap("/usr/APP/1.png"));
}

void p20_payoff_dialog::init_page_val()
{
    add_numb=0;
    Timer=180;
    UINT8 data = NO_BUTTON;
    API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&data),sizeof(data));
}

void p20_payoff_dialog::start_timer()
{
    timer->start(PAGE_FLUSH_TIMER);
}

void p20_payoff_dialog::timer_handle()
{
     update_page_info();
     update_hmi_page_index();
     add_numb++;
     if(add_numb==20)
     {
         add_numb=0;
         if(Timer>0)
         {
             Timer--;
         }
     }
     if(Timer<=0)
     {
         Timer = 0;
         hmi_button_dn_num=PRINTCANCEL_ACBUTTON;
         API_Write_DB_Nbyte(PL_HMI_BUTTON_DOWN,(INT8 *)(&hmi_button_dn_num),sizeof(hmi_button_dn_num));
     }
}

void p20_payoff_dialog::update_page_info()
{
//    ui->lbl_sysdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
//    ui->lbl_systime->setText(QTime::currentTime().toString("hh:mm:ss"));
  //  ui->label_phone->setText(phonenum);
  //   ui->label_code->setText(code);
  //   UINT16 u16_data = 0;
    int type_temp=0,tempvalue=2;

    if(language_num == 1)
    {
        //  ui->label_logo->setText(QString::fromUtf8("交 流 充 电 桩"));
        //ui->label_title->setText(QString::fromUtf8("充 电 结 算"));
       // ui->label_stubnum->setText(QString::fromUtf8("客  服  电  话  :"));
      //  ui->label_time->setText(QString::fromUtf8("充电时间"));
     //  ui->label_energy->setText(QString::fromUtf8("消耗电量"));
      //  ui->lbl_time_min_2->setText(QString::fromUtf8("时"));
     //   ui->lbl_time_min_3->setText(QString::fromUtf8("分"));

        API_Read_DB_Nbyte(PL_GunWaring_FLAG,(char*)&tempvalue,sizeof(tempvalue));
        if(tempvalue==2)
        {
            char temp_buf[100]={0};
            sprintf(temp_buf,"请移除充电桩侧充电枪  %d 秒",Timer);
            ui->label_state->setText(QString::fromUtf8(temp_buf));
        }
        else
        {
            char temp2_buf[100]={0};
            //sprintf(temp2_buf,"请将充电枪归位  %d 秒",Timer);
            sprintf(temp2_buf,"请移除车辆侧充电枪  %d 秒",Timer);
            ui->label_state->setText(QString::fromUtf8(temp2_buf));
        }

      //  ui->pbtn_cancel->setText(QString::fromUtf8(temp_buf));

    }
    else  if(language_num == 2)
    {
       //   ui->label_logo->setText("AC charging pile");
          ui->label_title->setText("Payoff Information");
          ui->label_stubnum->setText("Telephone :");
          ui->label_time->setText("Time");
          ui->label_energy->setText("Energy");
      //    ui->lbl_time_min_2->setText("H");
          ui->lbl_time_min_3->setText("M");
           ui->label_state->setText("Please extract the Charge Gun");
           char temp_buf[30]={0};
           sprintf(temp_buf,"Back %d S",Timer);
         // ui->pbtn_cancel->setText(temp_buf);
    }

     FLOAT32 f32_data = 0;
     UINT16 u16_data=0;

     API_Read_DB_Nbyte(PL_CHRTOTALUSE_TIME,(INT8 *)(&u16_data),sizeof(u16_data));
     //ui->lbl_time_hour->setText(QString::number(u16_data/60,'f',0));
     ui->lbl_time_min->setText(QString::number(u16_data,'f',0));

     API_Read_DB_Nbyte(PL_CHRUSED_KWH,(INT8 *)(&f32_data),sizeof(f32_data));
     ui->lbl_caclulate_energy->setText(QString::number(f32_data,'f',2));

     API_Read_DB_Nbyte(PL_CHRUSED_TOTALMONEY,(INT8 *)(&f32_data),sizeof(f32_data));
  //   ui->lbl_money_total->setText(QString::number(f32_data,'f',2));

     API_Read_DB_Nbyte(PL_CHARGESEVICE_MONEY,(INT8 *)(&f32_data),sizeof(f32_data));
 //    ui->lbl_money_service->setText(QString::number(f32_data,'f',2));
   //  ErrMsg("$$$$[%0.2f]$$$\n",f32_data);

     API_Read_DB_Nbyte(PL_ELECTRIC_MONEY,(INT8 *)(&f32_data),sizeof(f32_data));
   //  ui->lbl_money_electric->setText(QString::number(f32_data,'f',2));
}

void p20_payoff_dialog::update_hmi_page_index()
{
    API_Read_DB_Nbyte(PL_HMI_PAGE_INDEX,(INT8 *)(&hmi_page_index),sizeof(hmi_page_index));
    if(hmi_page_index != PAGEINDEX_ACPAYOFF)
    {
        exit_page_dlg();
    }
    else
    {

    }

}
/*
void p20_payoff_dialog::call_dlg_1()
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

void p20_payoff_dialog::call_pull_gun()
{
    timer->stop();
    if(pull_gun_dlg){
            delete pull_gun_dlg;
            pull_gun_dlg = NULL;
    }
    pull_gun_dlg = new  Dialog_pull_gun;
    pull_gun_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_pull_gun_timer()),pull_gun_dlg,SLOT(init_page_dlg()));
    connect(pull_gun_dlg,SIGNAL(signal_exit_dlg()),this,SLOT(start_timer()));

    emit signal_enable_pull_gun_timer();
    pull_gun_dlg->exec();
}

void p20_payoff_dialog::call_err_dlg()
{
    timer->stop();
    if(err_dlg){
            delete err_dlg;
            err_dlg = NULL;
    }
    err_dlg = new  Dialog_error;
    err_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_err_timer()),err_dlg,SLOT(init_page_dlg()));
    connect(err_dlg,SIGNAL(signal_exit_errdlg_payoff()),this,SLOT(start_timer()));

    emit signal_enable_err_timer();
    err_dlg->exec();
}

void p20_payoff_dialog::call_end_dlg()
{
    timer->stop();
    if(end_dlg){
            delete end_dlg;
            end_dlg = NULL;
    }
    end_dlg = new  Dialog_end;
    end_dlg->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(signal_enable_end_timer()),end_dlg,SLOT(init_page_dlg()));
    connect(end_dlg,SIGNAL(signal_exit_end()),this,SLOT(exit_page_dlg()));

    emit signal_enable_end_timer();
    end_dlg->exec();
}

void p20_payoff_dialog::exit_page_dlg()
{
    DebugMsg(hmilev,8,"exit_page_dlg\n");
    init_page_val();
    timer->stop();
    emit signal_exit_p20dlg();
    //delete p20_dlg;
    //p20_dlg = NULL;
}
