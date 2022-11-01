#pragma once

#include "IService.h"

#include "IResourceFactory.h"
#include "IServiceSettingsFactory.h"

class BookService : public IService {

public:

    BookService(
        shared_ptr<IResourceFactory> resource_factory, 
        shared_ptr<IServiceSettingsFactory> settings_factory);
    void start() final;

private:

    Service _service;
    shared_ptr<IServiceSettingsFactory> _settings_factory;

};