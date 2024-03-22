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

void axi_hls_tg(
    data_t *traffic_dst, 
    data_t traffic_dim,
    data_t traffic_idx,
    data_t traffic_rw
) {

    // Traffic generation
    #pragma HLS INTERFACE mode=m_axi port=traffic_dst depth=128 offset=slave bundle=traffic_dst

    // Traffic control
    #pragma HLS INTERFACE mode=s_axilite port=traffic_dim
    #pragma HLS INTERFACE mode=s_axilite port=traffic_idx
    #pragma HLS INTERFACE mode=s_axilite port=traffic_rw
    #pragma HLS INTERFACE mode=s_axilite port=return

    data_t local_buffer[TRAFFIC_CFG_SIZE_MAX];

    // Read from external memory
    if(traffic_rw == TRAFFIC_CFG_READ){

        memcpy(local_buffer, (const data_t*)traffic_dst, traffic_dim*sizeof(data_t));

    // Write to external memory
    } else if(traffic_rw == TRAFFIC_CFG_WRITE){

        for (int i = 0; i < traffic_dim; i++) {
        #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE_MAX max=TRAFFIC_CFG_SIZE_MAX
            traffic_dst[i] = traffic_idx + i;
        }

    }
}