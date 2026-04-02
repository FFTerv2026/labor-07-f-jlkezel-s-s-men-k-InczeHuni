#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QStringList>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void displayNewQuote();

private:
    void loadQuotes();

    QLabel *quoteLabel;
    QStringList quotes;
    int lastIndex = -1;
};

#endif
