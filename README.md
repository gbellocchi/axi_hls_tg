# AXI4 Traffic Generator
AXI4 traffic generator designed with AMD-Xilinx Vitis HLS.

## Dependencies
- Vitis HLS (v2022.2)

## Repository
The repository includes the following files and directories:
- `src`: HLS C++ source files and testbench;
- `common`: TCL and Mk components for HLS implementation and verification;
- `Makefile`: Top Makefile;
- `vitis-hls-setup.sh`: HLS settings.

## Setup
Run `source vitis-hls-setup.sh` to set up the HLS environment.

## Build
Run `make runhls` to build the HLS design.

Additionally, set the following variables (defined in `Makefile`):
- `CSIM`: C simulation;
- `CSYNTH`: HLS C/C++ to RTL synthesis;
- `COSIM`: C/RTL co-simulation;

## Output
Run `make get_all` to create an `output` with the generated RTL and software libraries.