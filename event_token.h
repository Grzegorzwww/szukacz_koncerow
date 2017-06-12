#ifndef EVENT_TOKEN_H
#define EVENT_TOKEN_H
#include <string>
#include <QString>

static const int FACEBOOK_TOKEN  = 1;
static const int LASTFM_TOKEN  = 2;

#define MAX_NUMBER_OF_TOKENS 50

using namespace std;
using std::string;

class ArtistToken
{
public:
    ArtistToken();

    int  occurance_no;
    QString source;
    QString articst_name;
    int token_type;
    long occurance_tab[MAX_NUMBER_OF_TOKENS];
    QString events_date[MAX_NUMBER_OF_TOKENS];
    QString events_name[MAX_NUMBER_OF_TOKENS];
    QString events_city[MAX_NUMBER_OF_TOKENS];
    QString events_country[MAX_NUMBER_OF_TOKENS];

};
#endif // EVENT_TOKEN_H
