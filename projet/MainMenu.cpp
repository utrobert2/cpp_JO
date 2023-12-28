//
// Created by utrob on 27/12/2023.
//

#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("RomanAntique-Italic.ttf")) {
        cout << "Error loading font" << endl;
    }

    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::Red);
    mainMenu[0].setString("Play");
    mainMenu[0].setPosition(Vector2f(width / 2, height / (MAX_MAIN_MENU + 1) * 1));

    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Options");
    mainMenu[1].setPosition(Vector2f(width / 2, height / (MAX_MAIN_MENU + 1) * 2));

    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Credits");
    mainMenu[2].setPosition(Vector2f(width / 2, height / (MAX_MAIN_MENU + 1) * 3));

    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setPosition(Vector2f(width / 2, height / (MAX_MAIN_MENU + 1) * 4));

    selectedItemIndex = 0;
}

MainMenu::~MainMenu() {

}

void MainMenu::draw(RenderWindow& window) {
    for (int i = 0; i < MAX_MAIN_MENU; i++) {
        window.draw(mainMenu[i]);
    }
}

void MainMenu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {  //
        mainMenu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex--;
        mainMenu[selectedItemIndex].setFillColor(Color::Red);
    }
}

void MainMenu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_MAIN_MENU) {
        mainMenu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex++;
        mainMenu[selectedItemIndex].setFillColor(Color::Red);
    }
}