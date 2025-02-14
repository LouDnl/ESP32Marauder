#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\TFT_eSPI\\Processors\\TFT_eSPI_STM32.h"
        ////////////////////////////////////////////////////
        // TFT_eSPI driver functions for STM32 processors //
        ////////////////////////////////////////////////////

#ifndef _TFT_eSPI_STM32H_
#define _TFT_eSPI_STM32H_

// Processor ID reported by getSetup()
#define PROCESSOR_ID 0x32F

// Include processor specific header
// None

// RPi support not tested - Fast RPi not supported

// Processor specific code used by SPI bus transaction startWrite and endWrite functions
#define SET_BUS_WRITE_MODE // Not used
#define SET_BUS_READ_MODE  // Not used

// SUPPORT_TRANSACTIONS is mandatory for STM32
#if !defined (SUPPORT_TRANSACTIONS)
  #define SUPPORT_TRANSACTIONS
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the parallel bus interface chip pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#if defined(TFT_PARALLEL_8_BIT)

  // The STM32 processors can toggle pins fast, TFTs need setup and hold times
  // for writes so here twc can be extended  with delays:
  //
  //                       0 1 2 3 4 5     Extra high periods
  // TFT_WR ¯|_ _ _ _ _ _ |¯ ¯ ¯ ¯ ¯ ¯ ¯|
  //            5 4 3 2 1 0                Extra low periods
  //        xxxx=======================xxxx
  //         |<---------- twc --------->|
  //           |<- tdst ->|<-- tdht -->|
  //
  // Data is placed bit by bit on bus during period xxxx and TFT_WR driven low
  // Period xxxx depends on D0-D7 pin allocations and bit manipulation needed
  // Data stable during period ===
  // Most TFTs can be "overclocked" and run >2x faster than data sheet figures

////////////////////////////////////////////////////////////////////////////////////////
// Write strobe timing setup
////////////////////////////////////////////////////////////////////////////////////////
  #if defined (ILI9341_DRIVER) || defined (ST7796_DRIVER) // WRX twc spec is 66ns = 15.15MHz

    // Extra write pulse low time (delay for data setup)
    #if defined (STM32F2xx) || defined (STM32F4xx)
      #define WR_TWRL_0       // Tested with STM32F446 - 27.6MHz when WR_TWRH_1 defined
      //#define WR_TWRL_3     // STM32F446 - 15.6MHz when WR_TWRH_3 defined
    #elif defined (STM32F7xx)
      #define WR_TWRL_1       //Tested with STM32F767
    #else
      #define WR_TWRL_5
    #endif

    // Extra write pulse high time (data hold time, delays next write cycle start)
    #if defined (STM32F2xx) || defined (STM32F4xx)
      #define WR_TWRH_1       // Tested with STM32F446
      //#define WR_TWRL_3
    #elif defined (STM32F7xx)
      #define WR_TWRH_1       //Tested with STM32F767
    #else
      #define WR_TWRH_5
    #endif

  #elif defined (ILI9481_DRIVER) // WRX twc spec is 100ns = 10MHz

    // Extra write pulse low time (delay for data setup)
    #if defined (STM32F2xx) || defined (STM32F4xx)
      //#define WR_TWRL_0    // STM32F446 - ~30MHz when WR_TWRH_0 defined
      //#define WR_TWRL_1    // STM32F446 - ~25MHz when WR_TWRH_0 defined
      #define WR_TWRL_2      // STM32F446 - ~20MHz when WR_TWRH_2 defined
      //#define WR_TWRL_3    // STM32F446 - ~16MHz when WR_TWRH_3 defined
      //#define WR_TWRL_4
      //#define WR_TWRL_5    // STM32F446 - ~12MHz when WR_TWRH_5 defined
    #elif defined (STM32F7xx)
      //#define WR_TWRL_0
      //#define WR_TWRL_1
      //#define WR_TWRL_2
      #define WR_TWRL_3
    #else
      //#define WR_TWRH_0    // Fastest
      //#define WR_TWRH_1
      //#define WR_TWRH_2
      #define WR_TWRH_3      // Slowest
    #endif

    // Extra write pulse high time (data hold time, delays next write cycle start)
    #if defined (STM32F2xx) || defined (STM32F4xx)
      //#define WR_TWRH_0
      //#define WR_TWRH_1
      #define WR_TWRH_2
      //#define WR_TWRH_3
    #elif defined (STM32F7xx)
      //#define WR_TWRH_0
      //#define WR_TWRH_1
      //#define WR_TWRH_2
      #define WR_TWRH_3
      //#define WR_TWRH_4
      //#define WR_TWRH_5
    #else
      //#define WR_TWRH_0     // Fastest
      //#define WR_TWRH_1
      //#define WR_TWRH_2
      #define WR_TWRH_3       // Slowest
    #endif

  #else // Default display slow settings

    // Extra write pulse low time (delay for data setup)
    //#define WR_TWRL_0
    //#define WR_TWRL_1
    //#define WR_TWRL_2
    //#define WR_TWRL_3
    //#define WR_TWRL_4
    #define WR_TWRL_5

    // Extra write pulse high time (data hold time, delays next write cycle start)
    //#define WR_TWRH_0
    //#define WR_TWRH_1
    //#define WR_TWRH_2
    //#define WR_TWRH_3
    //#define WR_TWRH_4
    #define WR_TWRH_5

  #endif

