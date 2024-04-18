Project Overview:
This repository contains the source code for a two-player XO (tic-tac-toe) game developed in C++. The game leverages POSIX shared memory for inter-process communication, allowing two players to participate in the same game instance on a Linux system.

Features:

    Interactive Gameplay: Players can interact with the game through the console, entering coordinates to place their X or O on a dynamically sized game grid.
    Shared Memory Utilization: Utilizes system-level shared memory to sync game state between two processes, showcasing an effective use of IPC (Inter-Process Communication) mechanisms.
    Real-time Game Updates: Changes made by one player are immediately visible to the other player, ensuring a seamless gameplay experience.

How to Run:

    Dependencies: Ensure you have a C++ compiler and a Linux environment set up.
    Compilation: Use the following command to compile the programs:

    g++ -o player1 player1.cpp
    g++ -o player2 player2.cpp

    Execution: Start player1 first, and then run player2 in a separate terminal. Follow the on-screen prompts to make moves.

System Requirements:

    Linux OS
    C++11 or higher

Contributing:
Feel free to fork this project, submit pull requests, or open issues if you encounter any bugs or have suggestions for improvements.
