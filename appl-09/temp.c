#include "appl_common.h"
#include "main.h"
#include "hardware/spi.h"

#define SPI_BAUDRATE_10MHZ ( (UCHAR)10000000U ) /* 10MHz */
#define GPIO_NUM_SPI_1_MISO             ( (UCHAR) 4U )
#define GPIO_NUM_SPI_1_CS               ( (UCHAR) 5U )
#define GPIO_NUM_SPI_1_SCK              ( (UCHAR) 6U )
#define GPIO_NUM_SPI_1_MOSI             ( (UCHAR) 7U )
#define SPI_REPEATED_TX_DATA         ( (UCHAR)0U )

#define SPICMD_WRITE_REG                ( 0x02U )
#define SPICMD_READ_REG                 ( 0x03U )
#define SPICMD_MODBITS_REG              ( 0x05U )
#define SPICMD_WRITE_TX0_ID             ( 0x40U )
#define SPICMD_WRITE_TX0_CONTENT        ( 0x41U )
#define SPICMD_WRITE_TX1_ID             ( 0x42U )
#define SPICMD_WRITE_TX1_CONTENT        ( 0x43U )
#define SPICMD_WRITE_TX2_ID             ( 0x44U )
#define SPICMD_WRITE_TX2_CONTENT        ( 0x45U )
#define SPICMD_REQ_TX0                  ( 0x81U )
#define SPICMD_REQ_TX1                  ( 0x82U )
#define SPICMD_REQ_TX2                  ( 0x83U )
#define SPICMD_READ_RX0_HDR             ( 0x90U )
#define SPICMD_READ_RX0_BODY            ( 0x92U )
#define SPICMD_READ_RX1_HDR             ( 0x94U )
#define SPICMD_READ_RX1_BODY            ( 0x96U )
#define SPICMD_READ_STAT                ( 0xA0U )
#define SPICMD_READ_RXSTAT              ( 0xB0U )
#define SPICMD_RESET                    ( 0xC0U )

