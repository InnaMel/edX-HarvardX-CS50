#include <cs50.h>
#include <stdio.h>

int main (void)
{
    int Hh = 0;
    do
    {
        printf("Height: ");
        Hh = get_int();
    }
    while ((Hh < 0) || (Hh >= 24));

    switch(Hh)
    {
        case 0:
            break;
        default:
        {
            int s = 0;
            for (int i = 0; i < Hh; i++)
            {
                bool in = false;
                for (int j = 0; j < Hh * 2 + 3; j++)
                {
    				if (j < Hh + 2)
	    			{
					    if (j + s == Hh - 1)
					    {
						    printf("#");
						    s++;
					    }
					    else
					    {
						    if ((s > i) && (j <= Hh - 1))
						    {
							    printf("#");
						    }
						    else
							    if ((j == Hh) || (j == Hh + 1))
							    {
								    printf(" ");
							    }
							    else
							    {
								    printf(" ");
							    }
					    }
				    }
				    else
				        {
					        if (in == false)
					        {
						        for (int k = 0; k < s; k++)
						        {
							        printf("#");
							        j++;
						        }
						        in = true;
					        }
					   /*     else
					        {
						        printf(" ");
					        }*/
				        }
			    }
			//		s ++;
			printf("\n");
	    	}
		break;
    	}
    }
}