////////////////////////////////////////////////////////////////////////////////////////
// Macros for all other SPI displays
////////////////////////////////////////////////////////////////////////////////////////
#else

  // Global define is _VARIANT_ARDUINO_STM32_, see board package stm32_def.h for specific variants
  #if defined (STM32F2xx) || defined (STM32F4xx) || defined (STM32F7xx)
    #define STM32_DMA // DMA is available with these processors
    // Initialise processor specific SPI and DMA instances - used by init()
    #define INIT_TFT_DATA_BUS spiHal.Instance = SPI1; \
                              dmaHal.Instance = DMA2_Stream3
    // The DMA hard-coding for SPI1 is in TFT_eSPI_STM32.c as follows:
    //     DMA_CHANNEL_3 
    //     DMA2_Stream3_IRQn and DMA2_Stream3_IRQHandler()
  #elif defined (STM32F1xx)
    // For Blue Pill and STM32F1xx processors with DMA support
    #define STM32_DMA // DMA is available with these processors
    #define INIT_TFT_DATA_BUS spiHal.Instance = SPI1; \
                              dmaHal.Instance = DMA1_Channel3
  #else
    // For STM32 processor with no implemented DMA support (yet)
    #define INIT_TFT_DATA_BUS spiHal.Instance = SPI1
  #endif

#endif

#ifdef STM32_DMA
  // Code to check if DMA is busy, used by SPI DMA + transaction + endWrite functions
  #define DMA_BUSY_CHECK { if (DMA_Enabled) while(dmaBusy()); }
#else
  #define DMA_BUSY_CHECK
#endif

// If smooth fonts are enabled the filing system may need to be loaded
#ifdef SMOOTH_FONT
  // Call up the filing system for the anti-aliased fonts                                    <<<==== TODO
  //#define FS_NO_GLOBALS
  //#include <FS.h>
#endif // end of parallel/SPI selection

////////////////////////////////////////////////////////////////////////////////////////
// Define the DC (TFT Data/Command or Register Select (RS))pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#if !defined (TFT_DC) || (TFT_DC < 0)
  #define DC_C // No macro allocated so it generates no code
  #define DC_D // No macro allocated so it generates no code
#else
  // Convert Arduino pin reference Dn or STM pin reference PXn to hardware port and mask
  #define DC_PIN_NAME digitalPinToPinName(TFT_DC)
  #define DC_PORT     get_GPIO_Port(STM_PORT(DC_PIN_NAME))
  #define DC_PIN_MASK STM_LL_GPIO_PIN(DC_PIN_NAME)
  // Use bit set reset register
  #define DC_C DC_PORT->BSRR = DC_PIN_MASK<<16
  #define DC_D DC_PORT->BSRR = DC_PIN_MASK
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the CS (TFT chip select) pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#if !defined (TFT_CS) || (TFT_CS < 0)
  #define CS_L // No macro allocated so it generates no code
  #define CS_H // No macro allocated so it generates no code
#else
  // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
  #define CS_PIN_NAME  digitalPinToPinName(TFT_CS)
  #define CS_PORT      get_GPIO_Port(STM_PORT(CS_PIN_NAME))
  #define CS_PIN_MASK  STM_LL_GPIO_PIN(CS_PIN_NAME)
  // Use bit set reset register
  #define CS_L CS_PORT->BSRR = CS_PIN_MASK<<16
  #define CS_H CS_PORT->BSRR = CS_PIN_MASK
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the RD (TFT Read) pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#ifdef TFT_RD
  // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
  #define RD_PIN_NAME  digitalPinToPinName(TFT_RD)
  #define RD_PORT      get_GPIO_Port(STM_PORT(RD_PIN_NAME))
  #define RD_PIN_MASK  STM_LL_GPIO_PIN(RD_PIN_NAME)
  // Use bit set reset register
  #define RD_L RD_PORT->BSRR = RD_PIN_MASK<<16
  #define RD_H RD_PORT->BSRR = RD_PIN_MASK
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the WR (TFT Write) pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#ifdef TFT_WR
  // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
  #define WR_PIN_NAME  digitalPinToPinName(TFT_WR)
  #define WR_PORT      get_GPIO_Port(STM_PORT(WR_PIN_NAME))
  #define WR_PIN_MASK  STM_LL_GPIO_PIN(WR_PIN_NAME)
  // Use bit set reset register
  #define WR_L WR_PORT->BSRR = WR_PIN_MASK<<16
  #ifdef ILI9341_DRIVER
    #define WR_H WR_PORT->BSRR = WR_PIN_MASK
  #else
    #define WR_H WR_PORT->BSRR = WR_PIN_MASK
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the touch screen chip select pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#if !defined (TOUCH_CS) || (TOUCH_CS < 0)
  #define T_CS_L // No macro allocated so it generates no code
  #define T_CS_H // No macro allocated so it generates no code
#else
  // Speed is not important for this signal
  #define T_CS_L digitalWrite(TOUCH_CS, LOW)
  #define T_CS_H digitalWrite(TOUCH_CS, HIGH)
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Make sure TFT_MISO is defined if not used to avoid an error message
////////////////////////////////////////////////////////////////////////////////////////
#if !defined (TFT_PARALLEL_8_BIT)
  #ifndef TFT_MISO
    #define TFT_MISO -1
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the parallel bus interface chip pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#if defined (TFT_PARALLEL_8_BIT)

  // Mask for the 8 data bits to set pin directions (not used)
  #define dir_mask 0

  #define CONSTRUCTOR_INIT_TFT_DATA_BUS // None

  #define INIT_TFT_DATA_BUS // Setup built into TFT_eSPI.cpp

