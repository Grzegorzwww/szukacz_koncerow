#ifndef FINDARTISTDIALOG_H
#define FINDARTISTDIALOG_H

#include <QDialog>
#include <defines.h>
#include <disppixfromurl.h>

namespace Ui {
class FindArtistDialog;
}

class FindArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindArtistDialog(QWidget *parent = 0);
    ~FindArtistDialog();

private:
    Ui::FindArtistDialog *ui;

    DISPPixFromUrl *pixFromUrl;
    QString last_fm_artist_name;
    QString facebbok_artist_name;

    QString searching_tag;

    bool last_fm_artist_to_send;
    bool facebook_artist_to_send;


public slots:



    void on_last_fm_artist_find(find_artist_t find);
    void on_facebook_artist_find(find_artist_t find);


    void on_search_next_artist(bool x);
private slots:

    void on_buttonBox_accepted();


    void on_buttonBox_rejected();

signals:


    artist_was_find(QString);
    artist_was_not_find(QString);


    facebook_artist_was_find(QString);
    facebook_artist_was_not_find(QString);

    sig_search_for_new_artist_tag();
};

#endif // FINDARTISTDIALOG_H
