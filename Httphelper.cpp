#include "Httphelper.h"
namespace web_handlers {
	ESP8266WebServer * server;
	Config * conf;

	void root() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		server->send(200, "text/plain", "Login OK");
	}

	void page1() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		server->send(200, "text/plain", "Login OK on Page1");
	}
}

HttpHelper::HttpHelper(Config *c)
{
	server = new ESP8266WebServer(80);
	conf = c;
}

HttpHelper::~HttpHelper()
{
	delete server;
}

void HttpHelper::setup() {
	ArduinoOTA.begin();
	if (server == NULL) return;
	web_handlers::conf = conf;
	web_handlers::server = server;
	root = web_handlers::root;
	page1 = web_handlers::page1;

	server->on("/", root);

	server->on("/aaa", page1);

	
	server->begin();
}


void HttpHelper::clientHandle() {
	if (server!=NULL) server->handleClient();
	ArduinoOTA.begin();
}






