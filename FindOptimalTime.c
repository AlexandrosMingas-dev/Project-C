#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define COL 2
#define N 40
#define H 7

void ReadArray( int size,char CelebName[][N],float CelebTime[][COL]);
void PrintArray(int size,char CelebName[][N],float CelebTime[][COL]);
void CalcBestTime(int size, float CelebTime[][COL],float Hours[H],int HourSum[H]);
void MaxTime(int size, int HourSum[],float Hours[],float *maxArrival,float *maxDepart);
void MinTime(int size, int HourSum[],float Hours[],float *minArrival,float*minDepart);
void PrintMaxMinArrayData(int size,char CelebName[][N],float CelebTime[][COL],float *maxminArrival,float*maxminDepart);

int main()
{
    int n;
    printf("Welcome to the BestTime2Party algorithm!\n");
    printf("Give the number of celebrities attending xmas bazaar ");
    scanf("%d",&n);

    float CelebTime[n][2];
    char CelebName[n][40];
    float Hours[H]={18.00,19.00,20.00,21.00,22.00,23.00,24.00};
    int HourSum[H]={0,0,0,0,0,0,0};
    int i,j,k,time;
    while(getchar()!='\n');

    ReadArray(n,CelebName,CelebTime);
    PrintArray(n,CelebName,CelebTime);
    CalcBestTime(n,CelebTime,Hours,HourSum);

    float maxArrival=0,maxDepart=0,minArrival=0,minDepart=0;
    MaxTime(H,HourSum,Hours,&maxArrival,&maxDepart);
    printf("The best time to visit would be %.2f-%.2f\n",maxArrival,maxDepart);
    printf("Bands playing from %.2f-%.2f\n",maxArrival,maxDepart);
    PrintMaxMinArrayData(n,CelebName,CelebTime,&maxArrival,&maxDepart);

    MinTime(H,HourSum,Hours,&minArrival,&minDepart);
    printf("The worst time to visit would be %.2f-%.2f\n",minArrival,minDepart);
    printf("Bands playing from %.2f-%.2f\n",minArrival,minDepart);
    PrintMaxMinArrayData(n,CelebName,CelebTime,&minArrival,&minDepart);

}
/////////////////////////////// functions ///////////////////////////////////////

void PrintMaxMinArrayData(int size,char CelebName[][N],float CelebTime[][COL],float *maxminArrival,float*maxminDepart)
{
    for(int i=0;i<size;i++){
        if (CelebTime[i][0]<*maxminDepart && CelebTime[i][1]>*maxminArrival) { // if the hour of arrival is smaller than the max min depart
            printf("%s\n", CelebName[i]); // and the depart is after the maxmin arrival it is in range so we print it
         }
    }
}

void MinTime(int size, int HourSum[],float Hours[],float *minArrival,float*minDepart)
{
    int i,min=HourSum[0]+HourSum[1];
    *minArrival=Hours[0];
    *minDepart=Hours[1];
    for(i=1;i<size-1;i++){
        if (HourSum[i]+HourSum[i+1]<=min){//if two continious hours have less bands playing than min
            *minArrival=Hours[i];
            *minDepart=Hours[i+1];
            min=HourSum[i]+HourSum[i+1];
        }
    }
}

void MaxTime(int size, int HourSum[],float Hours[],float *maxArrival,float*maxDepart)
{
    int i,max=HourSum[0]+HourSum[1];
    *maxArrival=Hours[0];
    *maxDepart=Hours[1];
    for(i=1;i<size-1;i++){
        if (HourSum[i]+HourSum[i+1]>=max){ //if two continious hours have more bands playing than max
            *maxArrival=Hours[i];
            *maxDepart=Hours[i+1];
            max=HourSum[i]+HourSum[i+1];
        }
    }
}

void CalcBestTime(int size, float CelebTime[][COL],float Hours[H],int HourSum[H])
{
    int i,j;
    for(i=0;i<size;i++){

        for(j=0;j<H;j++){
            if (CelebTime[i][0]<=Hours[j]&&CelebTime[i][1]>Hours[j]){
                HourSum[j]++; // an h wra Hours[] vriskete anamesa sthn wra tis bandas ++ to HourSum
        }
    }
}
}

void ReadArray(int size,char CelebName[][N],float CelebTime[][COL])
{
    int i;
    printf("Name the bands that will be attending and the time they will arrive and leave!\n");
    for(i=0;i<size;i++){
        printf("Band Name: ");
        fgets(CelebName[i], N, stdin); //fgets reads the name px Metallica\n\o
        CelebName[i][strcspn(CelebName[i], "\n")] = 0; //strcspn cleans the \n so when i print it doesnt change lines
        printf("Enter Arrival/Departure for %s: ", CelebName[i]);
        scanf("%f %f",&CelebTime[i][0],&CelebTime[i][1]); //scanf reads px 18.0 20.0\n
        while (getchar() != '\n');//here it doesnt take the \n from above and keeps the numbers
    }
}

void PrintArray(int size,char CelebName[][N],float CelebTime[][COL])
{
    int i;
     printf("%s %20s %20s\n","Band","Arrival","Departure");
    for(i=0;i<size;i++){
        printf("%s %15.2f %15.2f\n",CelebName[i],CelebTime[i][0],CelebTime[i][1]);
    }
}
