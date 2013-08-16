#include <s3c6410.h>
#include <types.h>

#define  VSPW         9
#define  VBPD          1
#define  LINEVAL     271
#define  VFPD          1


#define  HSPW         40    
#define  HBPD          1
#define  HOZVAL      479
#define  HFPD          1

#define LeftTopX     0
#define LeftTopY     0

#define RightBotX   479
#define RightBotY   271

#define FRAME_BUFFER   0x54000000

unsigned int fb_base_addr;
unsigned int bpp;
unsigned int xsize;
unsigned int ysize;

void PutPixel(unsigned int x, unsigned int y, unsigned int color)
{
    unsigned int *addr = (unsigned int *)fb_base_addr + (y * xsize + x);
    *addr =  color;
}

void ClearScr(unsigned int color)
{   
    unsigned int x,y;
    
    for (y = 0; y < ysize; y++)
        for (x = 0; x < xsize; x++)
            PutPixel(x, y, color);
}

void lcd_init()
{
    /* 设置GPIO引脚用于LCD */
    GPICON = 0xaaaaaaaa;  /* gpi0~gpi15用作lcd_vd[0~15] */
    GPJCON = 0xaaaaaaa;   /* gpj0~gpj11用作lcd */
    GPFCON &= ~(0x3<<28);
    GPFCON |=  (1<<28);    /* GPF14用作背光使能信号 */
    GPECON &= ~(0xf);
    GPECON |= (0x1);          /* GPE0用作LCD的on/off信号 */

    MIFPCON &= ~(1<<3);   /* Normal mode */

    SPCON    &= ~(0x3);
    SPCON    |= 0x1;            /* RGB I/F style */

    /* RGB I/F, RGB Parallel format,  */
    VIDCON0 &= ~((3<<26) | (3<<17) | (0xff<<6)  | (3<<2));
    /* vclk== HCLK / (CLKVAL+1) = 133/15 = 9MHz */
    VIDCON0 |= ((14<<6) | (1<<4) );      

    VIDCON1 &= ~(1<<7);   /* 在vclk的下降沿获取数据 */
    VIDCON1 |= ((1<<6) | (1<<5));  /* HSYNC高电平有效, VSYNC高电平有效 */

    VIDTCON0 = (VBPD << 16) | (VFPD << 8) | (VSPW << 0);
    VIDTCON1 = (HBPD << 16) | (HFPD << 8) | (HSPW << 0);
    VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

    WINCON0 &= ~(0xf << 2);
    /* unpacked 24 BPP (non-palletized R:8-G:8-B:8 ) */
    WINCON0 |= (0xb<<2);    

    VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
    VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
    VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1);

    VIDW00ADD0B0 = FRAME_BUFFER;
    VIDW00ADD1B0 =  (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff);
    /* VBASEL = VBASEU + (LINEWIDTH+OFFSIZE) x (LINEVAL+1) 
     *        = 0 + (480*4 + 0) * 272
     *        = 
     */
    //VIDW00ADD2 =  HOZVAL + 1;
    fb_base_addr = FRAME_BUFFER;
    xsize = HOZVAL + 1;
    ysize = LINEVAL + 1;
    bpp   = 24;

    /* 打开LCD */
    GPEDAT |= (1<<0);
    GPFDAT |= (1<<14);
    VIDCON0 |= 0x3;
    WINCON0 |= 1;

    /* ClearScr(0x0); */
}

#define FONTDATAMAX 2048

static unsigned int x_pos = 0;
static unsigned int y_pos = 0;

extern const unsigned char fontdata_8x8[FONTDATAMAX];

void lcd_putc(unsigned char c)
{
    int i,j;
    unsigned char line_dots;
    unsigned char *char_dots = fontdata_8x8 + c * 8;

    if(x_pos == 0 && y_pos == 0){
	ClearScr(0);
    }
    if(c == '\n'){
	y_pos += 8;
	if(y_pos > 272){
	    y_pos = 0;
	}
	return;
    }
    if(c == '\r'){
	x_pos = 0;
	return;
    }
    for(i = 0;i < 8;i++){
	line_dots = char_dots[i];
	for(j = 0;j < 8;j++){
	    if(line_dots & (0x80 >> j)){
		PutPixel(x_pos+j,y_pos+i,0xffffff);
	    } else {
		PutPixel(x_pos+j,y_pos+i,0x0);
	    }
	}
    }
    x_pos += 8;
    if(x_pos > 480)
	x_pos = 0;
    if(x_pos == 0){
	y_pos += 8;
	if(y_pos > 272){
	    y_pos = 0;
	}
    }
    
}
