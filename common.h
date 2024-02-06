#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    DET_REQUEST = 1,
    RANK_REQUEST,
    TRANS_REQUEST,
    DET_ANSWER,
    RANK_ANSWER,
    TRANS_ANSWER
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
