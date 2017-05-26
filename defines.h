#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <QString>

#endif // DEFINES_H

typedef struct artist_names_s {
    int token_no;
   QString full_name;
    QString lastfm_name;
    QString fb_name;
    QString songkick_name;
} artist_names_t;


static const QString ARTIST_LOG_NAME = "artist_log_file";
