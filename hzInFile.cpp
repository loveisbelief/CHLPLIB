void  hzInFile (CString FileName)
{
	FILE *in;
	unsigned char  c1, c2;
	int id;
	in=fopen((const char *)FileName, "rb");
	if(in==NULL)
	{
		AfxMessageBox("无法打开输入文件！");
		return;
	}
	while (!feof (in))
	{
		c1=(unsigned char ) fgetc(in);	// 转换为无符号字符
		if(c1<128)
			continue;	// 不处理单字节西文字符
		if(c1<176)
		{
			c2=fgetc(in);
			continue; 
		} // 也不处理非汉字字符，但要多读一个字节
		c2=(unsigned char ) fgetc(in);	// 读入汉字的第二个字节
		id=HZ_ID(c1,c2);	// 计算该汉字的下标
		HZFreq[id]++;		// 给该汉字的频度加1
	}
	fclose(in);
	return;
}
void OnSingleHz() 
{
	// 单字字频统计
	for(int i=0; i<HZ_NUM; i++) HZFreq[i]=0;
	ProcessFiles(hzInFile);
	FILE *outFile;
	outFile=fopen("hzfreq.txt", "wt");
	for(int id=0; id<HZ_NUM; id++)
		if(HZFreq[id]>0)
			fprintf(outFile, "%c%c\t%d\n", id/94+176, id%94+161, HZFreq[id]);
		fclose(outFile);	
		return;
}