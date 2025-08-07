 /*
 * File:   main.c
 * Author: HP
 *
 * Created on May 6, 2025, 8:05 PM
 */


#include <xc.h>
#include"main.h"
#include"ssd_display.h"
#include"adc.h"
#include"digital_keypad.h"
#include"can.h"
#include<stdio.h>
#include<string.h>

void config(void)
{
    init_ssd_control();
    init_adc();
    init_digital_keypad();
  
//    TRISB = 0x00;
//    PORTB = 0X00;
      init_can();
}
//static unsigned char ssd[MAX_SSD_CNT];
//static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

    unsigned int rpm_buff[8];
    unsigned int blink_buff[8];

void main(void) {
    config();
    unsigned short rpm_adc;
    unsigned long int delay = 0; 
    unsigned char key;
    int right = 0;
    int left = 0;
    
    unsigned int msg_id;
    
    
    unsigned int rpm_recieve[8] = {0};
    unsigned int blink_recieve[8] ={0};
    
    unsigned int rpm_len = 0;
    unsigned int blink_len = 0;
//    TRISB6 = TRISB7 = TRISB1 =  TRISB0=0;
//    RB1=RB0=RB7=RB6=0;
    
    while(1)
    {
        rpm_adc = read_adc(CHANNEL4) * (float)5.865;
        rpm_buff[0] = rpm_adc/1000;
        rpm_buff[1] = (rpm_adc/100) % 10;
        rpm_buff[2] = (rpm_adc/10) % 10;
        rpm_buff[3] = rpm_adc % 10;
        

        can_transmit(RPM_MSG_ID,rpm_buff,4);
        //can_receive(&msg_id,&rpm_recieve,&rpm_len);
        
//        if(msg_id == RPM_MSG_ID)
//        {
//            ssd[0] = digit[rpm_recieve[0]];
//            ssd[1] = digit[rpm_recieve[1]];
//            ssd[2] = digit[rpm_recieve[2]];
//            ssd[3] = digit[rpm_recieve[3]];
//
//            display(ssd);
//        }
        
        

        
        key = read_digital_keypad(STATE_CHANGE);
        
        if(key == SWITCH1)
        {   
            left = 1;
            right =0;
           
        }
        else if(key == SWITCH2)
        {
           
            right = 1;
            left = 0;
        }
        else if(key == SWITCH3)
        {
            right = 0;
            left = 0;
        }
        
        blink_buff[0] = right;
        blink_buff[1] = left;
        
        can_transmit(BLINK_MSG_ID,blink_buff,2);
//        can_receive(&msg_id,&blink_recieve,&blink_len);
        
//        if(msg_id == BLINK_MSG_ID)
//        {
//        
//            if(blink_recieve[0] == 1)
//            {
//                if(delay++==50)
//                {
//                    delay = 0;
//                    RB0 = 0;
//                    RB1 = 0;
//                    RB6 = !RB6;
//                    RB7 = !RB7;
//                }
//
//            }
//            else if(blink_recieve[1] == 1)
//            {
//                if(delay++ == 50)
//                {
//                    delay = 0;
//                    RB6 = 0;
//                    RB7 = 0;
//                    RB0 = !RB0;
//                    RB1 = !RB1;
//                }
//            }
//            else
//            {
//                PORTB = 0x00;
//            }
        //}
    }
    
    
    return;
}
