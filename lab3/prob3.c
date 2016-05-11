#include <stdio.h>

float add(float, float);
float subtract(float, float);
float multiply(float, float);
float divide(float, float);

int main()
{
   int action;
   float number1, number2;
   float solution;

   printf("This program computes a basic arithmetic function of your \n");
   printf("choosing for two numbers. Enter 1 for addition, 2 for \n");
   printf("subtraction, 3 for multiplication, and 4 for division. When \n");
   printf("finished, enter 0 to quit.\n");
   
   while (1){
      printf("Enter your choice: ");
      scanf("%i", &action);

      switch(action){
         case 1:
            printf("Enter two numbers: ");
            scanf("%f %f", &number1, &number2);
            solution = add(number1, number2);
            printf("%.2f + %.2f = %.2f\n", number1, number2, solution);
            break;
         
         case 2:
            printf("Enter two numbers: ");
            scanf("%f %f", &number1, &number2);
            solution = subtract(number1, number2);
            printf("%.2f - %.2f = %.2f\n", number1, number2, solution);
            break;

         case 3:
            printf("Enter two numbers: ");
            scanf("%f %f", &number1, &number2);
            solution = multiply(number1, number2);
            printf("%.2f*%.2f = %.2f\n", number1, number2, solution);
            break;

         case 4:
            printf("Enter two numbers: ");
            scanf("%f %f", &number1, &number2);
            solution = divide(number1, number2);
            printf("%.2f/%.2f = %.2f\n", number1, number2, solution);
            break;

         case 0:
            return 0;

         default:
            printf("That is not an option.\n");
            break;
      }
   }
}

float add(float x, float y){
   return x + y;
}

float subtract(float x, float y){
   return x - y;
}

float multiply(float x, float y){
   return x*y;
}

float divide(float x, float y){
   return x/y;
}
