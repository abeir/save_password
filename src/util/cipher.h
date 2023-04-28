
#ifndef CIPHER_H
#define CIPHER_H

#include "global_defines.h"
#include <QByteArray>
#include <QObject>


namespace PROTECT_NAMESPACE {

class Cipher
{
public:
    static QByteArray encrypt(const QByteArray &data, const QByteArray &key);
    static QByteArray decrypt(const QByteArray &data, const QByteArray &key);

    static QByteArray obfuscate(const QByteArray &data, const QByteArray &salt);

private:
    Cipher();
    Q_DISABLE_COPY_MOVE(Cipher)
};

}
#endif // CIPHER_H
