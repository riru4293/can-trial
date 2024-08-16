#include "private/mcp2515.h"
#include "private/rp2040.h"


#define SPICMD_WRITE_REG                ( (UINT8)0x02U )
#define SPICMD_READ_REG                 ( (UINT8)0x03U )
#define SPICMD_MODBITS_REG              ( (UINT8)0x05U )
#define SPICMD_WRITE_TX0_ID             ( (UINT8)0x40U )
#define SPICMD_WRITE_TX0_CONTENT        ( (UINT8)0x41U )
#define SPICMD_WRITE_TX1_ID             ( (UINT8)0x42U )
#define SPICMD_WRITE_TX1_CONTENT        ( (UINT8)0x43U )
#define SPICMD_WRITE_TX2_ID             ( (UINT8)0x44U )
#define SPICMD_WRITE_TX2_CONTENT        ( (UINT8)0x45U )
#define SPICMD_REQ_TX0                  ( (UINT8)0x81U )
#define SPICMD_REQ_TX1                  ( (UINT8)0x82U )
#define SPICMD_REQ_TX2                  ( (UINT8)0x83U )
#define SPICMD_READ_RX0_HDR             ( (UINT8)0x90U )
#define SPICMD_READ_RX0_BODY            ( (UINT8)0x92U )
#define SPICMD_READ_RX1_HDR             ( (UINT8)0x94U )
#define SPICMD_READ_RX1_BODY            ( (UINT8)0x96U )
#define SPICMD_READ_STAT                ( (UINT8)0xA0U )
#define SPICMD_READ_RXSTAT              ( (UINT8)0xB0U )
#define SPICMD_RESET                    ( (UINT8)0xC0U )

