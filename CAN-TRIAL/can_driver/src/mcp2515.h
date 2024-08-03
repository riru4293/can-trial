/*
 * (c) 2024 Project-K.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef MCP2515_H
#define MCP2515_H

/*!
 * \file mcp2515.h
 * \brief Definitions for the MCP2515.
 *
 * \author riru
 * \date 2024-06-21
 */


/*! 
 * \defgroup Mcp2515RegAddr MCP2515 register address
 * Legend:
 *   - R = Readable bit
 *   - W = Writable bit
 *   - U = Unimplemented bit, read as ‘0’
 *   - -n = Value at POR
 *   - ‘1’ = Bit is set
 *   - ‘0’ = Bit is cleared
 *   - x = Bit is unknown
 * 
 */
/*! \{ */
#define REG_RXF0SIDH                    ( (uint8_t)0x00U )
#define REG_RXF0SIDL                    ( (uint8_t)0x01U )
#define REG_RXF0EID8                    ( (uint8_t)0x02U )
#define REG_RXF0EID0                    ( (uint8_t)0x03U )


#define REG_RXF1SIDH                    ( (uint8_t)0x04U )
#define REG_RXF1SIDL                    ( (uint8_t)0x05U )
#define REG_RXF1EID8                    ( (uint8_t)0x06U )
#define REG_RXF1EID0                    ( (uint8_t)0x07U )
#define REG_RXF2SIDH                    ( (uint8_t)0x08U )
#define REG_RXF2SIDL                    ( (uint8_t)0x09U )
#define REG_RXF2EID8                    ( (uint8_t)0x0AU )
#define REG_RXF2EID0                    ( (uint8_t)0x0BU )

/*!
 * @brief BFPCTRL  
 * RXnBF PIN CONTROL AND STATUS REGISTER (ADDRESS: 0Ch)
 *
 * | bit#7 | bit#6 | bit#5 | bit#4 | bit#3 | bit#2 | bit#1 | bit#0 |
 * | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |
 * | U-0   | U-0   | R/W-0 | R/W-0 | R/W-0 | R/W-0 | R/W-0 | R/W-0 |
 * | -     | -     | B1BFS | B0BFS | B1BFE | B0BFE | B1BFM | B0BFM |
 * 
 * - bit 7: reserved
 * - bit 6: reserved
 * - bit 5: RX1BF Pin State bit (Digital Output mode only). Reads as ‘0’ when RX1BF is configured as interrupt pin.
 * - bit 4: RX0BF Pin State bit (Digital Output mode only). Reads as ‘0’ when RX0BF is configured as interrupt pin.
 * - bit 3: RX1BF Pin Function Enable bit.
 *   - 1 = Pin function enabled, operation mode determined by B1BFM bit.
 *   - 0 = Pin function disabled, pin goes to high-impedance state.
 * - bit 2: RX0BF Pin Function Enable bit.
 *   - 1 = Pin function enabled, operation mode determined by B0BFM bit.
 *   - 0 = Pin function disabled, pin goes to high-impedance state.
 * - bit 1: RX1BF Pin Operation Mode bit.
 *   - 1 = Pin is used as interrupt when valid message loaded into RXB1.
 *   - 0 = Digital Output mode.
 * - bit 0: RX0BF Pin Operation Mode bit.
 *   - 1 = Pin is used as interrupt when valid message loaded into RXB0.
 *   - 0 = Digital Output mode.
 * 
 */
#define REG_BFPCTRL                     ( (uint8_t)0x0CU )


#define REG_TXRTSCTRL                   ( (uint8_t)0x0DU )


