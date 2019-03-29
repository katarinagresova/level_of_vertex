#include <mpi.h>

using namespace std;

/**
 *  * Main function
 *   * @param argc number of arguments on command line
 *    * @param argv "array" of arguments
 *     * @return 0 if success, 1 otherwise
 *      */
int main(int argc, char *argv[]) {

int numprocs;               // number of procesors
        unsigned numberOfLeafs;     // number of leaf processors
        int myid;                   // my rank
        unsigned inputSize;                 // number of input numbers
        int mynumber;               // my value
        unsigned msgSize;                       // size of leaf bucket
        vector<int> bucket;             // all values of this process
        MPI_Status stat;            // struct- contains kod- source, tag, error

        //MPI INIT
	MPI_Init(&argc,&argv);                          // MPI init
        MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // get number of running processes
        MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // get rank of my process
        
}
