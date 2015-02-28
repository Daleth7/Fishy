#include "Fishy_Game_Handler.h"

#include "Fishy_Factory_GUI.h"
#include "Fish_Codes.h"
#include "Position_Generator_Outside.h"
#include "Constants_GUI.h"

#include <SFML/Window/Keyboard.hpp>

#include <stdexcept>
#include <sstream>
#include <cmath>
#include <cstdlib>

namespace GUI{
    namespace Handler{
        Fishy& Fishy::instance(
            const sf::VideoMode& vMode,
            unsigned difficulty
        ){
            static Fishy singleton(vMode, difficulty);
            return singleton;
        }

        bool Fishy::isState(state stateTarget)const
            {return mState == stateTarget;}

        bool Fishy::closeRequest()const
            {return mState == state::Exit;}

        Fishy::state Fishy::getState()const
            {return mState;}

        void Fishy::setState(state newState){
            mState = newState;
        }

        void Fishy::update(const sf::RenderWindow& screen){
            switch(mState){
                case state::Start:      updateStart(screen);    break;
                case state::PlayGame:   updateGame(screen);     break;
                case state::GameOver:   updateGameOver(screen); break;
                case state::Idle:       updateAuto(screen);     break;
                default:                break;
            }
        }

        void Fishy::reset(){
            mTank.clear();
            mPlayer = playerType(
                kStartMass, Data::Fish::code::Missingno,
                Collision::BoundEllipse{74, 26, 124, 26}, mRsrc
            );
            Fishy_Factory::fillTank(
                1.0, Data::Fish::code::Small_Feeder,
                mStartDiff, mTank, PosGen()
            );
        }

        void Fishy::clear(){mTank.clear();}

        void Fishy::draw(
            sf::RenderTarget& target,
            sf::RenderStates states
        )const{
            switch(mState){
                case state::Start:      drawStart(target, states);      break;
                case state::PlayGame:   drawGame(target, states);       break;
                case state::GameOver:   drawGameOver(target, states);   break;
                case state::Idle:       drawAuto(target, states);       break;
                case state::Pause:      drawPause(target, states);      break;
                default:                break;
            }
        }

        void Fishy::updateStart(const sf::RenderWindow& screen){
            this->updateAuto(screen);
            sf::IntRect area = mRsrc.getArea(Data::Fish::code::Button);
            area.left = (screen.getSize().x-area.width)/2u;
            area.top = (screen.getSize().y-area.height)/2u;

            if(
                (mPlayPress = area.contains(sf::Mouse::getPosition(screen))) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            )   mState = state::PlayGame;

            area.top += area.height*2;
            if(
                (mIdlePress = area.contains(sf::Mouse::getPosition(screen))) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            )   mState = state::Idle;

            area.top += area.height*2;
            if(
                (mExitPress = area.contains(sf::Mouse::getPosition(screen))) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            )   mState = state::Exit;
        }

        void Fishy::updateGame(const sf::RenderWindow& screen){
            using namespace sf;
            if(
                !mouseControl && (
                    Keyboard::isKeyPressed(Keyboard::W) ||
                    Keyboard::isKeyPressed(Keyboard::A) ||
                    Keyboard::isKeyPressed(Keyboard::S) ||
                    Keyboard::isKeyPressed(Keyboard::D) ||
                    Keyboard::isKeyPressed(Keyboard::Left) ||
                    Keyboard::isKeyPressed(Keyboard::Right) ||
                    Keyboard::isKeyPressed(Keyboard::Up) ||
                    Keyboard::isKeyPressed(Keyboard::Down)
                )
            )   mPlayer.update();

            if(mouseControl){
                sf::Vector2i
                    MPos(sf::Mouse::getPosition(screen)),
                    PPos(mPlayer.getPosition())
                ;
                const sf::Vector2f centerOffset{
                    mPlayer.getGlobalBounds().width/2,
                    mPlayer.getGlobalBounds().height/2
                    };
                PPos.x += centerOffset.x;
                PPos.x = MPos.x - PPos.x;
                if(PPos.x < 0 && !mPlayer.flipped())
                    mPlayer.flip();
                else if(PPos.x > 0 && mPlayer.flipped())
                    mPlayer.flip();

                mPlayer.setPosition(
                    sf::Mouse::getPosition(screen).x-centerOffset.x,
                    sf::Mouse::getPosition(screen).y-centerOffset.y
                );
            }
            for(auto it = mTank.begin(); it != mTank.end(); ++it){
                auto& fish = *(it->second);
                bool leave_loop(false);
                if(mPlayer.collided(fish)){
                    switch(mPlayer.try_to_eat(fish)){
                        case 1:
                            mPlayer.eat(fish);
                            mTank.remove(it);
                            if(std::rand()%2u){
                                Fishy_Factory::addFish(
                                    Constant::baseMass,
                                    Data::Fish::code::Small_Feeder,
                                    1, mTank, PosGen_Outside()
                                    );
                            }
                            leave_loop = true;
                            break;
                        case 0:
                            mState = state::GameOver;
                            leave_loop = true;
                            break;
                        default:    break;
                    }
                }
                if(leave_loop)  break;
            }

            this->updateAuto(screen);
        }

