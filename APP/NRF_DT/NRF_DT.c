#include "NRF_DT.h"

extern RockerTypeDef *RackerStruct_P;
extern volatile bit Delay_Time0_500ms_Flag;

sbit LED_RUN = P5^4;

void NRF_DT(void)
{
	
#ifdef NRF_CAR_MASTER 
	if(Delay_Time0_500ms_Flag == 1)
	{/*定时程序*/
		Get_Rocker();//获得摇杆数据
		ADC_UART_TEST();//测试遥感数据
		
		{/*发送摇杆数据*/	
#if (ROCKER_SUM == 1)	
			if(NRF24L01_TxPacket(RackerStruct_P) == TX_OK)
			{
				/*发送成功，LED RUN*/
				LED_RUN = !LED_RUN;
				UART_SendString("NRF24L01 TxPacket Send OK\r\n");
			}
			else
			{
				UART_SendString("NRF24L01 TxPacket Send ERR\r\n");
			}
#endif	
//#if (ROCKER_SUM == 2)
//			
//#endif	
		}	
	}
	
	{/*非定时程序*/
		
	}
#endif
	
#ifdef NRF_CAR_SLAVE
	if(Delay_Time0_500ms_Flag == 1)
	{/*定时程序*/
		
		
	}
	{/*非定时程序*/
		if(NRF24L01_RxPacket(&Rocker) == 0)//一旦接收到信息,则显示出来.
		{
			LED_RUN = !LED_RUN;
			UART_SendString("Get NRF24L01 Rx Packet:\r\n");
#if (ROCKER_SUM == 1)
			sprintf(str, "Rocker_X = %u\t", Rocker.ONE.X);
			UART_SendString(str);
			sprintf(str, "Rocker_Y = %u\r\n", Rocker.ONE.Y);
			UART_SendString(str);
#endif
//#if (ROCKER_SUM == 2)
//			sprintf(str, "Rocker_L_X = %u\t", Rocker.L.X);
//			UART_SendString(str);
//			sprintf(str, "Rocker_L_Y = %u\r\n", Rocker.L.Y);
//			UART_SendString(str);
//			sprintf(str, "Rocker_R_X = %u\t", Rocker.R.X);
//			UART_SendString(str);
//			sprintf(str, "Rocker_R_Y = %u\r\n", Rocker.R.Y);
//			UART_SendString(str);
//#endif
			tmp_buf[5] = '\r';
			tmp_buf[6] = '\n';
			tmp_buf[7] = '\0';//加入字符串结束符
			UART_SendString(Rocker);    
		}
	}
#endif	//NRF_CAR_SLAVE End
	
}




