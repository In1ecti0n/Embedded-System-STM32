#include "sys.h"


int main()
{
	SYS_Config();
	
	while(1)
	{
		SYS_Run();
	}
}
