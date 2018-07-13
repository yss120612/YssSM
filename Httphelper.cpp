#include "Httphelper.h"
#include <FS.h>
#include  "Log.h"
#include  "Config.h"

namespace web_handlers {
	ESP8266WebServer * server;
	Config * conf;

	/*const char * beginHTML PROGMEM = "<!DOCTYPE html>
		<html lang = \"en\">\n
		<head>\n
		<meta charset = \"utf-8\">\n
		<title>Система автоматики Yss</title>\n
		<meta name = \"description\" content = \"Версия 0.1\">\n
		<meta name = \"author\" content = \"Yss\">\n
		<link href = \"bootstrap.min.css\" rel = \"stylesheet\" />\n
		<script type = \"text/javascript\" src = \"/jquery.min.js\"></script>\n
		<script type = \"text/javascript\" src = \"/bootstrap.min.js\"></script>\n
		</head>\n
		<body>\n";*/

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

		//server->send(200, "text/plain", SPIFFS.);
		return false;
	} //bool handleFileRead



	void root() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		//server->send(200, "text/plain", "Login OK");
		if (!handleFileRead("/")) {
			//server->send(200, "text/plain", "NOT FOUND!!!");
		}
	}

	void distill() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		//server->send(200, "text/plain", "Login OK");
		if (!handleFileRead("/distillation.htm")) {
			//server->send(200, "text/plain", "NOT FOUND!!!");
		}
	}


	void page1() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		//server->send(200, "text/plain", "Login OK on Page1");
		if (!handleFileRead("/distillator.png")) {
			//server->send(200, "text/plain", "NOT FOUND!!!");
		}
	}

	void log() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		
//		server->send(200, "text/plain",logg.getAll("\n"));
		
	}


	void restart()
	{
		String restart = server->arg("device");          // Получаем значение device из запроса
		if (restart == "ok")
		{                         // Если значение равно Ок
			server->send(200, "text/plain", "Reset OK"); // Oтправляем ответ Reset OK
			ESP.restart();                                // перезагружаем модуль
			
		}
		else
		{                                        // иначе
			server->send(200, "text/plain", ""); // Oтправляем ответ No Reset
		}
	}


	void pageUpdate() {
		if (!server->authenticate(conf->getHttpU().c_str(), conf->getHttpP().c_str()))
			return server->requestAuthentication();
		String resp = "<!DOCTYPE html>\n<html>\n<head>\n";
			resp += "<meta charset = \"utf-8\">\n";
			resp += "<title>YssSM прошивка</title>\n";
			resp += "<meta name = \"description\" content = \"Версия 0.1\">\n";
			resp += "<meta name = \"author\" content = \"Yss\">\n";
			resp += "<link href = \"/css/bootstrap.min.css\" type = \"text/css\" rel = \"stylesheet\">\n";
			resp += "<script type = \"text/javascript\" src = \"/js/jquery.min.js\"></script>\n";
			resp += "<script type = \"text/javascript\" src = \"/js/bootstrap.min.js\"></script>\n";
			resp += "</head>\n<body>\n";
			resp += "<h2>Прошивка и веб сервер</h2>\n";
			resp += "<form method = \"POST\" action = \"/update?cmd=0\" enctype = \"multipart/form-data\">\n";
			resp += "<div class = \"btn - group\">\n";
			resp += "<input type = \"file\" class = \"btn btn-success\" name = \"update\" style = \"height: 38px;\">\n";
			resp += "<input type = \"submit\" class = \"btn btn-default active\" value = \"Прошивка\" onclick = \"this.value = 'Подождите...';\" style = \"height: 38px; \">\n";
			resp += "</div>\n";
			resp += "</form>\n";

			resp += "<form method = \"POST\" action = \"/update?cmd=100\" enctype = \"multipart/form-data\">";
			resp += "<div class = \"btn-group\">\n";
			resp += "<input type = \"file\" class = \"btn btn-success\" name = \"update\" style = \"height: 38px;\">\n";
			resp += "<input type = \"submit\" class = \"btn btn-default active\" value = \"Сервер\" onclick = \"this.value = 'Подождите...';\" style = \"height: 38px; \">\n";
			resp += "</div>\n";
			resp += "</form>\n";
			resp += "</body>\n</html>\n";

			server->send(200, "text/html", resp);
	}

}

