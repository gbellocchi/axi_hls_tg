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

/* Traffic generator top */

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
) {

    // Traffic generation
    #pragma HLS INTERFACE mode=m_axi port=wide_port depth=TRAFFIC_CFG_SIZE bundle=wide_port
    #pragma HLS INTERFACE mode=m_axi port=narrow_port depth=TRAFFIC_CFG_SIZE bundle=narrow_port

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

    wide_t wide_buffer[TRAFFIC_CFG_SIZE];
    narrow_t narrow_buffer[TRAFFIC_CFG_SIZE];

    read_loop: for (int i = 0; i < (traffic_dim/TRAFFIC_CFG_SIZE); i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
        axi_hls_tg_read<wide_t, ctrl_t>(wide_buffer, wide_port, TRAFFIC_CFG_SIZE);
        axi_hls_tg_read<narrow_t, ctrl_t>(narrow_buffer, narrow_port, TRAFFIC_CFG_SIZE);
    }

    compute_loop: for (int i = 0; i < (compute_dim/TRAFFIC_CFG_SIZE); i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
        axi_hls_tg_compute<wide_t, ctrl_t, int>(wide_buffer, traffic_id, TRAFFIC_CFG_SIZE);
        axi_hls_tg_compute<narrow_t, ctrl_t, int>(narrow_buffer, traffic_id, TRAFFIC_CFG_SIZE);
    }
    
    write_loop: for (int i = 0; i < (traffic_dim/TRAFFIC_CFG_SIZE); i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
        axi_hls_tg_write<wide_t, ctrl_t>(wide_port, wide_buffer, TRAFFIC_CFG_SIZE);
        axi_hls_tg_write<narrow_t, ctrl_t>(narrow_port, narrow_buffer, TRAFFIC_CFG_SIZE);
    }
}