////////////////////////////////////////////////////////////////////////////////////////
// Define the TFT_WR drive cycle timing
////////////////////////////////////////////////////////////////////////////////////////
  // Write low extra setup time
  #if   defined WR_TWRL_0
    #define     WR_TWRL
  #elif defined WR_TWRL_1 // 1 extra low period
    #define     WR_TWRL WR_L
  #elif defined WR_TWRL_2 // 2 extra low periods
    #define     WR_TWRL WR_L; WR_L
  #elif defined WR_TWRL_3 // 3 extra low periods
    #define     WR_TWRL WR_L; WR_L; WR_L
  #elif defined WR_TWRL_4 // 4 extra low periods
    #define     WR_TWRL WR_L; WR_L; WR_L; WR_L
  #elif defined WR_TWRL_5 // 5 extra low periods
    #define     WR_TWRL WR_L; WR_L; WR_L; WR_L; WR_L
  #endif

  // Write high extra hold time
  #if   defined WR_TWRH_0
    #define     WR_TWRH WR_H
  #elif defined WR_TWRH_1 // 1 extra high period
    #define     WR_TWRH  WR_H; WR_H
  #elif defined WR_TWRH_2 // 2 extra high periods
    #define     WR_TWRH  WR_H; WR_H; WR_H
  #elif defined WR_TWRH_3 // 3 extra high periods
    #define     WR_TWRH  WR_H; WR_H; WR_H; WR_H
  #elif defined WR_TWRH_4 // 4 extra high periods
    #define     WR_TWRH  WR_H; WR_H; WR_H; WR_H; WR_H
  #elif defined WR_TWRH_5 // 5 extra high periods
    #define     WR_TWRH  WR_H; WR_H; WR_H; WR_H; WR_H; WR_H
  #endif

  #define WR_STB WR_TWRL; WR_TWRH // Rising edge write strobe

////////////////////////////////////////////////////////////////////////////////////////
// Nucleo 64: hard-coded pins
////////////////////////////////////////////////////////////////////////////////////////
  #ifdef NUCLEO_64_TFT

    // Nucleo 64 boards use the same ports/pins
    #define D0_PIN_BIT LL_GPIO_PIN_9
    #define D1_PIN_BIT LL_GPIO_PIN_7
    #define D2_PIN_BIT LL_GPIO_PIN_10
    #define D3_PIN_BIT LL_GPIO_PIN_3
    #define D4_PIN_BIT LL_GPIO_PIN_5
    #define D5_PIN_BIT LL_GPIO_PIN_4
    #define D6_PIN_BIT LL_GPIO_PIN_10
    #define D7_PIN_BIT LL_GPIO_PIN_8

    // Ports associated with pins - better than get_GPIO_Port() which seems to be slow...
    #define D0_PIN_PORT GPIOA
    #define D1_PIN_PORT GPIOC
    #define D2_PIN_PORT GPIOA
    #define D3_PIN_PORT GPIOB
    #define D4_PIN_PORT GPIOB
    #define D5_PIN_PORT GPIOB
    #define D6_PIN_PORT GPIOB
    #define D7_PIN_PORT GPIOA

    // Pin masks for set/clear
    #define D0_PIN_MASK (1UL<< 9) // Set/clear mask for PA9
    #define D1_PIN_MASK (1UL<< 7) // Set/clear mask for PC7
    #define D2_PIN_MASK (1UL<<10) // Set/clear mask for PA10
    #define D3_PIN_MASK (1UL<< 3) // Set/clear mask for PB3
    #define D4_PIN_MASK (1UL<< 5) // Set/clear mask for PB5
    #define D5_PIN_MASK (1UL<< 4) // Set/clear mask for PB4
    #define D6_PIN_MASK (1UL<<10) // Set/clear mask for PB10
    #define D7_PIN_MASK (1UL<< 8) // Set/clear mask for PA8

    // Create bit set/reset mask based on LS byte of value B
    #define  D0_BSR_MASK(B) ((D0_PIN_MASK<<16)>>(((B)<< 4)&0x10))
    #define  D1_BSR_MASK(B) ((D1_PIN_MASK<<16)>>(((B)<< 3)&0x10))
    #define  D2_BSR_MASK(B) ((D2_PIN_MASK<<16)>>(((B)<< 2)&0x10))
    #define  D3_BSR_MASK(B) ((D3_PIN_MASK<<16)>>(((B)<< 1)&0x10))
    #define  D4_BSR_MASK(B) ((D4_PIN_MASK<<16)>>(((B)<< 0)&0x10))
    #define  D5_BSR_MASK(B) ((D5_PIN_MASK<<16)>>(((B)>> 1)&0x10))
    #define  D6_BSR_MASK(B) ((D6_PIN_MASK<<16)>>(((B)>> 2)&0x10))
    #define  D7_BSR_MASK(B) ((D7_PIN_MASK<<16)>>(((B)>> 3)&0x10))
    // Create bit set/reset mask for top byte of 16 bit value B
    #define  D8_BSR_MASK(B) ((D0_PIN_MASK<<16)>>(((B)>> 4)&0x10))
    #define  D9_BSR_MASK(B) ((D1_PIN_MASK<<16)>>(((B)>> 5)&0x10))
    #define D10_BSR_MASK(B) ((D2_PIN_MASK<<16)>>(((B)>> 6)&0x10))
    #define D11_BSR_MASK(B) ((D3_PIN_MASK<<16)>>(((B)>> 7)&0x10))
    #define D12_BSR_MASK(B) ((D4_PIN_MASK<<16)>>(((B)>> 8)&0x10))
    #define D13_BSR_MASK(B) ((D5_PIN_MASK<<16)>>(((B)>> 9)&0x10))
    #define D14_BSR_MASK(B) ((D6_PIN_MASK<<16)>>(((B)>>10)&0x10))
    #define D15_BSR_MASK(B) ((D7_PIN_MASK<<16)>>(((B)>>11)&0x10))

    // Write 8 bits to TFT
    #define tft_Write_8(C)   GPIOA->BSRR = D0_BSR_MASK(C) | D2_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOC->BSRR = D1_BSR_MASK(C); \
                             GPIOB->BSRR = D3_BSR_MASK(C) | D4_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB // Need to slow down strobe

    // Write 16 bits to TFT
    #define tft_Write_16(C)  GPIOA->BSRR = D8_BSR_MASK(C) | D10_BSR_MASK(C) | D15_BSR_MASK(C); \
                             WR_L; \
                             GPIOC->BSRR = D9_BSR_MASK(C); \
                             GPIOB->BSRR = D11_BSR_MASK(C) | D12_BSR_MASK(C) | D13_BSR_MASK(C) | D14_BSR_MASK(C); \
                             WR_STB; \
                             GPIOA->BSRR = D0_BSR_MASK(C) | D2_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOC->BSRR = D1_BSR_MASK(C); \
                             GPIOB->BSRR = D3_BSR_MASK(C) | D4_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB // Need to slow down strobe

    // 16 bit write with swapped bytes
    #define tft_Write_16S(C) GPIOA->BSRR = D0_BSR_MASK(C) | D2_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOC->BSRR = D1_BSR_MASK(C); \
                             GPIOB->BSRR = D3_BSR_MASK(C) | D4_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB; \
                             GPIOA->BSRR = D8_BSR_MASK(C) | D10_BSR_MASK(C) | D15_BSR_MASK(C); \
                             WR_L; \
                             GPIOC->BSRR = D9_BSR_MASK(C); \
                             GPIOB->BSRR = D11_BSR_MASK(C) | D12_BSR_MASK(C) | D13_BSR_MASK(C) | D14_BSR_MASK(C); \
                             WR_STB

    // Read a data bit
    #define RD_TFT_D0 (((GPIOA->IDR)&(D0_PIN_MASK))>>( 9-0)) // Read pin PA9
    #define RD_TFT_D1 (((GPIOC->IDR)&(D1_PIN_MASK))>>( 7-1)) // Read pin PC7
    #define RD_TFT_D2 (((GPIOA->IDR)&(D2_PIN_MASK))>>(10-2)) // Read pin PA10
    #define RD_TFT_D3 (((GPIOB->IDR)&(D3_PIN_MASK))>>( 3-3)) // Read pin PB3
    #define RD_TFT_D4 (((GPIOB->IDR)&(D4_PIN_MASK))>>( 5-4)) // Read pin PB5
    #define RD_TFT_D5 (((GPIOB->IDR)&(D5_PIN_MASK))<<(-4+5)) // Read pin PB4
    #define RD_TFT_D6 (((GPIOB->IDR)&(D6_PIN_MASK))>>(10-6)) // Read pin PB10
    #define RD_TFT_D7 (((GPIOA->IDR)&(D7_PIN_MASK))>>( 8-7)) // Read pin PA8

