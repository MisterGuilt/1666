#include "constantes.hpp"

class ListeDates
{
    private:
        std::vector<int> dates;
    public:
        ListeDates(int numeroListe);
        int getDate();
        int getNombreDates();
};
