#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>


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
    int CarteSpeciala()
    {
        //if(valoare == 1) return 1;
        //if(valoare == 7) return 7;
        //if(valoare == 11) return 11;
        return 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const Carte& ct)          //supraincarcare operator<<
    {
        os<<ct.valoare<<" "<<ct.simbol<<" "<<ct.culoare<<"\n";
        return os;
    }
    //supraincarcare operator >> (as avea nevoie)
    int GetValoare()
    {
        return valoare;
    }
    std::string GetSimbol()
    {
        return simbol;
    }       //getter
    std::string GetCuloare()
    {
        return culoare;
    }       //getter

    ~Carte(){}
};

class Jucator{
private:
    std::vector<Carte> mana;
    int nr_carti=0;
public:
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

    void AfisareMana()                              //functia asta va fi stearsa probabil, am folosit-o pt debugging
    {
        for (auto it = mana.begin(); it != mana.end(); ++it)
        {
            std::cout<<*it;
        }
        std::cout<<"\n";
    }


    void TragCarte(Carte c)
    {
        nr_carti++;
        mana.push_back(c);
    }

    void PuneCarte(Carte c)
    {
        EliminareCarte(c);
    }
    int Getnr_carti()                   //getter
    {
        return nr_carti;
    }

    std::vector<Carte> Getmana()
    {
        return mana;
    }

    ~Jucator(){}
};

class Pachet{
private:
    std::vector<Carte> pachet;
    int nr_carti = 0;
public:
    Pachet ()                                       //constructor
    {
        std::vector<Carte> _pachet;
        pachet = _pachet;
        int _nr_carti = 0;
        nr_carti = _nr_carti;
    }
    Pachet& operator=(const Pachet& other){             //operator de mutare
        pachet = std::move(other.pachet);
        nr_carti = std::move(other.nr_carti);
        return *this;
    }
    void EliminareCarte(Carte c)
    {
        for (auto it = pachet.begin(); it != pachet.end(); ++it)
        {
            if(it->GetValoare() == c.GetValoare() &&
               it->GetCuloare() == c.GetCuloare() &&
               it->GetSimbol() == c.GetSimbol())
            {
                pachet.erase(it);
                nr_carti--;
                break;
            }
        }
    }
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
            std::cout<<*it;
        }
        std::cout<<"\n";
    }
    int GetNr()
    {
        return nr_carti;
    }
    Carte TragCarte()
    {
        nr_carti--;
        Carte c = pachet[nr_carti];
        pachet.pop_back();
        return c;
    }
    Carte UltimaCarte ()
    {
        return *pachet.end();
    }


    ~Pachet(){}
};


class Joc{
private:
    int nr_jucatori;
    int jucator_prezent = 0;        //"a cui este randul"
    Pachet p;                       //pachetul din care se trag carti
    Pachet pjos;                    //pachetul de jos unde se pun carti
    std::vector<Jucator> jucatori;          //vetorul de jucatori
    bool conditie_speciala = false;
    bool joc_activ = true;

