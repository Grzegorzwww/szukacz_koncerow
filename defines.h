#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <QString>
#include <QPixmap>



typedef struct artist_names_s {
    int token_no;
   QString full_name;
    QString lastfm_name;
    QString fb_name;
    QString songkick_name;
} artist_names_t;


typedef struct find_artist_s {
    QString name;
    int listeners;
    QString category;
    QString url;
    QString pix_url;
} find_artist_t;


static const QString ARTIST_LOG_NAME = "artist_log_file";

#endif // DEFINES_H
