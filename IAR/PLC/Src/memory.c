#include "memory.h"
#include "fmc.h"

void SDRAM_free(void){
 uint32_t i;
   for(i = 0;i < IS42int16_t160G_SIZE/2; i++){
     my_array_in_SDRAM[i] = 0x0000;
//     while(my_array_in_SDRAM[i] != 0x0000)my_array_in_SDRAM[i] = 0x0000;
   }
   
}  

void NAND_free(void){
 uint32_t i; 
 my_array_in_NAND[0] = 0xFF;
 for(i = 0; i < NAND_512_SIZE; i++){
     my_array_in_NAND[0] = 0xFF;
     my_array_in_NAND[i];
 }
}

void NAND_readId(void)
{
	NAND_IDTypeDef NAND_ID;
	char buf[100];

	if (HAL_NAND_Read_ID(&hnand1, &NAND_ID) == HAL_OK)
	{
          
		sprintf(buf, "Nand Flash ID = %02X,%02X,%02X,%02X\n",NAND_ID.Maker_Id, NAND_ID.Device_Id, NAND_ID.Third_Id, NAND_ID.Fourth_Id);
	}
}

#define NAND_CMD_WR0 ((uint8_t)0x80)
#define NAND_CMD_WR1 ((uint8_t)0x10)
  

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram) {    //***********************************************

//static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Cmd) {    //***********************************************
FMC_SDRAM_CommandTypeDef Cmd;
__IO uint32_t tmpmrd =0;
Cmd.CommandMode= FMC_SDRAM_CMD_CLK_ENABLE;    //Step 3:  Configure a clock configuration enable command
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 1;
Cmd.ModeRegisterDefinition= 0;


HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000);    //Send the command
HAL_Delay(100);    

//Step 4: Insert 100 ms delay

Cmd.CommandMode= FMC_SDRAM_CMD_PALL;    //Step 5: Configure a PALL (precharge all) command
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 1;
Cmd.ModeRegisterDefinition= 0;
HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000); 

Cmd.CommandMode= FMC_SDRAM_CMD_AUTOREFRESH_MODE;    //Step 6 : Configure a Auto-Refresh command
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 4;
Cmd.ModeRegisterDefinition= 0;
HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000);

#define SDRAM_MODEREG_BURST_LENGTH_2 ((uint16_t) 0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_8 ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((uint16_t) 0x0000)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3 ((uint16_t) 0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ((uint16_t) 0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((uint16_t) 0x0200)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 

tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_8          |        //Step 7: Program the external memory mode register
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
Cmd.CommandMode= FMC_SDRAM_CMD_LOAD_MODE;
Cmd.CommandTarget= FMC_SDRAM_CMD_TARGET_BANK1;
Cmd.AutoRefreshNumber= 1;
Cmd.ModeRegisterDefinition= tmpmrd;
HAL_SDRAM_SendCommand(hsdram, &Cmd, 0x1000);
//Dummy = *((volatile uint32_t *)(SDRAM_BASE_ADDR | (0x33<<12)));


    /* Step 8: Set the refresh rate counter
64msec / 4096 fresh = 15.62 us 
refresh count= 15.62usec * 84MHz  - 20 =  1292 */
HAL_SDRAM_ProgramRefreshRate(hsdram, 1386);     //refresh count

}