#define REG_RXF0SIDH                    ( (UINT8)0x00U )
#define REG_RXF0SIDL                    ( (UINT8)0x01U )
#define REG_RXF0EID8                    ( (UINT8)0x02U )
#define REG_RXF0EID0                    ( (UINT8)0x03U )
#define REG_RXF1SIDH                    ( (UINT8)0x04U )
#define REG_RXF1SIDL                    ( (UINT8)0x05U )
#define REG_RXF1EID8                    ( (UINT8)0x06U )
#define REG_RXF1EID0                    ( (UINT8)0x07U )
#define REG_RXF2SIDH                    ( (UINT8)0x08U )
#define REG_RXF2SIDL                    ( (UINT8)0x09U )
#define REG_RXF2EID8                    ( (UINT8)0x0AU )
#define REG_RXF2EID0                    ( (UINT8)0x0BU )
#define REG_BFPCTRL                     ( (UINT8)0x0CU )
#define REG_TXRTSCTRL                   ( (UINT8)0x0DU )
#define REG_CANSTAT                     ( (UINT8)0x0EU )
#define REG_CANCTRL                     ( (UINT8)0x0FU )
#define REG_RXF3SIDH                    ( (UINT8)0x10U )
#define REG_RXF3SIDL                    ( (UINT8)0x11U )
#define REG_RXF3EID8                    ( (UINT8)0x12U )
#define REG_RXF3EID0                    ( (UINT8)0x13U )
#define REG_RXF4SIDH                    ( (UINT8)0x14U )
#define REG_RXF4SIDL                    ( (UINT8)0x15U )
#define REG_RXF4EID8                    ( (UINT8)0x16U )
#define REG_RXF4EID0                    ( (UINT8)0x17U )
#define REG_RXF5SIDH                    ( (UINT8)0x18U )
#define REG_RXF5SIDL                    ( (UINT8)0x19U )
#define REG_RXF5EID8                    ( (UINT8)0x1AU )
#define REG_RXF5EID0                    ( (UINT8)0x1BU )
#define REG_TEC                         ( (UINT8)0x1CU )
#define REG_REC                         ( (UINT8)0x1DU )
#define REG_RXM0SIDH                    ( (UINT8)0x20U )
#define REG_RXM0SIDL                    ( (UINT8)0x21U )
#define REG_RXM0EID8                    ( (UINT8)0x22U )
#define REG_RXM0EID0                    ( (UINT8)0x23U )
#define REG_RXM1SIDH                    ( (UINT8)0x24U )
#define REG_RXM1SIDL                    ( (UINT8)0x25U )
#define REG_RXM1EID8                    ( (UINT8)0x26U )
#define REG_RXM1EID0                    ( (UINT8)0x27U )
#define REG_CNF3                        ( (UINT8)0x28U )
#define REG_CNF2                        ( (UINT8)0x29U )
#define REG_CNF1                        ( (UINT8)0x2AU )
#define REG_CANINTE                     ( (UINT8)0x2BU )
#define REG_CANINTF                     ( (UINT8)0x2CU )
#define REG_EFLG                        ( (UINT8)0x2DU )
#define REG_TXB0CTRL                    ( (UINT8)0x30U )
#define REG_TXB0SIDH                    ( (UINT8)0x31U )
#define REG_TXB0SIDL                    ( (UINT8)0x32U )
#define REG_TXB0EID8                    ( (UINT8)0x33U )
#define REG_TXB0EID0                    ( (UINT8)0x34U )
#define REG_TXB0DLC                     ( (UINT8)0x35U )
#define REG_TXB0D0                      ( (UINT8)0x36U )
#define REG_TXB0D1                      ( (UINT8)0x37U )
#define REG_TXB0D2                      ( (UINT8)0x38U )
#define REG_TXB0D3                      ( (UINT8)0x39U )
#define REG_TXB0D4                      ( (UINT8)0x3AU )
#define REG_TXB0D5                      ( (UINT8)0x3BU )
#define REG_TXB0D6                      ( (UINT8)0x3CU )
#define REG_TXB0D7                      ( (UINT8)0x3DU )
#define REG_TXB1CTRL                    ( (UINT8)0x40U )
#define REG_TXB1SIDH                    ( (UINT8)0x41U )
#define REG_TXB1SIDL                    ( (UINT8)0x42U )
#define REG_TXB1EID8                    ( (UINT8)0x43U )
#define REG_TXB1EID0                    ( (UINT8)0x44U )
#define REG_TXB1DLC                     ( (UINT8)0x45U )
#define REG_TXB1D0                      ( (UINT8)0x46U )
#define REG_TXB1D1                      ( (UINT8)0x47U )
#define REG_TXB1D2                      ( (UINT8)0x48U )
#define REG_TXB1D3                      ( (UINT8)0x49U )
#define REG_TXB1D4                      ( (UINT8)0x4AU )
#define REG_TXB1D5                      ( (UINT8)0x4BU )
#define REG_TXB1D6                      ( (UINT8)0x4CU )
#define REG_TXB1D7                      ( (UINT8)0x4DU )
#define REG_TXB2CTRL                    ( (UINT8)0x50U )
#define REG_TXB2SIDH                    ( (UINT8)0x51U )
#define REG_TXB2SIDL                    ( (UINT8)0x52U )
#define REG_TXB2EID8                    ( (UINT8)0x53U )
#define REG_TXB2EID0                    ( (UINT8)0x54U )
#define REG_TXB2DLC                     ( (UINT8)0x55U )
#define REG_TXB2D0                      ( (UINT8)0x56U )
#define REG_TXB2D1                      ( (UINT8)0x57U )
#define REG_TXB2D2                      ( (UINT8)0x58U )
#define REG_TXB2D3                      ( (UINT8)0x59U )
#define REG_TXB2D4                      ( (UINT8)0x5AU )
#define REG_TXB2D5                      ( (UINT8)0x5BU )
#define REG_TXB2D6                      ( (UINT8)0x5CU )
#define REG_TXB2D7                      ( (UINT8)0x5DU )
#define REG_RXB0CTRL                    ( (UINT8)0x60U )
#define REG_RXB0SIDH                    ( (UINT8)0x61U )
#define REG_RXB0SIDL                    ( (UINT8)0x62U )
#define REG_RXB0EID8                    ( (UINT8)0x63U )
#define REG_RXB0EID0                    ( (UINT8)0x64U )
#define REG_RXB0DLC                     ( (UINT8)0x65U )
#define REG_RXB0D0                      ( (UINT8)0x66U )
#define REG_RXB0D1                      ( (UINT8)0x67U )
#define REG_RXB0D2                      ( (UINT8)0x68U )
#define REG_RXB0D3                      ( (UINT8)0x69U )
#define REG_RXB0D4                      ( (UINT8)0x6AU )
#define REG_RXB0D5                      ( (UINT8)0x6BU )
#define REG_RXB0D6                      ( (UINT8)0x6CU )
#define REG_RXB0D7                      ( (UINT8)0x6DU )
#define REG_RXB1CTRL                    ( (UINT8)0x70U )
#define REG_RXB1SIDH                    ( (UINT8)0x71U )
#define REG_RXB1SIDL                    ( (UINT8)0x72U )
#define REG_RXB1EID8                    ( (UINT8)0x73U )
#define REG_RXB1EID0                    ( (UINT8)0x74U )
#define REG_RXB1DLC                     ( (UINT8)0x75U )
#define REG_RXB1D0                      ( (UINT8)0x76U )
#define REG_RXB1D1                      ( (UINT8)0x77U )
#define REG_RXB1D2                      ( (UINT8)0x78U )
#define REG_RXB1D3                      ( (UINT8)0x79U )
#define REG_RXB1D4                      ( (UINT8)0x7AU )
#define REG_RXB1D5                      ( (UINT8)0x7BU )
#define REG_RXB1D6                      ( (UINT8)0x7CU )
#define REG_RXB1D7                      ( (UINT8)0x7DU )