/*!
 * @brief CANSTAT  
 * CAN STATUS REGISTER (ADDRESS: XEh)
 * 
 * | bit#7  | bit#6  | bit#5  | bit#4 | bit#3 | bit#2 | bit#1 | bit#0 |
 * | ------ | ------ | ------ | ----- | ----- | ----- | ----- | ----- |
 * | R-1    | R-0    | R-0    | U-0   | R-0   | R-0   | R-0   | U-0   |
 * | OPMOD2 | OPMOD1 | OPMOD0 | -     | ICOD2 | ICOD1 | ICOD0 | -     |
 *
 * - bit 7-5: OPMOD[2:0]: Operation Mode bits
 *   - 000 = Device is in Normal Operation mode
 *   - 001 = Device is in Sleep mode
 *   - 010 = Device is in Loopback mode
 *   - 011 = Device is in Listen-Only mode
 *   - 100 = Device is in Configuration mode
 * - bit 4: Unimplemented: Read as ‘0’
 * - bit 3-1: ICOD[2:0]: Interrupt Flag Code bits
 *   - 000 = No interrupt
 *   - 001 = Error interrupt
 *   - 010 = Wake-up interrupt
 *   - 011 = TXB0 interrupt
 *   - 100 = TXB1 interrupt
 *   - 101 = TXB2 interrupt
 *   - 110 = RXB0 interrupt
 *   - 111 = RXB1 interrupt
 * - bit 0: Unimplemented: Read as ‘0’
 */
#define REG_CANSTAT                     ( (uint8_t)0x0EU )


#define REG_CANCTRL                     ( (uint8_t)0x0FU )               /*!< CAN control    */


#define REG_RXF3SIDH                    ( (uint8_t)0x10U )
#define REG_RXF3SIDL                    ( (uint8_t)0x11U )
#define REG_RXF3EID8                    ( (uint8_t)0x12U )
#define REG_RXF3EID0                    ( (uint8_t)0x13U )


#define REG_RXF4SIDH                    ( (uint8_t)0x14U )
#define REG_RXF4SIDL                    ( (uint8_t)0x15U )
#define REG_RXF4EID8                    ( (uint8_t)0x16U )
#define REG_RXF4EID0                    ( (uint8_t)0x17U )


#define REG_RXF5SIDH                    ( (uint8_t)0x18U )
#define REG_RXF5SIDL                    ( (uint8_t)0x19U )
#define REG_RXF5EID8                    ( (uint8_t)0x1AU )
#define REG_RXF5EID0                    ( (uint8_t)0x1BU )


#define REG_TEC                         ( (uint8_t)0x1CU )
#define REG_REC                         ( (uint8_t)0x1DU )


#define REG_RXM0SIDH                    ( (uint8_t)0x20U )
#define REG_RXM0SIDL                    ( (uint8_t)0x21U )
#define REG_RXM0EID8                    ( (uint8_t)0x22U )
#define REG_RXM0EID0                    ( (uint8_t)0x23U )


#define REG_RXM1SIDH                    ( (uint8_t)0x24U )
#define REG_RXM1SIDL                    ( (uint8_t)0x25U )
#define REG_RXM1EID8                    ( (uint8_t)0x26U )
#define REG_RXM1EID0                    ( (uint8_t)0x27U )


#define REG_CNF3                        ( (uint8_t)0x28U )               /*!< CAN bus interface bit timing #3 */
#define REG_CNF2                        ( (uint8_t)0x29U )               /*!< CAN bus interface bit timing #2 */
#define REG_CNF1                        ( (uint8_t)0x2AU )               /*!< CAN bus interface bit timing #1 */


#define REG_CANINTE                     ( (uint8_t)0x2BU )               /*!< CAN interrupt enables           */
#define REG_CANINTF                     ( (uint8_t)0x2CU )               /*!< CAN interrupt flags             */
#define REG_EFLG                        ( (uint8_t)0x2DU )


