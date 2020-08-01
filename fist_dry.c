
#include "dookem.h"


void    loading(t_dookem *doomer)
{
}


int		init(t_dookem *doomer)
{
}

void    render(t_dookem *doomer)
{
}


void    controls(void)
{  
}

void    update(t_dookem *doomer)
{
}

int main(void)
{
    t_dookem doomer = {0};

    loading(&doomer);

    if(!(init(&doomer)))
	{
		printf("Render init failed {;_;} \n");
		exit(1);
	}

    while(1)
    {
        render(&doomer);
        update(&doomer);
        controls(&doomer);
    }
    return(0);
}