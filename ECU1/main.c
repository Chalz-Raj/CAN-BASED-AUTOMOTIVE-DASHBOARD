/*
 * File:   main.c
 * Author: HP
 *
 * Created on May 5, 2025, 3:26 PM
 */


#include <xc.h>
#include"matrix.h"
#include "main.h"
#include"clcd.h"
#include "adc.h"
#include "can.h"
#include<string.h>
#include<stdio.h>

void config(void)
{
 
   init_clcd();
   init_adc();
   init_matrix_keypad();
   init_can();
}
    unsigned int speed_buff[8];
    unsigned int gear_buff[8];
    unsigned int temp_buff[8];
//    unsigned int msg_id;
//    unsigned int len;

void main(void) {
    
    config();
    unsigned char key;
    unsigned short speed_adc;
    unsigned short temp_adc;
    unsigned int gear = 0;

    int k3=0;
//    unsigned int msg_id;
//
//    
//    unsigned int speed_recieve[8] = {0};
//    unsigned int gear_recieve[13] ={0};
//    unsigned int temp_recieve[8] ={0};
//    
//    unsigned int speed_len = 0;
//    unsigned int gear_len = 0;
//    unsigned int temp_len = 0;
    
    while(1)
    {
        key = read_switches(STATE_CHANGE);
        if(key == MK_SW1)
        {
            gear++;
            if(k3) //k3 =1
            {
                gear = 1;
                k3 = 0;
            }
            else
            {
                gear++;
                if(gear >5)
                {
                    gear = 5;
                }
            }
        }
        else if(key == MK_SW2)
        {
            if(k3) // k3=1
            {
                gear = 7;
            }
            else
            {
                
                if(gear >0)
                {
                    gear--;

                }
            }
        }
        else if(key == MK_SW3)
        {
            gear = 7;
            k3 = 1;
        }
        gear_buff[0] = gear+48;
//        clcd_print("GEAR",LINE1(0));
        can_transmit(GEAR_MSG_ID,gear_buff,1);
//        __delay_ms(50);
        //can_receive(&msg_id,&gear_recieve,&gear_len);
//        if(msg_id == GEAR_MSG_ID)
//        {
//            clcd_putch(gear_recieve[0],LINE2(0));
//        }
        
//       clcd_print("SPEED",LINE1(5));
        speed_adc = (read_adc(CHANNEL4))/10.33;         
        speed_buff[0] = (speed_adc/10) + 48;
        speed_buff[1] = (speed_adc%10) + 48;
        can_transmit(SPEED_MSG_ID,speed_buff,2);
//        __delay_ms(50);
        //can_receive(&msg_id,&speed_recieve,&speed_len);
          
//       if(msg_id == SPEED_MSG_ID)
//        {
//            clcd_putch(speed_recieve[0],LINE2(5));
//            clcd_putch(speed_recieve[1],LINE2(6));
////             clcd_putch(speed_buff[0],LINE2(5));
////            clcd_putch(speed_buff[1],LINE2(6));
//        }
//        clcd_print("TEMP",LINE1(11));
        temp_adc = ((read_adc(CHANNEL6)*(float)5)/(float)1023)*100;   
        temp_buff[0] =(temp_adc/10) + 48;
        temp_buff[1] = (temp_adc%10) +48;
        temp_buff[2] = 0xDF;
        temp_buff[3] = 'C';
        can_transmit(TEMP_MSG_ID,temp_buff,4);
//        __delay_ms(50);
        //can_receive(&msg_id,&temp_recieve,&temp_len);
       
//         if(msg_id == TEMP_MSG_ID)
//        {
//            clcd_putch(temp_recieve[0],LINE2(11));
//            clcd_putch(temp_recieve[1],LINE2(12));
//            clcd_putch(temp_recieve[2],LINE2(13));
//            clcd_putch(temp_recieve[3],LINE2(14));
//        }
        

        


//        
//        


        


       

        
        
    }
    return;
}
