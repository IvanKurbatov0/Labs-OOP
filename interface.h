#ifndef INTRFACE_H
#define INTRFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class Interface : public QWidget
{
    Q_OBJECT
    QLabel *n;
    QLineEdit *n_val;
    QGridLayout *layout;

    QPushButton *det_btn;
    QPushButton *rank_btn;
    QPushButton *trans_btn;

    QVector <QLineEdit*> vec;

    QLabel *output;





public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
public slots:
    void answer(QString);
    void add(const QString &text);

private slots:
    void formRequest();

signals:
    void request(QString);
};
#endif // INTRFACE_H