#define REG_RXF0SIDH                    ( 0x00U )
#define REG_RXF0SIDL                    ( 0x01U )
#define REG_RXF0EID8                    ( 0x02U )
#define REG_RXF0EID0                    ( 0x03U )
#define REG_RXF1SIDH                    ( 0x04U )
#define REG_RXF1SIDL                    ( 0x05U )
#define REG_RXF1EID8                    ( 0x06U )
#define REG_RXF1EID0                    ( 0x07U )
#define REG_RXF2SIDH                    ( 0x08U )
#define REG_RXF2SIDL                    ( 0x09U )
#define REG_RXF2EID8                    ( 0x0AU )
#define REG_RXF2EID0                    ( 0x0BU )
#define REG_BFPCTRL ( 0x0CU )
#define REG_TXRTSCTRL                   ( 0x0DU )
#define REG_CANSTAT                     ( 0x0EU )
#define REG_CANCTRL                     ( 0x0FU )
#define REG_RXF3SIDH                    ( 0x10U )
#define REG_RXF3SIDL                    ( 0x11U )
#define REG_RXF3EID8                    ( 0x12U )
#define REG_RXF3EID0                    ( 0x13U )
#define REG_RXF4SIDH                    ( 0x14U )
#define REG_RXF4SIDL                    ( 0x15U )
#define REG_RXF4EID8                    ( 0x16U )
#define REG_RXF4EID0                    ( 0x17U )
#define REG_RXF5SIDH                    ( 0x18U )
#define REG_RXF5SIDL                    ( 0x19U )
#define REG_RXF5EID8                    ( 0x1AU )
#define REG_RXF5EID0                    ( 0x1BU )
#define REG_TEC                         ( 0x1CU )
#define REG_REC                         ( 0x1DU )
#define REG_RXM0SIDH                    ( 0x20U )
#define REG_RXM0SIDL                    ( 0x21U )
#define REG_RXM0EID8                    ( 0x22U )
#define REG_RXM0EID0                    ( 0x23U )
#define REG_RXM1SIDH                    ( 0x24U )
#define REG_RXM1SIDL                    ( 0x25U )
#define REG_RXM1EID8                    ( 0x26U )
#define REG_RXM1EID0                    ( 0x27U )
#define REG_CNF3                        ( 0x28U )
#define REG_CNF2                        ( 0x29U )
#define REG_CNF1                        ( 0x2AU )
#define REG_CANINTE                     ( 0x2BU )
#define REG_CANINTF                     ( 0x2CU )
#define REG_EFLG                        ( 0x2DU )
#define REG_TXB0CTRL                    ( 0x30U )
#define REG_TXB0SIDH                    ( 0x31U )
#define REG_TXB0SIDL                    ( 0x32U )
#define REG_TXB0EID8                    ( 0x33U )
#define REG_TXB0EID0                    ( 0x34U )
#define REG_TXB0DLC                     ( 0x35U )
#define REG_TXB0D0                      ( 0x36U )
#define REG_TXB0D1                      ( 0x37U )
#define REG_TXB0D2                      ( 0x38U )
#define REG_TXB0D3                      ( 0x39U )
#define REG_TXB0D4                      ( 0x3AU )
#define REG_TXB0D5                      ( 0x3BU )
#define REG_TXB0D6                      ( 0x3CU )
#define REG_TXB0D7                      ( 0x3DU )
#define REG_TXB1CTRL                    ( 0x40U )
#define REG_TXB1SIDH                    ( 0x41U )
#define REG_TXB1SIDL                    ( 0x42U )
#define REG_TXB1EID8                    ( 0x43U )
#define REG_TXB1EID0                    ( 0x44U )
#define REG_TXB1DLC                     ( 0x45U )
#define REG_TXB1D0                      ( 0x46U )
#define REG_TXB1D1                      ( 0x47U )
#define REG_TXB1D2                      ( 0x48U )
#define REG_TXB1D3                      ( 0x49U )
#define REG_TXB1D4                      ( 0x4AU )
#define REG_TXB1D5                      ( 0x4BU )
#define REG_TXB1D6                      ( 0x4CU )
#define REG_TXB1D7                      ( 0x4DU )
#define REG_TXB2CTRL                    ( 0x50U )
#define REG_TXB2SIDH                    ( 0x51U )
#define REG_TXB2SIDL                    ( 0x52U )
#define REG_TXB2EID8                    ( 0x53U )
#define REG_TXB2EID0                    ( 0x54U )
#define REG_TXB2DLC                     ( 0x55U )
#define REG_TXB2D0                      ( 0x56U )
#define REG_TXB2D1                      ( 0x57U )
#define REG_TXB2D2                      ( 0x58U )
#define REG_TXB2D3                      ( 0x59U )
#define REG_TXB2D4                      ( 0x5AU )
#define REG_TXB2D5                      ( 0x5BU )
#define REG_TXB2D6                      ( 0x5CU )
#define REG_TXB2D7                      ( 0x5DU )
#define REG_RXB0CTRL                    ( 0x60U )
#define REG_RXB0SIDH                    ( 0x61U )
#define REG_RXB0SIDL                    ( 0x62U )
#define REG_RXB0EID8                    ( 0x63U )
#define REG_RXB0EID0                    ( 0x64U )
#define REG_RXB0DLC                     ( 0x65U )
#define REG_RXB0D0                      ( 0x66U )
#define REG_RXB0D1                      ( 0x67U )
#define REG_RXB0D2                      ( 0x68U )
#define REG_RXB0D3                      ( 0x69U )
#define REG_RXB0D4                      ( 0x6AU )
#define REG_RXB0D5                      ( 0x6BU )
#define REG_RXB0D6                      ( 0x6CU )
#define REG_RXB0D7                      ( 0x6DU )
#define REG_RXB1CTRL                    ( 0x70U )
#define REG_RXB1SIDH                    ( 0x71U )
#define REG_RXB1SIDL                    ( 0x72U )
#define REG_RXB1EID8                    ( 0x73U )
#define REG_RXB1EID0                    ( 0x74U )
#define REG_RXB1DLC                     ( 0x75U )
#define REG_RXB1D0                      ( 0x76U )
#define REG_RXB1D1                      ( 0x77U )
#define REG_RXB1D2                      ( 0x78U )
#define REG_RXB1D3                      ( 0x79U )
#define REG_RXB1D4                      ( 0x7AU )
#define REG_RXB1D5                      ( 0x7BU )
#define REG_RXB1D6                      ( 0x7CU )
#define REG_RXB1D7                      ( 0x7DU )

#define MASKOF_OPMOD                    ( 0xE0U )
#define MASKOF_CANSTAT_ICOD             ( 0x0EU )
#define MASKOF_CANCTRL_ABAT             ( 0x10U )
#define MASKOF_CANCTRL_OSM              ( 0x08U )
#define MASKOF_CANINT_MERRF             ( 0x80U )
#define MASKOF_CANINT_WAKIF             ( 0x40U )
#define MASKOF_CANINT_ERRIF             ( 0x20U )
#define MASKOF_CANINT_TX2IF             ( 0x10U )
#define MASKOF_CANINT_TX1IF             ( 0x08U )
#define MASKOF_CANINT_TX0IF             ( 0x04U )
#define MASKOF_CANINT_RX1IF             ( 0x02U )
#define MASKOF_CANINT_RX0IF             ( 0x01U )
#define MASKOF_EFLG_RX1OVR              ( 0x80U )
#define MASKOF_EFLG_RX0OVR              ( 0x40U )
#define MASKOF_EFLG_TXBO                ( 0x20U )
#define MASKOF_EFLG_TXEP                ( 0x10U )
#define MASKOF_EFLG_RXEP                ( 0x08U )
#define MASKOF_EFLG_TXWAR               ( 0x04U )
#define MASKOF_EFLG_RXWAR               ( 0x02U )
#define MASKOF_EFLG_EWARN               ( 0x01U )
#define MASKOF_TXBCTRL_ABTF             ( 0x40U )
#define MASKOF_TXBCTRL_MLOA             ( 0x20U )
#define MASKOF_TXBCTRL_TXERR            ( 0x10U )
#define MASKOF_TXBCTRL_TXREQ            ( 0x08U )
#define MASKOF_TXBCTRL_TXP              ( 0x03U )
#define MASKOF_RXBCTRL_RXM              ( 0x60U )
#define MASKOF_RXBCTRL_RXRTR            ( 0x08U )
#define MASKOF_RXB0CTRL_BUKT            ( 0x04U )
#define MASKOF_RXB0CTRL_FILHIT          ( 0x01U )
#define MASKOF_RXB1CTRL_FILHIT          ( 0x07U )
#define MASKOF_SIDL_IDE                 ( 0x08U )
#define MASKOF_RTR                      ( 0x40U )
#define MASKOF_DLC                      ( 0x0FU )

