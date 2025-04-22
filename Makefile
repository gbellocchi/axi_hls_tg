# =====================================================================
# Copyright (C) 2023 University of Modena and Reggio Emilia.
#
# Author: Gianluca Bellocchi, University of Modena and Reggio Emilia.
# =====================================================================

ROOT 				= $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

MK_PATH 			:= $(abspath $(lastword $(MAKEFILE_LIST)))
CUR_DIR 			:= $(patsubst %/,%,$(dir $(MK_PATH)))
XF_PROJ_ROOT 		?= $(shell bash -c 'export MK_PATH=$(MK_PATH);')

# Project
PRJ_ROOT			= $(CUR_DIR)
PRJ_NAME 			:= axi_hls_tg.prj
SOL_NAME 			:= sol1
ACC_NAME 			:= axi_hls_tg

# Vitis commands
CSIM				?= 1
CSYNTH				?= 1
COSIM				?= 1
COSIM_GUI			?= 0
DEVICE				?= zcu102
VIVADO_SYN 			?= 0
VIVADO_IMPL 		?= 0

# Directories
SRC_DIR 			= $(PRJ_ROOT)/src
OUT_DIR 			= $(PRJ_ROOT)/output
COMMON_DIR			= $(PRJ_ROOT)/common
MK_DIR 				= $(COMMON_DIR)/mk
TCL_DIR 			= $(COMMON_DIR)/tcl

# Source files
CPP_TOP_PATH 		:= $(SRC_DIR)/axi_hls_tg.cpp
CPP_TB_PATH 		:= $(SRC_DIR)/axi_hls_tg_tb.cpp

# Synthesis/Implementation
SYN_DIR				= $(PRJ_ROOT)/$(PRJ_NAME)/$(SOL_NAME)/syn/verilog
IMPL_DIR			= $(PRJ_ROOT)/$(PRJ_NAME)/$(SOL_NAME)/impl/verilog
IMPL_DRIVERS_DIR	= $(IMPL_DIR)/../misc/drivers/${ACC_NAME}*/src

-include $(MK_DIR)/hls.mk