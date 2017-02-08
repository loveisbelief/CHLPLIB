#include<stdio.h>
#include<string.h>
#include<iostream.h>
#define  HZ_NUM	6768
#define  HZ_ID(c1,c2) 	((c1)-176)*94 + ((c2)-161)
	// 计算汉字下标的宏
int  HZFreq[HZ_NUM];

void  hzInFile (char*FileName)
{
	// 单字字频统计
	int i;
	for(i=0; i<HZ_NUM; i++) HZFreq[i]=0;
	FILE *in;
	unsigned char  c1, c2;
	int id;
	in=fopen(FileName, "rb");
	if(in==NULL)
	{
		printf("无法打开输入文件！");
//		AfxMessageBox("无法打开输入文件！");
		return;
	}
	while (!feof (in))
	{
		c1=(unsigned char ) fgetc(in);	// 转换为无符号字符
		if(c1<128)
		{
			continue;	// 不处理单字节西文字符
		}
		else if(c1<176)
		{
			c2=fgetc(in);
			continue; 
		} // 也不处理非汉字字符，但要多读一个字节
		else
		{
			c2=(unsigned char ) fgetc(in);	// 读入汉字的第二个字节
			id=HZ_ID(c1,c2);	// 计算该汉字的下标
			HZFreq[id]++;		// 给该汉字的频度加1
		}
	}
	fclose(in);

	strcat(FileName,".hzf");
	FILE *outFile;
	outFile=fopen(/*(const char *)*/FileName, "wt");
	for(id=0; id<HZ_NUM; id++)
		if(HZFreq[id]>0)
			fprintf(outFile, "%c%c\t%d\n", id/94+176, id%94+161, HZFreq[id]);
		fclose(outFile);	
	return;
}
/*
   int   main(int   argc,   char*   argv[])  
   {  
   int   i;  
   for   (i   =   0;   i<argc;   i++)
	   cout<<argv[i]<<endl;  
   //cin>>i;
   if(argc==2)
   {
	   char *fileName=argv[1];
	   hzInFile(fileName);
   }
   cout<<"任务完成。"<<endl;
   return   0;  
   }
*/