    void random_generator()
    {
        srand(time(0));
    }
    void creare_jucatori()                      //nr jucatorilor variaza intre 2 si 4
    {
        int _nr_jucatori = rand() %3 +2;
        nr_jucatori = _nr_jucatori;
        std::cout<<_nr_jucatori<<"\n";
    }
    void ConstruirePachet(Pachet &pr)
    {
        for(int i = 1; i<=13; i++)
        {
            Carte carte1( i , "rosu" , "romb");
            Carte carte2( i , "rosu" , "inima");
            Carte carte3( i , "negru" , "inima");
            Carte carte4( i , "nergu" , "trefla");
            pr.AdaugareCarte(carte1);
            pr.AdaugareCarte(carte2);
            pr.AdaugareCarte(carte3);
            pr.AdaugareCarte(carte4);
        }
    }
    void creare_pachet()                    //aici se creaza un pachet cu toate cartile, iar apoi se muta cu operator=
    {
        Pachet _p;
        ConstruirePachet(_p);
        _p.AmestecarePachet();
        _p.AfisarePachet();
        p = _p;                         // constructor de copiere cu operator=
    }
    void impartire_carti()                  //functia imparte cate 5 carti la fiecare jucator
    {
        for(int i=0; i<nr_jucatori; i++)
        {
            Jucator juc;

            for(int j=0; j<5; j++)
            {
                juc.TragCarte(p.TragCarte());
            }
            jucatori.push_back(juc);
        }
    }
    void creare_pachet_jos()            //metoda apelata o singura data la incepera jocului
    {
        pjos.AdaugareCarte(p.TragCarte());
    }
    bool verificare( Carte c)           //verific daca poate fi pusa jos cartea c
    {
        if((c.GetCuloare()==pjos.UltimaCarte().GetCuloare()
        && c.GetSimbol()==pjos.UltimaCarte().GetSimbol())
        || c.GetValoare()==pjos.UltimaCarte().GetValoare())
        {
            return true;
        }
        return false;
    }
    void joc_efectiv()
    {
        while(joc_activ)
        {
            if(jucator_prezent==nr_jucatori || jucator_prezent==0)
            {
                std::cout<<"Cartile tale: \n";
                jucatori[0].AfisareMana();
                std::cout<<"Cartea de jos este: "<<pjos.UltimaCarte();
                std::cout<<"Ce carte dai jos? \n";
                int optiune;
                std::cin>>optiune;                                  // ?????????????
                std::cout<<"ok";
                /*
                 *
                 *
                 *
                 *
                 *
                 */
                if(jucatori[0].Getnr_carti()==0)
                {
                    joc_activ = false;
                }

                jucator_prezent = 1;
            }
            else
            {
                if(!conditie_speciala)                      //aici botul contra care joci alege prima carte pe care o poate pune jos, si apoi o pune
                {
                    bool dat_jos=false;
                    for (auto it = jucatori[jucator_prezent].Getmana().begin(); it != jucatori[jucator_prezent].Getmana().end(); ++it)
                    {
                        if(verificare(*it))
                        {
                            jucatori[jucator_prezent].EliminareCarte(*it);
                            pjos.AdaugareCarte(*it);
                            dat_jos=true;
                            int val_carte = it->CarteSpeciala();
                            if(val_carte!=0) conditie_speciala =true;           //aici verific daca (,) carte este 1, 7 sau 11
                            else conditie_speciala = false;
                            break;
                        }
                    }
                    if(dat_jos == false)                        //daca jucatorul nu are ce sa dea jos, va trage o carte
                    {
                        jucatori[jucator_prezent].TragCarte(p.TragCarte());
                    }
                }
                /*
                 * partea de implementare cand exista o conditie speciala inca nu este implementata
                 *
                 *
                 *
                else
                {
                    int val_carte = pjos.UltimaCarte().CarteSpeciala();
                    switch (val_carte) {
                        case 1:
                            jucator_prezent++;
                            break;
                        case 7:


                    }
                    bool dat_jos=false;
                    for (auto it = jucatori[jucator_prezent].mana.begin(); it != jucatori[jucator_prezent].mana.end(); ++it)
                    {
                        if(verificare(*it))
                        {
                            jucatori[jucator_prezent].EliminareCarte(*it);
                            pjos.AdaugareCarte(*it);
                            dat_jos=true;
                            break;
                        }
                    }
                    if(dat_jos== false)
                    {
                        jucatori[jucator_prezent].TragCarte(p.TragCarte());
                    }
                }
                */
                jucator_prezent ++;
                if(jucatori[jucator_prezent].Getnr_carti()==0)
                {
                    joc_activ = false;
                }
            }
            if(p.GetNr()==0)                                        //aici verific daca pachetul din care se trag carti
            {                                                       //mai are carti, in caz negativ , se pastreaza doar
                Carte ult = pjos.UltimaCarte();                     //ultima carte din pachetul de jos , restul se
                p = pjos;                                           //muta cu operatorul= in pachetul din care se trag
                p.AmestecarePachet();                               //carti , iar apoi se amesteca
                pjos.AdaugareCarte(ult);
                p.EliminareCarte(ult);
            }
        }

    }
public:

    void Start()
    {
        random_generator();
        creare_jucatori();
        creare_pachet();
        impartire_carti();
        creare_pachet_jos();
        joc_efectiv();
    }

};



int main()
{
    Joc joc_nou;
    joc_nou.Start();
    std::cout<<"Joc terminat";

}