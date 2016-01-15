#include <csignal>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include <enet/enet.h>

using namespace std;

bool forever = true;
const auto simulationTickInterval = 1000000 / 60;
ENetHost * server;


void destroy(int sig)
{
	cout << "shutting down - goodbye. code=" << sig <<endl;
    enet_host_destroy(server);
    enet_deinitialize();
	forever = false;
}

void printArgs(int argc, char ** argv){
  cout << "The name used to start the program: " << argv[ 0 ]
       << "\nArguments are:\n";
  for (int n = 1; n < argc; n++)
    cout << " " << n << ": " << argv[ n ] << '\n';
 
}

int main (int argc, char ** argv) 
{
	typedef chrono::high_resolution_clock Clock;
	//enet vars
	int is_enet_success = 0;
	ENetAddress address;
	ENetEvent event;
	int eventStatus;

	printArgs(argc, argv);

	//init
    signal(SIGABRT, &destroy);
	signal(SIGTERM, &destroy);
	signal(SIGINT, &destroy);

	auto lastFrameTime = Clock::now();

	is_enet_success = enet_initialize();

	//enet_address_set_host (& address, "x.x.x.x"); //A specific host address can be specified by
    address.host = ENET_HOST_ANY; 					//Bind the server to the default localhost.   
	address.port = 33333; 							

	server = enet_host_create( &address, 32, 2, 0, 0 );

    //handle init errors

    if( is_enet_success != 0)
    {
        cerr << "An error occurred while initializing ENet." << endl;

    }
    if( server == NULL )
    {
        cerr << "An error occurred while creating ENet Host." << endl;

    }

    //simulation
    while(forever)
    {
		auto currFrameTick = Clock::now();

		if( chrono::duration_cast<chrono::microseconds>(currFrameTick - lastFrameTime).count() >= simulationTickInterval  )
		{
			cout << ".";
			cout.flush();
			lastFrameTime = Clock::now();

			eventStatus = enet_host_service(server, &event, 0);

	        // If we had some event that interested us
        	string temp = "test";

			if(eventStatus != 0){
	            switch(event.type) {
	                case ENET_EVENT_TYPE_CONNECT:
	                    cout	<< endl 
								<< "(Server) We got a new connection from " << event.peer->address.host	
								<< endl;
	                    //event.peer -> data = (void *)temp.c_str();
	                    break;

	                case ENET_EVENT_TYPE_RECEIVE:
	                    cout	<< endl << "(Server) Message from client : " << event.peer->data << endl
								<< "on channel: " << event.channelID << endl
								<< "with event.data: " << event.data << endl
								<< "packet.data: " << event.packet->data
								<< endl;
						
	                    // Lets broadcast this message to all
	                    //enet_host_broadcast(server, 0, event.packet);
						enet_packet_destroy (event.packet);
	                    break;

	                case ENET_EVENT_TYPE_DISCONNECT:
	                    cout << event.peer->data << " disconnected." << endl;

	                    // Reset client's information
	                    event.peer->data = NULL;
	                    break;
	                case ENET_EVENT_TYPE_NONE:
	                    break;
	            }
			}
		}
    }

}