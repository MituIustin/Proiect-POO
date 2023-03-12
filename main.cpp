
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

class Card
{
private:

    int value;
    std::string color;
    std::string symbol;

public:

    Card()
    {
        value = 0;
        color = "pink";
        symbol = "square";
    }

    Card(int _value, std::string _color, std::string _symbol)
    {
        value = _value;
        color = _color;
        symbol = _symbol;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& c)
    {
        os<<c.value<<" "<<c.symbol<<" "<<c.color<<"\n";
        return os;
    }
    friend std::istream& operator>>(std::istream& in, Card& c)
    {
        in>>c.value;
        in>>c.symbol;
        in>>c.color;
        return in;
    }

    int get_value()
    {
        return value;
    }
    std::string get_color()
    {
        return color;
    }
    std::string get_symbol()
    {
        return symbol;
    }


};

class Pack
{

private:

    int number_of_cards;
    std::vector <Card> cards;

public:

    Pack ()
    {
        number_of_cards = 0;
    }

    void shuffle()
    {
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(cards), std::end(cards), rng);
    }

    void add_card( Card c)
    {
        number_of_cards++;
        cards.push_back(c);
    }

    Card get_first_card ()
    {
        Card c;
        c = cards[0];
        cards.erase(cards.begin());
        return c;
    }

    void add_top_card(Card c)
    {
        number_of_cards++;
        cards.push_back(c);
        std::rotate(cards.rbegin(), cards.rbegin() + 1, cards.rend());
    }
};

class Player
{
private:
    int number_of_cards = 0;
    std::vector <Card> players_cards;

    void draw_a_card(Card c)
    {
        players_cards.push_back(c);
        number_of_cards++;
    }


    void discard_a_card(Card c)
    {
        for(int i=0; i<number_of_cards; i++)
        {
            if(c.get_value() == players_cards[i].get_value()
               && c.get_color() == players_cards[i].get_color()
               && c.get_symbol() == players_cards[i].get_symbol())
            {
                players_cards.erase(players_cards.begin()+i);
                number_of_cards--;
                break;
            }
        }
    }

    Card pick_a_card()
    {
        Card c;
        std::cin>>c;
        return c;
    }

public:

    friend std::ostream& operator<<(std::ostream& os, const Player& p)
    {
        for(int i=0; i<p.number_of_cards; i++)
        {
            os<<p.players_cards[i];
        }
        return os;
    }

    void your_turn(Card c, Card c2, bool & dr, Card & returned_card)
    {
        std::cout<<"Carte de jos: ";
        std::cout<<c<<"\n";

        std::cout<<"Cartile tale:\n";

        for(int i=0; i<number_of_cards; i++)
        {
            std::cout<<players_cards[i];
        }

        std::cout<<"\n\nAlege 1 pentru a pune o carte jos\nAlege 2 pentru a trage o carte\n\n";

        int optiune;
        std::cin>>optiune;

        if(optiune == 1)
        {
            Card cc = pick_a_card();
            discard_a_card(cc);
            returned_card = cc;
        }
        else
        {
            draw_a_card(c2);
            dr = true;
        }


    }

    Card bot_turn(Card c1, Card c2, bool &dr, Card & returned_card)
    {
        std::cout<<"Cartile bot:\n";

        for(int i=0; i<number_of_cards; i++)
        {
            std::cout<<players_cards[i];
        }


        for(int i=0; i<number_of_cards; i++)
        {
            if((c1.get_color() == players_cards[i].get_color() &&
                c1.get_symbol() == players_cards[i].get_symbol())||
               c1.get_value() == players_cards[i].get_value())
            {
                returned_card = players_cards[i];
                discard_a_card(returned_card);
                break;

            }
        }
        draw_a_card(c2);
        dr=true;

    }

    void add_card(Card c)
    {
        number_of_cards++;
        players_cards.push_back(c);
    }


    int get_number_of_cards()
    {
        return number_of_cards;
    }
};


class Game
{
private:

    int number_of_players = 0;
    std::vector <Player> players;
    Pack draw_pack;
    Pack bottom_pack;


    void distribution()
    {
        for(int i=1; i<=5; i++)
        {
            for(int j=0; j<number_of_players; j++)
            {
                players[j].add_card(draw_pack.get_first_card());
            }
        }

        bottom_pack.add_card(draw_pack.get_first_card());

        for(int i=0; i<=3; i++)
        {
            std::cout<<players[i]<<"\n";

        }
    }

    void create_draw_pack()
    {
        for(int i=1; i<=13; i++)
        {
            Card card1(i, "rosie" , "romb");
            Card card2(i, "rosie" , "inima");
            Card card3(i, "neagra" , "trefla");
            Card card4(i, "neagra" , "inima");
            draw_pack.add_card(card1);
            draw_pack.add_card(card2);
            draw_pack.add_card(card3);
            draw_pack.add_card(card4);

        }
    }

    void create_players()
    {
        Player player1;
        Player player2;
        Player player3;
        Player player4;

        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        players.push_back(player4);

        number_of_players = 4;
    }

    void preparation()
    {
        create_draw_pack();
        draw_pack.shuffle();
        create_players();
    }

    bool playing()
    {
        for(int i=0; i<number_of_players; i++)
        {
            if(players[i].get_number_of_cards() == 0) return false;
        }
        return true;
    }

    void game_loop()
    {
        int turn = 0;
        while(playing())
        {
            if(turn==0 || turn==number_of_players)
            {
                Card possibly_drew_card = draw_pack.get_first_card();
                Card bottom_card = bottom_pack.get_first_card();
                Card returned_card;
                bool dr = true;

                players[0].your_turn(bottom_card, possibly_drew_card, dr, returned_card);


                if(dr == false)
                {
                    draw_pack.add_top_card(possibly_drew_card);
                    bottom_pack.add_card(returned_card);
                }
                else
                {
                    bottom_pack.add_top_card(bottom_card);

                }
                turn = 1;
            }
            else
            {
                Card possibly_drew_card = draw_pack.get_first_card();
                Card bottom_card = bottom_pack.get_first_card();
                Card returned_card;
                bool dr = true;

                players[turn].bot_turn(bottom_card, possibly_drew_card, dr, returned_card);
                if(dr == false)
                {
                    std::cout<<"Bot-ul a pus cartea: "<<returned_card;
                    draw_pack.add_top_card(possibly_drew_card);
                    bottom_pack.add_card(returned_card);
                }
                else
                {
                    std::cout<<"Bot-ul a tras o carte\n";
                    bottom_pack.add_top_card(bottom_card);
                }
                turn++;


            }
        }
    }

public:

    void start()
    {
        preparation();
        distribution();
        game_loop();
    }
};

int main()
{
    Game new_game;
    new_game.start();
    std::cout<<"End Game";
    return 0;
}