////////////////////////////////////////////////////////////////////////////////////////
// Nucleo 144: hard-coded pins
////////////////////////////////////////////////////////////////////////////////////////
  #elif defined (NUCLEO_144_TFT)

    #if !defined (STM32H7xx)
    // Nucleo 144 boards use the same ports/pins
    #define D0_PIN_BIT LL_GPIO_PIN_12
    #define D1_PIN_BIT LL_GPIO_PIN_15
    #define D2_PIN_BIT LL_GPIO_PIN_15
    #define D3_PIN_BIT LL_GPIO_PIN_13
    #define D4_PIN_BIT LL_GPIO_PIN_14
    #define D5_PIN_BIT LL_GPIO_PIN_11
    #define D6_PIN_BIT LL_GPIO_PIN_9
    #define D7_PIN_BIT LL_GPIO_PIN_13

    // Ports associated with pins - get_GPIO_Port() seems to be slow...
    #define D0_PIN_PORT GPIOF
    #define D1_PIN_PORT GPIOD
    #define D2_PIN_PORT GPIOF
    #define D3_PIN_PORT GPIOE
    #define D4_PIN_PORT GPIOF
    #define D5_PIN_PORT GPIOE
    #define D6_PIN_PORT GPIOE
    #define D7_PIN_PORT GPIOF

    // Pin masks for set/clear
    #define D0_PIN_MASK (1UL<<12) // Set/clear mask for PF12 PF3
    #define D1_PIN_MASK (1UL<<15) // Set/clear mask for PD15
    #define D2_PIN_MASK (1UL<<15) // Set/clear mask for PF15 PG14
    #define D3_PIN_MASK (1UL<<13) // Set/clear mask for PE13
    #define D4_PIN_MASK (1UL<<14) // Set/clear mask for PF14
    #define D5_PIN_MASK (1UL<<11) // Set/clear mask for PE11
    #define D6_PIN_MASK (1UL<< 9) // Set/clear mask for PE9
    #define D7_PIN_MASK (1UL<<13) // Set/clear mask for PF13 PG12

    // Create bit set/reset mask based on LS byte of value B
    #define  D0_BSR_MASK(B) ((D0_PIN_MASK<<16)>>(((B)<< 4)&0x10))
    #define  D1_BSR_MASK(B) ((D1_PIN_MASK<<16)>>(((B)<< 3)&0x10))
    #define  D2_BSR_MASK(B) ((D2_PIN_MASK<<16)>>(((B)<< 2)&0x10))
    #define  D3_BSR_MASK(B) ((D3_PIN_MASK<<16)>>(((B)<< 1)&0x10))
    #define  D4_BSR_MASK(B) ((D4_PIN_MASK<<16)>>(((B)<< 0)&0x10))
    #define  D5_BSR_MASK(B) ((D5_PIN_MASK<<16)>>(((B)>> 1)&0x10))
    #define  D6_BSR_MASK(B) ((D6_PIN_MASK<<16)>>(((B)>> 2)&0x10))
    #define  D7_BSR_MASK(B) ((D7_PIN_MASK<<16)>>(((B)>> 3)&0x10))
    // Create bit set/reset mask for top byte of 16 bit value B
    #define  D8_BSR_MASK(B) ((D0_PIN_MASK<<16)>>(((B)>> 4)&0x10))
    #define  D9_BSR_MASK(B) ((D1_PIN_MASK<<16)>>(((B)>> 5)&0x10))
    #define D10_BSR_MASK(B) ((D2_PIN_MASK<<16)>>(((B)>> 6)&0x10))
    #define D11_BSR_MASK(B) ((D3_PIN_MASK<<16)>>(((B)>> 7)&0x10))
    #define D12_BSR_MASK(B) ((D4_PIN_MASK<<16)>>(((B)>> 8)&0x10))
    #define D13_BSR_MASK(B) ((D5_PIN_MASK<<16)>>(((B)>> 9)&0x10))
    #define D14_BSR_MASK(B) ((D6_PIN_MASK<<16)>>(((B)>>10)&0x10))
    #define D15_BSR_MASK(B) ((D7_PIN_MASK<<16)>>(((B)>>11)&0x10))


    // Write 8 bits to TFT
    #define tft_Write_8(C)   GPIOF->BSRR = D0_BSR_MASK(C) | D2_BSR_MASK(C) | D4_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D1_BSR_MASK(C); \
                             GPIOE->BSRR = D3_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB

    // Write 16 bits to TFT
    #define tft_Write_16(C)  GPIOF->BSRR = D8_BSR_MASK(C) | D10_BSR_MASK(C) | D12_BSR_MASK(C) | D15_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D9_BSR_MASK(C); \
                             GPIOE->BSRR = D11_BSR_MASK(C) | D13_BSR_MASK(C) | D14_BSR_MASK(C); \
                             WR_STB;\
                             GPIOF->BSRR = D0_BSR_MASK(C) | D2_BSR_MASK(C) | D4_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D1_BSR_MASK(C); \
                             GPIOE->BSRR = D3_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB

    // 16 bit write with swapped bytes
    #define tft_Write_16S(C) GPIOF->BSRR = D0_BSR_MASK(C) | D2_BSR_MASK(C) | D4_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D1_BSR_MASK(C); \
                             GPIOE->BSRR = D3_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB; \
                             GPIOF->BSRR = D8_BSR_MASK(C) | D10_BSR_MASK(C) | D12_BSR_MASK(C) | D15_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D9_BSR_MASK(C); \
                             GPIOE->BSRR = D11_BSR_MASK(C) | D13_BSR_MASK(C) | D14_BSR_MASK(C); \
                             WR_STB

    // Read a data bit
    #define RD_TFT_D0 (((GPIOF->IDR)&(D0_PIN_MASK))>>(12-0)) // Read pin PF12
    #define RD_TFT_D1 (((GPIOD->IDR)&(D1_PIN_MASK))>>(15-1)) // Read pin PD15
    #define RD_TFT_D2 (((GPIOF->IDR)&(D2_PIN_MASK))>>(15-2)) // Read pin PF15
    #define RD_TFT_D3 (((GPIOE->IDR)&(D3_PIN_MASK))>>(13-3)) // Read pin PE13
    #define RD_TFT_D4 (((GPIOF->IDR)&(D4_PIN_MASK))>>(14-4)) // Read pin PF14
    #define RD_TFT_D5 (((GPIOE->IDR)&(D5_PIN_MASK))>>(11-5)) // Read pin PE11
    #define RD_TFT_D6 (((GPIOE->IDR)&(D6_PIN_MASK))>>( 9-6)) // Read pin PE9
    #define RD_TFT_D7 (((GPIOF->IDR)&(D7_PIN_MASK))>>(13-7)) // Read pin PF13

    #else

    // Test setup for STM32H743 - starts to run, slow and then crashes! Board support bug?

    // Nucleo 144 boards use the same ports/pins
    #define D0_PIN_BIT LL_GPIO_PIN_3
    #define D1_PIN_BIT LL_GPIO_PIN_15
    #define D2_PIN_BIT LL_GPIO_PIN_14
    #define D3_PIN_BIT LL_GPIO_PIN_13
    #define D4_PIN_BIT LL_GPIO_PIN_14
    #define D5_PIN_BIT LL_GPIO_PIN_11
    #define D6_PIN_BIT LL_GPIO_PIN_9
    #define D7_PIN_BIT LL_GPIO_PIN_12

    // Ports associated with pins - get_GPIO_Port() seems to be slow...
    #define D0_PIN_PORT GPIOF
    #define D1_PIN_PORT GPIOD
    #define D2_PIN_PORT GPIOG
    #define D3_PIN_PORT GPIOE
    #define D4_PIN_PORT GPIOE
    #define D5_PIN_PORT GPIOE
    #define D6_PIN_PORT GPIOE
    #define D7_PIN_PORT GPIOG

    // Pin masks for set/clear
    #define D0_PIN_MASK (1UL<< 3) // Set/clear mask for PF3
    #define D1_PIN_MASK (1UL<<15) // Set/clear mask for PD15
    #define D2_PIN_MASK (1UL<<14) // Set/clear mask for PG14
    #define D3_PIN_MASK (1UL<<13) // Set/clear mask for PE13
    #define D4_PIN_MASK (1UL<<14) // Set/clear mask for PE14
    #define D5_PIN_MASK (1UL<<11) // Set/clear mask for PE11
    #define D6_PIN_MASK (1UL<< 9) // Set/clear mask for PE9
    #define D7_PIN_MASK (1UL<<12) // Set/clear mask for PG12

    // Create bit set/reset mask based on LS byte of value B
    #define  D0_BSR_MASK(B) ((D0_PIN_MASK<<16)>>(((B)<< 4)&0x10))
    #define  D1_BSR_MASK(B) ((D1_PIN_MASK<<16)>>(((B)<< 3)&0x10))
    #define  D2_BSR_MASK(B) ((D2_PIN_MASK<<16)>>(((B)<< 2)&0x10))
    #define  D3_BSR_MASK(B) ((D3_PIN_MASK<<16)>>(((B)<< 1)&0x10))
    #define  D4_BSR_MASK(B) ((D4_PIN_MASK<<16)>>(((B)<< 0)&0x10))
    #define  D5_BSR_MASK(B) ((D5_PIN_MASK<<16)>>(((B)>> 1)&0x10))
    #define  D6_BSR_MASK(B) ((D6_PIN_MASK<<16)>>(((B)>> 2)&0x10))
    #define  D7_BSR_MASK(B) ((D7_PIN_MASK<<16)>>(((B)>> 3)&0x10))
    // Create bit set/reset mask for top byte of 16 bit value B
    #define  D8_BSR_MASK(B) ((D0_PIN_MASK<<16)>>(((B)>> 4)&0x10))
    #define  D9_BSR_MASK(B) ((D1_PIN_MASK<<16)>>(((B)>> 5)&0x10))
    #define D10_BSR_MASK(B) ((D2_PIN_MASK<<16)>>(((B)>> 6)&0x10))
    #define D11_BSR_MASK(B) ((D3_PIN_MASK<<16)>>(((B)>> 7)&0x10))
    #define D12_BSR_MASK(B) ((D4_PIN_MASK<<16)>>(((B)>> 8)&0x10))
    #define D13_BSR_MASK(B) ((D5_PIN_MASK<<16)>>(((B)>> 9)&0x10))
    #define D14_BSR_MASK(B) ((D6_PIN_MASK<<16)>>(((B)>>10)&0x10))
    #define D15_BSR_MASK(B) ((D7_PIN_MASK<<16)>>(((B)>>11)&0x10))


    // Write 8 bits to TFT
    #define tft_Write_8(C)   GPIOF->BSRR = D0_BSR_MASK(C); \
                             GPIOG->BSRR = D2_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D1_BSR_MASK(C); \
                             GPIOE->BSRR = D3_BSR_MASK(C) | D4_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB

    // Write 16 bits to TFT
    #define tft_Write_16(C)  GPIOF->BSRR = D8_BSR_MASK(C); \
                             GPIOG->BSRR = D10_BSR_MASK(C) | D15_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D9_BSR_MASK(C); \
                             GPIOE->BSRR = D11_BSR_MASK(C) | D12_BSR_MASK(C) | D13_BSR_MASK(C) | D14_BSR_MASK(C); \
                             WR_STB;\
                             GPIOF->BSRR = D0_BSR_MASK(C); \
                             GPIOG->BSRR = D2_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D1_BSR_MASK(C); \
                             GPIOE->BSRR = D3_BSR_MASK(C) | D4_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB

    // 16 bit write with swapped bytes
    #define tft_Write_16S(C) GPIOF->BSRR = D0_BSR_MASK(C); \
                             GPIOG->BSRR = D2_BSR_MASK(C) | D7_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D1_BSR_MASK(C); \
                             GPIOE->BSRR = D3_BSR_MASK(C) | D4_BSR_MASK(C) | D5_BSR_MASK(C) | D6_BSR_MASK(C); \
                             WR_STB; \
                             GPIOF->BSRR = D8_BSR_MASK(C); \
                             GPIOG->BSRR = D10_BSR_MASK(C) | D15_BSR_MASK(C); \
                             WR_L; \
                             GPIOD->BSRR = D9_BSR_MASK(C); \
                             GPIOE->BSRR = D11_BSR_MASK(C) | D12_BSR_MASK(C) | D13_BSR_MASK(C) | D14_BSR_MASK(C); \
                             WR_STB

    // Read a data bit
    #define RD_TFT_D0 (((GPIOF->IDR)&(D0_PIN_MASK))>>( 3-0)) // Read pin PF3
    #define RD_TFT_D1 (((GPIOD->IDR)&(D1_PIN_MASK))>>(15-1)) // Read pin PD15
    #define RD_TFT_D2 (((GPIOG->IDR)&(D2_PIN_MASK))>>(14-2)) // Read pin PG14
    #define RD_TFT_D3 (((GPIOE->IDR)&(D3_PIN_MASK))>>(13-3)) // Read pin PE13
    #define RD_TFT_D4 (((GPIOE->IDR)&(D4_PIN_MASK))>>(14-4)) // Read pin PE14
    #define RD_TFT_D5 (((GPIOE->IDR)&(D5_PIN_MASK))>>(11-5)) // Read pin PE11
    #define RD_TFT_D6 (((GPIOE->IDR)&(D6_PIN_MASK))>>( 9-6)) // Read pin PE9
    #define RD_TFT_D7 (((GPIOG->IDR)&(D7_PIN_MASK))>>(12-7)) // Read pin PG12
    #endif
