#include<stdio.h>
#include<string.h>
#include<iostream.h>
#define  HZ_NUM	6768
#define  HZ_ID(c1,c2) 	((c1)-176)*94 + ((c2)-161)
	// ���㺺���±�ĺ�
int  HZFreq[HZ_NUM];

void  hzInFile (char*FileName)
{
	// ������Ƶͳ��
	int i;
	for(i=0; i<HZ_NUM; i++) HZFreq[i]=0;
	FILE *in;
	unsigned char  c1, c2;
	int id;
	in=fopen(FileName, "rb");
	if(in==NULL)
	{
		printf("�޷��������ļ���");
//		AfxMessageBox("�޷��������ļ���");
		return;
	}
	while (!feof (in))
	{
		c1=(unsigned char ) fgetc(in);	// ת��Ϊ�޷����ַ�
		if(c1<128)
		{
			continue;	// �������ֽ������ַ�
		}
		else if(c1<176)
		{
			c2=fgetc(in);
			continue; 
		} // Ҳ������Ǻ����ַ�����Ҫ���һ���ֽ�
		else
		{
			c2=(unsigned char ) fgetc(in);	// ���뺺�ֵĵڶ����ֽ�
			id=HZ_ID(c1,c2);	// ����ú��ֵ��±�
			HZFreq[id]++;		// ���ú��ֵ�Ƶ�ȼ�1
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
   cout<<"������ɡ�"<<endl;
   return   0;  
   }
*/