#include "interface.h"
#include "common.h"

#include <iostream>

Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №3");
    setFixedSize(500, 400);


    det_btn= new QPushButton("определитель", this);
    rank_btn= new QPushButton("ранг", this);
    trans_btn= new QPushButton("транспонировать", this);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(det_btn);
    hlayout->addWidget(rank_btn);
    hlayout->addWidget(trans_btn);


    n=new QLabel("n =", this);
    n_val=new QLineEdit("2", this);
    QHBoxLayout *hlayout_2 = new QHBoxLayout;
    hlayout_2->addWidget(n);
    hlayout_2->addWidget(n_val);
    QVBoxLayout *vlayout =new QVBoxLayout;


    QHBoxLayout *hlayout_3 = new QHBoxLayout;
    output = new QLabel(this);
    hlayout_3->addWidget(output);


    int n=n_val->text().toInt();
    layout=new QGridLayout;
    for (int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
             vec.push_back(new QLineEdit("0"));
             layout->addWidget(vec[i*n+j], i, j);
        }
    }


    vlayout->addLayout(hlayout_2);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(hlayout_3);
    setLayout(vlayout);

    connect(det_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(rank_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(trans_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(n_val, SIGNAL(textChanged(const QString &)), this, SLOT(add(const QString &)));
}

Interface::~Interface()
{

    delete n;
    delete n_val;
    delete rank_btn;
    delete trans_btn;
    delete det_btn;
    delete output;
}

void Interface::formRequest()
{
    QString msg, curNum;
    QPushButton *btn = (QPushButton*)sender();
    int n = n_val->text().toInt();

    msg << QString().setNum(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            msg << vec[i*n+j]->text();
        }
    }

    if (btn == det_btn)
        msg << QString().setNum(DET_REQUEST);
    if (btn == rank_btn)
        msg << QString().setNum(RANK_REQUEST);
    if (btn == trans_btn)
        msg << QString().setNum(TRANS_REQUEST);

    emit request(msg);
}

void Interface::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int r = msg.left(p).toInt();
    msg = msg.mid(p+1, msg.length()-p-2);

    switch (r) {
        case DET_ANSWER:
            text += msg;
            output->setText(text);
            break;
        case RANK_ANSWER:
            text += msg;
            output->setText(text);
            break;
        case TRANS_ANSWER:
            text += msg.split(separator).join("");
            output->setText(text);
            break;
        default: return;
    }
}

void Interface::add(const QString &text)
{
    for (int i = vec.size() - 1; i >= 0; i--) {
        layout->removeWidget(vec[i]);
        delete vec[i];
        vec.remove(i);
    }
    int n=text.toInt();
    for (int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
             vec.push_back(new QLineEdit("0"));
             layout->addWidget(vec[i*n+j], i, j);
        }

    }
    layout->update();
}
