#include <stdio.h>
#include <stdlib.h>

int max = 9;


int main(){
	FILE* f;
	char* arrow[max]; 
	arrow[0] = "NOPE";
	arrow[1] = "UP";
	arrow[2] = "DOWN";
	arrow[3] = "LEFT";
	arrow[4] = "RIGHT";
	arrow[5] = "UP_LEFT";
	arrow[6] = "UP_RIGHT";
	arrow[7] = "DOWN_LEFT";
	arrow[8] = "DOWN_RIGHT";

	f = fopen("automata.dot","w+");
	//Init DOT structure
	fprintf(f, "digraph finite_state_machine {\n\trankdir=LR;\n\tsize=\"6,5\" \n\tnode [shape = circle];\n");
	int i,j;
	for(i = 1; i<max; i++){
		for(j=1; j<max; j++){
			if(i==j) continue;
			fprintf(f, "\n\t%s -> %s [ label = \"\" ];", arrow[i], arrow[j]);
		}
	}
	//End DOT structure
	fprintf(f, "\n}");
}