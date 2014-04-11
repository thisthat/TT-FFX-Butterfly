struct YYPOS{
	int line;
	int first_column;
	int last_column;
} yylloc;

typedef struct YYPOS YYPOS;

int yylex(void);

//Struct for every point
struct point {
	int arrow;
	int butterfly;
	YYPOS position; //For reference util during the built file process
};
struct listPoint
{
	struct point *point;
	struct listPoint *next;
};