#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QtWidgets>

class Settings : public QObject
{
    Q_OBJECT
private:
    QWidget* settingsWindow;
    QSettings* settings;
    QString recentPath;
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    void showSettings();
    void saveRecentFileSettings(QString path);
signals:
    void setRecentPath(QString);
public slots:
    QString getRecentPath();
};

#endif // SETTINGS_H
