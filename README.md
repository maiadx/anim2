Anim2 is a particle renderer designed for use in Computational Physics, as a way to easily represent the outputs of a simulation, or to use its Compute Shader support to utilize hardware-accelerated simulation.

(Please note that this project is only supported on Linux systems, and will not work on Windows)

to build the project, run `make config=release -j 6`

to install run `./install.sh`

Example C file is in Examples/

To build example C simulation:
    `gcc -lm example.c -o exampleProgram`
then to run the program:
    `./exampleProgram | anim2`
