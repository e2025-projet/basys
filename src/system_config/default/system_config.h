/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version 2.06
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

#include "bsp.h"
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.06"
#define SYS_VERSION               20600

// *****************************************************************************
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        96000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            48000000ul
#define SYS_CLK_BUS_REFERENCE_1             28054794ul
#define SYS_CLK_UPLL_BEFORE_DIV2_FREQ       96000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         8000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       32768ul
   
/*** Ports System Service Configuration ***/
#define SYS_PORT_A_ANSEL        0x3900
#define SYS_PORT_A_TRIS         0xB900
#define SYS_PORT_A_LAT          0x0000
#define SYS_PORT_A_ODC          0x0000
#define SYS_PORT_A_CNPU         0x0000
#define SYS_PORT_A_CNPD         0x0000
#define SYS_PORT_A_CNEN         0x0000

#define SYS_PORT_B_ANSEL        0x4014
#define SYS_PORT_B_TRIS         0x4FFF
#define SYS_PORT_B_LAT          0x0000
#define SYS_PORT_B_ODC          0x0000
#define SYS_PORT_B_CNPU         0x0000
#define SYS_PORT_B_CNPD         0x0000
#define SYS_PORT_B_CNEN         0x0000

#define SYS_PORT_C_ANSEL        0x9FE1
#define SYS_PORT_C_TRIS         0xFFFF
#define SYS_PORT_C_LAT          0x0000
#define SYS_PORT_C_ODC          0x0000
#define SYS_PORT_C_CNPU         0x0008
#define SYS_PORT_C_CNPD         0x0000
#define SYS_PORT_C_CNEN         0x0000

#define SYS_PORT_D_ANSEL        0x0000
#define SYS_PORT_D_TRIS         0xCD01
#define SYS_PORT_D_LAT          0x0030
#define SYS_PORT_D_ODC          0x0000
#define SYS_PORT_D_CNPU         0x0000
#define SYS_PORT_D_CNPD         0x0000
#define SYS_PORT_D_CNEN         0x0000

#define SYS_PORT_E_ANSEL        0xFC00
#define SYS_PORT_E_TRIS         0xFFFF
#define SYS_PORT_E_LAT          0x0000
#define SYS_PORT_E_ODC          0x0000
#define SYS_PORT_E_CNPU         0x0000
#define SYS_PORT_E_CNPD         0x0000
#define SYS_PORT_E_CNEN         0x0000

#define SYS_PORT_F_ANSEL        0xCE00
#define SYS_PORT_F_TRIS         0xFFFF
#define SYS_PORT_F_LAT          0x0000
#define SYS_PORT_F_ODC          0x0000
#define SYS_PORT_F_CNPU         0x0000
#define SYS_PORT_F_CNPD         0x0000
#define SYS_PORT_F_CNEN         0x0000

#define SYS_PORT_G_ANSEL        0x0C30
#define SYS_PORT_G_TRIS         0x0FFF
#define SYS_PORT_G_LAT          0x0000
#define SYS_PORT_G_ODC          0x0000
#define SYS_PORT_G_CNPU         0x0000
#define SYS_PORT_G_CNPD         0x0040
#define SYS_PORT_G_CNEN         0x0000


/*** Command Processor System Service Configuration ***/
#define SYS_CMD_ENABLE
#define SYS_CMD_DEVICE_MAX_INSTANCES    SYS_CONSOLE_DEVICE_MAX_INSTANCES
#define SYS_CMD_PRINT_BUFFER_SIZE       8192
#define SYS_CMD_BUFFER_DMA_READY
#define SYS_CMD_REMAP_SYS_CONSOLE_MESSAGE

/*** Console System Service Configuration ***/

