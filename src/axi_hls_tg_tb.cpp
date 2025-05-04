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
    ctrl_t traffic_dim = TRAFFIC_CFG_SIZE_TEST;
    ctrl_t compute_dim = COMPUTE_CFG_SIZE_TEST;
    ctrl_t traffic_id = TRAFFIC_CFG_IDX_TEST;

    // External wide memory
    wide_t dut_wide_memory[TRAFFIC_CFG_SIZE];
    wide_t ref_wide_memory[TRAFFIC_CFG_SIZE];

    // External narrow memory
    narrow_t dut_narrow_memory[TRAFFIC_CFG_SIZE];
    narrow_t ref_narrow_memory[TRAFFIC_CFG_SIZE];

    // Initialize external wide memory (HBM)
    for (int i = 0; i < traffic_dim/N_LOOPS_TEST; i++){
        dut_wide_memory[i] = rand();
        ref_wide_memory[i] = dut_wide_memory[i];
    }

    // Initialize external narrow memory
    for (int i = 0; i < traffic_dim/N_LOOPS_TEST; i++){
        dut_narrow_memory[i] = rand();
        ref_narrow_memory[i] = dut_narrow_memory[i];
    }

    // Test traffic generator
    axi_hls_tg(dut_wide_memory, dut_narrow_memory, traffic_dim, compute_dim, traffic_id);

    // Verification
    for (int i = 0; i < TRAFFIC_CFG_SIZE; i++) {
        // Compute golden results
        for (int j = 0; j < N_LOOPS_TEST; j++){
            ref_wide_memory[i] += traffic_id;
            ref_narrow_memory[i] += traffic_id;
        }  
        // Check DUT correctness
        if (dut_wide_memory[i] != ref_wide_memory[i]) {
            fprintf(stderr, "ERROR: WIDE_DUT test failed.\n ");
            return EXIT_FAILURE;
        } 
        else if (dut_narrow_memory[i] != ref_narrow_memory[i]) {
            fprintf(stderr, "ERROR: NARROW_DUT test failed.\n ");
            return EXIT_FAILURE;
        } 
    }

    return 0;
}

/* ===================================================================== */