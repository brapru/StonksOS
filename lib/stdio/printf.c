static inline int isdigit(int c)
{
        return '0' <= c && c <= '9';
}


static int skip_atoi(const char **s)
{
	int i = 0;
	while (isdigit(**s))
	    i = i * 10 + *((*s)++) - '0';
	return i;
}

int main()
{
	char *a[2];
	a[0] = "12";
	a[1] = "13";

    for (int x = 0; x <=1; x++)
    {
	int i = skip_atoi(a);
	printf("%d\n", i);
	    
    }
}
