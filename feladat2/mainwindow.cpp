#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(800, 600);
    setWindowTitle("CSV Viewer");


    tableWidget = new QTableWidget(this);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setCentralWidget(tableWidget);

    setupMenu();
}

void MainWindow::setupMenu() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAction = new QAction(tr("&Open File..."), this);
    openAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(openAction);

    connect(openAction, &QAction::triggered, this, &MainWindow::openCsvFile);
}

void MainWindow::openCsvFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open CSV File"), "", tr("CSV Files (*.csv);;All Files (*)"));

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(0);

    bool firstRow = true;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList pieces = line.split(",");

        if (firstRow) {

            tableWidget->setColumnCount(pieces.size());
            tableWidget->setHorizontalHeaderLabels(pieces);
            firstRow = false;
        } else {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            for (int i = 0; i < pieces.size(); ++i) {
                tableWidget->setItem(row, i, new QTableWidgetItem(pieces[i].trimmed()));
            }
        }
    }
    file.close();
}
