#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QList>

class Question {
public:
    QString question;
    QList<QString> answers;
    int correctAnswerIndex;

    bool operator==(const Question& other) const
    {
        return (this->question == other.question && this->correctAnswerIndex == other.correctAnswerIndex);
    }
};

#endif // QUESTION_H