#define SYS_CONSOLE_OVERRIDE_STDIO
#define SYS_CONSOLE_DEVICE_MAX_INSTANCES        2
#define SYS_CONSOLE_INSTANCES_NUMBER            1
#define SYS_CONSOLE_UART_IDX               DRV_USART_INDEX_0
#define DRV_USART_BAUD_RATE_IDX0    921600
#define SYS_CONSOLE_UART_BAUD_RATE_IDX     DRV_USART_BAUD_RATE_IDX0
#define SYS_CONSOLE_UART_RD_QUEUE_DEPTH    128
#define SYS_CONSOLE_UART_WR_QUEUE_DEPTH    128
#define SYS_CONSOLE_BUFFER_DMA_READY



/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true
// *****************************************************************************
/* Random System Service Configuration Options
*/

#define SYS_RANDOM_CRYPTO_SEED_SIZE  32

/*** Timer System Service Configuration ***/
#define SYS_TMR_POWER_STATE             SYS_MODULE_POWER_RUN_FULL
#define SYS_TMR_DRIVER_INDEX            DRV_TMR_INDEX_0
#define SYS_TMR_MAX_CLIENT_OBJECTS      5
#define SYS_TMR_FREQUENCY               1000
#define SYS_TMR_FREQUENCY_TOLERANCE     10
#define SYS_TMR_UNIT_RESOLUTION         10000
#define SYS_TMR_CLIENT_TOLERANCE        10
#define SYS_TMR_INTERRUPT_NOTIFICATION  false

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

/*** ENCX24J600 Driver Configuration ***/
/*** Driver Compilation and static configuration options. ***/
#define TCPIP_IF_ENCX24J600
#define DRV_ENCX24J600_INSTANCES_NUMBER 1
#define DRV_ENCX24J600_CLIENT_INSTANCES 1
#define DRV_ENCX24J600_MAC_TX_DESCRIPTORS_IDX0 3
#define DRV_ENCX24J600_MAC_RX_DESCRIPTORS_IDX0 3
#define DRV_ENCX24J600_MAX_RX_BUFFER_IDX0 1536
#define DRV_ENCX24J600_SPI_DRIVER_INDEX_IDX0 0
#define DRV_ENCX24J600_SPI_BPS_IDX0 10000000
#define DRV_ENCX24J600_SPI_SS_PORT_MODULE_IDX0 PORTS_ID_0
#define DRV_ENCX24J600_SPI_SS_PORT_CHANNEL_IDX0 PORT_CHANNEL_C
#define DRV_ENCX24J600_SPI_SS_PORT_PIN_IDX0 PORTS_BIT_POS_2
#define DRV_ENCX24J600_RX_BUFFER_SIZE_IDX0 16384
#define DRV_ENCX24J600_MAX_FRAME_SIZE_IDX0 1536
#define DRV_ENCX24J600_ETHERNET_TYPE_IDX0 TCPIP_ETH_OPEN_AUTO
#define DRV_ENCX24J600_DUPLEX_MODE_IDX0 TCPIP_ETH_OPEN_AUTO


/*** SPI Driver Configuration ***/
#define DRV_SPI_NUMBER_OF_MODULES		2
/*** Driver Compilation and static configuration options. ***/
/*** Select SPI compilation units.***/
#define DRV_SPI_POLLED 				0
#define DRV_SPI_ISR 				1
#define DRV_SPI_MASTER 				1
#define DRV_SPI_SLAVE 				0
#define DRV_SPI_RM 					0
#define DRV_SPI_EBM 				1
#define DRV_SPI_8BIT 				1
#define DRV_SPI_16BIT 				0
#define DRV_SPI_32BIT 				0
#define DRV_SPI_DMA 				0

