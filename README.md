# AXI4 Traffic Generator
AXI4 traffic generator designed with AMD Vitis HLS.

## Dependencies
- Vitis HLS &rarr; 2022.2

## Setup
```
source vitis-hls-setup.sh
```

## Build IP
```
make runhls
```

Additionally, set the following variables:
- CSIM: C simulation;
- CSYNTH: HLS C/C++ to RTL synthesis;
- COSIM: C/RTL co-simulation;