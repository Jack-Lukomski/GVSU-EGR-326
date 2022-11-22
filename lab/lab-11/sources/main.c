#include "msp.h"
#include "I2C.h"
#include "readInputs.h"
#include "pinsInint.h"

#define RTC_SLAVE_ADDRESS 0x68
#define EEPROM_SLAVE_ADDRESS 0b1010111

uint8_t emptyByte[8] = {0, 0, 0, 0, 0, 0, 0, 0};

uint8_t RTC_RecieveBuf;
uint8_t EEPROM_Recievebuf[5];
uint8_t EEPROM_TxBus[5];
uint16_t EEPROM_MemoryAddress = 0;
uint16_t EEPROM_ReadAddress = 0;

port2GPIO_t s_StoreTimeButton;
port2GPIO_t s_PrintTimeButton;

void vMain_InitliePerfs(void);
void vMain_SetTimeRTC(void);
void vMain_ReadTimeRTC(void);
void vMain_StoreRTCTime(void);
void vMain_printTime(void);
void vMain_EraseEEPROM(void);
void vMain_InitOnBoardButton(void);

void main(void)
{
    vMain_InitliePerfs();
    vMain_SetTimeRTC();
	while(1)
	{
	    if(xReadInputs_ReadPin(s_StoreTimeButton))
	    {
	        vMain_StoreRTCTime();
	    }

	    if(xReadInputs_ReadPin(s_PrintTimeButton))
	    {
	        vMain_printTime();
	    }

	    if(!(P1->IN & BIT(1)))
	    {
	        vMain_EraseEEPROM();
	    }
	}
}

void vMain_InitliePerfs(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    vI2C_Initlize(); // Initlize I2C
    vpinsInit_GPIO(&s_StoreTimeButton, pin4, input, pullup, disableInterrupt);
    vpinsInit_GPIO(&s_PrintTimeButton, pin6, input, pullup, disableInterrupt);
    vMain_InitOnBoardButton();
}

void vMain_SetTimeRTC(void)
{
    xI2C_Write(RTC_SLAVE_ADDRESS, MONTH_ADDRESS, 0x12);
    xI2C_Write(RTC_SLAVE_ADDRESS, DAYS_ADDRESS, 0x22);
    xI2C_Write(RTC_SLAVE_ADDRESS, HOURS_ADDRESS, 0x03);
    xI2C_Write(RTC_SLAVE_ADDRESS, MINUETS_ADDRESS, 0x40);
    xI2C_Write(RTC_SLAVE_ADDRESS, SECONDS_ADDRESS, 0x01);
}

void vMain_StoreRTCTime(void)
{
    uint8_t writeBusCount;

//    xI2C_WriteBurst(EEPROM_SLAVE_ADDRESS, EEPROM_MemoryAddress, 15, emptyByte);
//    printf("Cleared Current Memory Address..\n");

    xI2C_Read(RTC_SLAVE_ADDRESS, MONTH_ADDRESS, &RTC_RecieveBuf);
    EEPROM_TxBus[0] = RTC_RecieveBuf;
    xI2C_Read(RTC_SLAVE_ADDRESS, DAYS_ADDRESS, &RTC_RecieveBuf);
    EEPROM_TxBus[1] = RTC_RecieveBuf;
    xI2C_Read(RTC_SLAVE_ADDRESS, HOURS_ADDRESS, &RTC_RecieveBuf);
    EEPROM_TxBus[2] = RTC_RecieveBuf;
    xI2C_Read(RTC_SLAVE_ADDRESS, MINUETS_ADDRESS, &RTC_RecieveBuf);
    EEPROM_TxBus[3] = RTC_RecieveBuf;
    xI2C_Read(RTC_SLAVE_ADDRESS, SECONDS_ADDRESS, &RTC_RecieveBuf);
    EEPROM_TxBus[4] = RTC_RecieveBuf;

    printf("Writing ");

    for(writeBusCount = 0; writeBusCount < 5; writeBusCount++)
    {
        printf("%x:", EEPROM_TxBus[writeBusCount]);
    }

    printf(" to EEPROM memory address %d\n", EEPROM_MemoryAddress);

    xI2C_WriteBurst(EEPROM_SLAVE_ADDRESS, EEPROM_MemoryAddress, 5, EEPROM_TxBus);

    EEPROM_MemoryAddress += 5;

    if(EEPROM_MemoryAddress > 25)
    {
        EEPROM_MemoryAddress = 0;
    }
}

void vMain_printTime(void)
{
    uint8_t RecieveBufCount;

    xI2C_Readburst(EEPROM_SLAVE_ADDRESS | 1, EEPROM_ReadAddress, 5, EEPROM_Recievebuf);

    printf("Reading I2C from Memory Address %d:\n", EEPROM_ReadAddress);

    EEPROM_ReadAddress += 5;

    if(EEPROM_ReadAddress > 25)
    {
        EEPROM_ReadAddress = 0;
    }

    for(RecieveBufCount = 0; RecieveBufCount < 5; RecieveBufCount++)
    {
        printf("%x:", EEPROM_Recievebuf[RecieveBufCount]);
    }
    printf("\n");
}

void vMain_EraseEEPROM(void)
{
    uint8_t currEEPROM_MemAddress;

    printf("Erasing all EEPROM Memory\n");

    for(currEEPROM_MemAddress = 0; currEEPROM_MemAddress < 25; currEEPROM_MemAddress+=5)
    {
        xI2C_WriteBurst(EEPROM_SLAVE_ADDRESS, currEEPROM_MemAddress, 16, emptyByte);
    }
}

void vMain_InitOnBoardButton(void)
{
    P1->SEL0 &= ~BIT(1);
    P1->SEL1 &= ~BIT(1);
    P1->DIR &= ~BIT(1);
    P1->REN |= BIT(1);
    P1->OUT |= BIT(1);
}
