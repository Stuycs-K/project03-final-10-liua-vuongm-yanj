[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# PROJECT NAME HERE

### JAC(k)
- Andrew Liu
- Minh (Carmin) Vuong
- Jiayu Yan
       
# Project Description:

Our project is a mystery word guesser game. We have two modes. 

## "20 questions" - Single Player Mode 
One single player mode which we call "20 questions." There is one server who is called "answerer" who thinks of an object for the "questioner," the client, to guess. The questioner can ask up to 20 yes-or-no questions to determine what object the answer is thinking about. If the questioner is able to guess the mystery object in 20 questions or less, they win. Otherwise, the answerer wins.

## "2 minutes" - Multi Player Mode
  
# Instructions:

## "20 questions"

Answerer run ./server and enter 1 into stdin to select the game mode 20 Questions. When it displays "Waiting for client to connect," tell the questioner to connect. The questioner will run ./client and after making a successful connection, the answerer will have "Client connected!" displayed in their terminal and be asked to set their word. The questioner will be asked to enter their name and be prompted to ask their first question. The number of questions left will be displayed in the questioner's terminal and when they ask a question, the answerer can respond with "yes," "no," or "ans" to signify that the questioner has correctly guessed the mystery object! Once the game is over, whether because the answerer has ran out of questions or guessed the mystery object, a transcript of the game will be printed in the questioner's terminal. It will also be stored in a txt file named "transcript_(Name).txt" where name is the stdin you provided when the answerer was prompted to enter their name. **Good luck and have fun!!!**

## "2 minutes"

How does the user install/compile/run the program.
How does the user interact with this program?
