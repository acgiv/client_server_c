#define MAX_BUFFER 1024 /// INIZIALIZE THE MAXIMUM BUFFER SIZE OF THE CLIENT AND SERVER

#define PORT_WELCOME_SERVER 60000 /// INIZIALIZE THE WELCOME PORT OF THE SERVER

#define ADDRESS_CLIENT_SERVER = "127.0.0.1" ///INIZIALIZE THE ADDRESS OF THE SERVER AND THE CLIENT

struct sockaddr_in sad; /// INIZIALIZATION OF THE STRUCT WHICH WILL CONTAIN THE INFORMATION OF THE SERVER

struct sockaddr_in cad; /// INIZIALIZATION OF THE STRUCT WHICH WILL CONTAIN THE INFORMATION OF THE SERVER

///INIZIALIZE THE STRUCT TO PASS THE OPERATION, NUMBER AND RESULT BETWEEN THE CLIENT AND SERVER

#define stuct msgStruct{ char operation int first_number int secondo_numero int result}

#define NO_ERROR 0 /// INIZIALIZE VARIABLE TO CHECK FOR ERROR

#define QLEN 5 /// MAX NUMBER OF CLIENTS THAT CAN REAMIN CONNECTED WITCH THE SERVER AT THE SAME TIME