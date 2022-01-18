# Adventure-Game
  ![](https://cdn-www.comingsoon.net/assets/uploads/2021/01/lord-of-the-rings-e1610547648423.jpg)

This game can be run in, for example, Ubuntu by first compiling the projekti.c file. To do this you can use a program like gcc to compile it.

This repo contains a Makefile, so you can just type "make" to the terminal and it'll compile the projekti.c code to a file called "game".

## Tutorial

Here is what you can do in this game

Type:

  - **"A {Character name} {HP} {Weapon name} {ATK}"**, to create a character for the game. For example we can create a character named Frodo by typing:
  ```
    A Frodo 20 Sting 10
    Character Frodo has been added
  ```

  - **"L"**, to print the created characters. This lists the characters name, current health, weapon name, attack power and gained experience points from battle.
  ```
  L
  Name: Gollum HP: 12 Weapon: Hands ATK: 3 EXP 17
  Name: Frodo HP: 20 Weapon: Sting ATK: 10 EXP 0
  ```

  - **"H {Attackers name} {Defenders name}"**, to run an attack. The attacker and defender need to have been created for the attack to be successful. Also if a character has died, meaning their health is 0, they cannot attack nor defend.
  ```
    H Frodo Gollum
    The attack was successful
  ```
  - **"W {filename}"**, to save the current characters for a file that is located in the same place as this game.
  ```
    W LOTR
    Your file has been succesfully saved
  ```
  - **"O {filename}"**, to load a saved character file.
  ```
    O LOTR
    2 number of characters were succesfully downloaded from LOTR
  ```
  - **"Q"**, to exit the game.


### Errors
I don't believe the game has any big errors but I might have missed something.
