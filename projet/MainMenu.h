//
// Created by utrob on 27/12/2023.
//

#ifndef PROJET_MAINMENU_H
#define PROJET_MAINMENU_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define MAX_MAIN_MENU 4

class MainMenu {
    public:
    MainMenu(float width, float height);
    ~MainMenu();

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
private:
    int selectedItemIndex;
    Font font;
    Text mainMenu[MAX_MAIN_MENU];
};


#endif //PROJET_MAINMENU_H
