#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <QString>
#include <QStringList>

using namespace std;

class rational
{
    static QChar SEPARATOR;
    int chis, znam;
public:
    rational();
    rational(int);
    rational(int, int);
    rational(QString);
    rational(const QByteArray&);

    int nod(int, int);

    rational operator+(rational a);
    rational operator-(rational a);
    rational operator*(rational a);
    rational operator/(rational a);
    rational operator-();
    bool operator==(rational a);
    bool operator!=(rational a);

    static void setSeparator(QChar);

    friend istream& operator>>(istream&, rational&);
    friend ostream& operator<<(ostream&, rational);


    friend QString& operator<<(QString&, rational);

    friend QByteArray& operator>>(QByteArray&,rational&);
};

#endif // RATIONAL_H
