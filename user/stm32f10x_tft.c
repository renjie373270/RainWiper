#include "stm32f10x_tft.h"
#include "stm32f10x_gpio.h"
#include "Font.h"
#include "char.h"





#define Bank1_LCD_D    ((uint32_t)0x60020000)    //???????	  
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //???????

unsigned long color1=0;



void delayms(uint32_t x)
{
	uint32_t i,j;
	for(i=0;i<x;i++)
	for(j=0;j<8000;j++);
}			
//????????
void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;  

}		  
//????????
//??:dbw ????,1?16?,0?8??
void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

//???????
unsigned int LCD_RD_data(void){
	unsigned int a=0;
	a=*(__IO uint16_t *) (Bank1_LCD_D);   //???
	a=*(__IO uint16_t *) (Bank1_LCD_D);   //?????16?????	  
	return(a);	
}
uint16_t RGB(u8 R,u8 G,u8 B)	
{
	return((uint16_t)(R&0XF8)<<8|(uint16_t)(G&0XFC)<<3|(uint16_t)(B&0XF8)>>3);
}

//?16???????
void    LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

void FSMC_LCD_Init(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;	
  GPIO_InitTypeDef GPIO_InitStructure;	    
  //??FSMC????
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 			  //LCD????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 	 		  //LCD??
  GPIO_Init(GPIOE, &GPIO_InitStructure);   	   	
  // ?????FSMC?? FSMC-D0--D15
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);   
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);    
  //FSMC NE1  LCD??
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  //FSMC RS---LCD?? ??/??	??
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
  GPIO_Init(GPIOD, &GPIO_InitStructure); 	
  GPIO_SetBits(GPIOD, GPIO_Pin_13);			           //LCD????
  
  
  //FSMC??????
  p.FSMC_AddressSetupTime = 0x02;
  p.FSMC_AddressHoldTime = 0x00;
  p.FSMC_DataSetupTime = 0x05;
  p.FSMC_BusTurnAroundDuration = 0x00;
  p.FSMC_CLKDivision = 0x00;
  p.FSMC_DataLatency = 0x00;
  p.FSMC_AccessMode = FSMC_AccessMode_B;

 
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
 
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 		
  /* Enable FSMC Bank1_SRAM Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

//?????
void LCD_Init(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);	  //????
    delayms(1);			   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 
	delayms(1);			   

LCD_WR_CMD(0x0000, 0x00000);
LCD_WR_CMD(0x0000, 0x00000);
LCD_WR_CMD(0x0000, 0x00000);
LCD_WR_CMD(0x0000, 0x00000);
//{time, 0010 ,ms}
LCD_WR_CMD(0x0400, 0x06200);
LCD_WR_CMD(0x0008, 0x00808);
LCD_WR_CMD(0x0300, 0x00C00);//gamma
LCD_WR_CMD(0x0301, 0x05A0B);
LCD_WR_CMD(0x0302, 0x00906);
LCD_WR_CMD(0x0303, 0x01017);
LCD_WR_CMD(0x0304, 0x02300);
LCD_WR_CMD(0x0305, 0x01700);
LCD_WR_CMD(0x0306, 0x06309);
LCD_WR_CMD(0x0307, 0x00C09);
LCD_WR_CMD(0x0308, 0x0100C);
LCD_WR_CMD(0x0309, 0x02232);
LCD_WR_CMD(0x0010, 0x00016);//69.5Hz
LCD_WR_CMD(0x0011, 0x00101);//
LCD_WR_CMD(0x0012, 0x00000);//
LCD_WR_CMD(0x0013, 0x00001);//
LCD_WR_CMD(0x0100, 0x00330);//BT,AP
LCD_WR_CMD(0x0101, 0x00237);//DC0,DC1,VC
LCD_WR_CMD(0x0103, 0x00F00);//VDV
LCD_WR_CMD(0x0280, 0x06100);//VCM
LCD_WR_CMD(0x0102, 0x0C1B0);//VRH,VCMR,PSON,PON
//{time, 0100 ,ms}
LCD_WR_CMD(0x0001, 0x00100);
LCD_WR_CMD(0x0002, 0x00100);
LCD_WR_CMD(0x0003, 0x01030);
LCD_WR_CMD(0x0009, 0x00001);
LCD_WR_CMD(0x000C, 0x00000);
LCD_WR_CMD(0x0090, 0x08000);
LCD_WR_CMD(0x000F, 0x00000);
LCD_WR_CMD(0x0210, 0x00000);
LCD_WR_CMD(0x0211, 0x000EF);
LCD_WR_CMD(0x0212, 0x00000);
LCD_WR_CMD(0x0213, 0x0018F);//432=1AF, 400=18F
LCD_WR_CMD(0x0500, 0x00000);
LCD_WR_CMD(0x0501, 0x00000);
LCD_WR_CMD(0x0502, 0x0005F);
LCD_WR_CMD(0x0401, 0x00001);
LCD_WR_CMD(0x0404, 0x00000);
//{time, 0100 ,ms}
LCD_WR_CMD(0x0007, 0x00100);//BASEE
//{time, 0100 ,ms}
/*
LCD_WR_CMD(0x0200, 0x00000);
LCD_WR_CMD(0x0201, 0x00000);

	LCD_WR_CMD(0x0200, 0);
    LCD_WR_CMD(0x0201, 0);
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x0202;
	for(i=0;i<96000;i++)
	{
	  LCD_WR_Data(0xffff);
	}
	color1=0; */
}/*
void lcd_wr_zf(u16 StartX, u16 StartY, u16 X, u16 Y, u16 Color, u8 Dir, u8 *chr)
{	unsigned int temp=0,num,R_dis_mem=0,Size=0,x=0,y=0,i=0;


	if(Dir==2) LCD_WR_CMD(0x0003,0x1010);   //??????????  ???  ???  AM=0  I/D[1:0]=00	<--
	else if(Dir==3) LCD_WR_CMD(0x0003,0x1028);   //??????????  ???  ???  AM=1  I/D[1:0]=10	V
  	if(Dir==0){
		LCD_WR_CMD(0x0003,0x1030);		  //??????????  ???  ???  AM=0  I/D[1:0]=11  -->
		LCD_WR_CMD(0x0210, StartX); 	  //????????? 0-239
  		LCD_WR_CMD(0x0211, StartX+X-1);   //????????? 0-239
  		LCD_WR_CMD(0x0212, StartY);       //????????? 0-399
  		LCD_WR_CMD(0x0213, StartY+Y-1);   //????????? 0-399
		LCD_WR_CMD(0x0200, StartX);		  //???????
  		LCD_WR_CMD(0x0201, StartY);		  //???????	
		LCD_WR_REG(0x0202);               //????????
		Size=X*Y;						  //?????????????
		while(i<Size){					  
			temp=*chr++;				  //??????8???,???1??????8???
			for(num=0; num<8; num++){	  //??????????8???	    
				if((temp&0x80)>0){		  //??????????,?1???????16??????,????????						 
				
					LCD_WR_Data(Color); 		
				}
				else{
					LCD_WR_CMD(0x0200, StartX+x);		//???????
  					LCD_WR_CMD(0x0201, StartY+y);		//???????								
					LCD_WR_REG(0x0202);					//????????
					R_dis_mem=LCD_RD_data();		  	//?????,????????????	
					LCD_WR_Data(R_dis_mem); 		//??????????,?0????????16??????? 						
				}
				temp=temp<<1; 		  				//???????
				x++;
				if(x>=X){x=0; y++;}				    //??????????x?y,?????????????
				i++;	
			}				  
							
		}
	}
	else if(Dir==1){
		LCD_WR_CMD(0x0003,0x1018);   	  		//??????????  ???  ???  AM=1  I/D[1:0]=01	A
		LCD_WR_CMD(0x0210, StartY); 	  		//????????? 0-239
  		LCD_WR_CMD(0x0211, StartX+Y-1);    		//????????? 0-239
  		LCD_WR_CMD(0x0212, 399-(StartX+X-1));   //????????? 0-399
  		LCD_WR_CMD(0x0213, 399-StartX);    		//????????? 0-399
		LCD_WR_CMD(0x0200, StartY);		  	  	//???????
  		LCD_WR_CMD(0x0201, 399-StartX);	 	  	//???????	
		LCD_WR_REG(0x0202);                   	//????????

		Size=X*Y;						  		//?????????????
		while(i<Size){					  
			temp=*chr++;				  		//??????8???,???1??????8???
			for(num=0; num<8; num++){	  		//??????????8???	    
				if((temp&0x80)>0){		  		//??????????,?1???????16??????,????????						 
				
					LCD_WR_Data(Color); 		
				}
				else{
					LCD_WR_CMD(0x0200, StartY+y);		//???????
  					LCD_WR_CMD(0x0201, 399-(StartX+x));	//???????								
					LCD_WR_REG(0x0202);					//????????
					R_dis_mem=LCD_RD_data();		  	//?????,????????????	
					LCD_WR_Data(R_dis_mem); 		//??????????,?0????????16??????? 						
				}
				temp=temp<<1; 		  				//???????
				x++;
				if(x>=X){x=0; y++;}				    //??????????x?y,?????????????
				i++;	
			}							
		}
	}
}  
void LCD_ClearScreen(uint16_t color)
{
	uint32_t t,res;
	LCD_WR_CMD(0x0003,0x1018);   	  		//??????????  ???  ???  AM=1  I/D[1:0]=01	A
	LCD_WR_CMD(0x0210, StartY); 	  		//????????? 0-239
	LCD_WR_CMD(0x0211, StartX+Y-1);    		//????????? 0-239
	LCD_WR_CMD(0x0212, 399-(StartX+X-1));   //????????? 0-399
	LCD_WR_CMD(0x0213, 399-StartX);    		//????????? 0-399
	LCD_WR_CMD(0x0200, StartY);		  	  	//???????
	LCD_WR_CMD(0x0201, 399-StartX);	 	  	//???????	
	LCD_WR_REG(0x0202);                   	//????????		
	res=240*400;
	for(t=0;t<res;t++)
		LCD_WR_Data(color);
} */
void LCD_ClearScreen(uint16_t color)   
{
	uint32_t t,res;							  
	LCD_WR_CMD(0x0003,0x1018);   	        //??????????  ???  ???  AM=1  I/D[1:0]=01	A
	LCD_WR_CMD(0x0210, 0);/*y1*/ 	  	    //????????? 0-239
	LCD_WR_CMD(0x0211, 239);/*y2*/    	    //????????? 0-239
	LCD_WR_CMD(0x0212, 0);/*399-x1*/   		//????????? 0-399
	LCD_WR_CMD(0x0213, 399);/*399-x2*/    	//????????? 0-399	
	LCD_WR_CMD(0x0200, 0);/*y1*/		  	//???????
	LCD_WR_CMD(0x0201, 0);/*x1*/	 	  	//???????	
	LCD_WR_REG(0x0202);                   	//????????		
	res=240*400;
	for(t=0;t<res;t++)
		LCD_WR_Data(color);
}
void TFT_Init(uint16_t color)
{
	//SystemInit();   					 //???????72MHz
	FSMC_LCD_Init();							 //FSMC????		  
	LCD_Init();								 //?????		  
	LCD_ClearScreen(color);
}
void LCD_Point(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_WR_CMD(0x0003,0x1018);   	  	
	LCD_WR_CMD(0x0210, y); 	  		
	LCD_WR_CMD(0x0211, y);    		
	LCD_WR_CMD(0x0212, 399-x);   
	LCD_WR_CMD(0x0213, 399-x);    		
	LCD_WR_CMD(0x0200, y);		  	  	
	LCD_WR_CMD(0x0201, 399-x);	 	  
	LCD_WR_REG(0x0202);
	LCD_WR_Data(color);
} 

