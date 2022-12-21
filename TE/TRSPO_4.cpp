#include "mpi.h"
#include <iostream>

int N = 100000000;

void checkIfPass(const double& x,const double&y, int& counter);
double MonteCarlo(double* points, const int& n) ;
void sendToOther(const int& data, void* data_pi, const int& destination);
void sendToMain(const double &data_time, const double& data_pi);
void customCount(double* currentPoints,const int& countOfPoints);
void fillProcessSrc(const int& processCount,const int& basicDotsSet);
void showProcessResults(const int& processCount);
void calculations();

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int processCount, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bool isProcessMain = rank == 0 ? true: false;

    if (isProcessMain) {
        int basicDotsSet = N / processCount;
        fillProcessSrc(processCount, basicDotsSet);
        showProcessResults(processCount);
    }
    else {
        calculations();
    }
    MPI_Finalize();
}

double MonteCarlo(double* points, const int &n) {
    int counter = 0;
    for (int i = 0; i < n; i+=2) {
        checkIfPass(points[i], points[i+1], counter);
    }
    return (double)8 * counter / n;
}

void checkIfPass(const double &x, const double &y, int& counter){
    if (x * x + y * y <= 1) {
        counter++;
    }
}

void customCount(double* currentPoints, const int &countOfPoints){
    clock_t start = clock();
    double currentPi = MonteCarlo(currentPoints, countOfPoints);
    clock_t end = clock();
    double time = double(end - start) / CLOCKS_PER_SEC;
    sendToMain(time, currentPi);
}

void sendToMain(const double &data_time, const double &data_pi){
    MPI_Send(&data_time, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&data_pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
}

void sendToOther(const int &data, void* data_pi, const int &destination){
    MPI_Send(&data, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
    MPI_Send(data_pi, data, MPI_DOUBLE, destination, 0, MPI_COMM_WORLD);
}

void fillProcessSrc(const int &processCount, const int &basicDotsSet){
    for (int i = 1; i < processCount; i++) {
        int setCapacity = basicDotsSet * i;
        double* pointsSet = new double[setCapacity];
        for (int i = 0; i < setCapacity; i++) {
            pointsSet[i] = (double)rand() / RAND_MAX;
        }
        sendToOther(setCapacity, pointsSet, i);
        delete[] pointsSet;
    }
}

void showProcessResults(const int &processCount){
    for (int i = 1; i < processCount; i++) {
        double time;
        MPI_Recv(&time, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double pi;
        MPI_Recv(&pi, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Thread в„–" << i << "\t|runtime: " << time <<"\t|pi: " << pi << std::endl;
    }
}

void calculations(){
    int capacitySet;
    MPI_Recv(&capacitySet, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    double* pointsSet = new double[capacitySet];
    MPI_Recv(pointsSet, capacitySet, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    customCount(pointsSet, capacitySet);
    delete[] pointsSet;
}
