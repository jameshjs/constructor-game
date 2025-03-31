# 🏗️ Constructor – A Settlers of Catan-Inspired Game

Constructor is a terminal-based strategy board game inspired by *Settlers of Catan*, adapted with a University of Waterloo twist. Built for CS246 (Winter 2024), this project supports 4 human players and features interactive gameplay through resource management, building, trading, and strategic planning.

---

## 🎮 Game Overview

As a budding student housing developer in Waterloo, your goal is to build residences and roads to earn building points. The first builder to reach **10 points** wins!

Players take turns rolling dice, collecting resources from adjacent tiles, and constructing buildings to expand their influence. Be wary of the geese – they’ll block resource production and let players steal from others!

---

## 🧱 Features

- 🗺️ **Dynamic Board Layout**
  - Supports static layouts and randomized tile generation.
  - Tile values and resources configurable via file input.

- 🎲 **Fair vs Loaded Dice**
  - Builders can switch between fair (random) or loaded (user-input) dice.

- 🏘️ **Building System**
  - Construct Basements, upgrade to Houses, and eventually to Towers.
  - Each upgrade increases resource yield and building points.

- 🔄 **Trading Mechanic**
  - Offer and accept trades with other players.

- 🦢 **Geese Mechanic**
  - Similar to the “robber” from Settlers. Blocks tiles and enables stealing.

- 💾 **Save/Load Games**
  - Pause and resume gameplay with persistent save files.

- 🖥️ **Command-Line Interface**
  - Run games with specific board layouts or seeds via CLI options.

---

## 🛠️ Technologies

- **Language**: C++
- **Interface**: Text-based (Standard Input/Output)
- **Concepts**: Object-Oriented Design, File I/O, Command Parsing

---

## 🚀 Getting Started

### Compile the Game
```bash
g++ -std=c++17 -o constructor *.cpp
