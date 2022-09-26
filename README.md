# IRC Server

This IRC server/client project is compliant with RFC 1459 standards. Documentation can be found
at the following link: https://tools.ietf.org/html/rfc1459

This project includes both client and server code that can be run in parallel. Running an instance of the server allows for multiple clients instances to be run and to search for, list, create, and join channels on the server. Clients can change their nick names and chat with others in each channel they join.

# Notes about Server Commands

*  Currently, client UI is minimal so no feedback to commands is the result of a successful command.
*  Commands that should take more than one argument are still being worked on.
*  Currently, all users join with a default nick and full name i.e "Client x". These names can then be changed by using the /nick (name) and /user (name) commands.
*  Although RFC protocol allows for the joing of multiple channels simultaneously, due to current minimal UI, clients must leave channels before joining another.
