# C++ Brick Breaker

## Overview
A brick breaker / pong-style game built in C++ to practice core gameplay programming concepts:
game loop updates, input, collision handling, and simple game state.

## Features
- Paddle movement
- Ball movement + collision
- Brick destruction
- Win/Lose state and restart

## Code Structure
- `Game.*` - Main game loop and game state
- `Ball.*` - Ball movement and collision behavior
- `Box.*` - Bricks / collision objects
- `Console.*` - Rendering / drawing utilities (console-style)
- `BaseObject.*` - Shared object behavior / data

## Tech
- C++
- Visual Studio (.sln / .vcxproj)

## What I Learned
- Structuring a small game across multiple classes
- Debugging collision and state bugs
- Keeping gameplay code readable and modular
