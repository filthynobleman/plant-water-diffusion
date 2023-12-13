# Plant Water Diffusion
This repository contains the implementation of the water diffusion model, as described
in the paper _A Physically-inspired Approach to the Simulation of Plant Wilting_.  

- DOI: https://dl.acm.org/doi/10.1145/3610548.3618218
- PDF: http://computationalsciences.org/publications/maggioli-2023-plant-wilting/maggioli-2023-plant-wilting.pdf


## Building instructions
The building process is entirely managed with CMake.  
Create a building workspace:
```sh
    mkdir build
    cd build
```
Use CMake to configure the project and build it:
```sh
    cmake ..
    cmake --build . --config release -j
```
The build will produce the following executables in the `Release` directory:
 - `TestCommons`: for testing common functionalities of the codebase, such as custom exceptions and macros;
 - `TestUtils`: for testing utility classes, such as custom implementations for stack and queue;
 - `TestGraph`: for testing the loading of the graph data structure;
 - `TestWaterModel`: for testing the water model.

It is possible to avoid the building of the sample applications during the configuration using the
option `BUILD_SAMPLES`:
```sh
    cmake .. -DBUILD_SAMPLES=OFF
```

The building process produces the headers and a shared library `pwd`, which can be installed with CMake:
```sh
    cmake --install .
```
By default, CMake installs the library in `/usr/local`. It is possible to specify a different install
directory during the configuration:
```sh
    cmake .. -DCMAKE_INSTALL_PREFIX=/the/desired/path/
```

## Documentation
The documentation is managed using Doxygen, and a pre-built documentation is provided inside the `doc`
directory.  
To build the documentation, call Doxygen on the configuration file:
```sh
    doxygen Doxyfile
```
A working installation of GraphViz is needed to build the dependency graphs in the documentation.
