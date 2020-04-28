# IRC Server

This IRC server is compliant with RFC 1459 standards. Documentation can be found
at the following link: https://tools.ietf.org/html/rfc1459

# Current Bug(s)

*  Getting first initial client to connect to running server is spotty and sometimes takes multiple server reboots to get the initial client connected (Once initial client is connected, all subsequent clients easily connect).
*  Clients leaving and rejoining the server results in relatively unstable message passing afterwards (server crashes due to seg faults).