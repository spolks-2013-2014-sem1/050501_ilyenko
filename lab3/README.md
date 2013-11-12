Simple file sending client-server util
=================================

Binary building
---------------
Navigate to a project directory.
Run command `make lab3` to build the project.
Use `make clean` to clean-up the project binaries.

Usage
-----
To run as a server: `./lab3 -server`
To tun as a client: `./lab3 -client [path-to-file]`

Server works on local ip address *127.0.0.1* and uses TCP port *1441*.
Client works on local ip address *127.0.0.1* and uses TCP port *1442*.

A server places received files to the folder where the server was run.