#define REG_TXB0CTRL                    ( (uint8_t)0x30U )
#define REG_TXB0SIDH                    ( (uint8_t)0x31U )
#define REG_TXB0SIDL                    ( (uint8_t)0x32U )
#define REG_TXB0EID8                    ( (uint8_t)0x33U )
#define REG_TXB0EID0                    ( (uint8_t)0x34U )
#define REG_TXB0DLC                     ( (uint8_t)0x35U )
#define REG_TXB0D0                      ( (uint8_t)0x36U )
#define REG_TXB0D1                      ( (uint8_t)0x37U )
#define REG_TXB0D2                      ( (uint8_t)0x38U )
#define REG_TXB0D3                      ( (uint8_t)0x39U )
#define REG_TXB0D4                      ( (uint8_t)0x3AU )
#define REG_TXB0D5                      ( (uint8_t)0x3BU )
#define REG_TXB0D6                      ( (uint8_t)0x3CU )
#define REG_TXB0D7                      ( (uint8_t)0x3DU )


#define REG_TXB1CTRL                    ( (uint8_t)0x40U )
#define REG_TXB1SIDH                    ( (uint8_t)0x41U )
#define REG_TXB1SIDL                    ( (uint8_t)0x42U )
#define REG_TXB1EID8                    ( (uint8_t)0x43U )
#define REG_TXB1EID0                    ( (uint8_t)0x44U )
#define REG_TXB1DLC                     ( (uint8_t)0x45U )
#define REG_TXB1D0                      ( (uint8_t)0x46U )
#define REG_TXB1D1                      ( (uint8_t)0x47U )
#define REG_TXB1D2                      ( (uint8_t)0x48U )
#define REG_TXB1D3                      ( (uint8_t)0x49U )
#define REG_TXB1D4                      ( (uint8_t)0x4AU )
#define REG_TXB1D5                      ( (uint8_t)0x4BU )
#define REG_TXB1D6                      ( (uint8_t)0x4CU )
#define REG_TXB1D7                      ( (uint8_t)0x4DU )


#define REG_TXB2CTRL                    ( (uint8_t)0x50U )
#define REG_TXB2SIDH                    ( (uint8_t)0x51U )
#define REG_TXB2SIDL                    ( (uint8_t)0x52U )
#define REG_TXB2EID8                    ( (uint8_t)0x53U )
#define REG_TXB2EID0                    ( (uint8_t)0x54U )
#define REG_TXB2DLC                     ( (uint8_t)0x55U )
#define REG_TXB2D0                      ( (uint8_t)0x56U )
#define REG_TXB2D1                      ( (uint8_t)0x57U )
#define REG_TXB2D2                      ( (uint8_t)0x58U )
#define REG_TXB2D3                      ( (uint8_t)0x59U )
#define REG_TXB2D4                      ( (uint8_t)0x5AU )
#define REG_TXB2D5                      ( (uint8_t)0x5BU )
#define REG_TXB2D6                      ( (uint8_t)0x5CU )
#define REG_TXB2D7                      ( (uint8_t)0x5DU )


#define REG_RXB0CTRL                    ( (uint8_t)0x60U )
#define REG_RXB0SIDH                    ( (uint8_t)0x61U )
#define REG_RXB0SIDL                    ( (uint8_t)0x62U )
#define REG_RXB0EID8                    ( (uint8_t)0x63U )
#define REG_RXB0EID0                    ( (uint8_t)0x64U )
#define REG_RXB0DLC                     ( (uint8_t)0x65U )
#define REG_RXB0D0                      ( (uint8_t)0x66U )
#define REG_RXB0D1                      ( (uint8_t)0x67U )
#define REG_RXB0D2                      ( (uint8_t)0x68U )
#define REG_RXB0D3                      ( (uint8_t)0x69U )
#define REG_RXB0D4                      ( (uint8_t)0x6AU )
#define REG_RXB0D5                      ( (uint8_t)0x6BU )
#define REG_RXB0D6                      ( (uint8_t)0x6CU )
#define REG_RXB0D7                      ( (uint8_t)0x6DU )