unsigned char find_Font(uint8_t size,const char *p)
{	
	uint16_t i,count;
	count=size*size/8+2;
	for(i=0;i<sizeof(GB_24)/count;i++)
	{
		 if((GB_24[i].Index[0]==p[0])&&(GB_24[i].Index[1]==p[1]))
		 {
		 		break;      
		 }		
	}
	return i;	
}
void LCD_WriteFont(uint16_t x,uint16_t y,uint16_t size,uint16_t color,const  char *p)
{
	unsigned int a,b,j=0x80;
	for(a=0;a<size;a++)
	{
		j=0x80;
		for(b=0;b<8;b++)
		{			
			if(size==16)
			{
				if(p[2*a+0]&j)LCD_Point(x+b+0,y+a,color);
				if(p[2*a+1]&j)LCD_Point(x+b+8,y+a,color);							
			}
			if(size==24)
			{
				if(p[3*a+0]&j)LCD_Point(x+b+0,y+a,color);
				//else  LCD_Point(x+b+0,y+a,RGB(136,139,147));
				if(p[3*a+1]&j)LCD_Point(x+b+8,y+a,color);
				//else  LCD_Point(x+b+8,y+a,RGB(136,139,147));			
				if(p[3*a+2]&j)LCD_Point(x+b+16,y+a,color);
				//else  LCD_Point(x+b+16,y+a,RGB(136,139,147));
			}
			if(size==32)	  //??
			{
				if(p[4*a+0]&j)LCD_Point(x+b+0,y+a,color);
				if(p[4*a+1]&j)LCD_Point(x+b+8,y+a,color);
				if(p[4*a+2]&j)LCD_Point(x+b+16,y+a,color);
				if(p[4*a+3]&j)LCD_Point(x+b+24,y+a,color);
			}	 
			j>>=1;		
		}
	}
}
void LCD_WriteFontString(uint16_t x,uint16_t y,uint16_t color,const  char *p)
{
	uint16_t m,num;
	unsigned char tab[20];
	for(num=0;p[num]!='\0';num++);
	num/=2;	
	for(m=0;m<num;m++)
	{
		tab[m]=find_Font(24,&p[2*m]);       
	}
	for(m=0;m<num;m++)
	{
		 LCD_WriteFont(x+m*24,y,24,color,&(GB_24[tab[m]].Msk[0]));
	}
}
void LCD_DisplayFont(uint16_t color,const char *p)
{
	char dis[10][33];	 
	int i=0,j=0,count;
	int x=0,y=0;

	for(i=0;i<10;i++)
	for(j=0;j<33;j++)
	dis[i][j]='\0';//?'\0'???
	
	for(i=0;p[i]!='\0';i++);
	count=i/2;

	i=0;j=0;  
	for(i=0;i<10;i++)
	{
		for(j=0;j<32;j++)
		{
			if(p[32*i+j]!='\0')
				dis[i][j]=p[32*i+j];
			else
				break;
		}
	} 	
	for(i=0;i<10;i++)				
	{
		if(i*16>=count)return;
		LCD_WriteFontString(x,y,color,&dis[i][0]);
		y+=24;
	}
}
unsigned char find_Asc(const char *p)
{
	unsigned char i;
	for(i=0;i<sizeof(Asc)/17;i++)
	{
		if(*p==Asc[i].Index)
		break;
	}
	return i;
}
void LCD_WriteChar(uint16_t x,uint16_t y,uint16_t color,const char *p)
{
	uint16_t a,b,j=0x80;
	for(a=0;a<24;a++)
	{
		j=0x80;
		for(b=0;b<8;b++)
		{
			if(p[2*a+0]&j)
				LCD_Point(x+b+0,y+a,color);/*
			else
				LCD_Point(x+b+0,y+a,green);//??*/
			if(p[2*a+1]&j)
				LCD_Point(x+b+8,y+a,color);/*
			else
				LCD_Point(x+b+8,y+a,green);//??*/
			j>>=1;
		}
	}
}
void LCD_WriteCharString(uint16_t x,uint16_t y,uint16_t color,const char *p)
{
	uint16_t m,num;
	unsigned char tab[30];
	for(num=0;p[num]!='\0';num++);
	for(m=0;m<num;m++)
	{
		tab[m]=find_Asc(&p[m]);       
	}
	for(m=0;m<num;m++)
	{
		 LCD_WriteChar(x+m*12,y,color,&Asc[tab[m]].Msk[0]);
	}	
}
void LCD_DisplayAsc(uint16_t color,const char *p)
{	
	char dis[10][33];
	int i=0,j=0;
	int x=0,y=0;

	for(i=0;i<10;i++)
	for(j=0;j<33;j++)
	dis[i][j]='\0';//?'\0'????

	i=0;j=0;
	for(i=0;i<10;i++)
	{
		for(j=0;j<32;j++)
		{
			dis[i][j]=p[32*i+j];
		}
	}
	for(i=0;i<10;i++)
	{
		if(dis[i][31]=='\0')return;
		LCD_WriteCharString(x,y,color,&dis[i][0]);
		y+=24;
	}
}
void LCD_DisplayString(uint16_t x,uint16_t y,uint16_t color,const char *p)
{
	int count=0,i=0;	
	char str[3];

	for(i=0;p[i]!='\0';)
	{
		if((p[i]>=' ')&&(p[i]<='~'))
		{
			str[0]=p[i];
			str[1]='\0';
			str[2]='\0';
			i++;
			count++;
			if(count%((400-x)/12)>=32)			
			{
				x=0;
				y=y+24;
			}
			LCD_WriteCharString(x,y,color,str);
			x=x+12;
		}
		else
		{
			str[0]=p[i];
			str[1]=p[i+1];
			str[2]='\0';
			i=i+2;
			count+=2;
			if(count%((400-x)/12)>=32)			
			{
				x=0;
				y=y+24;
			}
			LCD_WriteFontString(x,y,color,str);
			x=x+24;
		}
	}
}
void test(void)
{			  
	char tab[]="Today is 00 ";
	tab[9]='2';
	tab[10]='8';
	TFT_Init(white);
	
	LCD_DisplayString(10,0,red,"I am happy now,");
	LCD_DisplayString(10,24,red,"Are you OK?");
	LCD_DisplayString(10,24*2,red,tab);
	LCD_DisplayString(10+12*12,24*2,red,"??");
	LCD_DisplayString(10,24*3,blue,"珍惜我们现在的美好生活！");
	LCD_DisplayString(10,24*6,black,"时光时光慢些吧!");
	LCD_DisplayString(10,24*7,blue,"不要再让你变老啦");
	LCD_DisplayString(10,24*8,red,"我愿用我一切换你岁月长留");
}
