#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

uint8_t ui8PinData=2;

void delay(int type, int qty);

int main(void)
{

    //    Input State Enabled
    uint8_t playerInputState = 1;

    uint8_t currentPlayCounter = 0;

    uint8_t showPattern = 1;

    uint8_t level=1;

    int randArr[10];

    //  Set system frequency at 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //  Select Ports B and C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    //  Initialize all Pins in Port B
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

    //  Initialize Pins in Port C for use with the Push Buttons
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

    while(1) {
        while(showPattern == 1) {
            //show pattern if player wins
            if(level == 6){
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
                delay(1000, 200);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

                delay(1000, 200);

                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
                delay(1000, 200);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

                delay(1000, 200);

                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
                delay(1000, 200);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

                level = 1;
                showPattern = 1;
                playerInputState = 0;
            }
            else {
                int i, j;

                for (j = 0; j < 10; j++) {
                    randArr[j] = rand() % 4;
                }

                for (i = 0;  i < level; i++) {
                    if(randArr[i] == 0){
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
                    }
                    if(randArr[i] == 1){
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
                    }
                    if(randArr[i] == 2){
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    }
                    if(randArr[i] == 3){
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                        delay(1000, 500);
                        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    }
                }
            }
            showPattern = 0;
            playerInputState = 1;
            currentPlayCounter = 0;
        }
        while(playerInputState == 1) {
            // Observes Pull Up Push Buttons
            int32_t data_in_pin_1 = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4);

            int32_t data_in_pin_2 = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5);

            int32_t data_in_pin_3 = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);

            int32_t data_in_pin_4 = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7);

            if (data_in_pin_1 == 0) {
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x10);
                delay(1000, 500);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
                if(randArr[currentPlayCounter] == 0){
                    currentPlayCounter++;
                    if(currentPlayCounter == level) {
                        level++;
                        showPattern = 1;
                        playerInputState = 0;
                        currentPlayCounter = 0;
                    }
                }
                else{
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    level = 1;
                    showPattern = 1;
                    playerInputState = 0;
                    currentPlayCounter =0;

                }
            }

            if (data_in_pin_2 == 0) {
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20);
                delay(1000, 500);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);
                if(randArr[currentPlayCounter] == 1){
                    currentPlayCounter++;
                    if(currentPlayCounter == level) {
                        level++;
                        showPattern = 1;
                        playerInputState = 0;
                        currentPlayCounter = 0;
                    }
                }
                else{
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    level = 1;
                    showPattern = 1;
                    playerInputState = 0;
                    currentPlayCounter =0;

                }
            }

            if (data_in_pin_3 == 0) {
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0x40);
                delay(1000, 500);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0x00);
                if(randArr[currentPlayCounter] == 2){
                    currentPlayCounter++;
                    if(currentPlayCounter == level) {
                        level++;
                        showPattern = 1;
                        playerInputState = 0;
                        currentPlayCounter = 0;
                    }
                }
                else{
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    level = 1;
                    showPattern = 1;
                    playerInputState = 0;
                    currentPlayCounter =0;

                }
            }

            if (data_in_pin_4 == 0) {
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0x80);
                delay(1000, 500);
                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0x00);
                if(randArr[currentPlayCounter] == 3){
                    currentPlayCounter++;
                    if(currentPlayCounter == level) {
                        level++;
                        showPattern = 1;
                        playerInputState = 0;
                        currentPlayCounter = 0;
                    }
                }
                else{
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);
                    delay(1000, 400);

                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x04);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x08);
                    delay(1000, 400);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);

                    level = 1;
                    showPattern = 1;
                    playerInputState = 0;
                    currentPlayCounter =0;
                }
            }
        }
    }

}

void delay(int type, int qty) {
    int clock = SysCtlClockGet();
    SysCtlDelay((clock/(3*type)) * qty);
}
