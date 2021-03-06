//------------------------------

//加入AT89X51.H檔。
#include <AT89X51.H>
//定義七段顯示器顯示方式陣列。
unsigned short seg_num[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};

//------------------------------

//宣告0.0001秒延遲函數。
void delay1ms(unsigned int count)
{
//宣告延遲儲存變數i和j。
  unsigned int i,j;
//為避免迴圈變數溢位（＜65535），以雙層迴圈設定延遲。
  for(i=0;i<50;i++)
  {
//第二層迴圈。
    for(j=0;j<count;j++)
    {
      ;
    }
  }
}

//------------------------------

//宣告中斷0涵數。
void T0_int(void) interrupt 1
{
//宣告迴圈控制與顯示數值變數i。
  int i;
//中斷0發生時，由迴圈設定依序顯示“1234”數值。
  for(i=0;i<=4;i++)
  {
//限制P2埠控制四個七段顯示器僅讓最右邊的致能輸出。
    P2=0xfc;
//將指定的數值藉由預先設置好的陣列解碼至P1輸出。
    P1=seg_num[i];
//呼叫延遲涵數延遲一秒。
    delay1ms(1000);
  }
}

//------------------------------

//宣告中斷1涵數。
void T1_int(void) interrupt 3
{
//宣告迴圈控制與顯示數值變數i。
  int i;
//中斷0發生時，由迴圈設定依序顯示“56789”數值。
  for(i=5;i<=9;i++)
  {
//限制P2埠控制四個七段顯示器僅讓最右邊的致能輸出。
    P2=0xfc;
//將指定的數值藉由預先設置好的陣列解碼至P1輸出。
    P1=seg_num[i];
//呼叫延遲涵數延遲一秒。
    delay1ms(1000);
  }
}

//------------------------------

//主程式。
int main(void)
{
//宣告迴圈控制與顯示數值變數i。
  int i;
//中斷致能暫存器（IE）啟動計時／計數器0中斷控制與計時／計數器1中斷控制。
  IE=0x85;
//設定計時／計數器0外部中斷為負緣觸發動作。
  IT0=1;
//設定計時／計數器1外部中斷為負緣觸發動作。
  IT1=1;
//計時／計數模式控制暫存器（TMOD）設定計時／計數器0如1為16位元計時／計數模式。
  TMOD=0x11;
//中斷優先權暫存器（IP）設定計時／計數1外部中斷為高層次中斷。
  IP=0x04;
//為了不斷執行，用無窮迴圈包住。
  while(1)
  {
//由迴圈設定依序顯示“0123456789”數值。
    for(i=0;i<=9;i++)
    {
//限制P2埠控制四個七段顯示器僅讓最右邊的致能輸出。
      P2=0xfc;
//將指定的數值藉由預先設置好的陣列解碼至P1輸出。
      P1=seg_num[i];
//呼叫延遲涵數延遲一秒。
      delay1ms(1000);
    }
  }
}
