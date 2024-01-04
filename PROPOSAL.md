# Final Project Proposal

## Group Members:
- Andrew Liu
- Minh (Carmin) Vuong
- Jiayu Yan
       
# Intentions:
20 Questions - a guessing game where a player thinks of a secret object and the other players have to guess it, in 20 attempts or less. The questions that can be asked must be yes or no questions.
    
# Intended usage:
Multiple clients can connect to one main server, which will act as a sort of gamemaster. One client (player) will tell the server their secret object. The other clients will then be able to ask the server questions, which will then be answered with a yes or no (coming from the client). The server will keep track of the guesses and the clients.
  
# Technical Details:
### topics covered in class
- Communication between server and its clients using sockets / pipes
- fork/exec processes to handle multiple guesses
- allocating memory to store information regarding previous guesses
- use file handling to store in a separate file

### roles / responsibilities
Carmin
- storing information in arrays and files

Jiayu
- forl/exec processes

Andrew
- sockets

### algorithms / data structures
- structs for the players (attempts, guesses)
- arrays for the previous guesses
- sending guesses between server and clients
    
# Intended pacing:
- 1/5
- 1/10
- 1/12
- 1/13
- 1/16 - Due
