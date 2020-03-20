# Process-Manager
A PID Manager that could essentially be used to manage different processes via a multi-threaded programming approach.

Currently written in 'C' Language with array as the primary data-structure, the program can do the following: 

--> Keep track of free PIDs and ensures that no two active processes are having the same pid.

--> You can create a number of threads—for example, 100 — and each thread will be able to request a pid, sleep for a random    period of time, and then release the pid.

--> Once a process terminates the PID manager may assign its pid to new process.

# Minimum and Maximum PID's can be edited and used accordingly.
# (Sleeping for a random period of time approximates the typical pid usage in which a pid is assigned to a new process,
