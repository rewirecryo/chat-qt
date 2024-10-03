# chat-qt
A Qt6-based chat client to work with
[chat-server](https://github.com/cryrasinia/chat-server).

To connect to a server, run:
`chat <remote_address> <remote_port> <username>`

## Dependencies
chat-qt depends on the following libraries

  - [Qt6 Framework (Qt Core, Qt Widgets, Qt GUI)](https://www.qt.io/)
  - [JSON for Modern C++](https://github.com/nlohmann/json)

## Building

To build, run:

`qmake chat.pro && make`