void Isprimne(int *Prime)
{
	Prime[0] = Prime[1] = 0;
	for(int i = 2;i <=maxn;i++)
	{
		Prime[i] = 1;
	}
	for(int i = 2 ;i <= maxn; i++)
	{
		for(int j = i * 2;j <= maxn; j+=i)
		{
			Prime[j] = 0;
		}
	}
}
