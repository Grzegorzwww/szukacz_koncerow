#include "findartistdialog.h"
#include "ui_findartistdialog.h"

FindArtistDialog::FindArtistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindArtistDialog)
{
    ui->setupUi(this);


    pixFromUrl = new DISPPixFromUrl(this);
    last_fm_artist_name = "-";
    facebbok_artist_name = "-";


    last_fm_artist_to_send = false;
    facebook_artist_to_send = false;




    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(on_search_next_artist(bool)));



}

FindArtistDialog::~FindArtistDialog()
{
    delete ui;
    delete pixFromUrl;
}



void FindArtistDialog::on_last_fm_artist_find(find_artist_t find){

    this->show();
     last_fm_artist_to_send = true;



    ui->label_10->setText("LAST.FM");
    ui->label_2->setText(find.name);
    ui->label_4->setText(QString::number(find.listeners));
    QString url_pic_temp = "<a href=\""+find.url+"\">"+find.url+"</a>";
    ui->label_6->setText(url_pic_temp);
    pixFromUrl->displayPic(ui->label_11, find.pix_url );

    last_fm_artist_name =  find.name;


}


void FindArtistDialog::on_facebook_artist_find(find_artist_t find){

    this->show();
    facebook_artist_to_send = true;

    ui->label_10->setText("Facebook.com");
    ui->label_2->setText(find.name);
    ui->label_4->setText("-");

    QString url_pic_temp = "<a href=\""+find.url+"\">"+find.url+"</a>";
    ui->label_6->setText(url_pic_temp);
    pixFromUrl->displayPic(ui->label_11, find.pix_url );

   facebbok_artist_name =  find.name;


}


void FindArtistDialog::on_search_next_artist(bool x){
    if(facebook_artist_to_send){

        emit sig_search_for_new_artist_tag();

    }



}



void FindArtistDialog::on_buttonBox_accepted()
{
    qDebug() <<"acepted";
    if(last_fm_artist_to_send){
        artist_was_find(last_fm_artist_name);
        last_fm_artist_to_send = false;
    }
    else if(facebook_artist_to_send){
        facebook_artist_was_find(facebbok_artist_name);
        facebook_artist_to_send = false;

    }
}

void FindArtistDialog::on_buttonBox_rejected()
{

    if(last_fm_artist_to_send){
        artist_was_not_find("-");
         last_fm_artist_to_send = false;
    }
    else if(facebook_artist_to_send){
        facebook_artist_was_not_find("-");
        facebook_artist_to_send = false;

    }
}
