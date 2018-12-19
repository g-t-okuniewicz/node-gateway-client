#include "mongoose.h"
#include <iostream>
#include <ctime>
#include <unistd.h>

static const char *url = "localhost:8080/sendreading";

static void ev_handler(struct mg_connection *c, int ev, void *p) {

	/*
	 * Error handling
	 * A successful connection generates the following events:
	 * MG_EV_POLL, MG_EV_CONNECT, MG_EV_SEND, and MG_EV_CLOSE
	 * If the connection fails MG_EV_SEND is not generated.
	 */

	//std::cout << "Event: " << ev << std::endl;

	static bool data_sent = false;

	if(ev == MG_EV_SEND)
		data_sent = true;

	if(ev == MG_EV_CLOSE && !data_sent) {
		std::cout << "Connection failed, no data sent. Check your URL and make sure the server is online" << std::endl;
		exit(1);
	} else if (ev == MG_EV_CLOSE && data_sent) {
		std::cout << "Data sent" << std::endl;
		data_sent = false;
	}
}

int main() {
	struct mg_mgr mgr;

	std::cout << "Starting the node" << std::endl;

	while(1) {

		//float reading = ((float) rand()) / (float) 50;
		float reading = -30 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(70)));
		std::cout << "Temperature: " << reading << std::endl;

		time_t now = time(0);
		tm *ltm = localtime(&now);

		char timestamp[8];
		sprintf(timestamp,
				"%d:%d:%02d",
				ltm->tm_hour,
				ltm->tm_min,
				ltm->tm_sec);

		std::cout << "Time: " << timestamp << std::endl;

		char message[50];
		sprintf(message,
				"<reading><time>%s</time><temperature>%.1f</temperature></reading>",
				timestamp,
				reading);

		mg_mgr_init(&mgr, NULL);

		mg_connect_http(&mgr,
				ev_handler,
				url,
				"Content-Type: text/plain\r\n",
				message
				);

		mg_mgr_free(&mgr);
		usleep(3000000);
	}

	return 0;
}