/*** SPI Driver Static Allocation Options ***/
#define DRV_SPI_INSTANCES_NUMBER 		1
#define DRV_SPI_CLIENTS_NUMBER 			1
#define DRV_SPI_ELEMENTS_PER_QUEUE 		10
/* SPI Driver Instance 0 Configuration */
#define DRV_SPI_SPI_ID_IDX0 				SPI_ID_2
#define DRV_SPI_TASK_MODE_IDX0 				DRV_SPI_TASK_MODE_ISR
#define DRV_SPI_SPI_MODE_IDX0				DRV_SPI_MODE_MASTER
#define DRV_SPI_ALLOW_IDLE_RUN_IDX0			false
#define DRV_SPI_SPI_PROTOCOL_TYPE_IDX0 		DRV_SPI_PROTOCOL_TYPE_STANDARD
#define DRV_SPI_COMM_WIDTH_IDX0 			SPI_COMMUNICATION_WIDTH_8BITS
#define DRV_SPI_CLOCK_SOURCE_IDX0 		    SPI_BAUD_RATE_MCLK_CLOCK
#define DRV_SPI_BAUD_RATE_IDX0 				10000000
#define DRV_SPI_BUFFER_TYPE_IDX0 			DRV_SPI_BUFFER_TYPE_ENHANCED
#define DRV_SPI_CLOCK_MODE_IDX0 			DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL
#define DRV_SPI_INPUT_PHASE_IDX0 			SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE
#define DRV_SPI_TRANSMIT_DUMMY_BYTE_VALUE_IDX0      0xFF

#define DRV_SPI_TX_INT_SOURCE_IDX0 			INT_SOURCE_SPI_2_TRANSMIT
#define DRV_SPI_RX_INT_SOURCE_IDX0 			INT_SOURCE_SPI_2_RECEIVE
#define DRV_SPI_ERROR_INT_SOURCE_IDX0 		INT_SOURCE_SPI_2_ERROR
#define DRV_SPI_INT_VECTOR_IDX0				INT_VECTOR_SPI2
#define DRV_SPI_INT_PRIORITY_IDX0			INT_PRIORITY_LEVEL1
#define DRV_SPI_INT_SUB_PRIORITY_IDX0		INT_SUBPRIORITY_LEVEL0        
#define DRV_SPI_QUEUE_SIZE_IDX0 			10
#define DRV_SPI_RESERVED_JOB_IDX0 			1
/*** Timer Driver Configuration ***/
#define DRV_TMR_INTERRUPT_MODE             true
#define DRV_TMR_INSTANCES_NUMBER           1
#define DRV_TMR_CLIENTS_NUMBER             1

/*** Timer Driver 0 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX0          TMR_ID_1
#define DRV_TMR_INTERRUPT_SOURCE_IDX0       INT_SOURCE_TIMER_1
#define DRV_TMR_INTERRUPT_VECTOR_IDX0       INT_VECTOR_T1
#define DRV_TMR_ISR_VECTOR_IDX0             _TIMER_1_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX0     INT_PRIORITY_LEVEL1
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX0 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX0           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX0               TMR_PRESCALE_VALUE_256
#define DRV_TMR_OPERATION_MODE_IDX0         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX0     false
#define DRV_TMR_POWER_STATE_IDX0            SYS_MODULE_POWER_RUN_FULL


 // *****************************************************************************
/* USART Driver Configuration Options
*/
#define DRV_USART_INSTANCES_NUMBER                  1
#define DRV_USART_CLIENTS_NUMBER                    1
#define DRV_USART_INTERRUPT_MODE                    true
#define DRV_USART_BYTE_MODEL_SUPPORT                false
#define DRV_USART_READ_WRITE_MODEL_SUPPORT          true
#define DRV_USART_BUFFER_QUEUE_SUPPORT              true
#define DRV_USART_QUEUE_DEPTH_COMBINED              512

// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: TCPIP Stack Configuration
// *****************************************************************************
// *****************************************************************************
#define TCPIP_STACK_USE_IPV4
#define TCPIP_STACK_USE_UDP

#define TCPIP_STACK_TICK_RATE		        		5
#define TCPIP_STACK_SECURE_PORT_ENTRIES             10

#define TCPIP_STACK_ALIAS_INTERFACE_SUPPORT   false

#define TCPIP_PACKET_LOG_ENABLE     0

