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
6. After entering their name users should type their first question into the empty new line that follows
7. The boss will then receive the question and will have the option to answer from (yes/no/ans)
8. After receiving the first answer from the boss the guesser will then be prompted to "Ask a question:"
6. The back-and-forth of questions and answers will continue until one guesser correctly identifies the mystery object OR when boss decides to end the game.

# Bugs:
- For multi player 20 question, when the user initially connects to a client, the first "Ask a question:" prompt will not show up. However, users are able to just enter their question into the empty line (which will then be sent to the server). All preceding questions will be prompted prior with the "Ask a question"
- There is no implementation in place to check when the client # exceeds the MAX capacity (5). Running based on assumption that client will stop joining once there are 5 players.
- When returning transcription files, there are sometimes random symbols at the end of the file



**Good luck and have fun!!!**
