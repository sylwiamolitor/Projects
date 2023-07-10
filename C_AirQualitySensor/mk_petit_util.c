#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
/*Na podstawie ksi¹¿ki "Jêzyk C. Pasja programowania mikrokontrolerów 8-bitowych*/

#include "diskio.h"
#include "pff.h"

#include "mk_petit_util.h"


uint16_t SD_BUF_SIZE;
uint8_t *sd_buf;


uint8_t  mk_petit_init( void * petit_buf, uint16_t sd_buf_size, uint8_t spi2x ) {
	uint8_t res;

	SPI_DIR 	|= CS | MOSI | SCK;
	SPI_PORT 	|= CS;
	SPCR 		|= (1<<SPE)|(1<<MSTR);

	sd_buf = petit_buf;
	SD_BUF_SIZE = sd_buf_size;

	if( spi2x ) SPCR |= (1<<SPI2X);

#if USE_SD_PWR == 1
	sd_pwr(0);
	_delay_ms(500);
	sd_pwr(1);
	_delay_ms(500);
#endif

	uint8_t i=255;
	while(i-- && (res = disk_initialize()));

	return res;
}






#if USE_FILE_APPEND == 1
/*
 *   Dopisywanie do pliku
 *
 *   *wfs - wskaŸnik na obiekt FATFS
 *   *fname - wskaŸnik na nazwê pliku
 *   *txt - tekst, który ma byæ dodany na koñcu
 *
 */
int mk_pf_file_append(FATFS *wfs, char * fname, char *txt) {

	uint16_t 	i, buf_free=0, len_txt = strlen(txt);
	uint32_t 	sektor=0, tmr = 65000;
	uint8_t 	res=0;
	WORD 		rb;
	uint8_t 	*bf = sd_buf;

#if USE_SD_PWR == 1
	sd_pwr(0);		// od³. zasilanie karty
	_delay_ms(100);
	sd_pwr(1);		// pod³. zasilanie karty
#endif
	res = mk_sd_init();	// inicjalizacja karty
	if( res ) return res;

	res = mk_mount(wfs);  // zamontuj
	if( res ) return res;

	res = mk_open(fname);	// otworz
	if( res ) return res;

	while(1) {
		// odczyt danych z liku do bufora
		res=1; 
		pf_read(sd_buf, 512, &rb);
		if( rb<512 ) break;
		// czy spacja
		for(i=0; i<512; i++) if( bf[i] == FILE_BLANK_CHAR ) break;
		// nie ma spacji
		if(512==i) { sektor++; continue; }
		// ile wolnego miejsca
		buf_free = 512 - i;
		// czy mozna zapisac w wolnym miejscu tekst
		if(buf_free>=len_txt) {
			//miesci sie i kopiujemy
			memcpy(&bf[i], txt, len_txt);
			//wsk na pocz. sektora
			tmr=1000; res=100;
			while( pf_lseek(sektor*512UL) && tmr-- );
			if(!tmr) break;
			// zapis bufora do sektora
			res=5;
			pf_write(&bf[0], 512, &rb);
			if(rb<512) {
				break;	// jeœli zapisano mniej bajtów - KONIEC pliku
			}

			res = 0; // zapisano

		} else { // zapis miedzy sektorami
			// koniec sektora
			memcpy(&bf[i], txt, buf_free);

			tmr=1000; res=100;
			while( pf_lseek(sektor*512UL) && tmr-- );
			if(!tmr) break;

			res=5;
			pf_write(&bf[0], 512, &rb);
			if(rb<512) break;
			pf_write(0, 0, &rb);

			// kolejny sektor
			res = mk_sd_init();
			if( res ) return res;

			res = mk_mount(wfs);
			if( res ) return res;

			res = mk_open(fname);
			if( res ) return res;

			tmr=1000; res=100;
			while( pf_lseek((sektor+1)*512UL) && tmr-- );
			if(!tmr) break;

			pf_read(sd_buf, SD_BUF_SIZE, &rb);

			memcpy(bf, &txt[buf_free], strlen(&txt[buf_free]));

			tmr=1000; res=100;
			while( pf_lseek((sektor+1)*512UL) && tmr-- );
			if(!tmr) break;
			pf_write(&bf[0], 512, &rb);

			pf_write(0, 0, &rb);

			res = mk_sd_init();
			if( res ) return res;

		}
		break;	// koniec
	}	

	disk_initialize();

	return res;
}
#endif



#if USE_SD_PWR == 1
/*
*		Wlaczanie zasilania karty i wylaczanie
 *
 * 		sd_pwr(1) - w³. zasilania
 * 		sd_pwr(0) - wy³. zasilania
 */
void sd_pwr( uint8_t OnOff ) {
	SD_PWR_DIR |= SD_PWR_PIN;
	if(OnOff) {
		SD_ON;
		SPCR |= (1<<SPE);
		_delay_ms(50);
		disk_initialize();
	} else {
		SD_OFF;
		SPCR &= ~(1<<SPE);
		PORTB &= ~(SCK|MISO|MOSI);
		_delay_ms(300);	// rozladowanie kondensatorow
	}
}
#endif