/* TCP/IP stack event notification */
#define TCPIP_STACK_USE_EVENT_NOTIFICATION
#define TCPIP_STACK_USER_NOTIFICATION   false
#define TCPIP_STACK_DOWN_OPERATION   true
#define TCPIP_STACK_IF_UP_DOWN_OPERATION   true
#define TCPIP_STACK_MAC_DOWN_OPERATION  true
#define TCPIP_STACK_INTERFACE_CHANGE_SIGNALING   false
#define TCPIP_STACK_CONFIGURATION_SAVE_RESTORE   true
/*** TCPIP Heap Configuration ***/

#define TCPIP_STACK_USE_INTERNAL_HEAP
#define TCPIP_STACK_DRAM_SIZE                       39250
#define TCPIP_STACK_DRAM_RUN_LIMIT                  2048

#define TCPIP_STACK_MALLOC_FUNC                     malloc

#define TCPIP_STACK_CALLOC_FUNC                     calloc

#define TCPIP_STACK_FREE_FUNC                       free



#define TCPIP_STACK_HEAP_USE_FLAGS                   TCPIP_STACK_HEAP_FLAG_ALLOC_UNCACHED

#define TCPIP_STACK_HEAP_USAGE_CONFIG                TCPIP_STACK_HEAP_USE_DEFAULT

#define TCPIP_STACK_SUPPORTED_HEAPS                  1

/*** ARP Configuration ***/
#define TCPIP_ARP_CACHE_ENTRIES                 		5
#define TCPIP_ARP_CACHE_DELETE_OLD		        	true
#define TCPIP_ARP_CACHE_SOLVED_ENTRY_TMO			1200
#define TCPIP_ARP_CACHE_PENDING_ENTRY_TMO			60
#define TCPIP_ARP_CACHE_PENDING_RETRY_TMO			2
#define TCPIP_ARP_CACHE_PERMANENT_QUOTA		    		50
#define TCPIP_ARP_CACHE_PURGE_THRESHOLD		    		75
#define TCPIP_ARP_CACHE_PURGE_QUANTA		    		1
#define TCPIP_ARP_CACHE_ENTRY_RETRIES		    		3
#define TCPIP_ARP_GRATUITOUS_PROBE_COUNT			1
#define TCPIP_ARP_TASK_PROCESS_RATE		        	2
#define TCPIP_ARP_PRIMARY_CACHE_ONLY		        	true




















/*** UDP Configuration ***/
#define TCPIP_UDP_MAX_SOCKETS		                	2
#define TCPIP_UDP_SOCKET_DEFAULT_TX_SIZE		    	1536
#define TCPIP_UDP_SOCKET_DEFAULT_TX_QUEUE_LIMIT    	 	3
#define TCPIP_UDP_SOCKET_DEFAULT_RX_QUEUE_LIMIT			3
#define TCPIP_UDP_USE_POOL_BUFFERS   false
#define TCPIP_UDP_USE_TX_CHECKSUM             			true
#define TCPIP_UDP_USE_RX_CHECKSUM             			true
#define TCPIP_UDP_COMMANDS   false




/*** IPv4 Configuration ***/

/*** Network Configuration Index 0 ***/
#define TCPIP_NETWORK_DEFAULT_INTERFACE_NAME_IDX0		"ENCX24J600"
#define TCPIP_NETWORK_DEFAULT_HOST_NAME_IDX0				"MCHPBOARD_E"
#define TCPIP_NETWORK_DEFAULT_MAC_ADDR_IDX0				0
#define TCPIP_NETWORK_DEFAULT_IP_ADDRESS_IDX0			"192.168.13.4"
#define TCPIP_NETWORK_DEFAULT_IP_MASK_IDX0				"255.255.255.0"
#define TCPIP_NETWORK_DEFAULT_GATEWAY_IDX0				"192.168.13.1"
#define TCPIP_NETWORK_DEFAULT_DNS_IDX0					"192.168.13.1"
#define TCPIP_NETWORK_DEFAULT_SECOND_DNS_IDX0			"0.0.0.0"
#define TCPIP_NETWORK_DEFAULT_POWER_MODE_IDX0			"full"
#define TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS_IDX0			\
													TCPIP_NETWORK_CONFIG_IP_STATIC
