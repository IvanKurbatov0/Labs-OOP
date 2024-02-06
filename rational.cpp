#include "rational.h"
#include "common.h"
#include <cmath>

QChar rational::SEPARATOR = separator;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a%b);
}
rational::rational()
{
   chis=0;
   znam=1;
}

rational::rational(int a)
{
    znam=1;
    chis=a;
}

rational::rational(int a ,int b)
{
    if(b!=0)
    {
        int d=abs(gcd(a, b));
        if (d>1)
        {
            chis=a/d;
            znam=b/d;
            if (znam < 0)
            {
                chis *= -1;
                znam *= -1;
            }
        }
        else
        {
            chis=a;
            znam=b;
            if (znam < 0)
            {
                chis *= -1;
                znam *= -1;
            }
        }
    }
}

rational::rational(QString s)
{
    QStringList lst = s.split("/");
    chis = lst[0].toInt();
    znam = 1;
    if (lst.size() == 1 || lst[1] == "")
        return;
    znam = lst[1].toInt();
    if (znam == 0)
        znam = 1;
    int d = abs(gcd(chis, znam));
    if (d > 1) {
        chis /= d;
        znam /= d;
    }
}

rational rational::operator+(rational a)
{
    rational res;
    if (znam<0)
    {
        chis *= -1;
        znam *= -1;
    }
    if (a.znam < 0)
    {
        a.chis *= -1;
        a.znam *= -1;
    }
    int lcm = znam * a.znam / abs(gcd(znam, a.znam));
    res.chis=lcm/znam*chis+lcm/a.znam*a.chis;
    res.znam = lcm;
    int d = abs(gcd(res.chis, res.znam));
    if (abs(gcd(res.chis, res.znam)) > 1)
    {
        res.chis /= d;
        res.znam /= d;
    }
    return res;
}

rational rational::operator-(rational a)
{
    rational res;
    if (znam < 0)
    {
        chis *= -1;
        znam *= -1;
    }
    if (a.znam < 0)
    {
        a.chis *= -1;
        a.znam *= -1;
    }
    int lcm = znam * a.znam / abs(gcd(znam, a.znam));
    res.chis=lcm/znam*chis-lcm/a.znam*a.chis;
    res.znam = lcm;
    int d = abs(gcd(res.chis, res.znam));
    if (d > 1)
    {
        res.chis /= d;
        res.znam /= d;
    }
    return res;
}

rational rational::operator*(rational a)
{
    rational res;
    if (znam < 0)
    {
        chis *= -1;
        znam *= -1;
    }
    if (a.znam < 0)
    {
        a.chis *= -1;
        a.znam *= -1;
    }
    res.chis=chis*a.chis;
    res.znam = znam * a.znam;
    int d = abs(gcd(res.chis, res.znam));
    if (d > 1)
    {
        res.chis /= d;
        res.znam /= d;
    }
    return res;
}

QString& operator<<(QString& s, rational a)
{
    if (a.znam != 0)
    {
        int d = abs(gcd(a.chis, a.znam));
        if (d > 1)
        {
            a.chis /= d;
            a.znam /= d;
        }
        s+=QString().setNum(a.chis);
        if (a.znam != 1)
        {
            s+="/";
            s+=QString().setNum(a.znam);
        }
        s+=separator;
    }
    return s;
}

istream& operator>>(istream& is, rational& a)
{
    is >> a.chis;
    char c;
    is >> c;
    is >> a.znam;
    if (a.znam == 0) exit(1);
    return is;
}

ostream& operator<<(ostream& os, rational a)
{
    if (a.znam != 0)
    {
        int d = abs(gcd(a.chis, a.znam));
        if (d > 1)
        {
            a.chis /= d;
            a.znam /= d;
        }
        if (a.znam == 1)
        {
            os << a.chis;
        }
        else os << a.chis << "/" << a.znam;
    }
    return os;
}

rational rational::operator/(rational a)
{
    rational res;
    if (znam < 0)
    {
        chis *= -1;
        znam *= -1;
    }
    if (a.znam < 0)
    {
        a.chis *= -1;
        a.znam *= -1;
    }
    res.chis = chis * a.znam;
    res.znam = znam * a.chis;
    int d = abs(gcd(a.chis, a.znam));
    if (d > 1)
    {
        res.chis /= d;
        res.znam /= d;
    }
    return res;
}

bool rational::operator==(rational a)
{
    return(chis == a.chis && znam == a.znam);
}

bool rational::operator!=(rational a)
{
    return(!(chis == a.chis && znam == a.znam));
}

rational rational::operator-()
{
    rational res;
    res.chis = chis * (-1);
    res.znam = znam;
    return res;
}

QByteArray& operator>>(QByteArray& arr, rational& r)
{
    int p = arr.indexOf(rational::SEPARATOR);
    if (p > 0)
    {
        r = rational((QString)arr.left(p));
        arr = arr.right(arr.length()-p-1);
    }
    return arr;
}

void rational::setSeparator(QChar ch)
{
    SEPARATOR = ch;
}
