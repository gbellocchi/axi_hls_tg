/* =====================================================================
 * 
 * Copyright (C) 2023 University of Modena and Reggio Emilia
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * =====================================================================
 * 
 * Project:         FlooNoC
 * 
 * Title:           axi_hls_tg.h
 * 
 * Description:     Configuration file for AXI HLS Traffic Generator.
 * 
 * Date:            6.12.2023
 * 
 * Author: 	        Gianluca Bellocchi <gianluca.bellocchi@unimore.it>
 * 
 * ===================================================================== */

#ifndef _AXI_HLS_TG_H_
#define _AXI_HLS_TG_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
// #include <stdlib.h>
using namespace std;

#include "ap_int.h"

typedef uint64_t data_t;

// Dimension of internal data buffer and DMA chunk
// By extension, this value also corresponds to the DMA burst dimension (number of beats)
#define TRAFFIC_CFG_SIZE 64
#define TRAFFIC_CFG_SIZE_MAX 256

// Optimizations
#define TRAFFIC_BURST_MODE 1 // 0: no burst, 1: automatic pipeline burst

// Testbench
#define TRAFFIC_CFG_SIZE_TEST 32
#define COMPUTE_CFG_SIZE_TEST 32
#define TRAFFIC_CFG_IDX_TEST 3

void axi_hls_tg(
#if TRAFFIC_BURST_MODE == 0
    volatile data_t *traffic_dst,
#elif TRAFFIC_BURST_MODE == 1
    data_t *traffic_dst,
#endif
    data_t traffic_dim,
    data_t compute_dim,
    data_t traffic_id
);

#endif