#define REG_RXB1CTRL                    ( (uint8_t)0x70U )
#define REG_RXB1SIDH                    ( (uint8_t)0x71U )
#define REG_RXB1SIDL                    ( (uint8_t)0x72U )
#define REG_RXB1EID8                    ( (uint8_t)0x73U )
#define REG_RXB1EID0                    ( (uint8_t)0x74U )
#define REG_RXB1DLC                     ( (uint8_t)0x75U )
#define REG_RXB1D0                      ( (uint8_t)0x76U )
#define REG_RXB1D1                      ( (uint8_t)0x77U )
#define REG_RXB1D2                      ( (uint8_t)0x78U )
#define REG_RXB1D3                      ( (uint8_t)0x79U )
#define REG_RXB1D4                      ( (uint8_t)0x7AU )
#define REG_RXB1D5                      ( (uint8_t)0x7BU )
#define REG_RXB1D6                      ( (uint8_t)0x7CU )
#define REG_RXB1D7                      ( (uint8_t)0x7DU )
/*! \} */


/*! 
 * \defgroup Mcp2515RegMask MCP2515 register mask 
 */
/*! \{ */

#define MASKOF_BFPCTRL_B1BFS            ( (uint8_t)0x20U )
#define MASKOF_BFPCTRL_B0BFS            ( (uint8_t)0x10U )
#define MASKOF_BFPCTRL_B1BFE            ( (uint8_t)0x08U )
#define MASKOF_BFPCTRL_B0BFE            ( (uint8_t)0x04U )
#define MASKOF_BFPCTRL_B1BFM            ( (uint8_t)0x02U )
#define MASKOF_BFPCTRL_B0BFM            ( (uint8_t)0x01U )


#define MASKOF_TXRTSCTRL_B2RTS          ( (uint8_t)0x20U )
#define MASKOF_TXRTSCTRL_B1RTS          ( (uint8_t)0x10U )
#define MASKOF_TXRTSCTRL_B0RTS          ( (uint8_t)0x08U )
#define MASKOF_TXRTSCTRL_B2RTSM         ( (uint8_t)0x04U )
#define MASKOF_TXRTSCTRL_B1RTSM         ( (uint8_t)0x02U )
#define MASKOF_TXRTSCTRL_B0RTSM         ( (uint8_t)0x01U )


#define MASKOF_CANSTAT_OPMOD            ( (uint8_t)0xE0U )               /*!< Operation mode      */
#define MASKOF_CANSTAT_ICOD             ( (uint8_t)0x0EU )               /*!< Inturrupt kind      */


#define MASKOF_CANCTRL_REQOP            ( (uint8_t)0xE0U )
#define MASKOF_CANCTRL_ABAT             ( (uint8_t)0x10U )               /*!< Abort send CAN message     */
#define MASKOF_CANCTRL_OSM              ( (uint8_t)0x08U )               /*!< One shot send CAN message  */
#define MASKOF_CANCTRL_CLKEN            ( (uint8_t)0x04U )
#define MASKOF_CANCTRL_CLKPRE           ( (uint8_t)0x03U )


#define MASKOF_CANINT_MERRF             ( (uint8_t)0x80U )
#define MASKOF_CANINT_WAKIF             ( (uint8_t)0x40U )
#define MASKOF_CANINT_ERRIF             ( (uint8_t)0x20U )
#define MASKOF_CANINT_TX2IF             ( (uint8_t)0x10U )
#define MASKOF_CANINT_TX1IF             ( (uint8_t)0x08U )
#define MASKOF_CANINT_TX0IF             ( (uint8_t)0x04U )
#define MASKOF_CANINT_RX1IF             ( (uint8_t)0x02U )
#define MASKOF_CANINT_RX0IF             ( (uint8_t)0x01U )


#define MASKOF_EFLG_RX1OVR              ( (uint8_t)0x80U )
#define MASKOF_EFLG_RX0OVR              ( (uint8_t)0x40U )
#define MASKOF_EFLG_TXBO                ( (uint8_t)0x20U )
#define MASKOF_EFLG_TXEP                ( (uint8_t)0x10U )
#define MASKOF_EFLG_RXEP                ( (uint8_t)0x08U )
#define MASKOF_EFLG_TXWAR               ( (uint8_t)0x04U )
#define MASKOF_EFLG_RXWAR               ( (uint8_t)0x02U )
#define MASKOF_EFLG_EWARN               ( (uint8_t)0x01U )


