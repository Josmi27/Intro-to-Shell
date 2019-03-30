# Intro-to-Shell
This implementation of a shell is able to read the command line input, parse it into the arguments,  execute the command, and return to the shell. More succinctly, it will be able to run a single foreground job at a time (no background jobs). When the shell executes the command, it will do so using a new process. This allows the shell to be unaffected by the command it is given.
