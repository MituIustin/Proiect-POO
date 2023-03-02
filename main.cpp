#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>

class Joc{
private:
public:
    bool Conditie_Speciala = false;
    void Start()
    {

    }

};

class Carte{
private:
    int valoare;
    std::string culoare;
    std::string simbol;
public:

    Carte()
    {
        valoare = rand()%13+1;

        int nr_culoare = rand()%2;
        if(nr_culoare == 0) culoare = "rosu";
        else culoare = "negru";

        if(nr_culoare == 0)
        {
            int nr_simbol = rand()%2;
            if(nr_simbol == 0) simbol = "romb" ;
            else simbol = "inima";
        }
        else
        {
            int nr_simbol = rand()%2;
            if(nr_simbol == 0) simbol = "trefla" ;
            else simbol = "inima";
        }

    }
    Carte(int val, std::string cul, std::string sim)
    {
        valoare = val;
        culoare = cul;
        simbol = sim;
    }

    int CarteSpeciala( Carte c)
    {
        if(c.GetValoare() == 1) return 1;
        if(c.GetValoare() == 7) return 7;
        if(c.GetValoare() == 11) return 11;
        return 0;
    }

    void AfisareCarte()
    {
        std::cout<<valoare<<" "<<simbol<<" "<<culoare<<"\n";
    }

    int GetValoare()
    {
        return valoare;
    }
    std::string GetSimbol()
    {
        return simbol;
    }
    std::string GetCuloare()
    {
        return culoare;
    }

    ~Carte(){}
};

class Pachet{
private:
    std::vector<Carte> pachet;
    int nr_carti = 0;
public:
    void AdaugareCarte(Carte c)
    {
        pachet.push_back(c);
        nr_carti++;
    }
    void AmestecarePachet()
    {
        std::random_shuffle(pachet.begin(),pachet.end());
    }
    void AfisarePachet()
    {
        for (auto it = pachet.begin(); it != pachet.end(); ++it)
        {
            it->AfisareCarte();
        }
        std::cout<<"\n";
    }
    Carte TragCarte()
    {
        nr_carti--;
        Carte c = pachet[nr_carti];
        pachet.pop_back();
        return c;
    }
    ~Pachet(){}
};

class Jucator{
private:
    std::vector<Carte> mana;
    int nr_carti=0;
public:


    void AfisareMana()
    {
        for (auto it = mana.begin(); it != mana.end(); ++it)
        {
            it->AfisareCarte();
        }
        std::cout<<"\n";
    }

    void EliminareCarte( Carte c)
    {
        for (auto it = mana.begin(); it != mana.end(); ++it)
        {
            if(it->GetValoare() == c.GetValoare() &&
                it->GetCuloare() == c.GetCuloare() &&
                it->GetSimbol() == c.GetSimbol())
            {
                mana.erase(it);
                nr_carti--;
                break;
            }
        }
    }
    void TragCarte(Carte c)
    {
        nr_carti++;
        mana.push_back(c);
    }

    ~Jucator(){}
};


void ConstruirePachet(Pachet &p)
{
    for(int i = 1; i<=13; i++)
    {
        Carte carte1( i , "rosu" , "romb");
        Carte carte2( i , "rosu" , "inima");
        Carte carte3( i , "negru" , "inima");
        Carte carte4( i , "nergu" , "trefla");
        p.AdaugareCarte(carte1);
        p.AdaugareCarte(carte2);
        p.AdaugareCarte(carte3);
        p.AdaugareCarte(carte4);
    }
}

int main()
{
    srand(time(0));

    int nr_jucatori = rand() %3 +2;
    std::cout<<nr_jucatori<<"\n";


    Pachet p;
    ConstruirePachet(p);
    p.AmestecarePachet();
    p.AfisarePachet();

    std::vector<Jucator> jucatori;

    for(int i=0; i<nr_jucatori; i++)
    {
        Jucator juc;

        for(int j=0; j<5; j++)
        {
            juc.TragCarte(p.TragCarte());
        }
        jucatori.push_back(juc);
    }

    p.AfisarePachet();

    for(int i=0; i<nr_jucatori; i++)
    {
        jucatori[i].AfisareMana();
    }


}