#define MASKOF_TXBCTRL_ABTF             ( (uint8_t)0x40U )
#define MASKOF_TXBCTRL_MLOA             ( (uint8_t)0x20U )
#define MASKOF_TXBCTRL_TXERR            ( (uint8_t)0x10U )
#define MASKOF_TXBCTRL_TXREQ            ( (uint8_t)0x08U )
#define MASKOF_TXBCTRL_TXP              ( (uint8_t)0x03U )

#define MASKOF_RXBCTRL_RXM              ( (uint8_t)0x60U )
#define MASKOF_RXBCTRL_RXRTR            ( (uint8_t)0x08U )
#define MASKOF_RXB0CTRL_BUKT            ( (uint8_t)0x04U )
#define MASKOF_RXB0CTRL_FILHIT          ( (uint8_t)0x01U )
#define MASKOF_RXB1CTRL_FILHIT          ( (uint8_t)0x07U )

#define MASKOF_SIDL_IDE                 ( (uint8_t)0x08U )
#define MASKOF_RTR                      ( (uint8_t)0x40U )
#define MASKOF_DLC                      ( (uint8_t)0x0FU )
/*! \} */


/*! 
 * \defgroup Mcp2515SpiCmd MCP2515 SPI command
 */
/*! \{ */
#define SPICMD_WRITE_REG                ( (uint8_t)0x02U )               /*!< Write bytes to register           */
#define SPICMD_READ_REG                 ( (uint8_t)0x03U )               /*!< Read bytes from register          */
#define SPICMD_MODBITS_REG              ( (uint8_t)0x05U )               /*!< Modify register bits in a byte    */
#define SPICMD_WRITE_TX0_ID             ( (uint8_t)0x40U )               /*!< Write TX0 CAN id and DLC          */
#define SPICMD_WRITE_TX0_CONTENT        ( (uint8_t)0x41U )               /*!< Write TX0 CAN content             */
#define SPICMD_WRITE_TX1_ID             ( (uint8_t)0x42U )               /*!< Write TX1 CAN id and DLC          */
#define SPICMD_WRITE_TX1_CONTENT        ( (uint8_t)0x43U )               /*!< Write TX1 CAN content             */
#define SPICMD_WRITE_TX2_ID             ( (uint8_t)0x44U )               /*!< Write TX2 CAN id and DLC          */
#define SPICMD_WRITE_TX2_CONTENT        ( (uint8_t)0x45U )               /*!< Write TX2 CAN content             */
#define SPICMD_REQ_TX0                  ( (uint8_t)0x81U )               /*!< Set TX0 transmission request      */
#define SPICMD_REQ_TX1                  ( (uint8_t)0x82U )               /*!< Set TX1 transmission request      */
#define SPICMD_REQ_TX2                  ( (uint8_t)0x83U )               /*!< Set TX2 transmission request      */
#define SPICMD_READ_RX0_HDR             ( (uint8_t)0x90U )               /*!< Read RX0 CAN id and DLC           */
#define SPICMD_READ_RX0_BODY            ( (uint8_t)0x92U )               /*!< Read RX0 CAN content              */
#define SPICMD_READ_RX1_HDR             ( (uint8_t)0x94U )               /*!< Read RX1 CAN id and DLC           */
#define SPICMD_READ_RX1_BODY            ( (uint8_t)0x96U )               /*!< Read RX1 CAN content              */
#define SPICMD_READ_STAT                ( (uint8_t)0xA0U )               
                                                                /*!< Reads a statuses
                                                                 *     - bit#7: CANINTF.RX0IF
                                                                 *     - bit#6: CANINTF.RX1IF
                                                                 *     - bit#5: TXB0CNTRL.TXREQ
                                                                 *     - bit#4: CANINTF.TX0IF
                                                                 *     - bit#3: TXB1CNTRL.TXREQ
                                                                 *     - bit#2: CANINTF.TX1IF
                                                                 *     - bit#1: TXB2CNTRL.TXREQ
                                                                 *     - bit#0: CANINTF.TX2IF
                                                                 */
