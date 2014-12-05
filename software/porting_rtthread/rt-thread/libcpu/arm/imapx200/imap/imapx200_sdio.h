#ifndef __IMAPX200_SDIO_H
#define __IMAPX200_SDIO_H


#define SDICON     	 (0x00 )		//SDI control
#define SDIPRE     	 (0x04 )		//SDI baud rate prescaler
#define SDICARG		 (0x08 )		//SDI command argument
#define SDICCON		 (0x0c )		//SDI command control
#define SDICSTA		 (0x10 )		//SDI command status
#define SDIRSP0		 (0x14 )		//SDI response 0
#define SDIRSP1		 (0x18 )		//SDI response 1
#define SDIRSP2		 (0x1c )		//SDI response 2
#define SDIRSP3		 (0x20 )		//SDI response 3
#define SDIDTIMER	 	 (0x24 )		//SDI data/busy timer
#define SDIBSIZE	 	 (0x28 )		//SDI block size
#define SDIDCON	 	 (0x2c )		//SDI data control
#define SDIDCNT		 (0x30 )		//SDI data remain counter
#define SDIDSTA		 (0x34 )		//SDI data status
#define SDIFSTA		 (0x38 )		//SDI FIFO status
#define SDIIMSK		 (0x3c )		//SDI interrupt mask. edited for 2440A
#define SDIDAT    	 	 (0x40 )		//SDI data 
#define SDIDMAADRA	 	 (0x80 )
#define SDIDMACA		 (0x84 )
#define SDIDMAADRB		 (0x88 )
#define SDIDMACB		 (0x8C )
#define SDIDMAADRC		 (0x90 )
#define SDIDMACC		 (0x94 )
#define SDIDMAADRD	 	 (0x98 )
#define SDIDMACD		 (0x9C )

#endif
