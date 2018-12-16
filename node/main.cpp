/*
 * main.cpp
 *
 * 1. int main | A simple terminal for user to input port number
 * 2. int initServer Z| Create the server listening connection
 * 3. static void ev_handler | Serve static html files
 *
 */

// Include Mongoose
#include "mongoose.h"
#include <string>
#include <iostream>

// Struct containing Mongoose HTTP settings
static struct mg_serve_http_opts s_http_server_opts;

// Event handler
static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	// if event is a http request
	if(ev == MG_EV_HTTP_REQUEST) {
		// Serve static html files
		mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
	}
}

int initServer(int port) {

	// Mongoose event manager
	struct mg_mgr mgr;
	// Mongoose connection
	struct mg_connection *nc;

	// Convert port to char
	std::string portToChar = std::to_string(port);
	static char const *sPort = portToChar.c_str();

	// Initialise Mongoose
	mg_mgr_init(&mgr, NULL);
	std::cout << "Starting web server on port " << sPort << std::endl;

	nc = mg_bind(&mgr, sPort, ev_handler);

	// If the connection fails
	if(nc == NULL) {
		std::cout << "Failed to create listener" << std::endl;
		return 1;
	}

	// Set up HTTP server options
	mg_set_protocol_http_websocket(nc);

	s_http_server_opts.document_root = ".";
	s_http_server_opts.enable_directory_listing = "yes";

	for(;;) {
		mg_mgr_poll(&mgr, 1000);
	}

	// Free up memory
	mg_mgr_free(&mgr);

	return 0;
}

int main() {

	int port;
	std::cout << "Enter port number: " << std::endl;

	std::cin >> port;

	initServer(port);

	return 0;
}




