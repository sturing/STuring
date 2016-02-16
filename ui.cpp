#include "ui.h"

UI::UI(QApplication* app_, QObject *parent) : QObject(parent)
{
    programmNameString = "STuring v3.0.2alpha";
    app = app_;
    fControl = new FileController();
    tmLine = new QLineEdit();
    tmRunBtn = new QPushButton(local.getTmRunBtnLocale());
    tmStopBtn = new QPushButton(local.getTmRunBtnLocale());
    clearHistoryBtn = new QPushButton(local.getClearHistoryBtnLocale());
    tmSrc = new CodeEditor();
    infoLbl = new QLabel("");
    speedSlider = new QSlider(Qt::Horizontal);
    speedLbl = new QLabel("Скорость:");
    errorConsole = new QTextEdit();
    errorConsole->setReadOnly(true);
    maxSpeedCkb = new QCheckBox("Максимальная скорость");

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
    maxSpdLayout->addWidget(maxSpeedCkb);
    maxSpdLayout->setAlignment(Qt::AlignLeft);

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
    maxSpeedCkb->setFont(fontLbl);

    turingLayout = new QVBoxLayout();
    turingLayout->setSpacing(3);
    turingLayout->setMargin(3);
    turingLayout->addWidget(tmSrc);
    appLayout->addLayout(turingLayout);
    historyCkbLayout = new QHBoxLayout();
    historyCkb = new QCheckBox("Данные из таблицы");
    historyCkbLayout->addWidget(historyCkb);
    historyCkbLayout->setAlignment(Qt::AlignLeft);
    rightLayout->addLayout(historyCkbLayout);
    errorLbl = new QLabel("Консоль ошибок:");
    errorLbl->setAlignment(Qt::AlignBottom);
    rightLayout->addWidget(history);
    rightLayout->addWidget(errorLbl);
    rightLayout->addWidget(errorConsole);
    errorConsole->setMinimumWidth(400);
    errorConsole->setMaximumWidth(400);
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

    aboutDialog = new QWidget();

    aboutDialog->setLayout(dialogMainLayout);
    aboutDialog->setFixedSize(dialogW, dialogH);
    aboutDialog->setWindowTitle("STuring - О Программе");
    aboutDialog->setWindowIcon(icon);

    mainWindow.setLayout(mainVerticalSeparator);
    mainWindow.setWindowTitle(programmNameString);
    mainWindow.setWindowIcon(icon);
    mainWindow.setMinimumSize(700, 500);
    mainWindow.show();

    QObject::connect(tmSrc, SIGNAL(textChanged()), this, SLOT(setSrcSize()));
    QObject::connect(clearHistoryBtn, SIGNAL(clicked()), history, SLOT(clearAllHistory()));
    QObject::connect(fControl, SIGNAL(opennedFile(QString,QString)), this, SLOT(openFile(QString, QString)));
    QObject::connect(fControl, SIGNAL(saveFileSign()),this, SLOT(saveFile()));
    QObject::connect(fControl, SIGNAL(sendPath(QString)), this, SLOT(fileNameWindow(QString)));
    QObject::connect(tmLine, SIGNAL(textChanged(QString)), this, SLOT(addUnSaved()));
    QObject::connect(tmSrc, SIGNAL(textChanged()), this, SLOT(addUnSaved()));
    fControl->createNewFile();
    fileSaved = 1;
}

void UI::openFile(QString src, QString line) {
    history->clearAllHistory();

    tmSrc->document()->setPlainText(src);
    tmLine->setText(line);
    addSaved();
}

void UI::createTableHistory() {
    history->updateTable();
}

void UI::dialogShow() {
    aboutDialog->setGeometry((2*mainWindow.x() + mainWindow.width())/ 2 - dialogW/2, (2*mainWindow.y() + mainWindow.height())/ 2 - dialogH/2, dialogW, dialogH);
    aboutDialog->show();
}

void UI::saveFile() {
    QString src =tmSrc->document()->toPlainText();
    QString line = tmLine->text();
    fControl->saveFile(src, line);
    addSaved();

   emit saveSettings();
}

void UI::fileNameWindow(QString str) {
    mainWindow.setWindowTitle(programmNameString +  " - " + str);
    allWindowTitle = mainWindow.windowTitle();
}

void UI::addUnSaved() {
    mainWindow.setWindowTitle(allWindowTitle + "*");
    fileSaved = 0;
}

void UI::addSaved() {
    mainWindow.setWindowTitle(allWindowTitle);
    fileSaved = 1;
}

void UI::createNewFile() {
    fileNameWindow(" - Новый");
    fControl->createNewFile();
    addSaved();
}

void UI::createActions() {
    menuBar = new QMenuBar();

    fileMenu = new QMenu("Файл");
    fileMenu->addAction("Новый", fControl, SLOT(createNewFile()), Qt::CTRL + Qt::Key_N);
    fileMenu->addAction("Открыть...", fControl, SLOT(openDialogEnable()), Qt::CTRL + Qt::Key_O);
    fileMenu->addAction("Сохранить", this, SLOT(saveFile()), Qt::CTRL + Qt::Key_S);
    fileMenu->addAction("Сохранить как...", fControl, SLOT(saveDialogEnable()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);

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

UI::~UI() {
    delete fControl;
    delete tmLine;
    delete tmRunBtn;
    delete tmStopBtn;
    delete clearHistoryBtn;
    delete tmSrc;
    delete maxSpeedCkb;
    delete maxSpdLayout;
    delete upLayout;
    delete turingLayout;
    delete downLayout;
    delete menuLayout;
    delete infoLbl;
    delete speedLbl;
    delete speedSlider;
    delete historyCkbLayout;
    delete historyCkb;
    delete saveAction;
    delete openAction;
    delete menuBar;
    delete fileMenu;
    delete about;
    delete logoLbl;
    delete programName;
    delete aboutLbl;
    delete dialogMainLayout;
    delete errorConsole;
    delete errorLbl;
    delete rightLayout;
    delete appLayout;
    delete mainVerticalSeparator;
    delete history;
    delete aboutDialog;
}
