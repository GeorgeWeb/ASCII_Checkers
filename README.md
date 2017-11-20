# Modern C++ Checkers game with ASCII art

This project implements a game of checkers with an optimal AI functionality.<br/>
It was given as a final coursework for my Data Structures &amp; Algorithms module at university.<br/>
A freedom of language choice was given so C++ was my language of choice for this one.

Realtime <strong>CI</strong> feedback from <strong>appveyor.com</strong><br/>
[![Build status](https://ci.appveyor.com/api/projects/status/86jebt7qqtrw5mfj/branch/master?svg=true)](https://ci.appveyor.com/project/GeorgeWeb/ascii-checkers/branch/master)

## Controls
- moving: move Coord1 Coord2 (e.g. move C2 D1)
- undoing: undo (works continuously)
- redoing: redo (works continuously)
- saving: save "name" (not extensions needed - just the save name - e.g. WorstGameEvah)

## Future development
- implement alpha-beta prunning in the minimax algorithm for AI
- add a decent amount of unit tests ASAP
- implement good Serialization in C++
- add C++Amp for faster and more robust AI algorithm processing
- create a cross-platform build system using CMake
