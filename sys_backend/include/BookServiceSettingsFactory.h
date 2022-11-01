#pragma once

#include "IServiceSettingsFactory.h"

class BookServiceSettingsFactory : public IServiceSettingsFactory {

public:

    BookServiceSettingsFactory();
    shared_ptr<Settings> get_settings() const final;

private:

    std::shared_ptr<Settings> _settings;

};