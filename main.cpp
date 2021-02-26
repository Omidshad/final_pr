
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "SFML/Window.hpp"

using namespace sf;
using namespace std;




///////////////////////////////////////////////////////////////////////
/// Definition The F_Player class
///
class F_Player
{
public:
    F_Player();
    virtual int Take_Pdamage() = 0;
    virtual int Show_Pdamage() = 0;
    virtual int Take_Strong_dm() = 0;

};

F_Player::F_Player()
{

}
////////////////////////////////////////////////////////////////////////
/// Definition The F_Enemy class
///
class F_Enemy
{
public:
    F_Enemy();
    virtual int Take_Edamage(int *) = 0;
    virtual int Show_Edamage(int )  = 0;

};

F_Enemy::F_Enemy()
{

}

////////////////////////////////////////////////////////////////////////
/// Definition The Shoot class
///
class Shoot
{
public:
    Sprite shape;

    Shoot(Texture *text, Vector2f windowSize);

};
////////////////////////////////////////////////////////////////////////
/// Definition The Player class
///

class Player : public F_Player
{
private:
    int HP;
    int HPmax;

public:
    Sprite shape;
    Texture *text;
    int Take_Pdamage() override;
    int Show_Pdamage() override;
    int Take_Strong_dm() override;
    Player(Texture *t);
    vector<Shoot> bullets;

};
/////////////////////////////////////////////////////////////////////////
/// Definition Enemy class
///

class Enemy : public F_Enemy
{
private:
    int HP;
    int HPmax;

public:
    Sprite shape;
    Enemy(Texture *texture, Vector2u pos);
    int Take_Edamage(int *) override;
    int Show_Edamage(int ) override;

};

/////////////////////////////////////////////////////////////////////////////
///definition The strong_Enemy class
///
class Strong_Enemy : public F_Enemy
{
private:
    int strong_HP;
    int strong_HPmax;

public:
    Sprite shape;
    Strong_Enemy(Texture *t, Vector2u s);
    int Take_Edamage(int *) override;
    int Show_Edamage(int ) override;

};

////////////////////////////////////////////////////////////////////////////
Player::Player(Texture *tex)
{
    HP = 10;
    HPmax = HP;
    HP +=3;
    this->text = tex;
    this-> shape.setTexture(*tex);
    this->shape.setScale(0.22f,0.22f);
    Take_Strong_dm();
    Take_Pdamage();
    Show_Pdamage();

}

int Player::Take_Pdamage()
{
    //*H = HP;
    HP--;
    return HP;
}

int Player::Show_Pdamage()
{
    //*HM = HPmax;
    return HPmax;
}

int Player::Take_Strong_dm()
{
    //*HS = HP;
    HP  -= 2 ;
    return HP;
}
///////////////////////////////////////////////////////////////////////////////

Shoot::Shoot(Texture *tex, Vector2f poss)
{
    this->shape.setTexture(*tex);
    this->shape.setScale(0.06f,0.06f);
    this->shape.setPosition(poss);
}
///////////////////////////////////////////////////////////////////////////////

Enemy::Enemy(Texture *text, Vector2u windowSize)
{
    this->HPmax = 2;
    this->HP = this->HPmax;

    this->shape.setTexture(*text);
    this->shape.setScale(0.25f, 0.25f);
    this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getLocalBounds().height));
    Take_Edamage(&HP);
    Show_Edamage(HPmax);
}


int Enemy::Take_Edamage(int *a)
{
    *a = HP;
    HP--;
    return HP;
}

int Enemy::Show_Edamage(int sh)
{
    sh = HPmax;
    return sh;
}
////////////////////////////////////////////////////////////////////////////////////


Strong_Enemy::Strong_Enemy(Texture *texture, Vector2u size)
{
    this->strong_HPmax = 1;
    this->strong_HP = this->strong_HPmax;

    this->shape.setTexture(*texture);
    this->shape.setScale(0.19f, 0.19f);
    this->shape.setPosition(size.x - this->shape.getGlobalBounds().width, rand() % (int)(size.y - this->shape.getLocalBounds().height));
    Take_Edamage(&strong_HP);
    Show_Edamage(strong_HPmax);

}

