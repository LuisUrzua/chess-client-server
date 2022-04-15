# Client_Server_Chess
Two player chess

<!-- ABOUT THE PROJECT -->
## About The Project

This is a client-server chess program. That means that the game is played using two computers using the same network.

<!-- GETTING STARTED -->
## Getting Started

You will need two physical computers or two virtual machines. Both machines need to run Linux, specifically Ubuntu since this code was developed/tested using it.

### Installation

1. Clone the repo on both machines
   ```sh
   git clone git@github.com:LuisUrzua/Client_Server_Chess.git
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


