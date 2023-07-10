/*
 * 
 *
 * Created: 07.01.2021 11:56:13
 * Author : LAPTOP SYLWII
 */ 


#define F_CPU 11059200L
#define UART_BAUD_RATE 9600
#define LED PB0
#define przycisk PD2

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "i2cmaster.h"
#include "pcf8574.h"
#include "lcdpcf8574.h"
#include "uart.h"
#include "diskio.h"
#include "pff.h"

#define PCF8583_ADDR 0xA2 //jaki znak jest pocz¹tkiem - spacja


int main(void)
{	
		uint8_t sd_bufor[512];  // g³ówny bufor
		char rekord[96]; //ci¹g znaków pomiaru, zapisywany na karcie SD
		char stan[10]; //Dobry_stan lub Zly_stan powietrza w zale¿noœci od norm (czy jakakolwiek jest przekroczona)

		DDRB |= (1<<LED);
		PORTB &=~(1<<LED); //na pocz¹tku dioda jest zgaszona
		DDRD |= (1<<przycisk);
		PORTD |= (1<<przycisk);
	
        //inicjalizacja LCD
        lcd_init(LCD_DISP_ON_BLINK);
        lcd_home();

		//ustawienie LCD
        lcd_led(0); 
		
		//inicjalizacja UART
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
		
		//inicjalizacja czytnika kart SD
		uint8_t ires;
		FATFS fs;
		ires = mk_petit_init( sd_bufor, sizeof(sd_bufor), 0 );
		
		//jesli inicjalizacja czytnika kart SD by³a poprawna
		if(ires == 0)
		{
			//zamontowanie
			pf_mount(&fs);
			//otwarcie pliku
			pf_open("TEST.TXT");
		}

	
		char buf[10];
		lcd_gotoxy(1, 0); 
		lcd_puts("PMS1.0 : ");
		lcd_gotoxy(12, 0);
		lcd_puts("/");
		
		lcd_gotoxy(1, 1);
		lcd_puts("PMS2.5 : ");
		lcd_gotoxy(12, 1);
		lcd_puts("/");
		
		lcd_gotoxy(1, 2);
		lcd_puts("PMS10  :");
		lcd_gotoxy(12, 2);
		lcd_puts("/");
		
		lcd_gotoxy(1, 3);
		lcd_puts("Czekam!");
		
		
		unsigned int pm1;
		unsigned int pm2_5;
		unsigned int pm10;
		
		unsigned int pm1ATM;
		unsigned int pm2_5ATM;
		unsigned int pm10ATM;
		
		unsigned int norma03;
		unsigned int norma05;
		unsigned int norma1;
		
		unsigned int norma2_5;
		unsigned int norma5;
		unsigned int norma10;
		
		
		
        while(1) 
		{	
		//uk³ad nie pracuje - zgaœ diodê
		PORTB &=~(1<<LED);
	
		//jeœli przycisk wciœniêty
		while(PIND & (1<<przycisk))
			   { 
				   //w³¹cz diodê
				    PORTB |= (1<<LED);
				   
				   //odbierz dane z czujnika
				    unsigned int tablicaDanych[32];
				    pobierzPomiary(tablicaDanych); //pomiar - co 5s 
				   
				   
				   //uwzgledniany jest zapis na wyzszych i nizszych bitach
				   pm1 = tablicaDanych[4] + tablicaDanych[5];
				   pm2_5 = tablicaDanych[6] + tablicaDanych[7];
				   pm10 = tablicaDanych[8] + tablicaDanych[9];
				   
				   pm1ATM = tablicaDanych[10] + tablicaDanych[11];
				   pm2_5ATM = tablicaDanych[12] + tablicaDanych[13];
				   pm10ATM = tablicaDanych[14] + tablicaDanych[15];
				   
				   norma03 = tablicaDanych[16] + tablicaDanych[17];
				   norma05 = tablicaDanych[18] + tablicaDanych[19];
				   norma1 = tablicaDanych[20] + tablicaDanych[21];
				   
				   norma2_5 = tablicaDanych[22] + tablicaDanych[23];
				   norma5 = tablicaDanych[24] + tablicaDanych[25];
				   norma10 = tablicaDanych[26] + tablicaDanych[27];
				  
				   //wyœwietl na wyœwietlaczu
					char buf[10];
					
					//PM 1.0
					lcd_gotoxy(1, 0); //ustaw kursor
					lcd_puts("PMS1.0 : ");
					lcd_gotoxy(9, 0);
					itoa(pm1, buf, 10); 
					lcd_puts(buf);
					lcd_gotoxy(12, 0);
					lcd_puts("/");
					itoa(pm1ATM, buf, 10); 
					lcd_puts(buf);
					
					//PM 2.5
					lcd_gotoxy(1, 1);
					lcd_puts("PMS2.5 : ");
					lcd_gotoxy(9, 1);
					itoa(pm2_5, buf, 10); 
					lcd_puts(buf);
					lcd_gotoxy(12, 1);
					lcd_puts("/");
					itoa(pm2_5ATM, buf, 10); 
					lcd_puts(buf);
					
					//PM 10
					lcd_gotoxy(1, 2);
					lcd_puts("PMS10  :");	
					lcd_gotoxy(9, 2);
					itoa(pm10, buf, 10); 
					lcd_puts(buf);
					lcd_gotoxy(12, 2);
					lcd_puts("/");
					itoa(pm10ATM, buf, 10);
					lcd_puts(buf);
					
					
				   lcd_gotoxy(1, 3);
					//jesli przekroczona jakakolwiek norma py³ów PM: 1.0(>12,5ug/m3), 2.5(>25ug/m3), 10(>50ug/m3) - normy WHO 24-godzinne
				   if(pm1 > 12 || pm2_5 >25  || pm10  > 50)
						{
 							lcd_puts("Zla jakosc!!!");
 							sprintf(stan,"Zly_stan");
						}
				   else
					   {
						   lcd_puts("Dobra jakosc!");
						   sprintf(stan, "Dobry_stan");
						   
					   }
				   
		   
				   //zapisz na kartê - jesli inicjalizacja byla poprawna
				   
 				   if(ires == 0)
				   { 
					    sprintf(rekord,"|PM1.0-%d/%d,PM2.5-%d/%d,PM10-%d/%d,%s:%d.%d.%d.%d.%d.%d",pm1, pm1ATM, pm2_5, pm2_5ATM, pm10, pm10ATM, stan, norma03, norma05, norma1, norma2_5, norma5, norma10);
						mk_pf_file_append(&fs, "TEST.TXT", rekord);
				   }
				   
				   //pomiar co 5s
				   _delay_ms(5000);
				   
				   //wyczysc ekran
				   lcd_clrscr();	 
				  
			}
			
        }

}