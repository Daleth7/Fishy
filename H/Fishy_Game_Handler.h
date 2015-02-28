/**
 *  \file Fishy_Game_Handler.h
 *  \brief Main handler for the game Fishy.
 */

#ifndef FISHY_GAME_HANDLER_CLASS_HEADER_2389832_JJHHHHHH_______
#define FISHY_GAME_HANDLER_CLASS_HEADER_2389832_JJHHHHHH_______

#include "Fishy_Tank_GUI.h"
#include "Fishy_GUI.h"
#include "Fish_Texture_Manager_GUI.h"
#include "Player_Fishy_AI.h"
#include "Constants_GUI.h"
#include "Fish_Codes.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>

#include <memory>

namespace GUI{
    namespace Handler{
        class Fishy : public sf::Drawable {
            public:
                using playerType    = Player_Fishy;
                using texType       = sf::Texture;
                using strType       = sf::Text;
                using fontType      = sf::Font;
                using bgType        = sf::RectangleShape;
                using resourceType  = FishTextureManager;

                enum class state : unsigned char {
                    Start, PlayGame, GameOver, Idle, Pause, Exit
                };

                bool mouseControl, pauseEnabled;

                /**
                 *  \brief Get the singleton instance of the class.
                 *
                 *  \param [in] vMode Video mode used by the window
                 *      this handler draws sprites to.
                 *  \param [in] startPop Starting population of fish
                 *      in the tank, not including the player.
                 *  \return A reference to the singleton object.
                 *
                 *  \details Parameters are for initializing the
                 *      singleton upon first call.
                 */
                static Fishy& instance(
                    const sf::VideoMode& vMode = sf::VideoMode(),
                    unsigned startPop = 0
                );
                /**
                 *  \brief Get the current state.
                 *
                 *  \return The current state of the game.
                 */
                state getState()const;
                /**
                 *  \brief Return whether or not the game is in the
                 *      specified state.
                 *
                 *  \param [in] stateTarget The state to check.
                 *  \return True if the game is in the state specified.
                 */
                bool isState(state stateTarget)const;
                /**
                 *  \brief Return whether or not the player has requested
                 *      to exit the game.
                 *
                 *  \return True if the player wants to exit the game.
                 */
                bool closeRequest()const;
                /**
                 *  \brief Set a new state for the game.
                 *
                 *  \param [in] newState The new state to be in.
                 */
                void setState(state newState);
                /**
                 *  \brief Update the game for the next frame.
                 *
                 *  \param [in] screen The render window or target
                 *      that the sprites are drawn to.
                 */
                void update(const sf::RenderWindow& screen);
                /**
                 *  \brief Regenerate fish in the tank, including
                 *      the player.
                 */
                void reset();
                /**
                 *  \brief Simply empty the tank and return the
                 *      player to the starting mass.
                 */
                void clear();

                Fishy(const Fishy&)             = delete;
                Fishy(Fishy&&)                  = delete;
                Fishy& operator=(const Fishy&)  = delete;
                Fishy& operator=(Fishy&&)       = delete;
                ~Fishy()                        = default;