#define TCPIP_NETWORK_DEFAULT_MAC_DRIVER_IDX0			DRV_ENCX24J600_MACObject
#define TCPIP_NETWORK_DEFAULT_IPV6_ADDRESS_IDX0			0
#define TCPIP_NETWORK_DEFAULT_IPV6_PREFIX_LENGTH_IDX0	0
#define TCPIP_NETWORK_DEFAULT_IPV6_GATEWAY_IDX0			0
// *****************************************************************************
/* BSP Configuration Options
*/
#define BSP_OSC_FREQUENCY 8000000


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*** Application Defined Pins ***/

/*** Functions for SegmentE pin ***/
#define SegmentEToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define SegmentEOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define SegmentEOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define SegmentEStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)))

/*** Functions for LED0 pin ***/
#define LED0Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0)
#define LED0On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0)
#define LED0Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0)
#define LED0StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0)))

/*** Functions for Anode2 pin ***/
#define Anode2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define Anode2On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define Anode2Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)
#define Anode2StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_9)))

/*** Functions for Anode3 pin ***/
#define Anode3Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10)
#define Anode3On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10)
#define Anode3Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10)
#define Anode3StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10)))

/*** Functions for LED1 pin ***/
#define LED1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)
#define LED1On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)
#define LED1Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)
#define LED1StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)))

/*** Functions for Anode0 pin ***/
#define Anode0Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12)
#define Anode0On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12)
#define Anode0Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12)
#define Anode0StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12)))

/*** Functions for Anode1 pin ***/
#define Anode1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13)
#define Anode1On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13)
#define Anode1Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13)
#define Anode1StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13)))

/*** Functions for LED2 pin ***/
#define LED2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)
#define LED2On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)
#define LED2Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)
#define LED2StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)))

/*** Functions for LED3 pin ***/
#define LED3Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3)
#define LED3On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3)
#define LED3Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3)
#define LED3StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3)))

/*** Functions for LED4 pin ***/
#define LED4Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4)
#define LED4On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4)
#define LED4Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4)
#define LED4StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4)))

/*** Functions for LED5 pin ***/
#define LED5Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5)
#define LED5On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5)
#define LED5Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5)
#define LED5StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5)))

/*** Functions for SegmentB pin ***/
#define SegmentBToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_14)
#define SegmentBOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_14)
#define SegmentBOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_14)
#define SegmentBStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_14)))

/*** Functions for LED_R pin ***/
#define LED_RToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define LED_ROn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define LED_ROff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define LED_RStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)

/*** Functions for LED_B pin ***/
#define LED_BToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)
#define LED_BOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)
#define LED_BOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)
#define LED_BStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_3)

/*** Functions for LED_G pin ***/
#define LED_GToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)
#define LED_GOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)
#define LED_GOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)
#define LED_GStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_12)

/*** Functions for SegmentG pin ***/
#define SegmentGToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)
#define SegmentGOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)
#define SegmentGOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)
#define SegmentGStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)))

/*** Functions for SegmentC pin ***/
#define SegmentCToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)
#define SegmentCOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)
#define SegmentCOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)
#define SegmentCStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)))

/*** Functions for SegmentF pin ***/
#define SegmentFToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7)
#define SegmentFOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7)
#define SegmentFOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7)
#define SegmentFStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7)))

/*** Functions for LED6 pin ***/
#define LED6Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)
#define LED6On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)
#define LED6Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)
#define LED6StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)))

/*** Functions for LED7 pin ***/
#define LED7Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)
#define LED7On() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)
#define LED7Off() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)
#define LED7StateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)))

/*** Functions for SegmentP pin ***/
#define SegmentPToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14)
#define SegmentPOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14)
#define SegmentPOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14)
#define SegmentPStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14)))

