long long Extend_Euclid(long long  a,long long b,long long  &x,long long  &y)
{
	if(b == 0)
	{
		x = 1;
		y = 0 ;
		return a;
	}
	long long d   = Extend_Euclid(b,a %b,x,y);
	long long tmp  =x;
	x = y;
	y = tmp - a / b * y;
	return d;
}
