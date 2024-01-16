# Dev Log:

## Andrew Liu

### 2024-01-02 - work on basic proposal
Brainstormed ideas for game and wrote out basic description for timestamp and roles

### 2024-01-03 - work with jiayu to transfer lab16
Copy and paste over jiayu's lab16 code to establish connection between client and server

### 2024-01-04 - fix my computer pipes
I realized that pipes on my computer doesn't work so I was fixing it

### 2024-01-04 - implement questioning and answering
allow the client and server to communicate through standard in. the client is now able to send questions to the server, and the server can respond with yes or no.

### 2024-01-05 - finalize proposals
finalized game structures and the technical aspects

### 2024-01-07 - add semaphores to project timeline and planning
added different semaphores to timeline
    - control how many questions the server can receive at once
    - control how many clients can connect to the server

### 2024-01-08 - started semaphores implementations
add accessSemaphore, releaseSemaphore, semSetup
filled out the body for each

### 2024-01-08 - started semaphore integration
I tried to add semaphores to the client logic, however, semaphores are still blocked even though others clients have freed
need to fix tomorrow
also did extensive testing with semaphores in semaphoretesting folder, playing around to see what i can do with semaphores

### 2024-01-09 - error debug session today
I FIGURED OUT HOMER DOESNT WORK FOR CODE, i took entire class period to debug and figure out, will be using marge. no code work today

### 2024-01-10 - tried implementing semaphores, ran into issues
semaphore release doesn't work after a write/read statement. semaphore release works after access semaphore, which is excpected behavior, however, putting it after a writre statement messes it up. will ask in class tomorrow. i also had trouble with semaphores not correctly updating to the number of max connections, it is fixed now.

### 2024-01-10 - going insane, debugging semaphore not releasing issue after print statement?????

added print statements to display the value of sem before incrementing and the value of sem after incrementing, print statement causes the semaphore to not incremenet????

### 2024-01-10 - remove semaphores, rethinking implementation

debugged for like 15 minutes and realized semaphores were not ideal for my usage, so I removed semaphores entirely from code
- my semaphore code unfortunately did not make it on the final project, it is in my branch "Andrew" and not merged into main
### 2024-01-11 - help jiayu with select code

as a group, we collectively tried to implement the select function into our client and server

### 2024-01-11 - debug why client isn't sending question to server properly

i first tried implementing select with two client sockets, but that didn't work so i reverted back my changes and now my original code doesnt work. was tyribng to debug

### 2024-01-12 started working on 20 questions game mode

added booleans to let user choose between two game modes, 20 questions and 2 minutes
- started working in 20Questions branch

### 2024-01-14 implemented 20 questions
- add selection phase for 20 question or 2 minutes
- add detection for if client disconnected
- add detection for if client won the game
- add file transcription for the client questions and answers received

## Carmin Vuong

### 2024-01-02 - started our proposal
Wrote out the basic outline of the proposal including rules and technical aspects

### 2024-01-05 - finalize proposals
collectively worked on proposal and finalized game structures and the technical aspects

### 2024-01-07 - detail out out project more and roles
improve intended pacing and member roles to the proposal, change minor rule in intended usage of the game

### 2024-01-08 - add implementation of a transcript
record + transcribe player's guesses and answers into a transcript file
start working on allowing multiple clients to have their separate files using PID

### 2024-01-09 - fix bugs due to merging + use names
fix some bugs due to merging code and differentiate client's transcripts using names instead of PID
format code a bit better and document a little better

### 2024-01-11 - attempted to implement multiple clients server connection
- attempted to implement multiple clients server connection
- it didn't work (server kept blocking and nothing was being received)

### 2024-01-14 printed file transcription for 20 questions
- print transcription at end regardless or win or loss

### 2024-01-15 add transcription for signals + prettify
- print transcription if client disconnects using signals
- reformat the terminal prompts and add color to make more aesthetically pleasing
- reword README.md + edit makefile

## Jiayu Yan

### 2024-01-02 - started basic proposal + assigned rules to each member
Brainstormed ideas for game and wrote out basic description for timestamp and roles

### 2024-01-05 - finalize proposal
collectively worked on proposal and finalized game structures and the technical aspects

### 2024-01-07 - started implementations
added additional concepts to our game
figured out client logic for game scoring + attempted implementation for leaderbaord

### 2024-01-08 - client application
decided to add struct for each player to organize score and name of client
added feature to keep track of score for each individual user

### 2024-01-09 - select for multiple client
connecting multiple clients to one server using select
debugging select code for various clients to use at once (in progress)

### 2024-01-10 - select for multiple client
connecting multiple clients to one server using select
debugging select code for various clients to use at once (in progress)

### 2024-01-11 - select for multiple client / implementing leaderboard
started implementation of leaderboard to reflect changes in the score between multiple clients

### 2024-01-13 - win/lose in client
determined win/lose condition for multiple clients
sent file containing detail back to winner client
fixed Leaderboard

### 2024-01-15 - new method for selection of modes
allow for user to select between two modes
changes to makefile to reflect new option
added transcription to multiple clients
