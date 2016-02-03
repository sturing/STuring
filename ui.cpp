#include "ui.h"

UI::UI(QObject *parent) : QObject(parent)
{
    tmLine = new QLineEdit();
    tmRunBtn = new QPushButton("Пуск");
    tmStopBtn = new QPushButton("Стоп");
    tmSrc = new QTextEdit();
    infoLbl = new QLabel("");
    speedSlider = new QSlider(Qt::Horizontal);
    speedLbl = new QLabel("Скорость: ");

    upLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    downLayout = new QHBoxLayout();
    upLayout->setSpacing(3);
    upLayout->addWidget(tmLine);
    upLayout->addWidget(tmRunBtn);
    upLayout->addWidget(tmStopBtn);

    downLayout->addWidget(infoLbl);
    downLayout->addWidget(speedLbl, 0, Qt::AlignRight);
    downLayout->addWidget(speedSlider);

    speedSlider->setValue(50);
    speedSlider->setMaximumWidth(250);
    speedSlider->setMinimumWidth(60);

    fontLine.setPointSize(14);
    fontLine.setFamily("Monospace");
    fontSrc.setFamily("Monospace");
    fontLine.setStyleHint(QFont::TypeWriter);
    fontSrc.setStyleHint(QFont::TypeWriter);
    fontSrc.setPointSize(12);
    fontLbl.setFamily("Monospace");
    fontLbl.setStyleHint(QFont::TypeWriter);
    fontLbl.setPointSize(12);
    tmLine->setFont(fontLine);
    tmSrc->setFont(fontSrc);
    infoLbl->setFont(fontLbl);

    mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(3);
    mainLayout->setMargin(3);
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(tmSrc);
    mainLayout->addLayout(downLayout);

    downLayout->setMargin(3);
    downLayout->setSpacing(5);
    speedLbl->setFont(fontLbl);

    tmStopBtn->setEnabled(false);
    setSrcSize();

    icon.addFile(":/ico");

    mainWindow.setLayout(mainLayout);
    mainWindow.setWindowTitle("STuring - v3.0 Milestone 1");
    mainWindow.setWindowIcon(icon);

    mainWindow.show();

    QObject::connect(tmSrc, SIGNAL(textChanged()), this, SLOT(setSrcSize()));
}

void UI::setSrcSize() {
    QString str = "Символы: ";

    int numChars = tmSrc->document()->characterCount() - 1;
    QString numCharsS = QString::number(numChars);

    str += numCharsS;
    str += "; Строки: ";

    int numStrings = tmSrc->document()->lineCount();
    QString numStringsS = QString::number(numStrings);

    str += numStringsS;
    str += ".";

    infoLbl->setText(str);
}

void UI::setPointer(int n) {
    tmLine->setSelection(n, 1);
}

void UI::setLine(string s) {
    tmLine->setText(QString::fromStdString(s));
}
