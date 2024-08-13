#include "private/mcp2515.h"
#include "private/rp2040.h"


#define SPICMD_WRITE_REG                ( (UCHAR)0x02U )
#define SPICMD_READ_REG                 ( (UCHAR)0x03U )
#define SPICMD_MODBITS_REG              ( (UCHAR)0x05U )
#define SPICMD_WRITE_TX0_ID             ( (UCHAR)0x40U )
#define SPICMD_WRITE_TX0_CONTENT        ( (UCHAR)0x41U )
#define SPICMD_WRITE_TX1_ID             ( (UCHAR)0x42U )
#define SPICMD_WRITE_TX1_CONTENT        ( (UCHAR)0x43U )
#define SPICMD_WRITE_TX2_ID             ( (UCHAR)0x44U )
#define SPICMD_WRITE_TX2_CONTENT        ( (UCHAR)0x45U )
#define SPICMD_REQ_TX0                  ( (UCHAR)0x81U )
#define SPICMD_REQ_TX1                  ( (UCHAR)0x82U )
#define SPICMD_REQ_TX2                  ( (UCHAR)0x83U )
#define SPICMD_READ_RX0_HDR             ( (UCHAR)0x90U )
#define SPICMD_READ_RX0_BODY            ( (UCHAR)0x92U )
#define SPICMD_READ_RX1_HDR             ( (UCHAR)0x94U )
#define SPICMD_READ_RX1_BODY            ( (UCHAR)0x96U )
#define SPICMD_READ_STAT                ( (UCHAR)0xA0U )
#define SPICMD_READ_RXSTAT              ( (UCHAR)0xB0U )
#define SPICMD_RESET                    ( (UCHAR)0xC0U )

