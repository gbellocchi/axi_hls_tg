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

void axi_hls_tg_read(data_t *dst, data_t *src, data_t size){
    memcpy((data_t*)dst, (const data_t*)src, size * sizeof(data_t));
}

void axi_hls_tg_compute(data_t *buffer, data_t id, data_t size){
    for (int i = 0; i < size; i++) {
    #pragma HLS LOOP_TRIPCOUNT min=TRAFFIC_CFG_SIZE max=TRAFFIC_CFG_SIZE
        buffer[i] += id;
    }
}

void axi_hls_tg_write(data_t *dst, data_t *src, data_t size){
    memcpy((data_t*)dst, src, size * sizeof(data_t));
}

void axi_hls_tg(
    data_t *traffic_dst,
    data_t traffic_dim,
    data_t traffic_id
) {

    // Traffic generation
    #pragma HLS INTERFACE mode=m_axi port=traffic_dst depth=TRAFFIC_CFG_SIZE bundle=traffic_dst

    // Traffic control
    #pragma HLS INTERFACE mode=s_axilite port=traffic_dim
    #pragma HLS INTERFACE mode=s_axilite port=traffic_id
    #pragma HLS INTERFACE mode=s_axilite port=return

    data_t local_buffer[TRAFFIC_CFG_SIZE];

    axi_hls_tg_read(local_buffer, traffic_dst, TRAFFIC_CFG_SIZE);
    axi_hls_tg_compute(local_buffer, traffic_id, TRAFFIC_CFG_SIZE);
    axi_hls_tg_write(traffic_dst, local_buffer, TRAFFIC_CFG_SIZE);

}