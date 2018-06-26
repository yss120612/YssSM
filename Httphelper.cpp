#include "Httphelper.h"
#include <FS.h>
namespace web_handlers {
	ESP8266WebServer * server;
	Config * conf;

	boolean handleFileRead(String path) {

		if (path.endsWith("/")) path += "index.htm";
		String contentType;
		if (path.endsWith(".htm") || path.endsWith(".html")) contentType = "text/html";
		else if (path.endsWith(".css")) contentType = "text/css";
		else if (path.endsWith(".js")) contentType = "application/javascript";
		else if (path.endsWith(".png")) contentType = "image/png";
		else if (path.endsWith(".gif")) contentType = "image/gif";
		else if (path.endsWith(".jpg")) contentType = "image/jpeg";
		else if (path.endsWith(".ico")) contentType = "image/x-icon";
		else if (path.endsWith(".xml")) contentType = "text/xml";
		else if (path.endsWith(".pdf")) contentType = "application/x-pdf";
		else if (path.endsWith(".zip")) contentType = "application/x-zip";
		else if (path.endsWith(".gz")) contentType = "application/x-gzip";
		else if (path.endsWith(".json")) contentType = "application/json";
		else contentType = "text/plain";

		//split filepath and extension
		String prefix = path, ext = "";
		int lastPeriod = path.lastIndexOf('.');
		if (lastPeriod >= 0) {
			prefix = path.substring(0, lastPeriod);
			ext = path.substring(lastPeriod);
		}

		//look for smaller versions of file
		//minified file, good (myscript.min.js)
		if (SPIFFS.exists(prefix + ".min" + ext)) path = prefix + ".min" + ext;
		//gzipped file, better (myscript.js.gz)
		if (SPIFFS.exists(prefix + ext + ".gz")) path = prefix + ext + ".gz";
		//min and gzipped file, best (myscript.min.js.gz)
		if (SPIFFS.exists(prefix + ".min" + ext + ".gz")) path = prefix + ".min" + ext + ".gz";

		if (SPIFFS.exists(path)) {

			File file = SPIFFS.open(path, "r");
			//if (server->hasArg())
				if (server->hasArg("download"))
					server->sendHeader("Content-Disposition", " attachment;");
			if (server->uri().indexOf("nocache") < 0)
				server->sendHeader("Cache-Control", " max-age=172800");

			//optional alt arg (encoded url), server sends redirect to file on the web
			//if (WiFi.status() == WL_CONNECTED && ESP8266WebServer::hasArg("alt")) {
			//	ESP8266WebServer::sendHeader("Location", ESP8266WebServer::arg("alt"), true);
			//	ESP8266WebServer::send(302, "text/plain", "");
			//}
			//else {
			//	//server sends file
			//	size_t sent = ESP8266WebServer::streamFile(file, contentType);
			//}
			size_t sent = server->streamFile(file, contentType);
			file.close();
			return true;
		} //if SPIFFS.exists
		return false;
	} //bool handleFileRead



	void root() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		//server->send(200, "text/plain", "Login OK");
		handleFileRead("/");
	}

	void page1() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		server->send(200, "text/plain", "Login OK on Page1");
	}


	void pageUpdate() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		String resp = "<html>\n<head>\n";
			resp += "<meta charset = \"utf-8\">\n";
			resp += "<title>YssSM прошивка</title>\n";
			resp += "<meta name = \"description\" content = \"Версия 0.1\">\n";
			resp += "<meta name = \"author\" content = \"Yss\">\n";
			resp += "<link href = \"bootstrap.min.css\" rel = \"stylesheet\">\n";
			resp += "<script type = \"text/javascript\" src = \"jquery.min.js\"></script>\n";
			resp += "<script type = \"text/javascript\" src = \"bootstrap.min.js\"></script>\n";
		//<script type = "text/javascript" src = "/dygraph.min.js">< / script>
		resp += "</head>\n<body>\n";
		resp += "<h2>Прошивка и веб сервер</h2>";
			resp += "<form method = \"POST\" action = \"/update?cmd=0\" enctype = \"multipart/form-data\">";
				resp += "<div class = \"btn - group\">";
				resp += "<input type = \"file\" class = \"btn btn-success\" name = \"update\" style = \"height: 38px;\">";
				resp += "<input type = \"submit\" class = \"btn btn-default active\" value = \"Прошивка\" onclick = \"this.value = 'Подождите...';\" style = \"height: 38px; \">";
				resp += "</div>";
			resp += "</form>";

			resp += "<form method = \"POST\" action = \"/update?cmd=100\" enctype = \"multipart/form-data\">";
			resp += "<div class = \"btn-group\">";
			resp += "<input type = \"file\" class = \"btn btn-success\" name = \"update\" style = \"height: 38px;\">";
			resp += "<input type = \"submit\" class = \"btn btn-default active\" value = \"Сервер\" onclick = \"this.value = 'Подождите...';\" style = \"height: 38px; \">";
			resp += "</div>";
			resp += "</form>";
		resp += "</body></html>\n";
		server->send(200, "text/html", resp);
	}

}

HttpHelper::HttpHelper(Config *c)
{
	server = new ESP8266WebServer(80);
	conf = c;
}

HttpHelper::~HttpHelper()
{
	delete httpUpdater;
	delete server;
}

//void HttpHelper::setMode(Mode * m) {
//	currentMode = m;
//}
//Mode * HttpHelper::getMode() {
//	return currentMode;
//}

void HttpHelper::setup() {
	//ArduinoOTA.begin();
	if (server == NULL) return;
	web_handlers::conf = conf;
	web_handlers::server = server;
	//root = web_handlers::root;
	//page1 = web_handlers::page1;

	server->on("/", web_handlers::root);

	server->on("/aaa", web_handlers::page1);

	server->on("/update", web_handlers::pageUpdate);
	
	server->begin();

	httpUpdater = new ESP8266HTTPUpdateServer();
	httpUpdater->setup(server);

}


void HttpHelper::clientHandle() {
	if (server!=NULL) server->handleClient();
	//ArduinoOTA.handle();
}








