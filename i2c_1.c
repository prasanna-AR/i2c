/**************************************************/
/* Author : Prasanna */
/* Date   : 03-02-2023 */
/* Filename: ic2*/
/* Description : ic2 master mode */
/*************************************************/
#include<htc.h>
#include<stdio.h>
#define _XTAL_FREQ20000000
__CONFIG(0x1F7A);

void delay();
void i2c_init(void);
void i2c_wait(void);
void i2c_start(void);
void i2c_write(unsigned char data);
void i2c_stop(void);
	
int main()
{
	delay();
	i2c_init();
	i2c_start();
	i2c_write(0x69);
	i2c_stop();
	while(1);
}
void delay(void)
{
	TMR1CS = 0; // TIMER1 CLOCK SOURCE SELECT BIT;
	T1CKPS0 =1; // SET PRESCALE VALUE;
	T1CKPS1 =1; // SET PRESCALE VALUE;
	TMR1H  = 0x0B;//TIMER VALUE LOAD MSB 100MS;
	TMR1L = 0xDB; //TIMER VALUE LOAD LSB 100MS;
	TMR1ON = 1; //TIMER ON;
	while(!TMR1IF); //INTERRUPT FLAGE BIT SET;
	TMR1IF = 0; //TIMER INTERRUPT FLAGE BIT CLEAR;
	TMR1ON = 0; //TIMER STOP;
}	
void i2c_init()
{
	SSPCON = 0x28; //SERIAL PORT ENABLE BIT, I2C MASTER MODE, CLOCK =FOSC/C4*(SSPADD+1);
	SSPCON2= 0x00; //ALL BIT ARE CLEAR;
	SSPSTAT= 0x00; //ALL BIT ARE CLEAR;
	SSPADD = 0x3F; //SLAVE DEVICE ADDRESS;
}
void i2c_wait(void)
{
	while(SSPCON2 & 0x1F || SSPSTAT & 0x04);//MSSP CONTROL REGISTOR AND MSSP STATUS REGISTER; 
	
}
void i2c_start(void)
{
	i2c_wait(); 
	SEN = 1;    //START CONDITION ENABLED BIT;
}
void i2c_stop(void)
{
	i2c_wait();
	PEN = 1;   //STOP CONDITION ENABLED BIT;
}
void i2c_write(unsigned char data)
{
	i2c_wait();
	SSPBUF = data;  //VALUE LOAD IN TO BUFFER REGISTER;
}					
	

	
		
		