////////////////////////////////////////////////////////////////////////////////////////
// Support for other STM32 boards (not optimised!)
////////////////////////////////////////////////////////////////////////////////////////
  #else

    // This will work with any STM32 to parallel TFT pin mapping but will be slower

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D0_PIN_NAME  digitalPinToPinName(TFT_D0)
    #ifndef D0_PORT
      #define D0_PORT    get_GPIO_Port(STM_PORT(D0_PIN_NAME))
    #endif
    #define D0_PIN_MASK  (const uint16_t)STM_LL_GPIO_PIN(D0_PIN_NAME)<<16
    // Use bit set reset register
    #define D0_BSR(B) D0_PORT->BSRR = (D0_PIN_MASK)>>(B)

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D1_PIN_NAME  digitalPinToPinName(TFT_D1)
    #ifndef D1_PORT
      #define D1_PORT    get_GPIO_Port(STM_PORT(D1_PIN_NAME))
    #endif
    #define D1_PIN_MASK  STM_LL_GPIO_PIN(D1_PIN_NAME)<<16
    // Use bit set reset register
    #define D1_BSR(B) D1_PORT->BSRR = D1_PIN_MASK>>(B)

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D2_PIN_NAME  digitalPinToPinName(TFT_D2)
    #ifndef D2_PORT
      #define D2_PORT      get_GPIO_Port(STM_PORT(D2_PIN_NAME))
    #endif
    #define D2_PIN_MASK  (const uint16_t)STM_LL_GPIO_PIN(D2_PIN_NAME)<<16
    // Use bit set reset register
    #define D2_BSR(B) D2_PORT->BSRR = D2_PIN_MASK>>(B)

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D3_PIN_NAME  digitalPinToPinName(TFT_D3)
    #ifndef D3_PORT
      #define D3_PORT      get_GPIO_Port(STM_PORT(D3_PIN_NAME))
    #endif
    #define D3_PIN_MASK  (const uint16_t)STM_LL_GPIO_PIN(D3_PIN_NAME)<<16
    // Use bit set reset register
    #define D3_BSR(B) D3_PORT->BSRR = D3_PIN_MASK>>(B)

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D4_PIN_NAME  digitalPinToPinName(TFT_D4)
    #ifndef D4_PORT
      #define D4_PORT      get_GPIO_Port(STM_PORT(D4_PIN_NAME))
    #endif
    #define D4_PIN_MASK  (const uint16_t)STM_LL_GPIO_PIN(D4_PIN_NAME)<<16
    // Use bit set reset register
    #define D4_BSR(B) D4_PORT->BSRR = D4_PIN_MASK>>(B)

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D5_PIN_NAME  digitalPinToPinName(TFT_D5)
    #ifndef D5_PORT
      #define D5_PORT      get_GPIO_Port(STM_PORT(D5_PIN_NAME))
    #endif
    #define D5_PIN_MASK  (const uint16_t)STM_LL_GPIO_PIN(D5_PIN_NAME)<<16
    // Use bit set reset register
    #define D5_BSR(B) D5_PORT->BSRR = D5_PIN_MASK>>(B)

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D6_PIN_NAME  digitalPinToPinName(TFT_D6)
    #ifndef D6_PORT
      #define D6_PORT      get_GPIO_Port(STM_PORT(D6_PIN_NAME))
    #endif
    #define D6_PIN_MASK  (const uint16_t)STM_LL_GPIO_PIN(D6_PIN_NAME)<<16
    // Use bit set reset register
    #define D6_BSR(B) D6_PORT->BSRR = D6_PIN_MASK>>(B)

    // Convert Arduino pin reference Dx or STM pin reference PXn to hardware port and mask
    #define D7_PIN_NAME  digitalPinToPinName(TFT_D7)
    #ifndef D7_PORT
      #define D7_PORT      get_GPIO_Port(STM_PORT(D7_PIN_NAME))
    #endif
    #define D7_PIN_MASK  (const uint16_t)STM_LL_GPIO_PIN(D7_PIN_NAME)<<16
    // Use bit set reset register
    #define D7_BSR(B) D7_PORT->BSRR = D7_PIN_MASK>>(B)

    // Write 8 bits to TFT for any Nucleo
    #define tft_Write_8(C) D7_BSR(((C)>>3)&0x10); D6_BSR(((C)>>2)&0x10); \
                           D5_BSR(((C)>>1)&0x10); D4_BSR(((C)>>0)&0x10); \
                           WR_L; \
                           D3_BSR(((C)<<1)&0x10); D2_BSR(((C)<<2)&0x10); \
                           D1_BSR(((C)<<3)&0x10); D0_BSR(((C)<<4)&0x10); \
                           WR_H

    // Write 16 bits to TFT
    #define tft_Write_16(C) tft_Write_8((C)>>8); tft_Write_8(C)

    // 16 bit write with swapped bytes
    #define tft_Write_16S(C) tft_Write_8(C); tft_Write_8((C)>>8)

  #endif // End of parallel/Nucleo 64/144 selections

    // Write 32 bits to TFT
    #define tft_Write_32(C) tft_Write_16((C)>>16); tft_Write_16(C)

    // Write two concatenated 16 bit values to TFT
    #define tft_Write_32C(C,D) tft_Write_16(C); tft_Write_16(D)

    // Write 16 bit value twice to TFT
    #define tft_Write_32D(C) tft_Write_16(C); tft_Write_16(C)