HttpHelper::HttpHelper()
{
	server = new ESP8266WebServer(80);
	SPIFFS.begin();
}

HttpHelper::~HttpHelper()
{
	delete httpUpdater;
	delete server;
	SPIFFS.end();
}

//void HttpHelper::setMode(Mode * m) {
//	currentMode = m;
//}
//Mode * HttpHelper::getMode() {
//	return currentMode;
//}

void HttpHelper::setup() {
	if (server == NULL) return;

	web_handlers::conf = &CONF;

	web_handlers::server = server;

	server->on("/distill", web_handlers::distill);
	
	server->on("/", web_handlers::root);

	server->on("/pict", web_handlers::page1);

	server->on("/log", std::bind(&HttpHelper::handleLog, this, "Lof file:\n"));

	server->on("/restart", web_handlers::restart);

	//server->on("/update", web_handlers::pageUpdate);
	server->on("/update", std::bind(&HttpHelper::handleUpdate, this));

	server->serveStatic("/heater",SPIFFS,"/heater.htm", NULL);

	server->serveStatic("/css/bootstrap.min.css", SPIFFS, "/css/bootstrap.min.css", NULL);

	server->serveStatic("/js/bootstrap.min.js", SPIFFS, "/js/bootstrap.min.js", NULL);

	server->serveStatic("/js/jquery.min.js", SPIFFS, "/js/jquery.min.js", NULL);
	
	server->begin();

	httpUpdater = new ESP8266HTTPUpdateServer();
	httpUpdater->setup(server);

}

void HttpHelper::handleLog(String s)
{
	server->send(200, "text/plain", s+logg.getAll("\n"));
}

void HttpHelper::handleUpdate() {
	if (!server->authenticate(CONF.getHttpU().c_str(), CONF.getHttpP().c_str()))
		return server->requestAuthentication();
	String resp = "<!DOCTYPE html>\n<html>\n<head>\n";
	resp += "<meta charset = \"utf-8\">\n";
	resp += "<title>YssSM прошивка</title>\n";
	resp += "<meta name = \"description\" content = \"Версия 0.1\">\n";
	resp += "<meta name = \"author\" content = \"Yss\">\n";
	resp += "<link href = \"/css/bootstrap.min.css\" type = \"text/css\" rel = \"stylesheet\">\n";
	resp += "<script type = \"text/javascript\" src = \"/js/jquery.min.js\"></script>\n";
	resp += "<script type = \"text/javascript\" src = \"/js/bootstrap.min.js\"></script>\n";
	resp += "</head>\n<body>\n";
	resp += "<h2>Прошивка и веб сервер</h2>\n";
	resp += "<form method = \"POST\" action = \"/update?cmd=0\" enctype = \"multipart/form-data\">\n";
	resp += "<div class = \"btn - group\">\n";
	resp += "<input type = \"file\" class = \"btn btn-success\" name = \"update\" style = \"height: 38px;\">\n";
	resp += "<input type = \"submit\" class = \"btn btn-default active\" value = \"Прошивка\" onclick = \"this.value = 'Подождите...';\" style = \"height: 38px; \">\n";
	resp += "</div>\n";
	resp += "</form>\n";

	resp += "<form method = \"POST\" action = \"/update?cmd=100\" enctype = \"multipart/form-data\">";
	resp += "<div class = \"btn-group\">\n";
	resp += "<input type = \"file\" class = \"btn btn-success\" name = \"update\" style = \"height: 38px;\">\n";
	resp += "<input type = \"submit\" class = \"btn btn-default active\" value = \"Сервер\" onclick = \"this.value = 'Подождите...';\" style = \"height: 38px; \">\n";
	resp += "</div>\n";
	resp += "</form>\n";
	resp += "</body>\n</html>\n";

	server->send(200, "text/html", resp);
}

void HttpHelper::clientHandle() {
	if (server!=NULL) server->handleClient();
	//ArduinoOTA.handle();
}








