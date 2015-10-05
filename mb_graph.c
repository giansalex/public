unsigned char 	LCD_massive[256];
unsigned int 	LED_massive[16];

flash unsigned int sin[] = {
	8, 9,10,11,12,13,13,14,14,15,15,15,14,14,13,13,12,11,10, 9,
	8, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6
};

void LED_Refresh(){
	unsigned char i;
	for (i = 0; i<16; i++){
   		spi((unsigned char)(LED_massive[i]>>8));     
	   	spi((unsigned char)(LED_massive[i]));     
	}
	LATCH = 1;
	LATCH = 0;
}

void LED_Clear(){
	unsigned char i;
	for (i = 0; i<16; i++){
		LED_massive[i] = 0xff;
	}
	LED_Refresh();
}

void LED_SetPixel(unsigned char x, unsigned char y){
	unsigned int temp;
	temp = 0xfe << y;
	LED_massive[x] = LED_massive[x] & temp;
}

void Effect_Chain(){
	if (led == 0) led = 1;

	if (led == 0b0000000000000001) plusminus = PLUS;
	if (led == 0b1000000000000000) plusminus = MINUS;
	
	if (plusminus == PLUS){
		led = led<<1;
	}

	if (plusminus == MINUS){
		led = 1;
		plusminus = PLUS;
	}
	
	spi(0xff - (unsigned char)(led>>8));     
  	spi(0xff - (unsigned char)led);     
 	LATCH = 1;
   LATCH = 0;
}

void Effect_Random(){
	unsigned int ran1;
	unsigned int ran2;
	ran1 = rand();
	ran2 = rand();
	ran1 = ran1&ran2;
	
	spi(0xff - (unsigned char)(ran1>>8));     
	spi(0xff - (unsigned char)(ran1));     
  	LATCH = 1;
   LATCH = 0;
}

void Effect_Lines(){
	unsigned char i;
	
	if (led == 0) led = 1;

	for (i = 0;i <16;i++){
		spi(0xff - (unsigned char)(led>>8));     
		spi(0xff - (unsigned char)led);     
	}

	led = led<<1;

   	LATCH = 1;
    LATCH = 0;
}

void Effect_Equalaser(){
	unsigned int ran;
	unsigned char u,d;
	unsigned char i;
	unsigned char temp;
	ran = rand();
	u = ((unsigned char)(ran>>8))/16;
	d = ((unsigned char)(ran))/16;

	temp = 1;
	for (i =0; i<u; i++){
		temp = (temp<<1) + 1;
	}
	u = temp;

	temp = 0b10000000;
	for (i =0; i<d; i++){
		temp = (temp>>1) + 0b10000000;
	}
	d = temp;
	
	spi(0xff - u);     
  	spi(0xff - d);     
  	LATCH = 1;
   LATCH = 0;
}

void Effect_Sin(){
	unsigned int temp;
	unsigned int temp2;
	
	temp = 1 << sin[phasecounter];
	temp2 = 0b1000000000000000 >> sin[phasecounter];

	temp = temp|temp2;

	spi(0xff - (unsigned char)(temp>>8));     
	spi(0xff - (unsigned char)temp);     
	
	LATCH = 1;
	LATCH = 0;
	phasecounter++; 
	if (phasecounter == 40) phasecounter = 0;
}

