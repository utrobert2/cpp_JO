#include <SFML/Graphics.hpp>
#include "MainMenu.h"

const int windowWidth = 1980;
const int windowHeight = 1080;
const float skateboardSpeed = 200.0f;
const float jumpSpeed = 400.0f;
const float gravity = 800.0f;

class Trick {
public:
    Trick(const std::string& name, int difficulty, int points) : trickName(name), trickDifficulty(difficulty), trickPoints(points) {}

    virtual void performTrick() const {
        std::cout << "Performing trick: " << trickName << " (Difficulty: " << trickDifficulty << ")" << std::endl;
    }

    int getDifficulty() const {
        return trickDifficulty;
    }

    int getPoints() const {
        return trickPoints;
    }

protected:
    std::string trickName;
    int trickDifficulty;
    int trickPoints;
};

class Ollie : public Trick {
public:
    Ollie() : Trick("Ollie", 3, 10), ollieHeight(20.0) {}

    void performTrick() const override {
        std::cout << "Performing Ollie with a height of " << ollieHeight << " units." << std::endl;
    }

private:
    double ollieHeight;
};

class Kickflip : public Trick {
public:
    Kickflip() : Trick("Kickflip", 5, 20), spinSpeed(360) {}

    void performTrick() const override {
        std::cout << "Performing Kickflip with a spin speed of " << spinSpeed << " degrees." << std::endl;
    }

private:
    int spinSpeed;
};

class Player {
public:
    Player(const std::string& name) : playerName(name), playerScore(0) {}

    void increaseScore(int points) {
        playerScore += points;
    }

    int getPlayerScore() const {
        return playerScore;
    }

private:
    std::string playerName;
    int playerScore;
};

class Skateboard {
public:
    Skateboard() : skateboard(sf::Vector2f(50.0f, 20.0f)) {
        if (!skateboardTexture.loadFromFile("skateboard.png")) {
        }

        skateboard.setTexture(&skateboardTexture);
        skateboard.setSize(sf::Vector2f(100.0f, 40.0f)); // Ajuster la taille selon vos besoins
        skateboard.setOrigin(50.0f, 20.0f);
        skateboard.setPosition(windowWidth / 2.0f, windowHeight - 50.0f);

        isJumping = false;
        jumpHeight = 0.0f;

    }

    void move(int direction) {
        float deltaTime = 0.01f;
        float movement = direction * skateboardSpeed * deltaTime;

        if (isJumping) {
            jumpHeight -= gravity * deltaTime;
            skateboard.move(0.0f, -jumpHeight * deltaTime);

            // Terminer le saut lorsque la planche touche le sol
            if (skateboard.getPosition().y >= windowHeight - 50.0f) {
                skateboard.setPosition(skateboard.getPosition().x, windowHeight - 50.0f);
                isJumping = false;
            }
        } else {
            float movement = direction * skateboardSpeed * deltaTime;
            skateboard.move(movement, 0.0f);

            // Limiter le mouvement de la planche à roulettes dans la fenêtre
            if (skateboard.getPosition().x < 50.0f) {
                skateboard.setPosition(50.0f, skateboard.getPosition().y);
            }

            if (skateboard.getPosition().x > windowWidth - 50.0f) {
                skateboard.setPosition(windowWidth - 50.0f, skateboard.getPosition().y);
            }
        }

        
    }

    void jump() {
        if (!isJumping) {
                isJumping = true;
            while (skateboard.getPosition().y < windowHeight - 50.0f) {

                jumpHeight = jumpSpeed;
                //chooseRandomTrick();
            }
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(skateboard);
    }

private:
    sf::RectangleShape skateboard;
    sf::Texture skateboardTexture;
    
    bool isJumping;
    float jumpHeight;

    sf::Clock clock;

    std::unique_ptr<Trick> currentTrick;
};

class SkateboardGame {
public:
    SkateboardGame() : window(sf::VideoMode(windowWidth, windowHeight), "Skateboard Game") {}

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    Skateboard skateboard;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    skateboard.move(-1);
                } else if (event.key.code == sf::Keyboard::Right) {
                    skateboard.move(1);
                } else if (event.key.code == sf::Keyboard::Space) {
                    skateboard.jump();
                }
            }
        }
    }

    void update() {
        // Add any game logic here
    }

    void render() {
        window.clear(sf::Color::White);
        skateboard.draw(window);
        window.display();
    }
};

int main() {
    SkateboardGame game;
    RenderWindow menu(VideoMode(800, 600), "Skateboard Game");
    MainMenu mainMenu(menu.getSize().x, menu.getSize().y);



    while(menu.isOpen()) {
        Event event;
        while(menu.pollEvent(event)) {
            switch(event.type) {
                case Event::KeyReleased:
                    switch(event.key.code) {
                        case Keyboard::Up:
                            mainMenu.MoveUp();
                            break;
                        case Keyboard::Down:
                            mainMenu.MoveDown();
                            break;
                        case Keyboard::Return:
                            switch(mainMenu.GetPressedItem()) {
                                case 0:
                                    cout << "Play button has been pressed" << endl;
                                    menu.close();
                                    game.run();
                                    break;
                                case 1:
                                    cout << "Option button has been pressed" << endl;
                                    break;
                                case 2:
                                    cout << "Credits button has been pressed" << endl;
                                    break;
                                case 3:
                                    menu.close();
                                    break;
                            }
                            break;
                    }
                    break;
                case Event::Closed:
                    menu.close();
                    break;
            }
        }

        menu.clear();
        mainMenu.draw(menu);
        menu.display();
    }


    return 0;
}
