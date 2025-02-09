#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    cachedQuestions.clear();
    QString fileName = QFileDialog::getOpenFileName(this, "JSON Files", "", "JSON Files (*.json);;");

    if (fileName.isNull())
        return;

    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&jsonFile);
    QString jsonString = in.readAll();
    jsonFile.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDocument.isNull())
        return;

    QJsonObject jsonObject = jsonDocument.object();
    QJsonArray answersArray = jsonObject["questions"].toArray();

    for (const QJsonValue &quetionValue : answersArray)
    {
        QJsonObject quetionObj = quetionValue.toObject();
        Question question;
        question.question = quetionObj["question"].toString();
        QJsonArray answersArray = quetionObj["answers"].toArray();
        for (const QJsonValue &answerValue : answersArray)
        {
            question.answers.append(answerValue.toString());
        }
        question.correctAnswerIndex = quetionObj["correctanswer"].toInt();
        cachedQuestions.append(question);
    }

    srand(QTime::currentTime().msec());
    std::random_shuffle(cachedQuestions.begin(), cachedQuestions.end());
    on_pushButton_clicked();
}

void MainWindow::updateQuestionAndAnswers(const Question& question) {
    ui->Label_Question->setText(question.question);
    ui->Label_Response_1->setText(question.answers[0]);
    ui->Label_Response_2->setText(question.answers[1]);
    ui->Label_Response_3->setText(question.answers[2]);
    ui->Label_Response_4->setText(question.answers[3]);
    ui->Label_Response_5->setText(question.answers[4]);
}



void MainWindow::checkAnswer(QAbstractButton* button)
{
    int id = buttonGroup.id(button);

    if (id == currentQuestion.correctAnswerIndex)
    {
        ui->Label_Result->setText("Correct Answer!");
        ui->Label_Result->setStyleSheet("color:green;");
    }
    else
    {
        ui->Label_Result->setText("Incorrect Answer!");
        ui->Label_Result->setStyleSheet("color:red;");
        return;
    }

    QTimer::singleShot(1000, [&]()
    {
        if (!cachedQuestions.isEmpty())
        {
            ui->Response_6->setChecked(true);
            ui->Label_Result->setText("New question!");
            ui->Label_Result->setStyleSheet("color:black;");
            currentQuestion = cachedQuestions.takeFirst();
            updateQuestionAndAnswers(currentQuestion);
            ui->Label_Count->setText(QString::number(cachedQuestions.size()));
        }
        else
        {
            ui->Label_Result->setText("No more quetions!");
            ui->Label_Result->setStyleSheet("color:red;");
        }
    });
 }

void MainWindow::on_pushButton_clicked()
{
    if (cachedQuestions.empty())
        return;

    buttonGroup.addButton(ui->Response_1, 1);
    buttonGroup.addButton(ui->Response_2, 2);
    buttonGroup.addButton(ui->Response_3, 3);
    buttonGroup.addButton(ui->Response_4, 4);
    buttonGroup.addButton(ui->Response_5, 5);
    buttonGroup.addButton(ui->Response_6, 6);

    connect(&buttonGroup, &QButtonGroup::buttonClicked, this, &MainWindow::checkAnswer);

    if (!cachedQuestions.isEmpty())
    {
        currentQuestion = cachedQuestions.takeFirst();
        updateQuestionAndAnswers(currentQuestion);
        ui->Label_Count->setText(QString::number(cachedQuestions.size()));
    }
    else
    {
        qDebug() << "Questions not found";
    }

}

