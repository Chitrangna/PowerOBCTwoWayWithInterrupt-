/*
 * Power--OBCm-Power.c
 *
 * Created: 01-08-2017 21:46:08
 * Author : Chitrangna Bhatt
 */ 

//#define F_CPU 8000000
//#include <avr/io.h>
#include "common.h"
#include "uart.h"
#include "i2c.h"
uint8_t data;

ISR(TWI_vect){
	/*uint8_t data= TWI_read_data_slave();
	transmit_UART(data);*/
	//transmit_UART('1');
	//TWCR|= (1<<TWINT)|(1<<TWEA);//|(1<<TWEN);//|(1<<TWIE);
	switch(TWSR){
		case 0x60://it is being addressed as sr
		//transmit_UART('a');
		TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);	//sending ack//why do we do this here//try removing it from here and check if it works
		break;
		
		case 0x80://checking whether ack has been sent
		//transmit_UART('d');
		data=TWDR;
		transmit_UART(data);
		//TWCR|= (1<<TWINT)|(1<<TWEA);//|(1<<TWEN);//|(1<<TWIE);
		TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
		break;
		
		case 0xA8 ://check for being addressed as st
		TWDR=data;//twcr is being set in the last line so data will be sent as soon as the address is received
		TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
		/*case 0xA0:
		TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);    //sei();
		break;*/
		/*
		default:
		transmit_UART('f');
		TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE)|(0<<TWSTA)|(0<<TWSTO);
		break;*/
		case 0xC0 ://nack from mr
		break;
		
	}
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
}

 
int main(void)
{
    // Initializations
    init_UART();
	TWI_init_slave();
	//_delay_ms(2000);
	sei();
	TWCR = (1<<TWEN)|                             // TWI Interface enabled.
	(1<<TWIE)|(1<<TWINT)|                  // Enable TWI Interupt and clear the flag.
	(1<<TWEA);   //TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
	while (1);
    // Variables
	/*while(1){
		transmit_UART('3');
		TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
		_delay_ms(2000);
		transmit_UART('4');
	}*/
		//TWCR|= (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
		//TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE);
}

