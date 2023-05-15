#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define ARR_SIZE 100000

int arr[ARR_SIZE];

void ParseParameters(int tempArr[])
{
  for (int i = 0, j = 1; j < ARR_SIZE + 1; i++, j++)
    arr[i] = tempArr[i];
    // sscanf(argv[j], "%d", &arr[i]);
}

void InsertionSort()
{
  int n = ARR_SIZE;
  int temp = 0;
  int i, j, key;

  for (i = 1; i < n; i++)
  {
    key = arr[i];
    j = i - 1;

    /* Move elements of arr[0..i-1], that are
      greater than key, to one position ahead
      of their current position */
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

int main()
{
  FILE *fp;
  fp = fopen("InsertionFork.csv", "a");
  if(fp == NULL)
    printf("ERROR!\n");

  // fprintf(fp,"time,trial\n");
  int k;
  int tempArr[ARR_SIZE];
  int id = getpid();
  double times[15];
  double timetaken1;

    srand(time(0));
  int i;
	for (i = 0; i < ARR_SIZE; i++)
	{
		tempArr[i] = rand() % 100000;
	}

  clock_t start1 = clock();

  fork();
  fork();
  fork();
  if (getpid() == id)
  {
    clock_t end1 = clock();
    timetaken1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
  }

  for (k = 0; k < 15; k++)
  {
    clock_t start = clock();
    ParseParameters(tempArr);
    InsertionSort();
    clock_t end = clock();

    double timetaken = ((double)(end - start) / CLOCKS_PER_SEC) + timetaken1;
    if (getpid() == id)
    {
      if(k==14)
        fprintf(fp,"%f,15\n", timetaken *8);
      else
        fprintf(fp, "%f,%d\n", (timetaken * 8),(k+1));
      
      printf("Time taken by 8 \x1b[1mPROCESSES\x1b[0m:\x1b[92m %f "
             "seconds\x1b[0m\n\n",
             (timetaken * 8));
    }
  }
  fclose(fp);
}
