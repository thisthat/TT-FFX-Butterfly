%{
#define YYSTYPE char*
#define YYSTYPE_IS_DECLARED 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Point.h"

//void yyerror (YYLTYPE *locp, char const *s);
void yyerror(char const *s);
void generateNodePoint(char* const xml_node,char* const xml_value);
void deallocate();

//Used by the rule that looking whenever a node is a butterfly
int flag = 0;

struct listPoint *headList;
struct listPoint *tailList;
struct point *lastPoint;
%}

%start xml

%token VALUE
%token OPEN 
%token CLOSE
%token SLASH
%token OPTION
%token OPEN_HEADER
%token CLOSE_HEADER
%token QUOTE
%token EQUAL
%%

xml:	OPEN_HEADER  version encoding CLOSE_HEADER root { };

version : VALUE EQUAL QUOTE VALUE QUOTE {};
encoding : VALUE EQUAL QUOTE VALUE QUOTE {};

root :	OPEN VALUE CLOSE listPoint OPEN SLASH VALUE CLOSE { }

listPoint :	point { }
		  |	listPoint point { }

point : OPEN VALUE optFlag VALUE OPEN SLASH VALUE CLOSE { generateNodePoint($2,$4);  }

optFlag : CLOSE {flag = 0;}
		| VALUE EQUAL QUOTE VALUE QUOTE CLOSE { flag = 1;}
		

%%

//int main () {

//	yyparse(); //Parsing the < file
	/* DEBUG AREA */
	/*
	struct listPoint *h = headList;
	int i = 0;
	while(h != NULL){
		fprintf(stderr, "element %d\n\tisButterfly: %d\n\tvalue: %d\n",++i,h->point->butterfly,h->point->arrow);
		h = h->next;
	}
	*/
	/* END DEBUG AREA */
//}


void yyerror (char const *s){
	fprintf(stderr,"Errore in linea %d dal carattere %d al %d\n %d-%s\n", yylloc.line,yylloc.first_column, yylloc.last_column,yychar,s);
}

void generateNodePoint(char* const xml_node,char* const xml_value){
	if(strcmp(xml_node,"position") == 0){
		return;
	}
	if(strcmp(xml_node,"point") != 0){
		return;
	}
	if(headList != NULL){
		//There is at least an element
		lastPoint = malloc(sizeof (struct point));
		lastPoint->arrow = atoi(xml_value);
		lastPoint->butterfly = flag;
		lastPoint->position = yylloc;
		struct listPoint *tmp;
		tmp = malloc(sizeof (struct listPoint));
		tmp->point = lastPoint;
		tmp->next = NULL;
		tailList->next = tmp;
		tailList = tmp;
	}
	else{
		//We don't have anything
		headList = malloc(sizeof (struct listPoint));
		lastPoint = malloc(sizeof (struct point));
		lastPoint->arrow = atoi(xml_value);
		lastPoint->butterfly = flag;
		lastPoint->position = yylloc;
		headList->point = lastPoint;
		headList->next = NULL;
		tailList = headList;
	}
}

void deallocate(){
	struct listPoint *h = headList;
	struct listPoint *tmp;
	int i = 0;
	while(h != NULL){
		tmp = h;
		free(h->point);
		h = h->next;
	}
	free(headList);
	free(h);
}



