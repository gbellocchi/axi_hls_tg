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

typedef ap_uint<64> wide_t;  // user-defined wide data type
typedef ap_uint<64> narrow_t; // user-defined narrow data type
typedef ap_uint<64> ctrl_t; // user-defined control data type

// Dimension of internal data buffer and DMA chunk
// By extension, this value also corresponds to the DMA burst dimension (number of beats)
#define TRAFFIC_CFG_SIZE 256
#define TRAFFIC_CFG_SIZE_MAX 256

// Optimizations
#define TRAFFIC_BURST_MODE 1 // 0: no burst, 1: automatic pipeline burst

// Testbench
#define N_LOOPS_TEST 32
#define TRAFFIC_CFG_SIZE_TEST TRAFFIC_CFG_SIZE*N_LOOPS_TEST
#define COMPUTE_CFG_SIZE_TEST TRAFFIC_CFG_SIZE*N_LOOPS_TEST
#define TRAFFIC_CFG_IDX_TEST 3

/* DMA read module */

template<typename D, typename C>
void axi_hls_tg_read(
    D *dst, 
#if TRAFFIC_BURST_MODE == 0
    volatile D *src,
#elif TRAFFIC_BURST_MODE == 1
    D *src,
#endif 
    C size
){
    read_from: memcpy((D*)dst, (const D*)src, size * sizeof(D));
}

/* Computation module */

template<typename D, typename C, typename v>
void axi_hls_tg_compute(
#if TRAFFIC_BURST_MODE == 0
    volatile D *buffer,
#elif TRAFFIC_BURST_MODE == 1
    D *buffer,
#endif 
    C id, 
    C size
){
    compute: for (v i = 0; i < size; i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
        buffer[i] += id;
    }
}
    
/* DMA write module */

template<typename D, typename C>
void axi_hls_tg_write(
#if TRAFFIC_BURST_MODE == 0
    volatile D *dst, 
#elif TRAFFIC_BURST_MODE == 1
    D *dst, 
#endif  
    D *src,
    C size
){
    write_back: memcpy((D*)dst, src, size * sizeof(D));
}

/* Traffic generator top definition */

void axi_hls_tg(
    // AXI4 interfaces
#if TRAFFIC_BURST_MODE == 0
    volatile wide_t *wide_port,
    volatile narrow_t *narrow_port,
#elif TRAFFIC_BURST_MODE == 1
    wide_t *wide_port,
    narrow_t *narrow_port,
#endif
    // Traffic dimension
    ctrl_t traffic_dim,
    // Compute dimension
    ctrl_t compute_dim,
    // Traffic ID
    ctrl_t traffic_id
);

#endif
