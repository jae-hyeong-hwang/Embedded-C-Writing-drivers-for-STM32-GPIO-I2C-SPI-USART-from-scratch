//HSI measurement
#include<stdint.h>

#define RCC_BASE_ADDR   0x40023800UL
#define RCC_CFGR_REG_OFFSET    0x08UL
#define RCC_CFGR_REG_ADDR   (RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)

int main(void)
{

  uint32_t *pRccCfgrReg = (uint32_t*) RCC_CFGR_REG_ADDR;

  //1. configure the RCC_CFGR register MCO1 bit fields to select HSI as clock source
  *pRccCfgrReg &= ~(0x3 << 21); //clear 21 and 22  bit positions

  //2. configure PA8 to AF0 mode to behave as MCO1 signal

  // )a enable the peripheral clock for GPIOA peripheral

  uint32_t *pRCCAhb1Enr = (uint32_t*)(RCC_BASE_ADDR + 0x30); // can get the address by adding the offset 0x30 to the RCCbase address
  *pRCCAhb1Enr |= ( 1<<0); // enable GPIOA peripheral clock

  // b) configure the mode of GPIOA pin8 as alternate function mode
  uint32_t *pGPIOAModeReg = (int32_t*)(GPIOA_BASE_ADDR + 00);//access the GPIO mode register from the GPIO register sets
  *pGPIOAModeReg &= ~(0x3 << 16); //clear
  *pGPIOAModeReg |= (0x2 << 16); //set

  //c) configure the alternation function register to set the mode 0 for PA8
  uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
  *pGPIOAAltFunHighReg &= ~(0xf << 0);


  for(;;);
}