        void Fishy::updateGameOver(const sf::RenderWindow& screen){
            sf::IntRect area = mRsrc.getArea(Data::Fish::code::Button);
            area.left = (screen.getSize().x-area.width)/2u;
            area.top = (screen.getSize().y-area.height)/2u;

            if(
                (mPlayPress = area.contains(sf::Mouse::getPosition(screen))) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            ){
                mState = state::PlayGame;
                this->reset();
            }

            area.top += area.height*2;
            if(
                (mMenuPress = area.contains(sf::Mouse::getPosition(screen))) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            ){
                mState = state::Start;
                    // Set mouse outside the button area so that it doesn't
                    // accidentally trigger the button at the start menu
                sf::Mouse::setPosition({area.left-1, area.top-1}, screen);
            }

            area.top += area.height*2;
            if(
                (mExitPress = area.contains(sf::Mouse::getPosition(screen))) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            )   mState = state::Exit;
        }

        void Fishy::updateAuto(const sf::RenderWindow& screen){
            sf::IntRect area = mRsrc.getArea(Data::Fish::code::ReturnButton);
            area.left = 10;
            area.top = screen.getSize().y-area.height - 10;

            if(
                (mReturnPress = area.contains(sf::Mouse::getPosition(screen))) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
            ){
                mState = state::Start;
                return;
            }

            static unsigned countDown(500u);
            const Data::Fish::raw_type lim
                = static_cast<Data::Fish::raw_type>(kFishCodeMax);
            if(--countDown == 0u){
                countDown = std::rand()%5u+1u;
                while(countDown-- > 0){
                    for(auto iter(mTank.begin()); iter != mTank.end(); ++iter){
                        sf::FloatRect bounds = iter->second->getGlobalBounds();
                        if(
                            (bounds.left+bounds.width) < 0u ||
                            (bounds.top+bounds.height) < 0u ||
                            screen.getSize().x < bounds.left ||
                            screen.getSize().y < bounds.top
                        ){
                            mTank.remove(iter);
                            break;
                        }
                    }
                }
                countDown = std::rand()%5u+1u;
                while(countDown-- > 0){
                    Data::Fish::raw_type factor = (std::rand()%lim)+1u
                    ;
                    Data::Fish::code newFish = static_cast<Data::Fish::code>(factor);
                    Fishy_Factory::addFish(
                        Constant::baseMass*(1.0+factor/10.0), newFish, 1u,
                        mTank, PosGen_Outside()
                    );
                }
                countDown = 500u;
            }
            const unsigned minpop = 10u;
            if((std::rand()%2u == 0u) && mTank.population() < minpop){
                Fishy_Factory::fillTank(
                    Constant::baseMass, Data::Fish::code::Medium_Feeder,
                    std::rand()%minpop+1u, mTank, PosGen_Outside()
                );
            }
            mTank.update();
        }

        void Fishy::drawStart(
            sf::RenderTarget& target,
            sf::RenderStates states
        )const{
            using namespace sf;
            const Vector2u& size(target.getSize());
            const unsigned charSize(150u);
            Text pS("Fishy", mFont, charSize);
            pS.setColor({200, 200, 15, 255});
            pS.move((size.x-2.5*charSize)/2, (size.y-4.5*charSize)/2);

            this->drawAuto(target, states);
            this->drawColorLayover(target, states, size, {15, 56, 126, 80});
            target.draw(pS, states);

            Sprite menuButton;
            menuButton.setTexture(mRsrc.getSheet());
            IntRect
                area = mRsrc.getArea(Data::Fish::code::Button),
                area2 = mRsrc.getArea(Data::Fish::code::ButtonPressed)
            ;
            menuButton.setTextureRect(area);
            menuButton.move(
                (target.getSize().x-area.width)/2u,
                (target.getSize().y-area.height)/2u
            );

            pS.setColor({0, 0, 0, 255});
            pS.setCharacterSize(charSize/3);
            pS.move(charSize*0.925, target.getSize().y/2u+5);

            auto drawButton = [&]
                (sf::String&& s, bool shift, bool but){
                    pS.move(0, shift*area.height*2);
                    pS.setString(s);
                    menuButton.setTextureRect(but ? area2 : area);
                    menuButton.move(0, shift*area.height*2);
                    target.draw(menuButton, states);
                    target.draw(pS, states);
                };

            drawButton("Play", false, mPlayPress);
            drawButton("Idle", true, mIdlePress);
            drawButton("Exit", true, mExitPress);
        }

