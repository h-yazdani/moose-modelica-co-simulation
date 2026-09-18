# moose-modelica-co-simulation
Open-source framework for co-simulation between MOOSE and Modelica. Includes the MOOSE UserObject, Modelica impure functions, file-based synchronization, and case-study inputs. Supports reproducible simulations and provides a transferable approach for co-simulation of building energy and geothermal systems.

The repository contains:

MOOSE UserObject source files
C/C++ source and header files
Modelica impure functions 
Weather data example 

The following files must be copied into the corresponding MOOSE and Modelica library directories.

1. MOOSE PorousFlow module

The MOOSE UserObject files:

TorchidHold.C
Torchidhold.h

should be copied into the MOOSE PorousFlow module as follows:

MOOSE/modules/porous_flow/
├── include/
│   └── userobjects/
│       └── Torchidhold.h
│
└── src/
    └── userobjects/
        └── TorchidHold.C

After copying the files, compile the MOOSE PorousFlow application according to the standard MOOSE build procedure.

2. Modelica C source and header files

All C source (.c) and header (.h) files required by the Modelica interface should be copied to:

Modelica://Buildings/Resources/C-Sources/

For example:

Buildings/
└── Resources/
    └── C-Sources/
        ├── resfunction.c
        ├── resfunction.h
        └── ...

These files provide the external C functions used by the Modelica models for communication with the MOOSE simulation.

3. Weather data

An example weather-data file can be copied to:

Modelica://Buildings/Resources/weatherdata/

For example:

Buildings/
└── Resources/
    └── weatherdata/
        └── example_weather_file.mos

The weather-data file is used by the Modelica building-energy model and can be replaced with another compatible weather file when reproducing a different location or case study.