////////////////////////////////////////////////////////////////////////////////////////
// Macros to write commands/pixel colour data to a SPI ILI9488 TFT
////////////////////////////////////////////////////////////////////////////////////////
#elif  defined (ILI9488_DRIVER) // 16 bit colour converted to 3 bytes for 18 bit RGB

  // Write 8 bits to TFT
  #define tft_Write_8(C) \
  { spiBuffer[0] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 1, 10); }

  // Convert 16 bit colour to 18 bit and write in 3 bytes
  #define tft_Write_16(C) \
  { spiBuffer[0] = ((C) & 0xF800)>>8; spiBuffer[1] = ((C) & 0x07E0)>>3; spiBuffer[2] = ((C) & 0x001F)<<3; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 3, 10); }

  // Convert swapped byte 16 bit colour to 18 bit and write in 3 bytes
  #define tft_Write_16S(C) \
  { spiBuffer[0] = (C) & 0xF8; spiBuffer[1] = ((C) & 0xE000)>>11 | ((C) & 0x07)<<5; spiBuffer[2] = ((C) & 0x1F00)>>5; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 3, 10); }

  // Write 32 bits to TFT
  #define tft_Write_32(C) \
  { spiBuffer[0] = (C)>>24; spiBuffer[1] = (C)>>16; spiBuffer[2] = (C)>>8; spiBuffer[3] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 4, 10); }

  // Write two address coordinates
  #define tft_Write_32C(C,D) \
  { spiBuffer[0] = (C)>>8; spiBuffer[1] = C; spiBuffer[2] = (D)>>8; spiBuffer[3] = D; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 4, 10); }

  // Write same value twice
  #define tft_Write_32D(C) \
  { spiBuffer[0] = spiBuffer[2] = (C)>>8; spiBuffer[1] = spiBuffer[3] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 4, 10); }

