## Tic Tac Toe Project

1. Requirements:
   - Player vs computer
   - Player vs player
   - Multiple rendering systems : graphical/ console
2. Design:
   - Classes :
     - Renderer Interface (Display game to user)
     - Game State Interface (Decision process/win lose checking)
     - Control Interface (Way of interacting with the game)
     - Player Interface (Player information)
     - Player Impl - human player/ AI player
     - Control Impl - graphical / console
     - Renderer Impl - Graphical / console
     - Main Function
   - Implementation Details
     - Renderer Interface
       - update function
       - init function
       - destructor clean up
     - Game State Interface
       - init function
       - renderer
       - game data structure
       - game over check
       - save game data structure
       - save game data
       - load game data
       - destructor clean up
     - Player class
       - type
       - move
       - score keeping
       - name
       - controller
     - Main function
       - init all objects
       - run the game
