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
 * Title:           axi_hls_tg_tb.cpp
 * 
 * Description:     Testbench for AXI HLS Traffic Generator.
 * 
 * Date:            6.12.2023
 * 
 * Author: 	        Gianluca Bellocchi <gianluca.bellocchi@unimore.it>
 * 
 * ===================================================================== */

#include "axi_hls_tg.h"

int main(int argc, char** argv) {

    // Parameters
    data_t traffic_dim = TRAFFIC_CFG_SIZE;
    data_t traffic_idx = TRAFFIC_CFG_IDX;

    // External memory
    data_t ext_memory[TRAFFIC_CFG_SIZE_MAX];

    // Test traffic from traffic generator to external memory
    axi_hls_tg(ext_memory, traffic_dim, traffic_idx, TRAFFIC_CFG_WRITE);

    for (int i = 0; i < traffic_dim; i++){
        if (ext_memory[i] != (traffic_idx + i)) {
            fprintf(stderr, "ERROR: Test Failed.\n ");
            return EXIT_FAILURE;
        }   
    }

    // Test read from buffer    
    axi_hls_tg(ext_memory, traffic_dim, traffic_idx, TRAFFIC_CFG_READ);

    return 0;
}

/* ===================================================================== */