#define REG_RXF0SIDH                    ( (UCHAR)0x00U )
#define REG_RXF0SIDL                    ( (UCHAR)0x01U )
#define REG_RXF0EID8                    ( (UCHAR)0x02U )
#define REG_RXF0EID0                    ( (UCHAR)0x03U )
#define REG_RXF1SIDH                    ( (UCHAR)0x04U )
#define REG_RXF1SIDL                    ( (UCHAR)0x05U )
#define REG_RXF1EID8                    ( (UCHAR)0x06U )
#define REG_RXF1EID0                    ( (UCHAR)0x07U )
#define REG_RXF2SIDH                    ( (UCHAR)0x08U )
#define REG_RXF2SIDL                    ( (UCHAR)0x09U )
#define REG_RXF2EID8                    ( (UCHAR)0x0AU )
#define REG_RXF2EID0                    ( (UCHAR)0x0BU )
#define REG_BFPCTRL                     ( (UCHAR)0x0CU )
#define REG_TXRTSCTRL                   ( (UCHAR)0x0DU )
#define REG_CANSTAT                     ( (UCHAR)0x0EU )
#define REG_CANCTRL                     ( (UCHAR)0x0FU )
#define REG_RXF3SIDH                    ( (UCHAR)0x10U )
#define REG_RXF3SIDL                    ( (UCHAR)0x11U )
#define REG_RXF3EID8                    ( (UCHAR)0x12U )
#define REG_RXF3EID0                    ( (UCHAR)0x13U )
#define REG_RXF4SIDH                    ( (UCHAR)0x14U )
#define REG_RXF4SIDL                    ( (UCHAR)0x15U )
#define REG_RXF4EID8                    ( (UCHAR)0x16U )
#define REG_RXF4EID0                    ( (UCHAR)0x17U )
#define REG_RXF5SIDH                    ( (UCHAR)0x18U )
#define REG_RXF5SIDL                    ( (UCHAR)0x19U )
#define REG_RXF5EID8                    ( (UCHAR)0x1AU )
#define REG_RXF5EID0                    ( (UCHAR)0x1BU )
#define REG_TEC                         ( (UCHAR)0x1CU )
#define REG_REC                         ( (UCHAR)0x1DU )
#define REG_RXM0SIDH                    ( (UCHAR)0x20U )
#define REG_RXM0SIDL                    ( (UCHAR)0x21U )
#define REG_RXM0EID8                    ( (UCHAR)0x22U )
#define REG_RXM0EID0                    ( (UCHAR)0x23U )
#define REG_RXM1SIDH                    ( (UCHAR)0x24U )
#define REG_RXM1SIDL                    ( (UCHAR)0x25U )
#define REG_RXM1EID8                    ( (UCHAR)0x26U )
#define REG_RXM1EID0                    ( (UCHAR)0x27U )
#define REG_CNF3                        ( (UCHAR)0x28U )
#define REG_CNF2                        ( (UCHAR)0x29U )
#define REG_CNF1                        ( (UCHAR)0x2AU )
#define REG_CANINTE                     ( (UCHAR)0x2BU )
#define REG_CANINTF                     ( (UCHAR)0x2CU )
#define REG_EFLG                        ( (UCHAR)0x2DU )
#define REG_TXB0CTRL                    ( (UCHAR)0x30U )
#define REG_TXB0SIDH                    ( (UCHAR)0x31U )
#define REG_TXB0SIDL                    ( (UCHAR)0x32U )
#define REG_TXB0EID8                    ( (UCHAR)0x33U )
#define REG_TXB0EID0                    ( (UCHAR)0x34U )
#define REG_TXB0DLC                     ( (UCHAR)0x35U )
#define REG_TXB0D0                      ( (UCHAR)0x36U )
#define REG_TXB0D1                      ( (UCHAR)0x37U )
#define REG_TXB0D2                      ( (UCHAR)0x38U )
#define REG_TXB0D3                      ( (UCHAR)0x39U )
#define REG_TXB0D4                      ( (UCHAR)0x3AU )
#define REG_TXB0D5                      ( (UCHAR)0x3BU )
#define REG_TXB0D6                      ( (UCHAR)0x3CU )
#define REG_TXB0D7                      ( (UCHAR)0x3DU )
#define REG_TXB1CTRL                    ( (UCHAR)0x40U )
#define REG_TXB1SIDH                    ( (UCHAR)0x41U )
#define REG_TXB1SIDL                    ( (UCHAR)0x42U )
#define REG_TXB1EID8                    ( (UCHAR)0x43U )
#define REG_TXB1EID0                    ( (UCHAR)0x44U )
#define REG_TXB1DLC                     ( (UCHAR)0x45U )
#define REG_TXB1D0                      ( (UCHAR)0x46U )
#define REG_TXB1D1                      ( (UCHAR)0x47U )
#define REG_TXB1D2                      ( (UCHAR)0x48U )
#define REG_TXB1D3                      ( (UCHAR)0x49U )
#define REG_TXB1D4                      ( (UCHAR)0x4AU )
#define REG_TXB1D5                      ( (UCHAR)0x4BU )
#define REG_TXB1D6                      ( (UCHAR)0x4CU )
#define REG_TXB1D7                      ( (UCHAR)0x4DU )
#define REG_TXB2CTRL                    ( (UCHAR)0x50U )
#define REG_TXB2SIDH                    ( (UCHAR)0x51U )
#define REG_TXB2SIDL                    ( (UCHAR)0x52U )
#define REG_TXB2EID8                    ( (UCHAR)0x53U )
#define REG_TXB2EID0                    ( (UCHAR)0x54U )
#define REG_TXB2DLC                     ( (UCHAR)0x55U )
#define REG_TXB2D0                      ( (UCHAR)0x56U )
#define REG_TXB2D1                      ( (UCHAR)0x57U )
#define REG_TXB2D2                      ( (UCHAR)0x58U )
#define REG_TXB2D3                      ( (UCHAR)0x59U )
#define REG_TXB2D4                      ( (UCHAR)0x5AU )
#define REG_TXB2D5                      ( (UCHAR)0x5BU )
#define REG_TXB2D6                      ( (UCHAR)0x5CU )
#define REG_TXB2D7                      ( (UCHAR)0x5DU )
#define REG_RXB0CTRL                    ( (UCHAR)0x60U )
#define REG_RXB0SIDH                    ( (UCHAR)0x61U )
#define REG_RXB0SIDL                    ( (UCHAR)0x62U )
#define REG_RXB0EID8                    ( (UCHAR)0x63U )
#define REG_RXB0EID0                    ( (UCHAR)0x64U )
#define REG_RXB0DLC                     ( (UCHAR)0x65U )
#define REG_RXB0D0                      ( (UCHAR)0x66U )
#define REG_RXB0D1                      ( (UCHAR)0x67U )
#define REG_RXB0D2                      ( (UCHAR)0x68U )
#define REG_RXB0D3                      ( (UCHAR)0x69U )
#define REG_RXB0D4                      ( (UCHAR)0x6AU )
#define REG_RXB0D5                      ( (UCHAR)0x6BU )
#define REG_RXB0D6                      ( (UCHAR)0x6CU )
#define REG_RXB0D7                      ( (UCHAR)0x6DU )
#define REG_RXB1CTRL                    ( (UCHAR)0x70U )
#define REG_RXB1SIDH                    ( (UCHAR)0x71U )
#define REG_RXB1SIDL                    ( (UCHAR)0x72U )
#define REG_RXB1EID8                    ( (UCHAR)0x73U )
#define REG_RXB1EID0                    ( (UCHAR)0x74U )
#define REG_RXB1DLC                     ( (UCHAR)0x75U )
#define REG_RXB1D0                      ( (UCHAR)0x76U )
#define REG_RXB1D1                      ( (UCHAR)0x77U )
#define REG_RXB1D2                      ( (UCHAR)0x78U )
#define REG_RXB1D3                      ( (UCHAR)0x79U )
#define REG_RXB1D4                      ( (UCHAR)0x7AU )
#define REG_RXB1D5                      ( (UCHAR)0x7BU )
#define REG_RXB1D6                      ( (UCHAR)0x7CU )
#define REG_RXB1D7                      ( (UCHAR)0x7DU )

