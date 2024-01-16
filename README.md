[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# 20 Question (Single / Multi Player)

# Team Name:

### JAC(k)
- Andrew Liu
- Minh (Carmin) Vuong
- Jiayu Yan

# Project Description:

Our project is a mystery word guesser game that enables users to guess a word based off of a series of yes or no questions. Our game contains 2 modes: single or multi player mode.

## "20 questions (S)" - Single Player Mode (1 guesser)
The 1st mode is the single player 20 questions game. The boss (server) answers the questions and determines the object being guessed. The player (client) has 20 questions to guess this object. The player can ask up to 20 yes-or-no questions to determine what object the answerer is thinking about. If the player is able to guess the mystery object in 20 questions or less, they win. Otherwise, they lose.

## "20 questions (M)" - Multi Player Mode (up to 5 guesser)
The 2nd mode in our game is the multi player version of 20 questions. The boss (server) is responsible for answering questions and determining the object that is being guessed. Up to 5 players (clients) are allowed to join a single game at once and each player have unlimited number of guesses to guess the word until one player gets it, becoming the winner.

# Instructions:

## 20 questions (S)

1. Run `make compile`
2. One person (boss) will run `./serverexe 1` to play in the single player mode
3. When the terminal displays ``Waiting for client to connect...``, another player (guesser) will connect by running  `./clientexe 1`.
4. The boss will see `Client connected!` and be prompted to enter their secret word.
5. The guesser will thenbe prompted to enter their name
6. After that, they will begin asking the questions.
6. The back-and-forth of questions and answers will continue until the guesser correctly identifies the mystery object, where the boss will type in `ans`, OR the guesser runs out of attempts.

## 20 questions (M)
1. Run `make compile`
2. One person (boss) will run `./serverexe 2` to play in the multi player mode
3. When the terminal displays ``Waiting for client to connect...``, the boss will enter the secert word, and other players (guessers) will connect by EACH running  `./clientexe 2`.
4. The boss will see `Client connected!` for each user that connects
5. The guesser will then be prompted to enter their name
6. After that, they will begin asking the questions.
6. The back-and-forth of questions and answers will continue until one guesser correctly identifies the mystery object OR when boss decides to end the game.

# Bugs:

**Good luck and have fun!!!**
