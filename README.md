# bookmark_extractor
A C application that finds and extracts bookmarks from Mozilla Firefox profiles stored locally.

This application scans the user's home directory for Mozilla Firefox profiles and proceeds to transmit the extracted bookmarks to a predefined IP address and port. In this case it's port 33333 on 127.0.0.1 (localhost).

Currently only works on Linux with portability on the horizon (see TODO).

Disclamer: This tool has been designed and developed for personal use and backup purposes.

### Todo
- Ensure that no external shell commands are required to increase portability for the given task:
    - Directory travesal
    - Transmission over the network
- Create a Makefile
