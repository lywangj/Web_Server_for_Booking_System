#include "BookService.h"

BookService::BookService(
        shared_ptr<IResourceFactory> resource_factory, 
        shared_ptr<IServiceSettingsFactory> settings_factory) {
    _settings_factory = settings_factory;
    _service.publish(resource_factory->get_resource());
}

void BookService::start() {
    _service.start(_settings_factory->get_settings());
}
