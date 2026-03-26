#include "CryptoManager.h"
#include <stdexcept>

CryptoManager::CryptoManager(QObject *parent) : QObject(parent)
{
    if (sodium_init() < 0) {
        throw std::runtime_error("Sodium initialization failed");
    }
    initialized = true;
}

CryptoManager::~CryptoManager() {}

QByteArray CryptoManager::encrypt(const QByteArray &data, const QByteArray &key, const QByteArray &nonce)
{
    if (key.size() != crypto_aead_xchacha20poly1305_ietf_KEYBYTES ||
        nonce.size() != crypto_aead_xchacha20poly1305_ietf_NPUBBYTES) {
        return QByteArray();
    }

    QByteArray ciphertext;
    ciphertext.resize(data.size() + crypto_aead_xchacha20poly1305_ietf_ABYTES);
    unsigned long long clen;

    crypto_aead_xchacha20poly1305_ietf_encrypt(
        (unsigned char *)ciphertext.data(), &clen,
        (const unsigned char *)data.data(), data.size(),
        nullptr, 0, // No additional data
        nullptr, (const unsigned char *)nonce.data(), (const unsigned char *)key.data()
    );

    return ciphertext;
}

QByteArray CryptoManager::decrypt(const QByteArray &data, const QByteArray &key, const QByteArray &nonce)
{
    if (key.size() != crypto_aead_xchacha20poly1305_ietf_KEYBYTES ||
        nonce.size() != crypto_aead_xchacha20poly1305_ietf_NPUBBYTES ||
        data.size() < crypto_aead_xchacha20poly1305_ietf_ABYTES) {
        return QByteArray();
    }

    QByteArray plaintext;
    plaintext.resize(data.size() - crypto_aead_xchacha20poly1305_ietf_ABYTES);
    unsigned long long plen;

    if (crypto_aead_xchacha20poly1305_ietf_decrypt(
            (unsigned char *)plaintext.data(), &plen,
            nullptr,
            (const unsigned char *)data.data(), data.size(),
            nullptr, 0,
            (const unsigned char *)nonce.data(), (const unsigned char *)key.data()
        ) != 0) {
        return QByteArray(); // Decryption failed
    }

    return plaintext;
}

QByteArray CryptoManager::generateRandom(int size)
{
    QByteArray bytes;
    bytes.resize(size);
    randombytes_buf(bytes.data(), size);
    return bytes;
}

bool CryptoManager::constantTimeCompare(const QByteArray &a, const QByteArray &b)
{
    if (a.size() != b.size()) return false;
    return crypto_verify_16((const unsigned char *)a.data(), (const unsigned char *)b.data()) == 0;
}
