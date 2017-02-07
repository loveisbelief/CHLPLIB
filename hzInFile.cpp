void  hzInFile (CString FileName)
{
	FILE *in;
	unsigned char  c1, c2;
	int id;
	in=fopen((const char *)FileName, "rb");
	if(in==NULL)
	{
		AfxMessageBox("�޷��������ļ���");
		return;
	}
	while (!feof (in))
	{
		c1=(unsigned char ) fgetc(in);	// ת��Ϊ�޷����ַ�
		if(c1<128)
			continue;	// �������ֽ������ַ�
		if(c1<176)
		{
			c2=fgetc(in);
			continue; 
		} // Ҳ������Ǻ����ַ�����Ҫ���һ���ֽ�
		c2=(unsigned char ) fgetc(in);	// ���뺺�ֵĵڶ����ֽ�
		id=HZ_ID(c1,c2);	// ����ú��ֵ��±�
		HZFreq[id]++;		// ���ú��ֵ�Ƶ�ȼ�1
	}
	fclose(in);
	return;
}
void OnSingleHz() 
{
	// ������Ƶͳ��
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