#include "Httphelper.h"


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
	if (server == NULL) return;

	server->on("/", root);

	server->on("/aaa", page1);

	server->begin();
}


void HttpHelper::clientHandle() {
	if (server!=NULL) server->handleClient();
}

void HttpHelper::page1() {
	if (!server->authenticate(conf->getHttpU().c_str(),conf->getHttpP().c_str()))
		return server->requestAuthentication();
	server->send(200, "text/plain", "Login OK on Page1");
}


void HttpHelper::root() {
	if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
		return server->requestAuthentication();
	server->send(200, "text/plain", "Login OK");
}
