/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'MAX10NIOS'
 * SOPC Builder design path: c:/Users/pahle/Documents/Research/ITCLab/COMMHARD/TINYRO/MAX10NIOS.sopcinfo
 *
 * Generated: Fri Oct 24 11:34:03 JST 2025
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00008820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x10
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00004020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x10
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00004000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00008820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x10
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00004020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x10
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00004000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2


/*
 * Stream_0 configuration
 *
 */

#define ALT_MODULE_CLASS_Stream_0 altera_avalon_pio
#define STREAM_0_BASE 0x9060
#define STREAM_0_BIT_CLEARING_EDGE_REGISTER 0
#define STREAM_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define STREAM_0_CAPTURE 0
#define STREAM_0_DATA_WIDTH 8
#define STREAM_0_DO_TEST_BENCH_WIRING 0
#define STREAM_0_DRIVEN_SIM_VALUE 0
#define STREAM_0_EDGE_TYPE "NONE"
#define STREAM_0_FREQ 50000000
#define STREAM_0_HAS_IN 0
#define STREAM_0_HAS_OUT 1
#define STREAM_0_HAS_TRI 0
#define STREAM_0_IRQ -1
#define STREAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define STREAM_0_IRQ_TYPE "NONE"
#define STREAM_0_NAME "/dev/Stream_0"
#define STREAM_0_RESET_VALUE 0
#define STREAM_0_SPAN 16
#define STREAM_0_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "MAX 10"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x9078
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x9078
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x9078
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "MAX10NIOS"
#define ALT_SYS_CLK_TICKS_PER_SEC NONE_TICKS_PER_SEC
#define ALT_TIMESTAMP_CLK_TIMER_DEVICE_TYPE NONE_TIMER_DEVICE_TYPE


/*
 * busy configuration
 *
 */

#define ALT_MODULE_CLASS_busy altera_avalon_pio
#define BUSY_BASE 0x9030
#define BUSY_BIT_CLEARING_EDGE_REGISTER 0
#define BUSY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUSY_CAPTURE 0
#define BUSY_DATA_WIDTH 1
#define BUSY_DO_TEST_BENCH_WIRING 0
#define BUSY_DRIVEN_SIM_VALUE 0
#define BUSY_EDGE_TYPE "NONE"
#define BUSY_FREQ 50000000
#define BUSY_HAS_IN 1
#define BUSY_HAS_OUT 0
#define BUSY_HAS_TRI 0
#define BUSY_IRQ -1
#define BUSY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BUSY_IRQ_TYPE "NONE"
#define BUSY_NAME "/dev/busy"
#define BUSY_RESET_VALUE 0
#define BUSY_SPAN 16
#define BUSY_TYPE "altera_avalon_pio"


/*
 * ena configuration
 *
 */

#define ALT_MODULE_CLASS_ena altera_avalon_pio
#define ENA_BASE 0x9040
#define ENA_BIT_CLEARING_EDGE_REGISTER 0
#define ENA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ENA_CAPTURE 0
#define ENA_DATA_WIDTH 1
#define ENA_DO_TEST_BENCH_WIRING 0
#define ENA_DRIVEN_SIM_VALUE 0
#define ENA_EDGE_TYPE "NONE"
#define ENA_FREQ 50000000
#define ENA_HAS_IN 0
#define ENA_HAS_OUT 1
#define ENA_HAS_TRI 0
#define ENA_IRQ -1
#define ENA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ENA_IRQ_TYPE "NONE"
#define ENA_NAME "/dev/ena"
#define ENA_RESET_VALUE 0
#define ENA_SPAN 16
#define ENA_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x9078
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * onchip_ram configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_ram altera_avalon_onchip_memory2
#define ONCHIP_RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_RAM_BASE 0x4000
#define ONCHIP_RAM_CONTENTS_INFO ""
#define ONCHIP_RAM_DUAL_PORT 0
#define ONCHIP_RAM_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_RAM_INIT_CONTENTS_FILE "MAX10NIOS_onchip_ram"
#define ONCHIP_RAM_INIT_MEM_CONTENT 0
#define ONCHIP_RAM_INSTANCE_ID "NONE"
#define ONCHIP_RAM_IRQ -1
#define ONCHIP_RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_RAM_NAME "/dev/onchip_ram"
#define ONCHIP_RAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_RAM_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_RAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_RAM_SINGLE_CLOCK_OP 0
#define ONCHIP_RAM_SIZE_MULTIPLE 1
#define ONCHIP_RAM_SIZE_VALUE 16384
#define ONCHIP_RAM_SPAN 16384
#define ONCHIP_RAM_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_RAM_WRITABLE 1


/*
 * request configuration
 *
 */

#define ALT_MODULE_CLASS_request altera_avalon_pio
#define REQUEST_BASE 0x9020
#define REQUEST_BIT_CLEARING_EDGE_REGISTER 0
#define REQUEST_BIT_MODIFYING_OUTPUT_REGISTER 0
#define REQUEST_CAPTURE 0
#define REQUEST_DATA_WIDTH 1
#define REQUEST_DO_TEST_BENCH_WIRING 0
#define REQUEST_DRIVEN_SIM_VALUE 0
#define REQUEST_EDGE_TYPE "NONE"
#define REQUEST_FREQ 50000000
#define REQUEST_HAS_IN 0
#define REQUEST_HAS_OUT 1
#define REQUEST_HAS_TRI 0
#define REQUEST_IRQ -1
#define REQUEST_IRQ_INTERRUPT_CONTROLLER_ID -1
#define REQUEST_IRQ_TYPE "NONE"
#define REQUEST_NAME "/dev/request"
#define REQUEST_RESET_VALUE 0
#define REQUEST_SPAN 16
#define REQUEST_TYPE "altera_avalon_pio"


/*
 * response configuration
 *
 */

#define ALT_MODULE_CLASS_response altera_avalon_pio
#define RESPONSE_BASE 0x9050
#define RESPONSE_BIT_CLEARING_EDGE_REGISTER 0
#define RESPONSE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RESPONSE_CAPTURE 0
#define RESPONSE_DATA_WIDTH 8
#define RESPONSE_DO_TEST_BENCH_WIRING 0
#define RESPONSE_DRIVEN_SIM_VALUE 0
#define RESPONSE_EDGE_TYPE "NONE"
#define RESPONSE_FREQ 50000000
#define RESPONSE_HAS_IN 1
#define RESPONSE_HAS_OUT 0
#define RESPONSE_HAS_TRI 0
#define RESPONSE_IRQ -1
#define RESPONSE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RESPONSE_IRQ_TYPE "NONE"
#define RESPONSE_NAME "/dev/response"
#define RESPONSE_RESET_VALUE 0
#define RESPONSE_SPAN 16
#define RESPONSE_TYPE "altera_avalon_pio"


/*
 * sysid_qsys_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys_0 altera_avalon_sysid_qsys
#define SYSID_QSYS_0_BASE 0x9070
#define SYSID_QSYS_0_ID 0
#define SYSID_QSYS_0_IRQ -1
#define SYSID_QSYS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_0_NAME "/dev/sysid_qsys_0"
#define SYSID_QSYS_0_SPAN 8
#define SYSID_QSYS_0_TIMESTAMP 1761271798
#define SYSID_QSYS_0_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x9000
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 1
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TIMER_DEVICE_TYPE 1
#define TIMER_0_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
