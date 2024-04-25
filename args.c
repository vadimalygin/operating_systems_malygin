#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	printf("Kolichestvo parametrov, peredannykh programme %d\n", argc);

	for(int i=0 ; i<argc; i++) {
		printf("Parametr %d: %s\n", i, argv[i]);
	}

	int j=0;
	while(envp[j]!=NULL){
		printf("Parametr okruzheniya %d: %s\n", j, envp[j]);
		j++;
	}
	return 0;
}
