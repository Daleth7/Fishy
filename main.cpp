#include "Fishy_Game_Handler.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <cstddef>
#include <memory>
#include <sstream>

int main(){
    std::srand(std::time(nullptr));

        // Constants
    const sf::VideoMode vMode(600, 600);
    const std::size_t fpsLim(40);
    const std::string title = "Fishy";


    using namespace sf;

        // Track the actual frame rate
    Clock fpsClock;
    sf::Font fpsFont;
    if(!fpsFont.loadFromFile("Font/Aramis_Italic.ttf"))
        throw 0xBAD1;
    sf::Text fpsTxt("FPS: ", fpsFont, 12u);
        fpsTxt.move(550, 580);
        fpsTxt.setColor(sf::Color::Yellow);

        // Set up the window and screen
    RenderWindow screen(vMode, title);
        screen.setFramerateLimit(fpsLim);
    sf::Image icon;
        icon.loadFromFile("Sprites/icon.png");
        screen.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::Event event;

    GUI::Handler::Fishy& fishyGame
        = GUI::Handler::Fishy::instance(vMode, 25u);

    GUI::Handler::Fishy::state curState = fishyGame.getState();

        // Status text images for when something is en/disabled
    sf::Text enabledtxt("", fpsFont, 20u);
        enabledtxt.move(10, 10);
        enabledtxt.setColor(sf::Color::Green);
    bool flashtxt(false);
    unsigned txtframecount; // in frames
    auto flashTxt = [&flashtxt, &enabledtxt, &txtframecount]
        (bool status, std::string&& message)
    {
        const unsigned txtcounter(1u);    // in seconds
        txtframecount = fpsLim*txtcounter;
        enabledtxt.setString(message + (status ? " en" : " dis") + "abled");
        flashtxt = true;
    };

    while(screen.isOpen()){
        if(fishyGame.closeRequest()){
            screen.close();
            break;
        }
        if(!fishyGame.isState(GUI::Handler::Fishy::state::PlayGame)){
            fishyGame.mouseControl = false;
            screen.setMouseCursorVisible(true);
        }
        while(screen.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                    screen.close();
                    break;
                case Event::Resized:
                    screen.setSize({vMode.width, vMode.height});
                    break;
                case Event::LostFocus:
                    if(
                        !fishyGame.isState(GUI::Handler::Fishy::state::GameOver) &&
                        fishyGame.pauseEnabled
                    ){
                        curState = fishyGame.getState();
                        fishyGame.setState(GUI::Handler::Fishy::state::Pause);
                    }
                    break;
                case Event::GainedFocus:
                    fishyGame.setState(curState);
                    break;
                case Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Space:
                            if(!fishyGame.isState(GUI::Handler::Fishy::state::PlayGame))
                                break;
                            screen.setMouseCursorVisible(!(fishyGame.mouseControl
                                = !fishyGame.mouseControl));
                            flashTxt(fishyGame.mouseControl, "Mouse Control");
                            break;
                        case sf::Keyboard::P:
                            flashTxt(
                                fishyGame.pauseEnabled = !fishyGame.pauseEnabled,
                                "Pause Capability"
                            );
                            break;
                        default:
                            break;
                    }
                    break;
                default:    break;
            }
        }

        screen.clear();

        fishyGame.update(screen);
        if(!fishyGame.isState(GUI::Handler::Fishy::state::Pause))
            curState = fishyGame.getState();

        screen.draw(fishyGame);

            // Update the fps text
        float passedTime = fpsClock.restart().asSeconds();
        std::stringstream ss;
            ss.precision(2);
            ss << "FPS: " << (1.0f/passedTime);
        fpsTxt.setString(ss.str());
        screen.draw(fpsTxt);

            // Update the status text
        if(flashtxt){
            screen.draw(enabledtxt);
            if(!(txtframecount-- > 0u)) flashtxt = false;
        }

        screen.display();
    }

    return 0;
}
