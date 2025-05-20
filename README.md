# **Classic GameBoy Project**

Reimagining the magic of the 1989 Nintendo GameBoy through modern C++ and SFML, this project is a complete object-oriented gaming console featuring three iconic games: Snake, Wordle, and Hangman.

🛠 Tech Stack
Language: C++
Graphics Library: SFML 
Paradigm: Object-Oriented Programming (OOP)

🧠 Features
🕹️ GameBoy Console Simulation

Interactive startup and menu system

Player profiles with persistent scores and achievements

On/off state handling

🧑 Player System

Unique player sessions

Score tracking and high score memories

Achievement system (optional)

🎮 Game Suite

Snake: Classic snake movement, growing with food, increasing difficulty

Wordle: 5-letter word guessing with limited attempts, visual keyboard

Hangman: Word-guessing with hints, visual progress, and categories (optional)

🧱 OOP Principles Implemented
Inheritance: Shared game behaviors via a base Game class

Polymorphism: Unified game interface with custom behavior per game

Composition: Complex features built from reusable components

Aggregation: Player and GameBoy managing scores and states

Abstraction: Common input/display elements and game mechanics

📁 Structure
GameBoy - Main controller managing games and players

Game - Abstract base class for all games

SnakeGame, WordleGame, HangmanGame - Inherited implementations

Player - Handles profile, scores, and achievements
