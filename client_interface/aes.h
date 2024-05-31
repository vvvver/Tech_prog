#ifndef AES_H
#define AES_H

//#include <iomanip>
#include <vector>
//#include <cstring>
#include <cstdint>
#include <QString>
#include <QByteArray>

uint8_t gmult(uint8_t a, uint8_t b);
void SubBytes(uint8_t state[4][4]);
void ShiftRows(uint8_t state[4][4]);
void MixColumns(uint8_t state[4][4]);
void AddRoundKey(uint8_t state[4][4], uint8_t roundKey[4][4]);
void KeyExpansion(const uint8_t* key, uint8_t expandedKey[176]);
void AESEncrypt(uint8_t* input, const uint8_t* key);
void InvSubBytes(uint8_t state[4][4]);
void InvShiftRows(uint8_t state[4][4]);
void InvMixColumns(uint8_t state[4][4]);
void AESDecrypt(uint8_t* input, const uint8_t* key);
std::vector<uint8_t> pad(const std::vector<uint8_t>& input);
std::vector<uint8_t> unpad(const std::vector<uint8_t>& input);

// Добавляем функции для шифрования и расшифровки строк
QString encryptMessage(const QString& message, const uint8_t* keyFromClient = nullptr);
QString decryptMessage(const QString& encryptedMessage, const uint8_t* keyFromClient = nullptr);

#endif // AES_H
#ifndef AES_H
#define AES_H

class aes
{
public:
    aes();
};

#endif // AES_H
