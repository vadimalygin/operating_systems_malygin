#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
	int *array;
	int shmid;
	int new = 1;
	char pathname[] = "fifo.c";
	key_t key;

	if((key = ftok(pathname, 0)) < 0) {
		printf("Ne udalos sgenerirovat ipc-kluch\n");
		exit(-1);
	}

	if((shmid = shmget(key, 3*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
		if(errno != EEXIST) {
			printf("Ne udalos sozdat segment razdelyaemoi pamyati\n");
			exit(-1);
		} else {
			if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
				printf("Ne udaetsya naiti segment razdelyaemoi pamyati\n");
				exit(-1);
			}
			new = 0;
		}
	if ((array = (int*)shmat(shmid, NULL, 0)) == (int*)(-1)){
		printf("Ne udalos prisoedinit segment razdelyaemoi pamyati k adresnomu prostranstvu processa\n");
		exit(-1);
	}
	if(new){
		array[0] = 1;
		array[1] = 0;
		array[2] = 1;
	} else {
		array[0] += 1;
		array[2] += 1;
	}
	printf("Programma 1 byla zapushena %d raz, a obshee kol-vo zapuskov obeih programm: %d\n", array[0], array[2]);
	if(shmdt(array) < 0){
		printf("Ne udalos udalit segment razdelyaemoi pamyati iz adresnogo prostranstva tekuschego processa\n");
		exit(-1);
	}
	}
	return 0;
}
