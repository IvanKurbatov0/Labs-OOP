#include "application.h"
#include "matrix.h"
#include "common.h"

Application::Application(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void Application::recieve(QByteArray msg)
{
    QString answer;
    int pos = msg.indexOf(separator);
    int n = msg.left(pos).toInt();
    matrix m(n);
    number val;
    int r;
    msg = msg.right(msg.length()-pos-1);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            msg >> val;
            m.InterIn(i, j, val);
        }
    }

    pos = msg.indexOf(separator);
    r = msg.left(pos).toInt();
    switch (r) {
        case DET_REQUEST:
            answer << QString().setNum(DET_ANSWER);
            answer << m.det();
            break;
        case RANK_REQUEST:
            answer << QString().setNum(RANK_ANSWER);
            answer << QString().setNum(m.rank());
            break;
        case TRANS_REQUEST:
            answer << QString().setNum(TRANS_ANSWER);
            m.trans();
            for (int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    answer << m.get(i, j);
                    answer << (QChar)' ';
                }
                answer << (QChar)'\n';
            }
            break;
        default: return;
    }

    comm->send(QByteArray().append(answer));
}
