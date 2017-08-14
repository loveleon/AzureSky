#include<string>
using namespace std;

typedef unsigned char	BYTE;
typedef unsigned short	WORD;

//format analysis http://blog.csdn.net/friendwaters/article/details/2737328

//gif header and global label 
typedef struct tag_gif_global
{
	char header[6];					//GIF87-GIF89
	WORD scrwidth;
	WORD scrheight;					
	char pflds;						//global desc
	char bcindx;					//background color index
	char pxasrat;					//pixel aspect radio
}gif_global;

//gif color
typedef struct tag_gif_color 
{ 
	BYTE r;
	BYTE g;
	BYTE b; 
}gif_color;

//gif table
typedef struct tag_gif_table
{		
	short colres;					// color depth 
	short sogct;					// size of global color table 
	gif_color paleta[256];			// paleta  max colors is 256
}gif_table;

//gif image
typedef struct tag_gif_image
{									//0x00101100 ","
	WORD l;							//offset x
	WORD t;							//offset y
	WORD w;							//width
	WORD h;							//height
	BYTE pf;						//flag
}gif_image;

//gif extension
//Extension start:					0x21 "!"
//Extension end:					0x00 0 
//Graphic Control Extension:		0xF9 
//Comment Extension:				0xFE 
//Plain Text Extension:				0x01
//Application Extension:			0xFF
//File end:							0x3B ";"
typedef struct tag_gif_extension_control
{			              
	BYTE flags;						/*bak:3|disposalmethod:3|userinputflag:1|transpcolflag:1*/
	WORD delaytime;
	BYTE transpcolindex;
}gif_extension_control;

class GIFParser
{
public:
	bool Analysis(const std::string& gif);
	int get_num_frames(FILE* fp, gif_table* TabColSrc, gif_global* dscgif);
	bool DecodeExtension(FILE *fp);

private:
	long m_lNumFrames;
	long m_fInterval;
};