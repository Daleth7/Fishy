Required for compilation:
    - Set search directories to include /SFML, /Data, and /H
    - When adding files to a project, include all .cpp files under /Src and /Data
    - Link the libraries, in order: lib/libsfml-graphics-s.a, lib/libsfml-window-s.a, lib/libsfml-system-s.a
      -- The listed libraries are for release build. For debug build, append "-d" at the end of each library name.
    - Define the macro SFML_STATIC
    - Enable C++11 on your compiler

A makefile to simplify compilation is under construction.


Messing with the code:
    - Total beginners:
      -- Open Src/Practice_Fishy_AI.cpp
      -- Practice changing the Fishy AI by modifying the function void Practice_Fishy::updateConcrete()
    - Beginners:
      -- Same as above but for Practice_Fishy_AI2
      -- Open Src/Fishy_Factory_GUI.cpp and uncomment the case Fishy::code_type::Shark
    - Not beginners:
      -- Look at Data/Fish_Codes.h for a list of available codes (you may add more)
      -- Create a class for your AI and inherit from the interface GUI::Fishy under H/Fishy_GUI.h
      -- Override the eat_concrete() and updateConcrete() members from GUI::Fishy
      -- Draw the sprite for your fish and place it in Sprites/Fish.png. Sprite borders follow GUI::Constant::imgWidth and GUI::Constant::imgHeight in H/Tile_Constants.h
      -- Open Src/Fishy_Factory_GUI.cpp and add your fish code to the switch case statement
      -- Open Fishy_Game_Handler and change kFishCodeMax at the bottom to your fish code instead of Shark
      
Reminders:
    - When not running the program through an IDE, the Font and Sprites directories must be in the same directory as the executable.