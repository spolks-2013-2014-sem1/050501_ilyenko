Simple TCP one-client echo server.
=================================

Binary building
---------------
Navigate to a project directory.
Run command `make lab2` to build the project.
Use `make clean` to clean-up the project binaries.

Use
---
Server works on local ip address *127.0.0.1* and uses TCP port *1441*.
Use `telnet localhost 1441` or `nc 127.0.0.1 1441` to connect to the server.
Server will end receiving when get the EOT character `Ctrl-D` *(U+0004)* from the client.