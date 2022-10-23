
#include "Counter.h"


int main(int argc, char **argv)
{
    bool result = true;
    std::string path = "data/data.txt";
    
    std::string line;
    Statistics stats;

    result &= Counter::process(path, &stats);
    result &= Counter::print("output.txt", &stats);
    return 0;
}



// process nepocita jen znaky, ale spocita vic veci (vety, radky)
// vety - kazda konci prave 1 .!?
// optional mezery mezi vetami
// uvnitr vety slova nebo cisla
// mezi kazdym minimalne 1 mezera
// slovo obsahuje pouze znaky anglicke abecedy
// cislo vyhradne dekadicke cislice
// desetinna cisla -> desetinna . (za kterou je urcite dalsi cislice)
// konce radku mezi vetami a mezi slovy nebo mezi cisly -> get_line
// isdigit(), isalpha() - pouzit s charem, vraci true/false
// pocet radku, vet, slov, cisel, celkovy soucet hodnot vsech prirozenych, soucet hodnot vsech desetinnych
// symbol konce radku nepocitam
// symbols = pocet tecek, vykricniku a otazniku


// odevzdavat jen counter a statistics (.hpp, .cpp)