        void Fishy::drawGame(
            sf::RenderTarget& target,
            sf::RenderStates states
        )const{
            this->drawAuto(target, states);
            target.draw(mPlayer, states);
            std::stringstream ss;
                ss
                    << "Score: "
                    << std::lrint((mPlayer.mass() - kStartMass)*100)
                ;
            sf::Text score("Score: 0", mFont, 25u);
            score.setColor(sf::Color::White);
            score.setString(ss.str());
            target.draw(score, states);
        }

        void Fishy::drawGameOver(
            sf::RenderTarget& target,
            sf::RenderStates states
        )const{
            using namespace sf;
            const Vector2u& size(target.getSize());
            this->drawColorLayover(target, states, size, {255, 10, 14, 127});
            const unsigned charSize(100u);
            Text pS("Game Over", mFont, charSize);
            pS.setColor({200, 2, 5, 255});
            pS.move((size.x-4.5*charSize)/2, (size.y-3*charSize)/2);
            target.draw(pS, states);

            Sprite menuButton;
            menuButton.setTexture(mRsrc.getSheet());
            IntRect
                area = mRsrc.getArea(Data::Fish::code::Button),
                area2 = mRsrc.getArea(Data::Fish::code::ButtonPressed)
            ;
            menuButton.setTextureRect(area);
            menuButton.move(
                (target.getSize().x-area.width)/2u,
                (target.getSize().y-area.height)/2u
            );

            pS.setColor({0, 0, 0, 255});
            pS.setCharacterSize(charSize/3);
            pS.move(charSize*1.9, target.getSize().y*0.21);

            auto drawButton = [&]
                (sf::String&& s, bool shift, bool but){
                    pS.move(0, shift*area.height*2);
                    pS.setString(s);
                    menuButton.setTextureRect(but ? area2 : area);
                    menuButton.move(0, shift*area.height*2);
                    target.draw(menuButton, states);
                    target.draw(pS, states);
                };

            drawButton("Play", false, mPlayPress);
            drawButton("Menu", true, mMenuPress);
            drawButton("Exit", true, mExitPress);
        }

        void Fishy::drawAuto(
            sf::RenderTarget& target,
            sf::RenderStates states
        )const{
            target.draw(mTank, states);

            if(mState == state::Start)  return;
            using namespace sf;
            Sprite menuButton;
            menuButton.setTexture(mRsrc.getSheet());
            const IntRect area = mRsrc.getArea(
                mReturnPress
                    ? Data::Fish::code::ReturnButtonPressed
                    : Data::Fish::code::ReturnButton
                );
            menuButton.setTextureRect(area);
            menuButton.move(10, target.getSize().y-area.height - 10);

            target.draw(menuButton, states);
        }

        void Fishy::drawPause(
            sf::RenderTarget& target,
            sf::RenderStates states
        )const{
            using namespace sf;
            const Vector2u& size(target.getSize());
            const unsigned charSize(100u);
            Text pS("PAUSED", mFont, charSize);
            pS.setColor(Color::White);
            pS.move((size.x-3*charSize)/2, (size.y-charSize)/2);
            this->drawAuto(target, states);
            this->drawColorLayover(target, states, size, {127, 127, 127, 127});
            target.draw(pS, states);
        }

        void Fishy::drawColorLayover(
            sf::RenderTarget& target,
            sf::RenderStates states,
            const sf::Vector2u& size,
            const sf::Color& colour
        )const{
            using namespace sf;
            RectangleShape pBg({
                static_cast<float>(size.x),
                static_cast<float>(size.y)
            });
            pBg.setFillColor(colour);
            target.draw(pBg, states);
        }

        Fishy::Fishy(
            const sf::VideoMode& vMode,
            unsigned difficulty
        )
            : mouseControl(false), pauseEnabled(true)
            , mRsrc(), mTank(), mBgTex()
            , mPlayer(
                kStartMass, Data::Fish::code::Missingno,
                Collision::BoundEllipse{74, 26, 124, 26}, mRsrc
                )
            , mFont(), mState(state::Start)
            , mMenuPress(false), mPlayPress(false)
            , mIdlePress(false), mExitPress(false)
            , mReturnPress(false)
            , mStartDiff(difficulty)
        {
            if(!mRsrc.loadFromFile("Sprites/Fish.png"))
                throw std::runtime_error("Sprite sheet missing.");
            if(!mBgTex.loadFromFile("Sprites/reef_bg.png"))
                throw std::runtime_error("Bg file missing.");
            if(!mFont.loadFromFile("Font/data_latin.ttf"))
                throw std::runtime_error("Font missing.");
            mTank.setSize({
                static_cast<float>(vMode.width),
                static_cast<float>(vMode.height)
            });
            mTank.setResource(mRsrc);
            Fishy_Factory::fillTank(
                1.0, Data::Fish::code::Small_Feeder,
                mStartDiff, mTank, PosGen()
                );
            mTank.setTexture(mBgTex);
            mTank.setFillColor({255, 255, 255, 200});
        }
    }
}
