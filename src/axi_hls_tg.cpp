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
 * Title:           axi_hls_tg.cpp
 * 
 * Description:     AXI HLS Traffic Generator.
 * 
 * Date:            6.12.2023
 * 
 * Author: 	        Gianluca Bellocchi <gianluca.bellocchi@unimore.it>
 * 
 * ===================================================================== */

#include "axi_hls_tg.h"

/* Read module */

void axi_hls_tg_read(
    data_t *dst, 
#if TRAFFIC_BURST_MODE == 0
    volatile data_t *src,
#elif TRAFFIC_BURST_MODE == 1
    data_t *src,
#endif 
    data_t size
){
    read_from: memcpy((data_t*)dst, (const data_t*)src, size * sizeof(data_t));
}

/* Computation module */

void axi_hls_tg_compute(
#if TRAFFIC_BURST_MODE == 0
    volatile data_t *buffer,
#elif TRAFFIC_BURST_MODE == 1
    data_t *buffer,
#endif 
    data_t id, 
    data_t size
){
    compute: for (int i = 0; i < size; i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE max=TRAFFIC_CFG_SIZE
        buffer[i] += id;
    }
}

/* Write module */

void axi_hls_tg_write(
#if TRAFFIC_BURST_MODE == 0
    volatile data_t *dst, 
#elif TRAFFIC_BURST_MODE == 1
    data_t *dst, 
#endif  
    data_t *src,
    data_t size
){
    write_back: memcpy((data_t*)dst, src, size * sizeof(data_t));
}

/* Traffic generator top */

void axi_hls_tg(
    // AXI4 interfaces
#if TRAFFIC_BURST_MODE == 0
    volatile data_t *traffic_dst,
#elif TRAFFIC_BURST_MODE == 1
    data_t *traffic_dst,
#endif
    // Traffic dimension
    data_t traffic_dim,
    // Compute dimension
    data_t compute_dim,
    // Traffic ID
    data_t traffic_id
) {

    // Traffic generation
    #pragma HLS INTERFACE mode=m_axi port=traffic_dst depth=TRAFFIC_CFG_SIZE bundle=traffic_dst

    // Traffic control
    #pragma HLS INTERFACE mode=s_axilite port=traffic_dim
    #pragma HLS INTERFACE mode=s_axilite port=compute_dim
    #pragma HLS INTERFACE mode=s_axilite port=traffic_id
    #pragma HLS INTERFACE mode=s_axilite port=return

    // Optimizations
#if TRAFFIC_BURST_MODE == 0
    #pragma HLS pipeline off
#elif TRAFFIC_BURST_MODE == 1
    #pragma HLS pipeline
#endif

    data_t local_buffer[TRAFFIC_CFG_SIZE];

    for (int i = 0; i < (traffic_dim/TRAFFIC_CFG_SIZE); i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
        axi_hls_tg_read(local_buffer, traffic_dst, TRAFFIC_CFG_SIZE);
    }

    for (int i = 0; i < (compute_dim/TRAFFIC_CFG_SIZE); i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
        axi_hls_tg_compute(local_buffer, traffic_id, TRAFFIC_CFG_SIZE);
    }
    
    for (int i = 0; i < (traffic_dim/TRAFFIC_CFG_SIZE); i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
        axi_hls_tg_write(traffic_dst, local_buffer, TRAFFIC_CFG_SIZE);
    }
}