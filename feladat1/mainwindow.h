#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void browse();
    void find();

private:

    QLineEdit *fileNameEdit;
    QLineEdit *textContentEdit;
    QLineEdit *directoryEdit;
    QTableWidget *filesTable;
    QLabel *filesFoundLabel;

    void showFiles(const QStringList &files);
    QStringList findFiles(const QStringList &files, const QString &text);
};

#endif
