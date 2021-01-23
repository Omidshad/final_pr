#include "mainwindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <QApplication>

using namespace sf;
using namespace std;


int main(int argc, char *argv[])
{
    RenderWindow window(VideoMode(1080, 720),"TODO");
    window.setFramerateLimit(60);

    //draw line for x
    RectangleShape linex;
    linex.setSize(Vector2f(window.getSize().x , 3.f));
    linex.setPosition(window.getSize().x /4 - 268, window.getSize().y /5 - 10 );
    linex.setFillColor(Color(128,128,128));

    //draw line for y
    RectangleShape liney;
    liney.setSize(Vector2f(3.f, window.getSize().y + 100.f));
    liney.setPosition(Vector2f(window.getSize().x /5 - 81.f, window.getSize().y /4 - 179.f));
    liney.setFillColor(Color(128,128,128));

    //draw add icon
    Texture add;
    if(!add.loadFromFile("C:/Users/king/Music/Qt/5/5/image/add.png"))
        throw "cant find add image!!";
    Sprite spr;
    spr.setTexture(add);
    spr.setPosition(Vector2f(window.getSize().x - 80, window.getSize().y /2 + 258));
    spr.setScale(0.5f, 0.5f);

    //draw delete icon
    Texture del;
    if(!del.loadFromFile("C:/Users/king/Music/Qt/5/5/image/delete.png"))
        throw "cant find delete image!!";
    Sprite delet;
    delet.setTexture(del);
    delet.setPosition(Vector2f(window.getSize().x /4 - 260, window.getSize().y /9 - 50));
    delet.setScale(0.4f, 0.4f);

    //draw complete task icon
    Texture complete;
    if(!complete.loadFromFile("C:/Users/king/Music/Qt/5/5/image/complete.png"))
        throw "cant find complete img!!";
    Sprite comp;
    comp.setTexture(complete);
    comp.setPosition(Vector2f(window.getSize().x /4 - 195, window.getSize().y /9 - 50));
    comp.setScale(0.4f, 0.4f);


    //draw favorite icon
    Texture favorite;
    if(!favorite.loadFromFile("C:/Users/king/Music/Qt/5/5/image/favorite.png"))
        throw "cant find favorite image";
    Sprite unf;
    unf.setTexture(favorite);
    unf.setPosition(Vector2f(window.getSize().x - 80 , window.getSize().y /4  - 150));
    unf.setScale(Vector2f(0.4f, 0.4f));

    //draw edit icon
    Texture edit;
    if(!edit.loadFromFile("C:/Users/king/Music/Qt/5/5/image/edit.png"))
        throw "cant find edit image";
    Sprite ed;
    ed.setTexture(edit);
    ed.setPosition(Vector2f(delet.getPosition().x, delet.getPosition().y + delet.getGlobalBounds().height));
    ed.setScale(0.4f, 0.4f);
    ed.setColor(Color(255, 51, 240));

    // set background
    Texture background;
    if(!background.loadFromFile("C:/Users/king/Music/Qt/5/5/image/todo.png"))
        throw "cant find background image!";
    Sprite backg;
    backg.setTexture(background);
    backg.setPosition(Vector2f(window.getSize().x /20 - 52.5, window.getSize().y /20 - 35));
    backg.setColor(Color(255,255, 255));



    //loop program
    while (window.isOpen())
    {
        Event evet;
        while (window.pollEvent(evet))
        {
            if(evet.type == Event::Closed)
                window.close();
            if(evet.type == Event::KeyPressed)
                if(evet.key.code == Keyboard::Escape)
                    window.close();
        }

        window.clear(Color::White);
        window.draw(backg);
        window.draw(spr);
        window.draw(delet);
        window.draw(comp);
        window.draw(unf);
        window.draw(ed);
        window.draw(linex);
        window.draw(liney);

        window.display();


    }


    return 0;
}
