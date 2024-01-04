# Final Project Proposal

## Group Members:
- Andrew Liu
- Minh (Carmin) Vuong
- Jiayu Yan

# Intentions:
20 Questions - a guessing game where a player thinks of a secret object and the other players have to guess it, in 20 attempts or less. The questions that can be asked must be yes or no questions. Players will be ranked based on the number of questions that they take to guess the object.

# Intended usage:
Multiple clients can connect to one main server, which will act as a sort of gamemaster. The server user will have a secret object. The other clients will then be able to ask the server questions, which will then be answered with a yes or no. The server will keep track of the guesses and the clients. A leaderboard will be made ranking each client.

# Technical Details:
### topics covered in class
- Communication between server and its clients using sockets / pipes
- fork/exec processes to handle multiple guesses
- allocating memory to store information regarding previous guesses
- use file handling to store in a separate file

### roles / responsibilities
Carmin
- storing information in arrays and files
- keep track of attempts and guesses

Jiayu
- fork/exec processes
- allow communicatiion for multiple clients

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
