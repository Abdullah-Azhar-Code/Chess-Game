# Chess-Game
A fully functional Chess game built in C++ using SFML, featuring complete chess rules, move validation, check/checkmate detection, pawn promotion, captured-piece tracking, and a modern UI panel — all implemented without OOP for simplicity.
Chess Game — C++ & SFML
=======================
Overview
--------
This project is a fully functional Chess Game developed in C++ using the SFML graphics library.
The game features complete chess mechanics, turn-based gameplay, move validation,
check/checkmate
logic, pawn promotion, move highlighting, and a UI panel displaying game status and captured pieces.
Features
--------
• Full piece movement rules
• Check, Checkmate, Stalemate detection
• Pawn promotion
• Move highlighting (valid moves, selected piece, check state)
• Captured pieces tracking
• NonnOOP implementation for simplicity
• Right panel showing status, turn, and captures
• Mouse-driven interaction
Technical Requirements
----------------------
• C++17 or later
• SFML 2.5 or later
• Windows, Linux, or macOS support
• Recommended IDE: Visual Studio / CodeBlocks / CLion / VSCode
Folder Structure
----------------
Chess/
nnn Chess_25L_2537.cpp
nnn README.md
nnn chess_pieces/
n nnn pawn_white.png
n nnn pawn_black.png
n nnn rook_white.png
n nnn rook_black.png
n nnn (other textures)
nnn Font/
nnn Inter_28pt-SemiBold.ttf
Build Instructions
------------------
Windows:
1. Install SFML and configure include/lib directories.
2. Link the following modules:
- sfml-graphics
- sfml-window
- sfml-system
- sfml-audio
3. Ensure chess_pieces/ and Font/ are placed next to the .exe.
4. Compile and run.
Linux:
g++ Chess_25L_2537.cpp -o chess -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./chess
Internal Logic Summary
----------------------
• Board Representation:
- pieces_names[8][8] stores textual names for all pieces
- chessboard_pieces[8][8] stores sprite objects
• Move Storage:
- valid_moves[64][2] stores generated legal moves
• Captured Pieces:
- whiteCaptured[32]
- blackCaptured[32]
• UI Elements:
- turnText: Displays the current player's turn
- statusText: Shows "Check", "Checkmate", "Stalemate"
- whiteCapturedLabel / blackCapturedLabel: Lists captures
- rightPanel: Gray UI panel on the right side
Gameplay Logic
--------------
• User clicks a piece ® highlights valid moves
• Clicking a highlighted square ® moves the piece
• After every move:
- Turn switches
- Board updates
- Captured pieces update
- Check/Checkmate/Stalemate reevaluated
• King safety is ensured by temporary board simulation
• Pawn promotion triggers when a pawn reaches last rank
Missing / Future Features
-------------------------
• Castling
• En Passant
• AI Opponent
• Undo/Redo System
• Timers / Match History
• Better UI Layout
• Sound Effects
Author
------
Developed by: Abdullah Azhar
Purpose: Educational chess logic and SFML project.




