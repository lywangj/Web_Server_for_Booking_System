#include "BookServiceSettingsFactory.h"

BookServiceSettingsFactory::BookServiceSettingsFactory() {
    _settings = make_shared<Settings>();
    _settings->set_port(8080);
    _settings->set_default_header("Connection", "close");
    _settings->set_default_header( "Access-Control-Allow-Origin", "*");
}

shared_ptr<Settings> BookServiceSettingsFactory::get_settings() const {
    return _settings;
}
