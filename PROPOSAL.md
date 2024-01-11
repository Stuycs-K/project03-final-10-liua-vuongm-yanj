# Final Project Proposal

## Group Members:
- Andrew Liu
- Minh (Carmin) Vuong
- Jiayu Yan

# Intentions:
2 Minutes - a guessing game where a player thinks of a secret object and the other players have to guess it, in under 2 minutes. The questions that can be asked must be yes or no questions. Players will be ranked based on the number of questions that they take to guess the object.

# Intended usage:
Multiple clients can connect to one main server, which will act as the player thinking of the word / secret object. The other clients will then be able to ask the server questions, which will then be answered with a yes or no (by the player using the server). The client will keep track of their individual number of guesses. Once the 2 minutes are up, the server will declare the game over and exit the program. A leaderboard will be made ranking each client. After each round the server will read the scores of the leaderboard file and eliminate the client ranked at the bottom until there is only 1 client left. At the end of each round, a transcript of the previous guesses and responses will be made and put into a file and then print out a copy to each client.

# Technical Details:
### topics covered in class
- Communication between server and its clients using sockets / pipes
- use select to handle multiple clients
- allocating memory to store information regarding previous guesses
- use signals to tell clients the game is over
- use files to create a transcript of the game for each client / leaderboard file for the server
- Using semaphores to manage flow of questions to the server (limiting to one client question at once)

### roles / responsibilities
Carmin
- storing information in arrays and files
- keep track of attempts and guesses
- detect winning

Jiayu
- fork/exec processes
- allow communication for multiple clients

Andrew
- pipes/sockets
- handle communication between server and clients
- implement semaphores so that server can only receive one question at a time

### algorithms / data structures
- structs for the players (attempts, guesses)
- arrays for the previous guesses
- sending guesses between server and clients

# Intended pacing:
- 1/5 - establish communication between server and client
- 1/8:
    - Jiayu: 
        - Client keeps track of their score
        - Updating the leaderboard with Client Score 
    - Andrew: 
        - work on semaphores to only allow one question to be sent to server at a time
        - limit semaphores to one client, test with two to see if block
    - Carmin: 
        - storing client's guesses in memory 
        - work on transcribing the client's guesses + response back into a file
- 1/9:
    - Jiayu:
        - Reading the leaderboard / elimiating the last client
    - Andrew:
        - continue working on semaphore implementation
    - Carmin:
        - continue working on transcribing guesses + response back into files
- 1/10:
    - Jiayu:
        - continue working on reading from leaderboard / eliminating the last client
    - Andrew:
        - finish semaphore implementation
    - Carmin:
        - finish the file transcription of the game
- 1/11:
    - Jiayu:
        - Finish up eliminating last client
    - Andrew:
        - add way for server to control when to start the game and how many players have joined
    - Carmin:
        - work on each client receiving transcript after a win
- 1/12:
    - Jiayu:
        - figure out how to signal the end of a game 
        - block eliminated client from continuing to the next round 
    - Andrew:
        - add semaphores to prevent a client from connecting if the game is already is progress    
    - Carmin:
        - continue working on transcription
- 1/13 (Weekend)
    - Jiayu:
        - Printing out the leaderboard file to the server at the end of the entire game
    - Andrew:
        - continue implementing the semaphores to prevent client from connecting if game in progress
    - Carmin:
        - finish working on each client receiving transcript after a win
- 1/14 (Weekend)
    - Jiayu:
        - Look over all implementations I've made.
    - Andrew:
        - add semaphores to limit the number of clients that can connect to the game  (if time permits)
    - Carmin:
        - review code and do more testing
- 1/15 (MLK Day)
    - Jiayu:
        - Finalize / fix up bugs
    - Andrew
        - Finalize / fix up bugs
    - Carmin:
        - Finalize / fix up bugs
- 1/16 - Due
