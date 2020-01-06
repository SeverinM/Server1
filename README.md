# Server1

## What is it ?
Server1 is an authoritative multiplayer layer, mostly made for multiplayer games. 

*This is the server side , the client side can be found [here](https://gitlab.com/SeverinM/server1-unity_client)*

## How does it work ? 

* Each player/client control an entity , meaning only this entity can send messages to the server
* The server fetch every input , compute the next state and send this new state to the clients
* Repeat

## Targets

Only tested on windows 10 64 bits right now but can work on every plateform.

## How to use it 
*Actually require 2 computers on the same network*

### Server part ### 

1. Pull this repository
2. Generate the project using CMake
3. fill each lib folder with the correct library
4. do the same for the .so / .dll files
5. move the shader folder into (YOUR_BUILD_PATH)/NetworkHandling/
6. Compile PhysicModel , then Visual World , then NetworkHandling
7. That's all !

(*Parts 3-5 will be removed soon*)

### Client part ###

1. Pull the repository above
2. Launch it via Unity
3. Setup ip adress and port via the gameobject TCP and UDPSend
4. Launch the scene AFTER the server part
5. Click on both buttons
6. An OpenGL window should open with a cube, use ZQSD (WASD for french keyboard layout) on Unity to move it
7. Repeat these part for each client you want


## Libraries 
* SFML (Network and System)
* glfw3
* reactPhysics3d

## TO-DO
- [x] Basic UDP / TCP communication
- [x] Basic room / lobby integration
- [x] Basic synchronization between clients
- [ ] Make this program compile on every platform
- [ ] Better client 
- [ ] NAT implementation (currently only work on local network)

I am currently alone in this project , for any questions you ask can me at *severinmichaut@gmail.com*
