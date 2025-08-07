/*
 * File:   MAIN.c
 * Author: HP
 *
 * Created on May 19, 2025, 3:52 PM
 */


#include <xc.h>
#include"can.h"
#include"clcd.h"
#include"MAIN.h"
//void clcd_putch(const unsigned char data, unsigned char addr);
void config(void)
{
    init_clcd();
    init_can();
}



void main(void) {
    
    config();
    
    unsigned int msg_id;

    
    unsigned int speed_recieve[8] = {0};
    unsigned int gear_recieve[8] ={0};
    unsigned int temp_recieve[8] ={0};
    
    unsigned int speed_len = 0;
    unsigned int gear_len = 0;
    unsigned int temp_len = 0;
    
    unsigned int rpm_recieve[8] = {0};
    unsigned int blink_recieve[8] ={0};
    
    unsigned int rpm_len = 0;
    unsigned int blink_len = 0;
    
    unsigned int delay = 0;
    
    
    clcd_print("G SP TEMP RPM  I",LINE1(0));
    while(1)
    {
        
          can_receive(&msg_id,gear_recieve,&gear_len);
          
          can_receive(&msg_id,speed_recieve,&speed_len);
          
          
          
          can_receive(&msg_id,temp_recieve,&temp_len);
          
          can_receive(&msg_id,rpm_recieve,&rpm_len);
          
          can_receive(&msg_id,blink_recieve,&blink_len);
          
          
        switch(msg_id)
        {
            case SPEED_MSG_ID : 
            {
                clcd_putch(speed_recieve[0],LINE2(2));
                clcd_putch(speed_recieve[1],LINE2(3));
                break;
            }
            case GEAR_MSG_ID :
            {
                clcd_putch(gear_recieve[0],LINE2(0));
                break;
            }
            case TEMP_MSG_ID :
            {
                clcd_putch(temp_recieve[0],LINE2(5));
                clcd_putch(temp_recieve[1],LINE2(6));
                clcd_putch(temp_recieve[2],LINE2(7));
                clcd_putch(temp_recieve[3],LINE2(8));
                break;
            }
            case RPM_MSG_ID :
            {
                clcd_putch(rpm_recieve[0],LINE2(10));
                clcd_putch(rpm_recieve[1],LINE2(11));
                clcd_putch(rpm_recieve[2],LINE2(12));
                clcd_putch(rpm_recieve[3],LINE2(13));
                break;
            }
            case BLINK_MSG_ID :
            {
                if(blink_recieve[0] == 1)
                {
                    if(delay++==50)
                    {
                        delay = 0;
                        clcd_putch('R',LINE2(15));
                    }
                }
                else if(blink_recieve[1]==1)
                {
                    if(delay++==50)
                    {
                        delay = 0;
                        clcd_putch('L',LINE2(15));
                    }
                }
                else
                {
                    clcd_putch(' ',LINE2(15));
                }
                break;
            }
        }
    }
    return;
}