#define MASKOF_OPMOD                    ( (UCHAR)0xE0U )
#define MASKOF_CANSTAT_ICOD             ( (UCHAR)0x0EU )
#define MASKOF_CANCTRL_ABAT             ( (UCHAR)0x10U )
#define MASKOF_CANCTRL_OSM              ( (UCHAR)0x08U )
#define MASKOF_CANINT_MERRF             ( (UCHAR)0x80U )
#define MASKOF_CANINT_WAKIF             ( (UCHAR)0x40U )
#define MASKOF_CANINT_ERRIF             ( (UCHAR)0x20U )
#define MASKOF_CANINT_TX2IF             ( (UCHAR)0x10U )
#define MASKOF_CANINT_TX1IF             ( (UCHAR)0x08U )
#define MASKOF_CANINT_TX0IF             ( (UCHAR)0x04U )
#define MASKOF_CANINT_RX1IF             ( (UCHAR)0x02U )
#define MASKOF_CANINT_RX0IF             ( (UCHAR)0x01U )
#define MASKOF_EFLG_RX1OVR              ( (UCHAR)0x80U )
#define MASKOF_EFLG_RX0OVR              ( (UCHAR)0x40U )
#define MASKOF_EFLG_TXBO                ( (UCHAR)0x20U )
#define MASKOF_EFLG_TXEP                ( (UCHAR)0x10U )
#define MASKOF_EFLG_RXEP                ( (UCHAR)0x08U )
#define MASKOF_EFLG_TXWAR               ( (UCHAR)0x04U )
#define MASKOF_EFLG_RXWAR               ( (UCHAR)0x02U )
#define MASKOF_EFLG_EWARN               ( (UCHAR)0x01U )
#define MASKOF_TXBCTRL_ABTF             ( (UCHAR)0x40U )
#define MASKOF_TXBCTRL_MLOA             ( (UCHAR)0x20U )
#define MASKOF_TXBCTRL_TXERR            ( (UCHAR)0x10U )
#define MASKOF_TXBCTRL_TXREQ            ( (UCHAR)0x08U )
#define MASKOF_TXBCTRL_TXP              ( (UCHAR)0x03U )
#define MASKOF_RXBCTRL_RXM              ( (UCHAR)0x60U )
#define MASKOF_RXBCTRL_RXRTR            ( (UCHAR)0x08U )
#define MASKOF_RXB0CTRL_BUKT            ( (UCHAR)0x04U )
#define MASKOF_RXB0CTRL_FILHIT          ( (UCHAR)0x01U )
#define MASKOF_RXB1CTRL_FILHIT          ( (UCHAR)0x07U )
#define MASKOF_SIDL_IDE                 ( (UCHAR)0x08U )
#define MASKOF_RTR                      ( (UCHAR)0x40U )
#define MASKOF_DLC                      ( (UCHAR)0x0FU )

#define OPMODE_NORMAL                   ( (UCHAR)0x00U )
#define BAUDRATE_NUMOF_ITEMS            ( (UCHAR)3U )


static const UCHAR BAUDRATE[ BAUDRATE_NUMOF_ITEMS ] = { 0x02U, 0x89U, 0x07U }; /* CNF3,CNF2,CNF1 */


static VOID write_reg( const UCHAR addr, const UCHAR val );
static UCHAR read_reg( const UCHAR addr );


drv_result_t init_mcp2515( VOID )
{
    /* Reset */
    begin_spi();
    write_spi( SPICMD_RESET );
    end_spi();
    sleep_ms(100); // 適当なwait

    /* Baudrate 125Kbps */
    begin_spi();
    write_spi( SPICMD_WRITE_REG );
    write_spi( REG_CNF3 );
    write_array_spi( BAUDRATE_NUMOF_ITEMS, BAUDRATE );
    end_spi();

    /* 受信バッファ１設定。すべて受信。RX1への切り替え禁止。 */
    write_reg( REG_RXB0CTRL, 0x60 );

    /* 受信バッファ２設定。フィルタ一致のみ受信。 */
    write_reg( REG_RXB1CTRL, 0x00 );

    /* ノーマルモード */
    begin_spi();
    write_spi( SPICMD_MODBITS_REG );
    write_spi( REG_CANCTRL );
    write_spi( MASKOF_OPMOD );
    write_spi( OPMODE_NORMAL );
    end_spi();
    sleep_ms(100); // 適当なwait

    return DRV_SUCCESS;
}


static VOID write_reg( const UCHAR addr, const UCHAR val )
{
    begin_spi();

    write_spi( SPICMD_WRITE_REG );
    write_spi( addr );
    write_spi( val );

    end_spi();
}


static UCHAR read_reg( const UCHAR addr )
{
    UCHAR val;

    begin_spi();

    write_spi( SPICMD_READ_REG );
    write_spi( addr );
    read_array_spi( sizeof( val ), &val );

    end_spi();

    return val;
}
