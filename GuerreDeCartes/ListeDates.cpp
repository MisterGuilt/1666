#include "ListeDates.hpp"

ListeDates::ListeDates(int numeroListe)
{
    if(numeroListe == 0)// Dates des tetes
    {
        dates.push_back(ROICOEUR);
        dates.push_back(DAMECOEUR);
        dates.push_back(VALETCOEUR);
        dates.push_back(ROIPIQUE);
        dates.push_back(DAMEPIQUE);
        dates.push_back(VALETPIQUE);
        dates.push_back(ROICARREAU);
        dates.push_back(DAMECARREAU);
        dates.push_back(VALETCARREAU);
        dates.push_back(ROITREFLE);
        dates.push_back(DAMETREFLE);
        dates.push_back(VALETTREFLE);
    }
    if(numeroListe == 1)// Dates maudites
    {
        dates.push_back(UN);
        dates.push_back(DEUX);
        dates.push_back(TROIS);
        dates.push_back(QUATRE);
        dates.push_back(CINQ);
        dates.push_back(SIX);
        dates.push_back(SEPT);
    }
}

int ListeDates::getDate()
{
    int recup = dates[0];
    dates.erase(dates.begin());
    return recup;
}

int ListeDates::getNombreDates()
{
    return dates.size();
}