#define SPICMD_READ_RXSTAT              ( (uint8_t)0xB0U )               
                                                                /*!< Read RX status
                                                                 *     | bit#7 | bit#6 | Received Message        |
                                                                 *     | ----- | ----- | ----------------------- |
                                                                 *     | 0     | 0     | No Rx message           |
                                                                 *     | 0     | 1     | Message in RXB0         |
                                                                 *     | 1     | 0     | Message in RXB1         |
                                                                 *     | 1     | 1     | Message in both buffers |
                                                                 * 
                                                                 *     | bit#4 | bit#3 | Msg Type Received       |
                                                                 *     | ----- | ----- | ----------------------- |
                                                                 *     | 0     | 0     | Standard data frame     |
                                                                 *     | 0     | 1     | Standard remote frame   |
                                                                 *     | 1     | 0     | Extended data frame     |
                                                                 *     | 1     | 1     | Extended remote frame   |
                                                                 * 
                                                                 *     | bit#2 | bit#1 | bit#0 | Filter Match            |
                                                                 *     | ----- | ----- | ----- | ----------------------- |
                                                                 *     | 0     | 0     | 0     | RXF0                    |
                                                                 *     | 0     | 0     | 1     | RXF1                    |
                                                                 *     | 0     | 1     | 0     | RXF2                    |
                                                                 *     | 0     | 1     | 1     | RXF3                    |
                                                                 *     | 1     | 0     | 0     | RXF4                    |
                                                                 *     | 1     | 0     | 1     | RXF5                    |
                                                                 *     | 1     | 1     | 0     | RXF0 (rollover to RXB1) |
                                                                 *     | 1     | 1     | 1     | RXF1 (rollover to RXB1) |
                                                                 */
#define SPICMD_RESET                    ( (uint8_t)0xC0U )               /*!< Reset the MCP2515 */
/*! \} */


/*! 
 * \defgroup Mcp2515OpMode MCP2515 operation mode
 */
/*! \{ */
#define OPMODE_NORMAL       ( (uint8_t)0x00U )   /*!< Normal mode          */
#define OPMODE_SLEEP        ( (uint8_t)0x20U )   /*!< Sleep mode           */
#define OPMODE_LOOPBACK     ( (uint8_t)0x40U )   /*!< Loop back mode       */
#define OPMODE_LISTENONLY   ( (uint8_t)0x60U )   /*!< Listen only mode     */
#define OPMODE_CONFIG       ( (uint8_t)0x80U )   /*!< Config mode.         */
/*! \} */


#define CAN_BAUDRATE_125KBPS    ( (uint8_t[]){ 0x02U, 0x89U, 0x07U } )
#define CAN_BAUDRATE_250KBPS    ( (uint8_t[]){ 0x02U, 0x89U, 0x03U } )
#define CAN_BAUDRATE_500KBPS    ( (uint8_t[]){ 0x02U, 0x89U, 0x01U } )
#define CAN_BAUDRATE_1000KBPS   ( (uint8_t[]){ 0x02U, 0x89U, 0x07U } )

#define SPI_BAUDRATE_10MHZ ( 10000000U ) /* 10MHz */

// #define GPIO_NUM_MISO            ( (uint8_t) 4U )
// #define GPIO_NUM_CS              ( (uint8_t) 5U )
// #define GPIO_NUM_SCK             ( (uint8_t) 6U )
// #define GPIO_NUM_MOSI            ( (uint8_t) 7U )
// #define GPIO_NUM_INT             ( (uint8_t)21U )

#define REGVAL_ALLBIT_ON    ( (uint8_t)0xFFU )
#define REGVAL_ALLBIT_OFF   ( (uint8_t)0x00U )

#define REGVAL_CANINT_WAKIF_ENABLED   ( (uint8_t)( REGVAL_ALLBIT_ON & MASKOF_CANINT_WAKIF ) )



#endif /* MCP2515_H */