#define OPMODE_NORMAL       ( 0x00U )
#define BAUDRATE_NUMOF_ITEMS    ( 3 )

static VOID read_array_spi( const size_t n, UCHAR *buf );
static VOID write_array_spi( const size_t n, const UCHAR const *buf );
static VOID write_spi( const UCHAR val );
static VOID write_reg( const UCHAR addr, const UCHAR val );
static UCHAR read_reg( const UCHAR addr );

static const UCHAR BAUDRATE[ BAUDRATE_NUMOF_ITEMS ] = { 0x02U, 0x89U, 0x07U }; /* CNF3,CNF2,CNF1 */
static UCHAR txhdr[ 5 ] = { 0x477U >> 3U, (0x477U << 5U) & 0xE0U, 0x00U, 0x00U, 0x08U };
static UCHAR txbdy[ 8 ] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U, 0x88U };

static UCHAR tmp_buf[ 8 ] = { 0U };
static UCHAR eflg[10] = { 0U };
static UCHAR tec[10] = { 0U };
static UCHAR canstat[10] = { 0U };
static UCHAR canintf[10] = { 0U };
static UCHAR txb0ctrl[10] = { 0U };

VOID temp_exec( VOID )
{
    UCHAR i;

    /* Initialize SPI. */
    (VOID)spi_init( spi0, SPI_BAUDRATE_10MHZ );

    /* MCP2515リセット。コンフィグレーションモード */
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
    write_spi( SPICMD_RESET );
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );
    sleep_ms(100); // 適当なwait

    /* MCP2515ボーレート設定 */
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
    write_spi( SPICMD_WRITE_REG );
    write_spi( REG_CNF3 );
    write_array_spi( BAUDRATE_NUMOF_ITEMS, BAUDRATE );
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );

    /* 受信バッファ１設定。すべて受信。RX1への切り替え禁止。 */
    write_reg( REG_RXB0CTRL, 0x60 );

    /* 受信バッファ２設定。フィルタ一致のみ受信。 */
    write_reg( REG_RXB1CTRL, 0x00 );

    printf("EFLG: %x, TEC:%x, CANSTAT:%x, CANINTF:%x, TXB0CTRL:%x\n--\n",
            read_reg( REG_EFLG ), read_reg( REG_TEC ), read_reg( REG_CANSTAT )
          , read_reg( REG_CANINTF ), read_reg( REG_TXB0CTRL ));

    /* ノーマルモード */
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
    write_spi( SPICMD_MODBITS_REG );
    write_spi( REG_CANCTRL );
    write_spi( MASKOF_OPMOD );
    write_spi( OPMODE_NORMAL );
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );
    sleep_ms(100); // 適当なwait

    while(1) {
        /* Clear interruption by received. */
        write_reg( REG_CANINTF, 0x00U );

        sleep_ms(100);
    }
}

static VOID read_array_spi( const size_t n, UCHAR *buf )
{
    // gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
    (VOID)spi_read_blocking( spi0, SPI_REPEATED_TX_DATA, buf, n );
    // gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );
}

static VOID write_array_spi( const size_t n, const UCHAR const *buf )
{
    // gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
    (VOID)spi_write_blocking( spi0, buf, n );
    // gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );
}

static VOID write_spi( const UCHAR val )
{
    write_array_spi( sizeof( UCHAR ), &val );
}

static VOID write_reg( const UCHAR addr, const UCHAR val ) {
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
    write_spi( SPICMD_WRITE_REG );
    write_spi( addr );
    write_spi( val );
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );
}

static UCHAR read_reg( const UCHAR addr ) {
    UCHAR val;
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_LOW );
    write_spi( SPICMD_READ_REG );
    write_spi( addr );
    read_array_spi( sizeof( val ), &val );
    gpio_put( GPIO_NUM_SPI_1_CS, GPIO_VOLT_HIGH );
    return val;
}
