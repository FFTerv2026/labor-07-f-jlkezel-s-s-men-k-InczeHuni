#include "mainwindow.h"
#include <QtWidgets>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    quoteLabel = new QLabel("Loading quotes...");
    quoteLabel->setWordWrap(true);
    quoteLabel->setAlignment(Qt::AlignCenter);
    quoteLabel->setObjectName("quoteLabel");

    QPushButton *nextButton = new QPushButton("New Inspiration");
    nextButton->setObjectName("nextButton");

    layout->addStretch();
    layout->addWidget(quoteLabel);
    layout->addStretch();
    layout->addWidget(nextButton);

    setCentralWidget(centralWidget);
    resize(500, 400);

    loadQuotes();
    displayNewQuote();

    connect(nextButton, &QPushButton::clicked, this, &MainWindow::displayNewQuote);
    this->setStyleSheet(
        "QMainWindow { background-color: #2c3e50; }"
        "#quoteLabel { "
        "   color: #ecf0f1; "
        "   font-size: 22px; "
        "   font-style: italic; "
        "   font-family: 'Georgia'; "
        "   padding: 20px; "
        "}"
        "#nextButton { "
        "   background-color: #27ae60; "
        "   color: white; "
        "   border-radius: 10px; "
        "   padding: 10px; "
        "   font-weight: bold; "
        "   font-size: 16px; "
        "   margin: 20px; "
        "}"
        "#nextButton:hover { background-color: #2ecc71; }"
        "#nextButton:pressed { background-color: #1e8449; }"
        );
}

void MainWindow::loadQuotes() {
    QFile file("quotes.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.trimmed().isEmpty()) {
                quotes.append(line);
            }
        }
        file.close();
    } else {
        quotes << "Stay hungry, stay foolish. ~Steve Jobs";
    }
}

void MainWindow::displayNewQuote() {
    if (quotes.isEmpty()) return;

    int newIndex;

    do {
        newIndex = QRandomGenerator::global()->bounded(quotes.size());
    } while (newIndex == lastIndex && quotes.size() > 1);

    lastIndex = newIndex;
    quoteLabel->setText(quotes[lastIndex]);
}
