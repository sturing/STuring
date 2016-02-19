#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
   settingsWindow = new QWidget();
   settingsWindow->window()->setWindowTitle("STuring - Настройки");
   settings = new QSettings("settings.conf", QSettings::IniFormat);

   recentPath = settings->value("pathFile/recentFile", "").toString();

   emit setRecentPath(recentPath);
}

QString Settings::getRecentPath() {
    return recentPath;
}

Settings::~Settings()
{
   delete settingsWindow;
}

void Settings::showSettings() {
    settingsWindow->show();
}

void Settings::saveRecentFileSettings(QString path) {
    settings->setValue("pathFile/recentFile", path);
    settings->sync();
}
