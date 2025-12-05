#include <stdbool.h>
#include <stdint.h>

#include "printf_custom/printf.h"
#include <gcode_parser/GCodeParser.h> 
#include "definitions.h"

#define serial_buffer_size 3
extern char GcodeParser_line;
volatile RX_receive_buffer[serial_buffer_size];
uint8_t rx_head_index = 0; //Input insert here
uint8_t rx_tail_index = 0; //Output takes out here

void serial_read_ISR(SERCOM_USART_EVENT event, uintptr_t context );
void dma_channel_0_ISR(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle);

void custom_uart_init(){
    SERCOM1_USART_ReadCallbackRegister(serial_read_ISR, 0);
    SERCOM1_USART_ReadNotificationEnable(true, true); 

    //This DMA is deprecated, not suitable for UART with user input
    // DMAC_Initialize(); //Initialize DMA channels here
    // DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, dma_channel_0_ISR, 0);
    //Enable DMA channel 0 to read serial data and put it in the buffer.
    // DMAC_ChannelTransfer(DMAC_CHANNEL_0, (const void *)&SERCOM1_REGS->USART_INT.SERCOM_DATA, &RX_receive_buffer, sizeof(RX_receive_buffer)); //Maybe the blocksize can tell the DMA the size of the receive buffer and after filling the receive buffer, move back and do it again. 
}

//_put_char is implement here to the printf to work!
void _putchar(char character){
    SERCOM1_USART_Write((uint8_t*)&character, 1);
}

void tx_software_trigger(){
    // SERCOM1_REGS->USART_INT.SERCOM_INTENSET = 0b10;
    // if ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & (0x1)) > 0)
    //     SERCOM1_REGS->USART_INT.SERCOM_DATA = (uint16_t)'A';
    // if ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) == SERCOM_USART_INT_INTFLAG_RXC_Msk){
    //     uint8_t dummy = SERCOM1_REGS->USART_INT.SERCOM_DATA;
    // }
    if (SERCOM1_REGS->USART_INT.SERCOM_DATA != NULL){ //Flush the data buffer to allow TX
        uint8_t dummy = SERCOM1_REGS->USART_INT.SERCOM_DATA;
    }
}

void serial_read_ISR(SERCOM_USART_EVENT event, uintptr_t context ){
    char temp_serial = 0;
    SERCOM1_USART_Read(&temp_serial, 1); //Only read 1 byte
    // printf("data: %c\n", temp_serial);
    // printf("event: %d\n", event);
    // printf("error: %d\n", SERCOM1_USART_ErrorGet());
    bool status = GcodeParser_AddCharToLine(temp_serial); 
    // LED_D7_Toggle();
    // printf("line: %c\n", *(&GcodeParser_line + 3));
    // if (status == true){
    //     printf("Complete line ready to parse true\n");
    // }
}

//This line of code is deprecated, left here for furture reference.
void dma_channel_0_ISR(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle){
    //So this interrupt is called after the block transfer is completed. The block size I set up is 128 characters so after the block transfer is finished, this interrupt is enable.
    //THis is for testing
    // printf("DMA channel 0 serial buffer filled");
    if (event == DMAC_TRANSFER_EVENT_COMPLETE){
        rx_head_index++;
        printf("dma is active\n");
        printf(RX_receive_buffer);
        // bool status = GcodeParser_AddCharToLine(RX_receive_buffer[0]);
        // DMAC_ChannelResume(DMAC_CHANNEL_0);

        //Let's try to re-enable the DMA channel then. 
        DMAC_REGS->DMAC_CHCTRLA |= (uint8_t)DMAC_CHCTRLA_ENABLE_Msk;
        // DMAC_ChannelTransfer(DMAC_CHANNEL_0, (const void *)&SERCOM1_REGS->USART_INT.SERCOM_DATA, &RX_receive_buffer, sizeof(RX_receive_buffer));
    }
}
