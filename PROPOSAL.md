# Final Project Proposal

## Group Members:
- Andrew Liu
- Minh (Carmin) Vuong
- Jiayu Yan

# Intentions:
2 Minutes - a guessing game where a player thinks of a secret object and the other players have to guess it, in under 2 minutes. The questions that can be asked must be yes or no questions. Players will be ranked based on the number of questions that they take to guess the object.

# Intended usage:
Multiple clients can connect to one main server, which will act as the player thinking of the word / secret object. The other clients will then be able to ask the server questions, which will then be answered with a yes or no (by the player using the server). The client will keep track of their individual number of guesses. Once the 2 minutes are up, the server will declare the game over and exit the program. A leaderboard will be made ranking each client. After each round the server will read the scores of the leaderboard file and eliminate the client ranked at the bottom until there is only 1 client left. At the end of the final game, a transcript of the previous guesses and responses will be made and put into a file and then print out a copy to each client.

# Technical Details:
### topics covered in class
- Communication between server and its clients using sockets / pipes
- fork/exec processes to handle multiple clients
- allocating memory to store information regarding previous guesses
- use signals to tell clients the game is over
- use files to create a transcript of the game

### roles / responsibilities
Carmin
- storing information in arrays and files
- keep track of attempts and guesses

Jiayu
- fork/exec processes
- allow communication for multiple clients

Andrew
- pipes/sockets
- handle communication between server and clients

### algorithms / data structures
- structs for the players (attempts, guesses)
- arrays for the previous guesses
- sending guesses between server and clients

# Intended pacing:
- 1/5 - establish communication between server and client
- 1/9 - finish server logic
- 1/12 - possibly expand this to multiple clients and players
- 1/13 - add logic for a leaderboard, whoever guesses the quickest wins!
- 1/16 - Due