/*** Functions for SegmentA pin ***/
#define SegmentAToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12)
#define SegmentAOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12)
#define SegmentAOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12)
#define SegmentAStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_12)))

/*** Functions for SegmentD pin ***/
#define SegmentDToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)
#define SegmentDOn() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)
#define SegmentDOff() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)
#define SegmentDStateGet() (!(PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)))

/*** Functions for ButtonUp pin ***/
#define ButtonUpStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1)

/*** Functions for ButtonLeft pin ***/
#define ButtonLeftStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_0)

/*** Functions for ButtonRight pin ***/
#define ButtonRightStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_8)

/*** Functions for SWITCH7 pin ***/
#define SWITCH7StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9)

/*** Functions for SWITCH6 pin ***/
#define SWITCH6StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10)

/*** Functions for SWITCH5 pin ***/
#define SWITCH5StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11)

/*** Functions for SWITCH4 pin ***/
#define SWITCH4StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_14)

/*** Functions for SWITCH3 pin ***/
#define SWITCH3StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_15)

/*** Functions for SWITCH2 pin ***/
#define SWITCH2StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_4)

/*** Functions for SWITCH1 pin ***/
#define SWITCH1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_5)

/*** Functions for SWITCH0 pin ***/
#define SWITCH0StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_3)

/*** Functions for ButtonDown pin ***/
#define ButtonDownStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_15)

/*** Functions for ButtonCenter pin ***/
#define ButtonCenterStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)

/*** Functions for LCD_RS pin ***/
#define LCD_RSToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define LCD_RSOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define LCD_RSOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define LCD_RSStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15)
#define LCD_RSStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15, Value)

/*** Functions for JB1 pin ***/
#define JB1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_9)
#define JB1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_9)
#define JB1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_9)
#define JB1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_9)
#define JB1StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_9, Value)

/*** Functions for LCD_EN pin ***/
#define LCD_ENToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define LCD_ENOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define LCD_ENOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define LCD_ENStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define LCD_ENStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4, Value)

/*** Functions for LCD_RW pin ***/
#define LCD_RWToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define LCD_RWOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define LCD_RWOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define LCD_RWStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define LCD_RWStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5, Value)

/*** Functions for LCD5 pin ***/
#define LCD5_PORT PORT_CHANNEL_E
#define LCD5_PIN PORTS_BIT_POS_5
#define LCD5_PIN_MASK (0x1 << 5)

/*** Functions for LCD6 pin ***/
#define LCD6_PORT PORT_CHANNEL_E
#define LCD6_PIN PORTS_BIT_POS_6
#define LCD6_PIN_MASK (0x1 << 6)

/*** Functions for LCD7 pin ***/
#define LCD7_PORT PORT_CHANNEL_E
#define LCD7_PIN PORTS_BIT_POS_7
#define LCD7_PIN_MASK (0x1 << 7)

/*** Functions for JA8 pin ***/
#define JA8_PORT PORT_CHANNEL_G
#define JA8_PIN PORTS_BIT_POS_7
#define JA8_PIN_MASK (0x1 << 7)

/*** Functions for JA9 pin ***/
#define JA9_PORT PORT_CHANNEL_G
#define JA9_PIN PORTS_BIT_POS_8
#define JA9_PIN_MASK (0x1 << 8)

/*** Functions for JA10 pin ***/
#define JA10_PORT PORT_CHANNEL_G
#define JA10_PIN PORTS_BIT_POS_9
#define JA10_PIN_MASK (0x1 << 9)

/*** Functions for AIN2 pin ***/
#define AIN2_PORT PORT_CHANNEL_E
#define AIN2_PIN PORTS_BIT_POS_8
#define AIN2_PIN_MASK (0x1 << 8)

/*** Functions for BIN1 pin ***/
#define BIN1_PORT PORT_CHANNEL_E
#define BIN1_PIN PORTS_BIT_POS_9
#define BIN1_PIN_MASK (0x1 << 9)

