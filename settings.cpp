#include "settings.h"

Settings::Settings()
{

}

Settings::Settings_Set Settings::settings() const
{
    return m_currentSettings;
}
