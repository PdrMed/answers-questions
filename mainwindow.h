#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QTime>
#include <QList>
#include <QString>
#include <random>
#include <QButtonGroup>
#include <QTimer>
#include <QFileDialog>
#include "Question.h"

class Question;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void checkAnswer(QAbstractButton* button);
private:
    QButtonGroup buttonGroup;
    QList<Question> cachedQuestions;
    Question currentQuestion;
    Ui::MainWindow *ui;
    void updateQuestionAndAnswers(const Question& question);
};
#endif // MAINWINDOW_H
