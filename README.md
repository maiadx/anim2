Anim2 is a particle renderer designed for use in Computational Physics, as a way to easily represent the outputs of a simulation, or to use its Compute Shader support to utilize hardware-accelerated simulation.

[Please note that this project is only supported on Linux systems, and will not work on windows]

to build, run make config=release -j 6

to install run ./install.sh

Example C file is in Examples/

to run:
    gcc -lm example.c -o exampleProgram
then,
    ./exampleProgram | anim2