/*** Functions for BIN2 pin ***/
#define BIN2_PORT PORT_CHANNEL_B
#define BIN2_PIN PORTS_BIT_POS_5
#define BIN2_PIN_MASK (0x1 << 5)

/*** Functions for AIN1 pin ***/
#define AIN1_PORT PORT_CHANNEL_B
#define AIN1_PIN PORTS_BIT_POS_3
#define AIN1_PIN_MASK (0x1 << 3)

/*** Functions for JB4 pin ***/
#define JB4_PORT PORT_CHANNEL_D
#define JB4_PIN PORTS_BIT_POS_8
#define JB4_PIN_MASK (0x1 << 8)

/*** Functions for JB1 pin ***/
#define JB1_PORT PORT_CHANNEL_D
#define JB1_PIN PORTS_BIT_POS_9
#define JB1_PIN_MASK (0x1 << 9)

/*** Functions for JB3 pin ***/
#define JB3_PORT PORT_CHANNEL_D
#define JB3_PIN PORTS_BIT_POS_10
#define JB3_PIN_MASK (0x1 << 10)

/*** Functions for JB2 pin ***/
#define JB2_PORT PORT_CHANNEL_D
#define JB2_PIN PORTS_BIT_POS_11
#define JB2_PIN_MASK (0x1 << 11)

/*** Functions for JB8 pin ***/
#define JB8_PORT PORT_CHANNEL_D
#define JB8_PIN PORTS_BIT_POS_0
#define JB8_PIN_MASK (0x1 << 0)

/*** Functions for JB10 pin ***/
#define JB10_PORT PORT_CHANNEL_C
#define JB10_PIN PORTS_BIT_POS_13
#define JB10_PIN_MASK (0x1 << 13)

/*** Functions for JB7 pin ***/
#define JB7_PORT PORT_CHANNEL_C
#define JB7_PIN PORTS_BIT_POS_14
#define JB7_PIN_MASK (0x1 << 14)

/*** Functions for JB9 pin ***/
#define JB9_PORT PORT_CHANNEL_D
#define JB9_PIN PORTS_BIT_POS_1
#define JB9_PIN_MASK (0x1 << 1)

/*** Functions for IR_Mode pin ***/
#define IR_Mode_PORT PORT_CHANNEL_F
#define IR_Mode_PIN PORTS_BIT_POS_1
#define IR_Mode_PIN_MASK (0x1 << 1)

/*** Functions for IR_PWDN pin ***/
#define IR_PWDN_PORT PORT_CHANNEL_G
#define IR_PWDN_PIN PORTS_BIT_POS_1
#define IR_PWDN_PIN_MASK (0x1 << 1)

/*** Functions for LCD0 pin ***/
#define LCD0_PORT PORT_CHANNEL_E
#define LCD0_PIN PORTS_BIT_POS_0
#define LCD0_PIN_MASK (0x1 << 0)

/*** Functions for LCD1 pin ***/
#define LCD1_PORT PORT_CHANNEL_E
#define LCD1_PIN PORTS_BIT_POS_1
#define LCD1_PIN_MASK (0x1 << 1)

/*** Functions for LCD2 pin ***/
#define LCD2_PORT PORT_CHANNEL_E
#define LCD2_PIN PORTS_BIT_POS_2
#define LCD2_PIN_MASK (0x1 << 2)

/*** Functions for LCD3 pin ***/
#define LCD3_PORT PORT_CHANNEL_E
#define LCD3_PIN PORTS_BIT_POS_3
#define LCD3_PIN_MASK (0x1 << 3)

/*** Functions for LCD4 pin ***/
#define LCD4_PORT PORT_CHANNEL_E
#define LCD4_PIN PORTS_BIT_POS_4
#define LCD4_PIN_MASK (0x1 << 4)


/*** Application Instance 0 Configuration ***/
/*
   USART Read Write model constants used by the application:
   
       MAIN_DRV_USART  : Identifies the USART Driver instance to use
*/
#define MAIN_DRV_USART                 0

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/