#define MASKOF_OPMOD                    ( (UINT8)0xE0U )
#define MASKOF_CANSTAT_ICOD             ( (UINT8)0x0EU )
#define MASKOF_CANCTRL_ABAT             ( (UINT8)0x10U )
#define MASKOF_CANCTRL_OSM              ( (UINT8)0x08U )
#define MASKOF_CANINT_MERRF             ( (UINT8)0x80U )
#define MASKOF_CANINT_WAKIF             ( (UINT8)0x40U )
#define MASKOF_CANINT_ERRIF             ( (UINT8)0x20U )
#define MASKOF_CANINT_TX2IF             ( (UINT8)0x10U )
#define MASKOF_CANINT_TX1IF             ( (UINT8)0x08U )
#define MASKOF_CANINT_TX0IF             ( (UINT8)0x04U )
#define MASKOF_CANINT_RX1IF             ( (UINT8)0x02U )
#define MASKOF_CANINT_RX0IF             ( (UINT8)0x01U )
#define MASKOF_EFLG_RX1OVR              ( (UINT8)0x80U )
#define MASKOF_EFLG_RX0OVR              ( (UINT8)0x40U )
#define MASKOF_EFLG_TXBO                ( (UINT8)0x20U )
#define MASKOF_EFLG_TXEP                ( (UINT8)0x10U )
#define MASKOF_EFLG_RXEP                ( (UINT8)0x08U )
#define MASKOF_EFLG_TXWAR               ( (UINT8)0x04U )
#define MASKOF_EFLG_RXWAR               ( (UINT8)0x02U )
#define MASKOF_EFLG_EWARN               ( (UINT8)0x01U )
#define MASKOF_TXBCTRL_ABTF             ( (UINT8)0x40U )
#define MASKOF_TXBCTRL_MLOA             ( (UINT8)0x20U )
#define MASKOF_TXBCTRL_TXERR            ( (UINT8)0x10U )
#define MASKOF_TXBCTRL_TXREQ            ( (UINT8)0x08U )
#define MASKOF_TXBCTRL_TXP              ( (UINT8)0x03U )
#define MASKOF_RXBCTRL_RXM              ( (UINT8)0x60U )
#define MASKOF_RXBCTRL_RXRTR            ( (UINT8)0x08U )
#define MASKOF_RXB0CTRL_BUKT            ( (UINT8)0x04U )
#define MASKOF_RXB0CTRL_FILHIT          ( (UINT8)0x01U )
#define MASKOF_RXB1CTRL_FILHIT          ( (UINT8)0x07U )
#define MASKOF_SIDL_IDE                 ( (UINT8)0x08U )
#define MASKOF_RTR                      ( (UINT8)0x40U )
#define MASKOF_DLC                      ( (UINT8)0x0FU )

#define OPMODE_NORMAL                   ( (UINT8)0x00U )
#define BAUDRATE_NUMOF_ITEMS            ( (UINT8)3U )


static const UINT8 BAUDRATE[ BAUDRATE_NUMOF_ITEMS ] = { 0x02U, 0x89U, 0x07U }; /* CNF3,CNF2,CNF1 */


static VOID write_reg( const UINT8 addr, const UINT8 val );
static UINT8 read_reg( const UINT8 addr );


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


    return DRV_SUCCESS;
}


static VOID write_reg( const UINT8 addr, const UINT8 val )
{
    begin_spi();

    write_spi( SPICMD_WRITE_REG );
    write_spi( addr );
    write_spi( val );

    end_spi();
}


static UINT8 read_reg( const UINT8 addr )
{
    UINT8 val;

    begin_spi();

    write_spi( SPICMD_READ_REG );
    write_spi( addr );
    read_array_spi( sizeof( val ), &val );

    end_spi();

    return val;
}


static void modify_reg( const UINT8 addr, const UINT8 mask, const UINT8 val ) {

    drv_begin_spi();

    drv_write_spi( SPICMD_MODBITS_REG );
    drv_write_spi( addr );
    drv_write_spi( mask );
    drv_write_spi( val );

    drv_end_spi();
}


VOID drv_clear_irq_occurrence( drv_irq_t irq )
{
    modify_reg( REG_CANINTF, irq, DRV_IRQ_NONE );
}


drv_irq_t drv_get_irq_occurrence()
{
    UINT8 enabled;
    UINT8 occurred;

    enabled = read_reg( REG_CANINTE );
    occurred = read_reg( REG_CANINTF );

    return (drv_irq_t)( occurred & enabled );
}


VOID drv_disable_irq_factor( drv_irq_t irq )
{
    modify_reg( REG_CANINTE, irq, DRV_IRQ_NONE );
}


VOID drv_enable_irq_factor( drv_irq_t irq )
{
    modify_reg( REG_CANINTE, irq, DRV_IRQ_ALL );
}

#ifdef DEBUG
UINT8 drvtmp_get_eflg( VOID )
{
    return read_reg( REG_EFLG );
}

VOID drvtmp_to_normal_mode( VOID )
{
    begin_spi();
    write_spi( SPICMD_MODBITS_REG );
    write_spi( REG_CANCTRL );
    write_spi( MASKOF_OPMOD );
    write_spi( OPMODE_NORMAL );
    end_spi();

    while( 0U != ( read_reg( REG_CANSTAT ) & 0xE0U ) );
}
#endif /* DEBUG */
