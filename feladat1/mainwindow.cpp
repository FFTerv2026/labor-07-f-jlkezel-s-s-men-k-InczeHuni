#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    fileNameEdit = new QLineEdit("*");
    textContentEdit = new QLineEdit();
    directoryEdit = new QLineEdit(QDir::currentPath());

    QPushButton *browseButton = new QPushButton("Browse...");
    QPushButton *findButton = new QPushButton("Find");

    filesTable = new QTableWidget(0, 2);
    filesTable->setHorizontalHeaderLabels({"Filename", "Size"});
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    filesFoundLabel = new QLabel("0 file(s) found");


    mainLayout->addWidget(new QLabel("Named:"));
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(new QLabel("Containing text:"));
    mainLayout->addWidget(textContentEdit);
    mainLayout->addWidget(directoryEdit);
    mainLayout->addWidget(browseButton);
    mainLayout->addWidget(filesTable);
    mainLayout->addWidget(filesFoundLabel);
    mainLayout->addWidget(findButton);

    setCentralWidget(centralWidget);

    connect(browseButton, &QPushButton::clicked, this, &MainWindow::browse);
    connect(findButton, &QPushButton::clicked, this, &MainWindow::find);
}

void MainWindow::browse() {
    QString directory = QFileDialog::getExistingDirectory(this, "Select Directory", directoryEdit->text());
    if (!directory.isEmpty()) directoryEdit->setText(directory);
}

void MainWindow::find() {
    filesTable->setRowCount(0); // Táblázat ürítése

    QString fileName = fileNameEdit->text();
    QString text = textContentEdit->text();
    QString path = directoryEdit->text();

    QDir directory(path);
    QStringList filter;
    if (!fileName.isEmpty()) filter << fileName;

    QStringList files = directory.entryList(filter, QDir::Files | QDir::NoSymLinks);


    QProgressDialog progress("Searching files...", "Cancel", 0, files.size(), this);
    progress.setWindowModality(Qt::WindowModal);

    for (int i = 0; i < files.size(); ++i) {
        progress.setValue(i);
        if (progress.wasCanceled()) break;

        QString filePath = directory.absoluteFilePath(files[i]);
        QFile file(filePath);

        bool found = false;
        if (text.isEmpty()) {
            found = true;
        } else if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            if (in.readAll().contains(text)) found = true;
            file.close();
        }

        if (found) {
            QFileInfo fileInfo(filePath);
            int row = filesTable->rowCount();
            filesTable->insertRow(row);
            filesTable->setItem(row, 0, new QTableWidgetItem(fileInfo.fileName()));
            filesTable->setItem(row, 1, new QTableWidgetItem(QString::number(fileInfo.size() / 1024) + " KB"));
        }
    }

    progress.setValue(files.size());
    filesFoundLabel->setText(QString("%1 file(s) found").arg(filesTable->rowCount()));
}
