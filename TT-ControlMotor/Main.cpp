#include "Main.hpp"

void helper();
inline bool existsFile(const std::string& name);

int main(int argc, char** argv)
{
    //Init Wiring Library
    wiringPiSetup();
    //Param Declaration and Default
    string input_file;
    string address = "TT-FFX-Butterfly.log";
    int port_number = 15150;
    bool udp = false;
    bool port = false;
    bool file = true;

    //Check Param
    if (argc < 2) {
        helper();
        return 0;
    }

    //Get Input File Name
    input_file = argv[1];
    if(!existsFile(input_file)){
        std::cerr << "Input file { " << input_file << " } doesn't exists!" << std::endl;
        return 0;
    }
    //check other option
    int i = 2;
    while( i < argc){
        if(strcmp(argv[i],"-lUDP") == 0){
            if(i+1 < argc){
                address = argv[i+1];
                udp = true;
                file = false;
            }
            else{
                std::cerr << "Missing address for option -lUDP"<< std::endl;
                helper();
                return 0;
            }
        }
        else if(strcmp(argv[i],"-lFile") == 0){
            if(i+1 < argc){
                address = argv[i+1];
                udp = false;
                file = true;
            }
            else{
                std::cerr << "Missing file_name for option -lFile"<< std::endl;
                helper();
                return 0;
            }
        }
        else if(strcmp(argv[i],"-port") == 0){
            if(i+1 < argc){
                port = true;
                port_number = atoi(argv[i+1]);
            }
            else{
                std::cerr << "Missing port_number for option -port"<< std::endl;
                helper();
                return 0;
            }
        }
        i++;
    }
    //Check incompatible configuration
    if(port && !udp){
        std::cerr << "Option -port can be used only with -lUDP option active"<< std::endl;
        helper();
        return 0;
    }

    //DEBUG PARAMETER
    fprintf(stderr, "Input:%s\nUDP: %d\nFILE:%d\nAddress:%s\nPort:%d\n",input_file.c_str(),udp,file,address.c_str(),port_number);

    //OPEN LOGGER
    Log *logger;
    if(udp){
        logger = new LogUDP(address,port_number);
    }
    else{
        logger = new LogFile(address);
    }
    logger->open();

    std::cout << "Starting the Parser.." << std::endl;
    yyin = fopen(input_file.c_str(),"r");
    yyparse();
    std::cout << "Parser ended - GET " << n_point << " elements" << std::endl;
    
    /* DEBUG AREA */
    char c;
    int j = 0;
    do {

        if(j++ == 0) //just one
            fprintf(stderr,"%d-Press ENTER to start",j); 
        c = getchar();
    } while(c != '\n'); 

    //Init Structure
    NodeHandler *nh = new NodeHandler(headList,logger); 
    std::cout << ".::Init::." << std::endl;
    //Start everything
    nh->start();
    std::cout << ".::End::.\n" << std::endl;
    delete nh;
    //Deallocate memory used by the chain
    deallocate();
    //Close the logger
    logger->close();
    return EXIT_SUCCESS;
}


void helper(){
    std::cerr << "Usage:: TT-FFX-Butterfly file_name [-lUDP address | -lFile output_name] [-port port_number]" << std::endl << std::endl;
}

inline bool existsFile(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

