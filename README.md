# Chess Client/Server
Chess game between two players on two different computers.

<!-- ABOUT THE PROJECT -->
## About The Project

![Alt text](images/starting-position.png?raw=true "Title")

It features all of the basic rules of chess which include: pawn-promotion, castling, enpassant capture, stalemate, and checkmate. The computers communicate using a TCP protocol. The chessboard is displayed using the console. It should be noted that this program was designed for Ubuntu machines and it uses Unicode symbols to display the different chess pieces.

<!-- GETTING STARTED -->
## Getting Started
You will need two physical computers or two virtual machines. Both machines need to run Linux, specifically Ubuntu since this code was developed/tested using it.

### Installation
1. Clone the repo on both machines
   ```sh
   git clone git@github.com:LuisUrzua/chess-client-server.git
   ```
2. Build the project from the top level directory. You should get two executables named, 'client.exe' and 'server.exe'
   ```sh
   make
   ```
3. One one machine run the server executable first
   ```sh
   ./bin/server.exe
   ```
4. On the other run the client executable second
   ```sh
   ./bin/client.exe
   ```

