
void SPI_MasterInit(void){
    DDRB = 0xB0;
    SPCR |= 0x51;
    SREG = SREG|0x80;
    //spsr
}
 
void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF))){
        ;
    }
}
 
void SPI_SlaveInit(void) {
    // set DDRB to have MISO line as output and MOSI, SCK, and SS as input
    DDRB = 0x40;
    // set SPCR register to enable SPI and enable SPI interrupt (pg. 168)
    SPCR = SPCR|0xC0;
    // make sure global interrupts are enabled on SREG register (pg. 9)
    SREG = SREG|0x80;
   
}
 
 
ISR(SPI_STC_vect) { // this is enabled in with the SPCR register’s “SPI
    // Interrupt Enable”
    // SPDR contains the received data, e.g. unsigned char receivedData =
    // SPDR;
    receviedData= SPDR;
}

// http://pastebin.com/1hHhZMMw