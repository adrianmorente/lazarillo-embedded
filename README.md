# lazarillo_embedded

# Modules

### lazarillo-hmi

Embedded app with graphical user interface that allows the user to interact with the robot.


### lazarillo-utils

Module containing classes and definitions useful for any Lazarillo service.


### messages-definition

Module containing the different messages that Lazarillo services use to communicate between them.


### motor-manager

Service responsible of handling the state and orders to the motors that allow the robot to move.


### serialization

Module containing the logic and definitions for serializing the messages used in communication.


### service-base

Module that defines the logic that any service in the charger should use. This avoids redundant code.


### web-gateway

Process that opens a Websockets server to the central control panel [https://github.com/adrianmorente/lazarillo-admin](lazarillo-admin) where an expert handles the Lazarillo devices, sends requests, etc.
