#include "msp.h"
#include "I2C.h"
#include "readInputs.h"
#include "pinsInint.h"

#define RTC_SLAVE_ADDRESS 0x68
#define EEPROM_SLAVE_ADDRESS 0b1010111

uint8_t RTC_RecieveBuf;
uint8_t EEPROM_Recievebuf;
port2GPIO_t s_TimeButton;

void vMain_InitliePerfs(void);
void vMain_SetTimeRTC(void);
void vMain_ReadTimeRTC(void);
void vMain_StoreRTCTime(void);

uint8_t test = 10;

void main(void)
{
    vMain_InitliePerfs();
    vMain_SetTimeRTC();
	while(1)
	{
	    if(!xReadInputs_read(s_TimeButton))
	    {
	        vMain_StoreRTCTime();
	    }
	    xI2C_Read(EEPROM_SLAVE_ADDRESS, 0, &EEPROM_Recievebuf);
	    printf("%x\n", EEPROM_Recievebuf);
	}
}

void vMain_InitliePerfs(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    vI2C_Initlize(); // Initlize I2C
    vpinsInit_GPIO(&s_TimeButton, pin4, input, pullup, disableInterrupt);
}

void vMain_SetTimeRTC(void)
{
    xI2C_Write(RTC_SLAVE_ADDRESS, MONTH_ADDRESS, 0x11);
    xI2C_Write(RTC_SLAVE_ADDRESS, DAYS_ADDRESS, 0x11);
    xI2C_Write(RTC_SLAVE_ADDRESS, HOURS_ADDRESS, 0x03);
    xI2C_Write(RTC_SLAVE_ADDRESS, MINUETS_ADDRESS, 0x30);
    xI2C_Write(RTC_SLAVE_ADDRESS, SECONDS_ADDRESS, 0x00);
}

void vMain_StoreRTCTime(void)
{
    xI2C_Read(RTC_SLAVE_ADDRESS, MONTH_ADDRESS, &RTC_RecieveBuf);
    xI2C_Write(EEPROM_SLAVE_ADDRESS, 0, 0x11);
//    xI2C_Read(RTC_SLAVE_ADDRESS, DAYS_ADDRESS, &RTC_RecieveBuf);
//    xI2C_Write(EEPROM_SLAVE_ADDRESS, 1, RTC_RecieveBuf);
//    xI2C_Read(RTC_SLAVE_ADDRESS, HOURS_ADDRESS, &RTC_RecieveBuf);
//    xI2C_Write(EEPROM_SLAVE_ADDRESS, 2, RTC_RecieveBuf);
//    xI2C_Read(RTC_SLAVE_ADDRESS, SECONDS_ADDRESS, &RTC_RecieveBuf);
//    xI2C_Write(EEPROM_SLAVE_ADDRESS, 3, RTC_RecieveBuf);
//    xI2C_Read(RTC_SLAVE_ADDRESS, MINUETS_ADDRESS, &RTC_RecieveBuf);
//    xI2C_Write(EEPROM_SLAVE_ADDRESS, 4, RTC_RecieveBuf);
}
