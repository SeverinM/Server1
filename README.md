# Server1

## What is it ?
Server1 is an authoritative multiplayer layer, mostly made for multiplayer games. 

*This is the server side , the client side can be found [here](https://gitlab.com/SeverinM/server1-unity_client)*

## How does it work ? 

* Each player/client control an entity , meaning only this entity can send messages to the server
* The server fetch every input , compute the next state and send this new state to the clients
* Repeat

## Targets

Right now the server part only work on Windows 10 64 bits but it will be soon for every platform

## How to use it 
*Required : Unity and Visual Studio*

1. Pull this repository
2. Set *NetworkHandling* as the startup project
3. You can change the listening port in the file *Utils.h* inside the project
3. Pull the client repository
4. Open this repository with Unity
5. Setup the port and the ip adress of the GameObject *TCP* and *UDP* , **Don't touch anything else**
6. Make sure the client and the server is on the same port
7. Launch the server program
8. Launch the client program and click on both button

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