            protected:
                /**
                 *  \brief Draw all sprites including fish and tank
                 *      to the render target.
                 *
                 *  \param [in] target The render target to draw the
                 *      sprites to.
                 *  \param [in] states The render states to configure
                 *      how the sprites will be drawn to the target.
                 */
                virtual void draw(
                    sf::RenderTarget& target,
                    sf::RenderStates states
                )const override;
                /**
                 *  \brief Update the start menu screen if in the
                 *      Start state.
                 *
                 *  \param [in] screen The render window or target
                 *      that the sprites are drawn to.
                 *
                 *  \details Check for button presses.
                 */
                virtual void updateStart(const sf::RenderWindow& screen);
                /**
                 *  \brief Update the game side if in the
                 *      PlayGame state.
                 *
                 *  \param [in] screen The render window or target
                 *      that the sprites are drawn to.
                 *
                 *  \details Move the AI fish and update the player.
                 */
                virtual void updateGame(const sf::RenderWindow& screen);
                /**
                 *  \brief Update the game over screen if in the
                 *      GameOver state.
                 *
                 *  \param [in] screen The render window or target
                 *      that the sprites are drawn to.
                 *
                 *  \details Check for button press to return
                 *      to the Start state.
                 */
                virtual void updateGameOver(const sf::RenderWindow& screen);
                /**
                 *  \brief Update the idle screen if in the
                 *      Auto state.
                 *
                 *  \param [in] screen The render window or target
                 *      that the sprites are drawn to.
                 *
                 *  \details Update the positions of all fish in
                 *      the tank.
                 */
                virtual void updateAuto(const sf::RenderWindow& screen);
                /**
                 *  \brief Draw the start menu screen.
                 *
                 *  \param [in] target The render target to draw the
                 *      sprites to.
                 *  \param [in] states The render states to configure
                 *      how the sprites will be drawn to the target.
                 */
                virtual void drawStart(
                    sf::RenderTarget& target,
                    sf::RenderStates states
                )const;
                /**
                 *  \brief Draw the game screen.
                 *
                 *  \param [in] target The render target to draw the
                 *      sprites to.
                 *  \param [in] states The render states to configure
                 *      how the sprites will be drawn to the target.
                 */
                virtual void drawGame(
                    sf::RenderTarget& target,
                    sf::RenderStates states
                )const;
                /**
                 *  \brief Draw the game over screen.
                 *
                 *  \param [in] target The render target to draw the
                 *      sprites to.
                 *  \param [in] states The render states to configure
                 *      how the sprites will be drawn to the target.
                 */
                virtual void drawGameOver(
                    sf::RenderTarget& target,
                    sf::RenderStates states
                )const;
                /**
                 *  \brief Draw the idle screen.
                 *
                 *  \param [in] target The render target to draw the
                 *      sprites to.
                 *  \param [in] states The render states to configure
                 *      how the sprites will be drawn to the target.
                 */
                virtual void drawAuto(
                    sf::RenderTarget& target,
                    sf::RenderStates states
                )const;
                /**
                 *  \brief Draw the pause screen.
                 *
                 *  \param [in] target The render target to draw the
                 *      sprites to.
                 *  \param [in] states The render states to configure
                 *      how the sprites will be drawn to the target.
                 */
                virtual void drawPause(
                    sf::RenderTarget& target,
                    sf::RenderStates states
                )const;
                /**
                 *  \brief Draw a semi-transparent sheet over the tank.
                 *
                 *  \param [in] target Render target to draw on.
                 *  \param [in] states States to dictate how the layover is drawn.
                 *  \param [in] size size of the layover to draw.
                 *  \param [in] colour Colour of the layover.
                 *
                 *  \details Used to apply subtle colour change to all objects.
                 */
                void drawColorLayover(
                    sf::RenderTarget& target,
                    sf::RenderStates states,
                    const sf::Vector2u& size,
                    const sf::Color& colour
                )const;

            private:
                /**
                 *  \brief Sole constructor for the singleton.
                 *
                 *  \param [in] vMode Video mode used by the window
                 *      the handler draws the sprites to.
                 *  \param [in] startPop Starting population of fish
                 *      in the tank, excluding the player.
                 */
                Fishy(
                    const sf::VideoMode& vMode,
                    unsigned startPop
                );

                resourceType            mRsrc;
                Tank                    mTank;
                texType                 mBgTex;
                playerType              mPlayer;
                fontType                mFont;
                state                   mState;
                bool
                                        mMenuPress, mPlayPress,
                                        mIdlePress, mExitPress,
                                        mReturnPress
                ;
                unsigned                mStartDiff;
                static constexpr playerType::mass_type
                    kStartMass = Constant::baseMass*1.10;
                static constexpr Data::Fish::code
                    kFishCodeMax = Data::Fish::code::Shark;
        };
    }
}

#endif
