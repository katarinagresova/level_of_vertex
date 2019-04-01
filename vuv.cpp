#include <mpi.h>
#include <cmath>

using namespace std;

bool is_forward(int myid, int vertices) {
	return myid < vertices;
}
bool is_leaf(int myid, int vertices) {
    return myid >= vertices/2 && myid < vertices;
}

bool has_right(int myid, int vertices) {
    return myid >= vertices && ((myid - vertices) % 2 == 0) && (myid < 2 * vertices - 2);
}

/**
 * Main function
 * @param argc number of arguments on command line
 * @param argv "array" of arguments
 * @return 0 if success, 1 otherwise
 */
int main(int argc, char *argv[]) {

	int numprocs;               // number of procesors
	unsigned numberOfLeafs;     // number of leaf processors
	int myid;                   // my rank
	int vertices;         		// number of vertices
	int mynumber;               // my value
	int* etour;
	MPI_Status stat;            // struct- contains kod- source, tag, error

	//MPI INIT
	MPI_Init(&argc,&argv);                          // MPI init
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // get number of running processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // get rank of my process

	if (strlen(argv[1]) == 1) {
		if (myid == 0) {
			cout << argv[1][0] << ":0" << endl;
		}
		MPI_Finalize(); 
		return 0;
	} else if(strlen(argv[1]) == 2) {
		if (myid == 0) {
			cout << argv[1][0] << ":0," << argv[1][1] << ":1" << endl;
		}
		MPI_Finalize(); 
		return 0;
	}

	vertices = (numprocs + 2) / 2;
	int weight;
	etour = new int[numprocs];

	// Lets count from 1
	myid++;

	// mark forward and retreat edges
	if (is_forward(myid, vertices)) {
		weight = -1;
	} else {
		weight = 1;
	}

	int* arr_weights = new int[numprocs];
	MPI_Allgather(&weight, 1, MPI_INT, arr_weights, 1, MPI_INT, MPI_COMM_WORLD);

	// compute Etour
	int next_value;
	if (is_forward(myid, vertices)) {
		if (is_leaf(myid, vertices)) {
			next_value = vertices + myid - 1;
		} else {
			next_value = 2 * myid + 1;
		} 
	} else {
		if (has_right(myid, vertices)) {
            next_value = myid - vertices + 2;
		} else {
            next_value = (vertices - 2) / 2 + (myid / 2);
		}
	}
  
    // handle root
    if (myid == vertices + 1) {
        next_value = myid;
    }
    next_value--;
    myid--;

    // distribute Etour info among all processors
    MPI_Allgather(&next_value, 1, MPI_INT, etour, 1, MPI_INT, MPI_COMM_WORLD);

    int suffix;
    int position3;
    int* arr_final = new int[numprocs];
	if (etour[myid] == myid) {
    	suffix = 0;
    } else {
    	suffix = arr_weights[myid];
    }
    MPI_Allgather(&suffix, 1, MPI_INT, arr_final, 1, MPI_INT, MPI_COMM_WORLD);

    for (int k = 0; k < log2(numprocs); k++) {
	    suffix = arr_final[myid] + arr_final[etour[myid]];
	    position3 = etour[etour[myid]];

	    MPI_Allgather(&suffix, 1, MPI_INT, arr_final, 1, MPI_INT, MPI_COMM_WORLD);
	    MPI_Allgather(&position3, 1, MPI_INT, etour, 1, MPI_INT, MPI_COMM_WORLD);
    }	

    if (arr_weights[numprocs - 1] != 0) {
    	suffix = arr_final[myid] + arr_weights[numprocs - 1];
    }
    MPI_Allgather(&suffix, 1, MPI_INT, arr_final, 1, MPI_INT, MPI_COMM_WORLD);

    if (myid == 1) { 
    	cout << argv[1][0] << ":0,";
    	for (int i = 0; i < vertices - 2; i++) {
    		cout << argv[1][i + 1] << ":" << arr_final[i] + 1 << ",";
    	}
    	cout << argv[1][vertices - 1] << ":" << arr_final[vertices - 2] + 1 << endl;
    }	

	MPI_Finalize(); 
	return 0;
}