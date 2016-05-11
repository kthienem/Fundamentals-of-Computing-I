#include <stdio.h>
#include <math.h>

#define SIZE 50

float average(int[], int);
float standardDev(int[], int, float);

int main()
{
   int grades[SIZE] = {0};
   size_t i; //counter for array position
   float value;
   float avg;
   float stddev;
   
   i = 0;
   scanf("%f", &value);

   while (value >= 0){
      grades[i] = value;
      i++;
      scanf("%f", &value);
   }

   avg = average(grades, i);
   printf("The average is %.2f\n", avg);

   stddev = standardDev(grades, i, avg);
   printf("The standard deviation is %.2f\n", stddev);
}

float average(int grades[], int i){
   size_t k; //counter for array position
   float total = 0; // sum of all the grades

   for (k = 0; k < i; ++k){
      total += grades[k];
   }
 
   return total/(k);
}

float standardDev(int grades[], int i, float avg){
   float sum = 0; // sum of (x - avg of grades)^2
   size_t k; //counter for array position

   for (k = 0; k < i; ++k){
      sum += pow((grades[k] - avg), 2);
   }
   return sqrt(sum/(k-1));
}
