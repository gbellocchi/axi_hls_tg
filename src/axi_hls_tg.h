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
using namespace std;

#include "ap_int.h"

#define TRAFFIC_CFG_SIZE_MAX 1024
#define TRAFFIC_CFG_SIZE 128
#define TRAFFIC_CFG_IDX 3
#define TRAFFIC_CFG_READ 0
#define TRAFFIC_CFG_WRITE 1

typedef uint64_t data_t;

void axi_hls_tg(
    data_t *traffic_dst, 
    data_t traffic_dim,
    data_t traffic_idx,
    data_t traffic_rw
);

#endif
