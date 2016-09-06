#ifndef EVENT_TOKEN_H
#define EVENT_TOKEN_H
#include <string>
#include <QString>


#define MAX_NUMBER_OF_TOKENS 50

using namespace std;
using std::string;

class ArtistToken
{
public:
    ArtistToken();

    int  occurance_no;
    QString articst_name;
    long occurance_tab[MAX_NUMBER_OF_TOKENS];
    QString events_date[MAX_NUMBER_OF_TOKENS];
    QString events_name[MAX_NUMBER_OF_TOKENS];
    QString events_city[MAX_NUMBER_OF_TOKENS];
    QString events_country[MAX_NUMBER_OF_TOKENS];


};

#endif // EVENT_TOKEN_H
