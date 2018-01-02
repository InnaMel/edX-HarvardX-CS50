#include <cs50.h>
#include <stdio.h>

int main (void)
{
  int height = 0;

  //started cycle "do while"
  do
  {
    printf ("Height: ");

    //getting height for pyramid
    height = get_int ();
  }

  while ((height < 0) || (height > 23));

  //switching our actions depending on conditions
  switch (height)
  {

  // if height is zero - doing nothing
  case 0:
    break;
  default:
    {

    //printing pyramid
    int space = height - 1;

    //step by row
    for (int i = 0; i < height; i++)
    {

      //step by column
      for (int j = 0; j < (height + 1); j++)
      {

        //if column less space - print white space
        if (j < space)
        {
          printf (" ");
        }

        //if space less column  - print #
        else

        {
        printf ("#");
        }
      }

      //decrement space
      space--;

      //line free, translation
      printf ("\n");
    }
    }
  }
  return 0;
}