////////////////////////////////////////////////////////////////////////////////////////
// Macros to write commands/pixel colour data to a SPI Raspberry Pi TFT
////////////////////////////////////////////////////////////////////////////////////////
#elif  defined (RPI_DISPLAY_TYPE)

  #define tft_Write_8(C) \
  { spiBuffer[0] = 0; spiBuffer[1] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 2, 10); }

  #define tft_Write_16(C) \
  { spiBuffer[0] = (C)>>8; spiBuffer[1] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 2, 10); }

  #define tft_Write_16S(C) \
  { spiBuffer[0] = C; spiBuffer[1] = (C)>>8; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 2, 10); }

  #define tft_Write_32(C) \
  { spiBuffer[1] = ((C)>>24); spiBuffer[3] = ((C)>>16); spiBuffer[5] = ((C)>>8); spiBuffer[7] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 8, 10); }

  #define tft_Write_32C(C,D) \
  { spiBuffer[1] = ((C)>>8); spiBuffer[3] = (C); spiBuffer[5] = ((D)>>8); spiBuffer[7] = D; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 8, 10); }

  #define tft_Write_32D(C) \
  { spiBuffer[1] = ((C)>>8); spiBuffer[3] = (C); spiBuffer[5] = ((C)>>8); spiBuffer[7] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 8, 10); }

