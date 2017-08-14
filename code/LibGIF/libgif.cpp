#include "libgif.h"
#include <stdio.h>

bool GIFParser::Analysis(const std::string& gif)
{
	FILE* fp;
	fopen_s(&fp, gif.c_str(), "rb");
	//FILE* fp = fopen("E:/cocos2d-x-3.0/tests/cpp-empty-test/Resources/ipad/run.gif","rb");
	if(NULL == fp)  
	{
		return false;
	}

	gif_global global;
	int size_global = sizeof(gif_global);
	if(1 != fread(&global, 13, 1, fp))return false;
	if(strncmp(global.header,"GIF8",4))return false;

	gif_table table;
	table.sogct = (short)(1 << ((global.pflds & 0x07)+1));        
	table.colres = (short)(((global.pflds & 0x70) >> 4) + 1);    

	//is has global color table
	bool b_global_color_table = 0 != (global.pflds & 0x80);
	if(b_global_color_table)
	{
		int size_global_color_table = sizeof(gif_color) * table.sogct;
		if(1 != fread(&table.paleta, size_global_color_table, 1, fp))return false;
	}

	m_lNumFrames = get_num_frames(fp, &table, &global);

	char ch;
	gif_image image;
	bool bPreviousWasNull = true;
	for(bool bContinue = true; bContinue;)
	{
		if (fread(&ch, sizeof(ch), 1, fp) != 1) {break;}

		if (bPreviousWasNull || ch==0)
		{
			switch (ch)
			{
			// extension
			case '!': 
				{
					bContinue = DecodeExtension(fp);
					break;
				}
			// image
			case ',': 
				{
					fread(&image,sizeof(image),1, fp);
					if (((image.l + image.w) > global.scrwidth)||((image.t + image.h) > global.scrheight)) break;

					//Local Palette 
					gif_color  locpal[256];	
					//Current Palette 
					gif_color* pcurpal = table.paleta;	
					//Current Palette color count  
					short palcount = table.sogct;		

					// Local colour map?
					if (image.pf & 0x80) 
					{
						palcount = (short)(1 << ((image.pf & 0x07) +1));
						fread(locpal, sizeof(gif_color) * palcount,1, fp);
						pcurpal = locpal;
					}

					//select the correct bit per pixel value
					int bpp;
					if (palcount <= 2)  bpp = 1;
					else if (palcount <= 16) bpp = 4;
					else bpp = 8;

					break;
				}
			case ';': //terminator
				bContinue=false;
				break;
			default:
				bPreviousWasNull = (ch==0);
				break;
			}
		}
	}
	return true;
}

int GIFParser::get_num_frames(FILE* fp, gif_table* TabColSrc, gif_global* dscgif)
{
	int nframes = 0;
	long pos = ftell(fp);
	gif_table TempTabCol;
	memcpy(&TempTabCol, TabColSrc, sizeof(gif_table));

	char ch;
	gif_image image;
	bool bFlag = true;
	bool b_continue = true;
	while(b_continue)
	{
		if(1 != fread(&ch, sizeof(ch), 1, fp))break;
		//if one char can't known, to skip, until char == 0, resafe
		if(bFlag || ch == 0)
		{
			switch (ch)
			{
			//0x21 extension start
			case '!': 			
				{
					//DecodeExtension(fp);
					break;
				}
			//0x2c image start
			case ',': 
				{
					int size_image = sizeof(image);
					if(1 != fread(&image, 9, 1, fp))break;

					// in case of images with empty screen descriptor, give a last chance
					if (dscgif->scrwidth == 0 && dscgif->scrheight == 0)
					{
						dscgif->scrwidth = image.w;
						dscgif->scrheight = image.h;
					}

					if (((image.l + image.w) > dscgif->scrwidth)||((image.t + image.h) > dscgif->scrheight))break;

					nframes++;
					break;
				}
			//0x3B image terminator
			case ';': 
				{
					b_continue = false;
					break;
				}
			default:
				{
					bFlag = (ch == 0);
					break;
				}
			}
		}
	}
	fseek(fp, pos,SEEK_SET);
	return nframes;
}

bool GIFParser::DecodeExtension(FILE *fp)
{
	return true;
	//bool bContinue;
	//unsigned char count;
	//unsigned char fc;

	//bContinue = (1 == fread(&fc, sizeof(fc), 1, fp));
	//if (bContinue) 
	//{
	//	// AD - for transparency    0xF9   Graphic Control Label 
	//	if (fc == 0xF9)	
	//	{
	//		bContinue = (1 == fread(&count, sizeof(count), 1, fp));             //block size, default 4
	//		if (bContinue) 
	//		{
	//			bContinue = (count == fread(&gifgce, 1, 4, fp));
	//			gifgce.delaytime = ntohs(gifgce.delaytime); // Avoid Byte order problem with Mac <AMSN>
	//			if (bContinue) 
	//			{
	//				long nBkgndIndex  = (gifgce.flags & 0x1) ? gifgce.transpcolindex : -1;
	//				DWORD dwFrameDelay = gifgce.delaytime;
	//				BYTE DisposalMethod = ((gifgce.flags >> 2) & 0x7);
	//			}	
	//		}	
	//	}

	//	if (fc == 0xFE) 
	//	{ //<DP> Comment block
	//		bContinue = (1 == fread(&count, sizeof(count), 1, fp));
	//		if (bContinue) 
	//		{
	//			char m_comment[256];
	//			bContinue = (1 == fread(m_comment, count, 1, fp));
	//			m_comment[count]='\0';
	//		}	
	//	}

	//	if (fc == 0xFF) { //<DP> Application Extension block
	//		bContinue = (1 == fread(&count, sizeof(count), 1, fp));
	//		if (bContinue) 
	//		{
	//			bContinue = (count==11);
	//			if (bContinue)
	//			{
	//				char AppID[11];
	//				bContinue = (1 == fread(AppID, count, 1, fp));
	//				if (bContinue) 
	//				{
	//					bContinue = (1 == fread(&count, sizeof(count), 1, fp));
	//					if (bContinue) 
	//					{
	//						BYTE* dati = (BYTE*)malloc(count);
	//						bContinue = (dati!=NULL);
	//						if (bContinue)
	//						{
	//							bContinue = (1 == fread(dati, count, 1, fp));
	//							if (count>2)
	//							{
	//								int m_loops = dati[1]+256*dati[2];
	//							}
	//						}
	//						free(dati);
	//					}	
	//				}	
	//			}	
	//		}	
	//	}
	//	while (bContinue && fread(&count, sizeof(count), 1, fp) && count) {
	//		//log << "Skipping " << count << " bytes" << endl;
	//		fseek(fp, count, SEEK_CUR);
	//	}
	//}
	//return bContinue;
}



