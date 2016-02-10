#include "ui.h"

UI::UI(QApplication* app_, QObject *parent) : QObject(parent)
{
    programmNameString = "STuring v3.0 Beta 1";
    app = app_;
    fControl = new FileController();
    tmLine = new QLineEdit();
    tmRunBtn = new QPushButton("Пуск");
    tmStopBtn = new QPushButton("Стоп");
    clearHistoryBtn = new QPushButton("Очистить историю");
    tmSrc = new CodeEditor();
    infoLbl = new QLabel("");
    speedSlider = new QSlider(Qt::Horizontal);
    speedLbl = new QLabel("Скорость:");
    errorConsole = new QTextEdit();
    errorConsole->setReadOnly(true);

    maxSpeedLbl = new QLabel("Максимальная скорость:");
    maxSpeedCkb = new QCheckBox();

    upLayout = new QHBoxLayout();
    menuLayout = new QHBoxLayout();
    createActions();
    turingLayout = new QVBoxLayout();
    maxSpdLayout = new QHBoxLayout();

    downLayout = new QHBoxLayout();
    appLayout = new QHBoxLayout();
    appLayout->setSpacing(3);
    appLayout->setMargin(0);
    upLayout->setSpacing(3);
    upLayout->addWidget(tmLine);
    upLayout->addWidget(tmRunBtn);
    upLayout->addWidget(tmStopBtn);
    upLayout->addWidget(clearHistoryBtn);
    upLayout->setMargin(3);
    history = new History();
    rightLayout = new QVBoxLayout();
    rightLayout->setMargin(3);

    downLayout->addWidget(infoLbl);
    downLayout->addLayout(maxSpdLayout, Qt::AlignRight);
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
    maxSpeedLbl->setFont(fontLbl);

    turingLayout = new QVBoxLayout();
    turingLayout->setSpacing(3);
    turingLayout->setMargin(3);
    turingLayout->addWidget(tmSrc);
    appLayout->addLayout(turingLayout);
    historyCkbLayout = new QHBoxLayout();
    historyLbl = new QLabel("Данные из таблицы: ");
    historyCkb = new QCheckBox(false);
    historyCkbLayout->addWidget(historyLbl);
    historyCkbLayout->addWidget(historyCkb);
    historyCkbLayout->setAlignment(Qt::AlignLeft);
    rightLayout->addLayout(historyCkbLayout);
    errorLbl = new QLabel("Консоль ошибок:");
    rightLayout->addWidget(history);
    rightLayout->addWidget(errorLbl);
    rightLayout->addWidget(errorConsole);
    errorConsole->setMaximumWidth(400);
    errorConsole->setMaximumHeight(200);
    createTableHistory();
    appLayout->addLayout(rightLayout);
    mainVerticalSeparator = new QVBoxLayout();
    mainVerticalSeparator->addLayout(menuLayout);
    mainVerticalSeparator->addLayout(upLayout);
    mainVerticalSeparator->addLayout(appLayout);
    mainVerticalSeparator->addLayout(downLayout);
    mainVerticalSeparator->setMargin(0);
    mainVerticalSeparator->setSpacing(0);

    downLayout->setMargin(3);
    downLayout->setSpacing(5);
    speedLbl->setFont(fontLbl);

    tmStopBtn->setEnabled(false);
    setSrcSize();

    icon.addFile(":/ico");
    logo = QPixmap(":/ico");
    logoLbl = new QLabel();
    logoLbl->setPixmap(logo.scaled(100, 100, Qt::KeepAspectRatio));
    programName = new QLabel(programmNameString);
    QFont programNameFont = programName->font();
    programNameFont.setBold(true);
    programName->setFont(programNameFont);
    aboutLbl = new QLabel("STuring - Эмулятор машины Тьюринга.\nРазработчик программы: Смирнов Олег,\nSOVAZ Corp.");

    history->setEnabled(false);

    dialogMainLayout = new QVBoxLayout();
    dialogMainLayout->setAlignment(Qt::AlignCenter);
    dialogMainLayout->insertWidget(-1, programName, 0, Qt::AlignHCenter);
    dialogMainLayout->insertWidget(-1, logoLbl, 0, Qt::AlignHCenter);
    dialogMainLayout->insertWidget(-1, aboutLbl, 0, Qt::AlignHCenter);

    aboutDialog.setLayout(dialogMainLayout);
    aboutDialog.setFixedSize(dialogW, dialogH);
    aboutDialog.setWindowTitle("STuring - О Программе");
    aboutDialog.setWindowIcon(icon);

    mainWindow.setLayout(mainVerticalSeparator);
    mainWindow.setWindowTitle(programmNameString);
    mainWindow.setWindowIcon(icon);
    mainWindow.setMinimumSize(700, 500);
    mainWindow.show();


    QObject::connect(tmSrc, SIGNAL(textChanged()), this, SLOT(setSrcSize()));
    QObject::connect(clearHistoryBtn, SIGNAL(clicked()), history, SLOT(clearAllHistory()));
    QObject::connect(fControl, SIGNAL(opennedFile(QString,QString)), this, SLOT(openFile(QString, QString)));
}

void UI::openFile(QString src, QString line) {
    history->clearAllHistory();

    tmSrc->document()->setPlainText(src);
    tmLine->setText(line);
}

void UI::createTableHistory() {
    history->updateTable();
}

void UI::dialogShow() {
    aboutDialog.setGeometry((2*mainWindow.x() + mainWindow.width())/ 2 - dialogW/2, (2*mainWindow.y() + mainWindow.height())/ 2 - dialogH/2, dialogW, dialogH);
    aboutDialog.show();
}

void UI::createActions() {
    menuBar = new QMenuBar();

    fileMenu = new QMenu("Файл");
    fileMenu->addAction("Новый", fControl, SLOT(createNewFile()), Qt::CTRL + Qt::Key_N);
    fileMenu->addAction("Открыть...", fControl, SLOT(openDialogEnable()), Qt::CTRL + Qt::Key_O);
    //fileMenu->addAction("Сохранить");
    fileMenu->addAction("Сохранить как...", fControl, SLOT(saveDialogEnable()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    fileMenu->addAction("Выход", app, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    about = new QMenu("Справка");
    about->addAction("О Программе...", this, SLOT(dialogShow()), Qt::Key_F1);
    about->addAction("О Qt...", app, SLOT(aboutQt()), Qt::Key_F2);
    menuBar->addMenu(fileMenu);
    menuBar->addSeparator();
    menuBar->addMenu(about);
    menuLayout->addWidget(menuBar);

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

void UI::setLine(QString s) {
    tmLine->setText(s);
}
