// Master code
void SPI_MasterInit(void) {
    // Set DDRB to have MOSI, SCK, and SS as output and MISO as input
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);     // identical to DDRB=0xB0;
    // Set SPCR register to enable SPI, enable master, and use SCK frequency
    //   of fosc/16  (pg. 168)
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);    // identical to SPCR|=0x51;
    // Make sure global interrupts are enabled on SREG register (pg. 9)
    sei();                                  // identical to SREG = SREG|0x80;
}

void SPI_MasterTransmit(unsigned char cData) {
    // data in SPDR will be transmitted, e.g. SPDR = cData;
    SPCR = cData;
    // set SS low
    PORTB = (PORTB & 0xEF);
    // wait for transmission to complete
    while(!(SPSR & (1<<SPIF))) { 
        ;
    }
    // set SS high
    PORTB = (PORTB | 0x10);
}

// Servant code
void SPI_ServantInit(void) {
    // set DDRB to have MISO line as output and MOSI, SCK, and SS as input
    DDR_SPI = (1<<DD_MISO);         
    // set SPCR register to enable SPI and enable SPI interrupt (pg. 168)
    SPCR = (1<<SPE);
    // make sure global interrupts are enabled on SREG register (pg. 9)
    sei();
}


ISR(SPI_STC_vect) { 
    // this is enabled in with the SPCR register’s “SPI
    // Interrupt Enable”
    // SPDR contains the received data, e.g. unsigned char receivedData =
    // SPDR;
    receivedData = SPDR;
}

1hHhZMMw