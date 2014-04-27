#include "Main.hpp"

int main()
{

Log *logger = new LogTcp("192.168.0.255");
logger->open();
logger->write("asd");
logger->write("ok");
    std::cout << "Starting the Parser.." << std::endl;
    yyin = fopen("./Parser_XML/input_text.xml","r");
    yyparse();

    std::cout << "Parser ended - GET " << n_point << " elements" << std::endl;

    /* DEBUG AREA */
    char c;
    int j = 0;
    do {
        if(j++ == 0) //just one
            std::cout << "Press ENTER to start" << std::endl;
        c = getchar();
    } while(c != '\n');
    

    NodeHandler *nh = new NodeHandler(headList); 

    
    

    std::cout << "_________________" << std::endl;
    nh->start();

    std::cout << "_________________\nEND_PROCCESS" << std::endl;
    delete nh;
    //Deallocate memory used by the chain
    deallocate();
    logger->write("Fine");
    logger->close();
    return EXIT_SUCCESS;
}


