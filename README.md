[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# PROJECT NAME HERE

### JAC(k)
- Andrew Liu
- Minh (Carmin) Vuong
- Jiayu Yan
       
# Project Description:

Our project is a mystery word guesser game. We have two modes. 

## "20 questions" - Single Player Mode (1 guesser)
One of the modes is single-player which we call "20 questions." There is one server who is called the "answerer" who thinks of an object for the "guesser," the client, to guess. The guesser can ask up to 20 yes-or-no questions to determine what object the answerer is thinking about. If the questioner is able to guess the mystery object in 20 questions or less, they win. Otherwise, they lose.

## "2 minutes" - Multi Player Mode
  
# Instructions:

## "20 questions"

1. One person will run `make compile`
2. The answerer will run `make server` or `./serverexe` and input `1` into the terminal prompt to play this mode
3. When the terminal displays ``Waiting for client to connect...``, the guesser will connect by running either `make client` or `./clientexe`.
4. The answerer will see `Client connected!` and be prompted to enter their secret word.
5. The guesser will be prompted to enter their name. After that, they will begin asking the questions.
6. The back-and-forth of questions and answers will continue until the guesser correctly identifies the mystery object, where the answerer will type in `ans`, OR the guesser runs out of attempts.

**Good luck and have fun!!!**

## "2 minutes"

How does the user install/compile/run the program.
How does the user interact with this program?
