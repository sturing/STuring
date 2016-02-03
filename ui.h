#ifndef UI_H
#define UI_H

#include <QObject>
#include <QtWidgets>
#include <string>

using namespace std;

class UI : public QObject
{
    Q_OBJECT

public: //(пришлось сделать public. Пишите, как сделать так, чтобы все работало с инкапсуляцией)
    QIcon icon;
    QWidget mainWindow;
    QLineEdit* tmLine;
    QPushButton* tmRunBtn;
    QPushButton* tmStopBtn;
    QTextEdit* tmSrc;
    QHBoxLayout* upLayout;
    QVBoxLayout* mainLayout;
    QTime time;
    QHBoxLayout* downLayout;
    QLabel* infoLbl;
    QLabel* speedLbl;
    QFont fontLine, fontSrc, fontLbl;
    QSlider* speedSlider;
public:
    explicit UI(QObject *parent = 0);
signals:

public slots:
    void setSrcSize();
    void setPointer(int);
    void setLine(string);

};

#endif // UI_H
