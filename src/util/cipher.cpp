
#include "cipher.h"


namespace PROTECT_NAMESPACE {



QByteArray Cipher::encrypt(const QByteArray &data, const QByteArray &key)
{
    Q_UNUSED(key)
    return data;
}

QByteArray Cipher::decrypt(const QByteArray &data, const QByteArray &key)
{
    Q_UNUSED(key)
    return data;
}

QByteArray Cipher::obfuscate(const QByteArray &data, const QByteArray &salt)
{
    Q_UNUSED(salt)
    return data;
}

Cipher::Cipher()
{
}



}
