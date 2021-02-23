
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "SFML/Window.hpp"

using namespace sf;
using namespace std;



class Shoot
{
public:
    Sprite shape;

    Shoot(Texture *text, Vector2f windowSize);

};
////////////////////////////////////////////////////////////////////////

class Player
{
private:
    int HP;
    int HPmax;

public:
    Sprite shape;
    Texture *text;
    int take_pdamage(int *);
    int show_phmax(int *);
    Player(Texture *);
    vector<Shoot> bullets;

};
////////////////////////////////////////////////////////////////////////

class Enemy
{
private:
    int HP;
    int HPmax;

public:
    Sprite shape;
    Enemy(Texture *texture,Vector2u pos);
    int take_edamage(int *);
    int show_Ephmaxe(int );

};
////////////////////////////////////////////////////////////////////////////


Player::Player(Texture *tex)
{
    this->HP = 10;
    this->HPmax = HP;
    this->text = tex;
    this-> shape.setTexture(*tex);
    this->shape.setScale(0.2f,0.2f);
    take_pdamage(&HP);
    show_phmax(&HPmax);

}

int Player::take_pdamage(int *H)
{
    *H = HP;
    --HP;
    return HP;
}

int Player::show_phmax(int *HM)
{
    *HM = HPmax;
    return HPmax;
}
/////////////////////////////////////////////////////////////////////////////

Shoot::Shoot(Texture *tex, Vector2f poss)
{
    this->shape.setTexture(*tex);
    this->shape.setScale(0.06f,0.06f);
    this->shape.setPosition(poss);
}

Enemy::Enemy(Texture *text, Vector2u windowSize)
{
    this->HPmax = 2;
    this->HP = this->HPmax;

    this->shape.setTexture(*text);
    this->shape.setScale(0.25f, 0.25f);
    this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getLocalBounds().height));
    take_edamage(&HP);
    //show_Ephmaxe(HPmax);
}


int Enemy::take_edamage(int *a)
{
    *a = HP;
    HP--;
    return HP;
}


int Enemy::show_Ephmaxe(int sh)
{
    sh = HPmax;
    return sh;
}
////////////////////////////////////////////////////////////////////////////////////



int main(int argc, char *argv[])
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1080,800),"Spaceship Game!", Style::Default);
    window.setFramerateLimit(60);
    int count = 10;


    //init text
    Font font;
    font.loadFromFile("C:/Users/king/Music/Qt/5/5/Unisono-Quickpath-free.otf");

    //init picture
    Texture playertext;
    playertext.loadFromFile("C:/Users/king/Music/Qt/5/5/image/spship.png");

    Texture enemytext;
    enemytext.loadFromFile("C:/Users/king/Music/Qt/5/5/image/enemy.png");

    Texture shoottext;
    shoottext.loadFromFile("C:/Users/king/Music/Qt/5/5/image/misslie.png");

    //score init
    Text score;
    score.setFont(font);
    score.setCharacterSize(25);
    score.setFillColor(Color::White);
    score.setPosition(10.f, 10.f);

    //gameOver
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(35);
    gameOver.setFillColor(Color::Red);
    gameOver.setPosition(220.f, window.getSize().y / 2);
    gameOver.setString("Game Over!!");


    //inti palyer
    Player pl(&playertext);
    int shoot_time = 15;
    Text hptext;
    hptext.setFont(font);
    hptext.setCharacterSize(14);
    hptext.setFillColor(Color::White);
    int score_int = 0;


    //enemy init
    vector<Enemy> enemies;
    int enemy_time = 0;
    enemies.push_back(Enemy(&enemytext,window.getSize()));
    Text ehptext;
    ehptext.setFont(font);
    ehptext.setCharacterSize(14);
    ehptext.setFillColor(Color::White);


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

        if(count > 1)
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
            if(shoot_time < 15)
            {
                shoot_time++;
            }

            if(Mouse::isButtonPressed(Mouse::Left) && shoot_time >= 15)     //shooting
            {
                pl.bullets.push_back(Shoot(&shoottext, pl.shape.getPosition()));
                shoot_time = 0;
            }

            //bullets
            for(size_t i=0; i<pl.bullets.size(); i++)
            {
                //move bullets
                pl.bullets[i].shape.move(20.f, 0.f);
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
                        if(enemies[j].take_edamage(&damage))
                        {
                            enemies.erase(enemies.begin() + j);
                            score_int++;
                        }
                        /*
                        else

                        {
                            damage--;
                            enemies[j].take_edamage(&damage);  //enemy take damage
                        }
                        */

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

                    int Heal = 10;
                    hptext.setString(to_string(pl.take_pdamage(&Heal)) + "/" + to_string(pl.show_phmax(&Heal)));
                    enemies.erase(enemies.begin() + i);
                    count--;
                    break;

                }

            }

            if(enemy_time < 100)
                enemy_time++;

            if(enemy_time >= 100)
            {
                enemies.push_back(Enemy(&enemytext,window.getSize()));
                enemy_time = 0;
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
            //ehptext.setString(to_string(enemies[i].show_Ephmaxe(i)) + "/" + to_string(enemies[i].take_edamage(0)));
            //ehptext.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - ehptext.getGlobalBounds().height);
            //window.draw(ehptext);
            window.draw(enemies[i].shape);
        }

        //UI
        window.draw(hptext);
        window.draw(score);
        if(count <= 1)
            window.draw(gameOver);

        window.display();
    }


    return 0;
}

