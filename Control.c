#include "main.h"
//#include "ultrasonic.h"
#include "delay.h"
//#include "lid.h"
#include "uart.h"

uint8_t Tx_Buffer[] = "good";
#define countof(a) (sizeof(a) / sizeof(*(a)))

void Ledinit(){
	
	
	GPIO_InitTypeDef GPIO_InitStructure;	 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	/* Configure PC10 and PC11 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
}

void ultra_sta(){
	GPIO_InitTypeDef GPIO_InitStructure;	 
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOF, ENABLE);
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;//Trig
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//Echo
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//control pin of the motor: PF4
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOF, &GPIO_InitStructure);
}

 void ultras(float *p){
	 unsigned char i;
  unsigned long int j;
	float Ultr_Temp;
	 for(i=0;i<5;i++){
		
	 GPIO_SetBits(GPIOB,GPIO_Pin_4);  
	 delay_ms(10);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_4); 
		 
	 //LCD_Clear(LCD_COLOR_GREY); 
   while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==0);
		
	 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==1){
	 delay_us(8);//8us
	 j++; 
   }
   Ultr_Temp+=340/2*j*10;//  模块最大可测距3m 
		j=0;
		delay_ms(60);//防止发射信号对回响信号的影响
	 }
	 *p=Ultr_Temp/5/1000000;
	 
   }
 

int main(void){
	int i;
  float temp;
 //cha DisNum[16];	
  uint8_t DisNum[16];
 	SystemInit();
	// USART_Configuration();
	
	delay_init(48);
	STM320518_LCD_Init();
 	ultra_sta(); 
	
//   Ledinit();
	LCD_Clear(LCD_COLOR_GREY); 
 
 
 
//GPIO_ResetBits(GPIOF,GPIO_Pin_4); 
GPIO_SetBits(GPIOB,GPIO_Pin_5); //Counterclockwise, well it needs a second delay for the relay react..
//don;t believe two realys can response the same time and the time to take is 10ms? That's ridiculous long
//respect to the datasheet saying, One relay is for using connect two red wires for counterclockwise and 
//and the other you know...
//I only can control a little bit of  time and totally cannot control the speed. The chip on it saying GPM3F and 
//it is General Plus....I do not know before..
//delay_ms(15); 
 delay_ms(150);
GPIO_ResetBits(GPIOB,GPIO_Pin_5); 


}