int Strong_Enemy::Take_Edamage(int *h)
{
    *h = strong_HP;
    strong_HP--;
    return strong_HP;

}

int Strong_Enemy::Show_Edamage(int a)
{
    a = strong_HPmax;
    return a;
}





//////////////////////////////////////////main program
int main(int argc, char *argv[])
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1080,800),"Spaceship Game!", Style::Default);
    window.setFramerateLimit(60);
    int count = 10;


    /////////init text
    Font font;
    font.loadFromFile("C:/Users/king/Music/Qt/5/5/Unisono-Quickpath-free.otf");

    /////////init picture
    Texture playertext;
    playertext.loadFromFile("C:/Users/king/Music/Qt/5/5/image/spship.png");
    /////////inti first enemy image
    Texture enemytext;
    enemytext.loadFromFile("C:/Users/king/Music/Qt/5/5/image/enemy.png");

    ////////init strong enemy image
    Texture strong_enemytext;
    strong_enemytext.loadFromFile("C:/Users/king/Music/Qt/5/5/image/enemy_strong.png");

    ////////init bullets image
    Texture shoottext;
    shoottext.loadFromFile("C:/Users/king/Music/Qt/5/5/image/misslie.png");

    //////////score init
    Text score;
    score.setFont(font);
    score.setCharacterSize(25);
    score.setFillColor(Color::White);
    score.setPosition(10.f, 10.f);

    //////////Game Over
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(35);
    gameOver.setFillColor(Color::Red);
    gameOver.setPosition(220.f, window.getSize().y / 2);
    gameOver.setString("Game Over!!");


    ///////////inti palyer
    Player pl(&playertext);
    int shoot_time = 15;
    Text hptext;
    hptext.setFont(font);
    hptext.setCharacterSize(14);
    hptext.setFillColor(Color::White);
    int score_int = 0;


    ////////////enemy init
    vector<Enemy> enemies;
    int enemy_time = 0;
    enemies.push_back(Enemy(&enemytext,window.getSize()));
    Text ehptext;
    ehptext.setFont(font);
    ehptext.setCharacterSize(14);
    ehptext.setFillColor(Color::White);

    /////////////strong enemy inti
    vector<Strong_Enemy> str_enemies;
    int strong_time = 0;
    str_enemies.push_back(Strong_Enemy(&strong_enemytext, window.getSize()));


    ///////////while loop game
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            if(event.KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        if(count > 0)
        {
            //player update
            if(Keyboard::isKeyPressed(Keyboard::W))
                    pl.shape.move(0.f, -7.f);
            if(Keyboard::isKeyPressed(Keyboard::A))
                    pl.shape.move(-7.f, 0.f);
            if(Keyboard::isKeyPressed(Keyboard::S))
                    pl.shape.move(0.f, 7.f);
            if(Keyboard::isKeyPressed(Keyboard::D))
                    pl.shape.move(7.f, 0.f);

            hptext.setPosition(pl.shape.getPosition().x, pl.shape.getPosition().y - hptext.getGlobalBounds().height);

            //collision with window
            if(pl.shape.getPosition().x <= 0)   //left
            {
                pl.shape.setPosition(0.f, pl.shape.getPosition().y);
            }
            if(pl.shape.getPosition().x >= window.getSize().x - pl.shape.getGlobalBounds().width)    //right
            {
                pl.shape.setPosition( window.getSize().x - pl.shape.getGlobalBounds().width, pl.shape.getPosition().y);
            }
            if(pl.shape.getPosition().y <=0)    //top
            {
                pl.shape.setPosition(pl.shape.getPosition().x, 0.f);
            }
            if(pl.shape.getPosition().y >= window.getSize().y - pl.shape.getGlobalBounds().height)   //bottom
            {
                pl.shape.setPosition(pl.shape.getPosition().x, window.getSize().y - pl.shape.getGlobalBounds().height);
            }

            //draw score
            score.setString("Score: " + to_string(score_int));

            //update contorol
            if(shoot_time < 10)
            {
                shoot_time++;
            }

            if(Mouse::isButtonPressed(Mouse::Left) && shoot_time >= 10)     //shooting
            {
                pl.bullets.push_back(Shoot(&shoottext, pl.shape.getPosition()));
                shoot_time = 0;
            }

            //bullets
            for(size_t i=0; i<pl.bullets.size(); i++)
            {
                //move bullets
                pl.bullets[i].shape.move(18.f, 0.f);

                //out of window
                if(pl.bullets[i].shape.getPosition().x > window.getSize().x)
                {
                    pl.bullets.erase(pl.bullets.begin() + i);
                    break;
                }

                //enemy collision
                for(size_t j =0; j< enemies.size(); j++)
                {
                    if(pl.bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
                    {

                        int damage = 2;
                        if(enemies[j].Take_Edamage(&damage))
                        {
                            enemies.erase(enemies.begin() + j);
                            score_int++;
                        }

                        pl.bullets.erase(pl.bullets.begin() + i);
                        break;
                    }
                }

                //Strong enemy colision
                for(size_t k=0; k < str_enemies.size(); k++)
                {
                    if(pl.bullets[i].shape.getGlobalBounds().intersects(str_enemies[k].shape.getGlobalBounds()))
                    {

                        int s_damage = 1;
                        if(str_enemies[k].Take_Edamage(&s_damage))
                        {
                            str_enemies.erase(str_enemies.begin() + k);
                            score_int += 3;
                        }

                        pl.bullets.erase(pl.bullets.begin() + i);
                        break;
                    }
                }


            }

            //update enemies
            for(size_t i =0; i<enemies.size(); i++)
            {
                enemies[i].shape.move(-6.f, 0);


                if(enemies[i].shape.getPosition().y <= 0 - enemies[i].shape.getGlobalBounds().width)
                {
                    enemies.erase(enemies.begin() + i);
                    break;
                }
                if(enemies[i].shape.getGlobalBounds().intersects(pl.shape.getGlobalBounds()))
                {

                    hptext.setString(to_string(pl.Take_Pdamage()) + "/" + to_string(pl.Show_Pdamage()));
                    enemies.erase(enemies.begin() + i);
                    count--;
                    break;

                }
            }

            for(size_t i =0; i<str_enemies.size(); i++)
            {

                str_enemies[i].shape.move(-7.f, 0);

                if(str_enemies[i].shape.getPosition().y <= 0 - str_enemies[i].shape.getGlobalBounds().width)
                {
                    str_enemies.erase(str_enemies.begin() + i);
                    break;
                }

                if(str_enemies[i].shape.getGlobalBounds().intersects(pl.shape.getGlobalBounds()))
                {

                    hptext.setString(to_string(pl.Take_Strong_dm()) + "/" + to_string(pl.Show_Pdamage()));
                    str_enemies.erase(str_enemies.begin() + i);
                    count -= 2;
                    break;
                }

            }


            if(enemy_time < 55)
                enemy_time++;

            if(enemy_time >= 55)
            {
                enemies.push_back(Enemy(&enemytext,window.getSize()));
                enemy_time = 0;
            }

            if(strong_time < 150)
                strong_time++;

            if(strong_time >= 150)
            {
                str_enemies.push_back(Strong_Enemy(&strong_enemytext, window.getSize()));
                strong_time = 0;
            }
        }

        //draw ===================================================== draw
        window.clear();

        //Bullets
        window.draw(pl.shape);
        for(size_t i=0; i<pl.bullets.size(); i++)
        {
            window.draw(pl.bullets[i].shape);
        }

        //Enemy
        for(size_t i =0; i<enemies.size(); i++)
        {
            int weak_enemy = 2;
            ehptext.setString(to_string(enemies[i].Show_Edamage(weak_enemy)));
            ehptext.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - ehptext.getGlobalBounds().height);
            window.draw(ehptext);
            window.draw(enemies[i].shape);
        }

        //Strong enemy
        for(size_t j = 0; j<str_enemies.size(); j++)
        {
            window.draw(str_enemies[j].shape);
        }

        //UI
        window.draw(hptext);
        window.draw(score);

        if(count < 1)
            window.draw(gameOver);

        window.display();
    }


    return 0;
}

