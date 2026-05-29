# Mini RPG

A lightweight C++ RPG game featuring real-time combat mechanics, cooldown-based abilities, multiple hero classes, and progressive dungeon floors with bosses.

## Gameplay Overview

Mini RPG is a console-based action RPG where the player chooses a hero class and fights through multiple stages of enemies and bosses.

Each stage introduces:
- Enemies with different stats
- A boss fight at the end
- Random post-combat bonuses
- Increasing difficulty per floor

## Hero Classes

### Mage
- High attack power
- Low speed
- Ability: Double attack burst

### Spartan
- Balanced stats
- High defense
- Ability: Stun enemy

### Assassin
- Very fast attacks
- Low defense
- Ability: Multi-hit combo

## Combat System

- Real-time input combat using keyboard
- Cooldown-based actions (attack / ability / dodge)
- Enemy attack warnings (dodge timing system)
- Stun mechanics
- Randomized bonus effects after fights

## Features

- 3 playable hero classes
- 3 dungeon floors
- Unique boss per floor
- Dynamic stat system (attack, defense, speed, HP)
- Cooldown-based ability system
- Dodge timing mechanic
- Post-fight upgrade system
- Real-time hybrid combat loop

## Controls

- A -> Attack
- D -> Dodge
- E -> Special ability
- S -> Show stats

## Build Instructions

Compile:

g++ -std=c++23 main.cpp characters.cpp bonus.cpp stage.cpp -o rpg_game

Run:

./rpg_game

## Project Structure

- main.cpp -> Game loop and stage progression
- stage.cpp -> Combat system and dungeon logic
- Characters.cpp -> Hero & enemy logic
- bonus.cpp -> Post-fight upgrade system
- tools.h -> Utility functions (timer, input, RNG)

## Design Highlights

- Cooldown-based combat instead of turn-based menus
- Timing-based dodge system
- Modular class design (Hero / Villain inheritance)
- Stage-based progression system
- Randomized stat bonuses for replayability