////////////////////////////////////////////////////////////////////////////////////////
// Macros for all other SPI displays
////////////////////////////////////////////////////////////////////////////////////////
#else

  #define tft_Write_8(C) \
  { spiBuffer[0] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 1, 10); }

  #define tft_Write_16(C) \
  { spiBuffer[0] = (C)>>8; spiBuffer[1] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 2, 10); }

  #define tft_Write_16S(C) \
  { spiBuffer[0] = C; spiBuffer[1] = (C)>>8; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 2, 10); }

  #define tft_Write_32(C) \
  { spiBuffer[0] = (C)>>24; spiBuffer[1] = (C)>>16; spiBuffer[2] = (C)>>8; spiBuffer[3] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 4, 10); }

  #define tft_Write_32C(C,D) \
  { spiBuffer[0] = (C)>>8; spiBuffer[1] = C; spiBuffer[2] = (D)>>8; spiBuffer[3] = D; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 4, 10); }

  #define tft_Write_32D(C) \
  { spiBuffer[0] = spiBuffer[2] = (C)>>8; spiBuffer[1] = spiBuffer[3] = C; \
  HAL_SPI_Transmit(&spiHal, spiBuffer, 4, 10); }

#endif

////////////////////////////////////////////////////////////////////////////////////////
// Macros to read from display using SPI or software SPI
////////////////////////////////////////////////////////////////////////////////////////
#if defined (TFT_SDA_READ)
  // Macros to support a bit banged function call for STM32 and bi-directional SDA pin
  #define TFT_eSPI_ENABLE_8_BIT_READ // Enable tft_Read_8();
  #define SCLK_L digitalWrite(TFT_SCLK, LOW)
  #define SCLK_H digitalWrite(TFT_SCLK, HIGH)
#elif !defined (TFT_PARALLEL_8_BIT)
  // Use a SPI read transfer
  #define tft_Read_8() spi.transfer(0)
#endif

#endif // Header end
