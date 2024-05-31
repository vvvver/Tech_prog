#include "aes.h"
//#include <iomanip>
#include <vector>
#include <cstring>
#include <cstdint>
#include <QString>
#include <QByteArray>

using namespace std;

// S-box
const uint8_t sbox[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// Обратный S-box
const uint8_t rsbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

// Константы для раундового ключа Rijndael
const uint8_t Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

// Функция для умножения на 2 в поле GF(2^8)
uint8_t gmult(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    uint8_t hi_bit_set;
    for (int counter = 0; counter < 8; counter++) {
        if (b & 1) p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set) a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

// Шаг SubBytes
void SubBytes(uint8_t state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = sbox[state[i][j]];
        }
    }
}

// Шаг ShiftRows
void ShiftRows(uint8_t state[4][4]) {
    uint8_t temp;

    // Сдвиг первой строки на 1 столбец влево
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Сдвиг второй строки на 2 столбца влево
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Сдвиг третьей строки на 3 столбца влево
    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}

// Шаг MixColumns
void MixColumns(uint8_t state[4][4]) {
    uint8_t temp[4];
    for (int i = 0; i < 4; i++) {
        temp[0] = gmult(state[0][i], 2) ^ gmult(state[1][i], 3) ^ state[2][i] ^ state[3][i];
        temp[1] = state[0][i] ^ gmult(state[1][i], 2) ^ gmult(state[2][i], 3) ^ state[3][i];
        temp[2] = state[0][i] ^ state[1][i] ^ gmult(state[2][i], 2) ^ gmult(state[3][i], 3);
        temp[3] = gmult(state[0][i], 3) ^ state[1][i] ^ state[2][i] ^ gmult(state[3][i], 2);

        state[0][i] = temp[0];
        state[1][i] = temp[1];
        state[2][i] = temp[2];
        state[3][i] = temp[3];
    }
}

// Шаг AddRoundKey
void AddRoundKey(uint8_t state[4][4], uint8_t roundKey[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] ^= roundKey[i][j];
        }
    }
}

// Расширение ключа
void KeyExpansion(const uint8_t* key, uint8_t expandedKey[176]) {
    uint8_t temp[4];
    int i = 0;
    while (i < 16) {
        expandedKey[i] = key[i];
        i++;
    }

    i = 16;
    int k = 0;
    while (i < 176) {
        for (int j = 0; j < 4; j++) {
            temp[j] = expandedKey[(i - 4) + j];
        }

        if (i % 16 == 0) {
            uint8_t ttemp = temp[0];
            temp[0] = sbox[temp[1]] ^ Rcon[k];
            temp[1] = sbox[temp[2]];
            temp[2] = sbox[temp[3]];
            temp[3] = sbox[ttemp];
            k++;
        }

        for (int j = 0; j < 4; j++) {
            expandedKey[i] = expandedKey[i - 16] ^ temp[j];
            i++;
        }
    }
}

// Шифрование AES
void AESEncrypt(uint8_t* input, const uint8_t* key) {
    uint8_t state[4][4];
    uint8_t expandedKey[176];

    // Копирование входных данных в состояние
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = input[i * 4 + j];
        }
    }

    // Расширение ключа
    KeyExpansion(key, expandedKey);

    // Начальный AddRoundKey
    AddRoundKey(state, (uint8_t(*)[4])expandedKey);

    // 9 основных раундов
    for (int round = 1; round < 10; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, (uint8_t(*)[4])(expandedKey + round * 16));
    }

    // Финальный раунд
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, (uint8_t(*)[4])(expandedKey + 160));

    // Копирование состояния в выходные данные
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            input[i * 4 + j] = state[j][i];
        }
    }
}

// Шаг InvSubBytes
void InvSubBytes(uint8_t state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = rsbox[state[i][j]];
        }
    }
}

// Шаг InvShiftRows
void InvShiftRows(uint8_t state[4][4]) {
    uint8_t temp;

    // Сдвиг первой строки на 1 столбец вправо
    temp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;

    // Сдвиг второй строки на 2 столбца вправо
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Сдвиг третьей строки на 3 столбца вправо
    temp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}

// Шаг InvMixColumns
void InvMixColumns(uint8_t state[4][4]) {
    uint8_t temp[4];
    for (int i = 0; i < 4; i++) {
        temp[0] = gmult(state[0][i], 0x0e) ^ gmult(state[1][i], 0x0b) ^ gmult(state[2][i], 0x0d) ^ gmult(state[3][i], 0x09);
        temp[1] = gmult(state[0][i], 0x09) ^ gmult(state[1][i], 0x0e) ^ gmult(state[2][i], 0x0b) ^ gmult(state[3][i], 0x0d);
        temp[2] = gmult(state[0][i], 0x0d) ^ gmult(state[1][i], 0x09) ^ gmult(state[2][i], 0x0e) ^ gmult(state[3][i], 0x0b);
        temp[3] = gmult(state[0][i], 0x0b) ^ gmult(state[1][i], 0x0d) ^ gmult(state[2][i], 0x09) ^ gmult(state[3][i], 0x0e);

        state[0][i] = temp[0];
        state[1][i] = temp[1];
        state[2][i] = temp[2];
        state[3][i] = temp[3];
    }
}

// Расшифрование AES
void AESDecrypt(uint8_t* input, const uint8_t* key) {
    uint8_t state[4][4];
    uint8_t expandedKey[176];

    // Копирование входных данных в состояние
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = input[i * 4 + j];
        }
    }

    // Расширение ключа
    KeyExpansion(key, expandedKey);

    // Начальный AddRoundKey
    AddRoundKey(state, (uint8_t(*)[4])(expandedKey + 160));

    // 9 основных раундов
    for (int round = 9; round > 0; round--) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, (uint8_t(*)[4])(expandedKey + round * 16));
        InvMixColumns(state);
    }

    // Финальный раунд
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, (uint8_t(*)[4])expandedKey);

    // Копирование состояния в выходные данные
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            input[i * 4 + j] = state[j][i];
        }
    }
}

// Выравнивание текста до кратного 16 байтам
vector<uint8_t> pad(const vector<uint8_t>& input) {
    size_t padLength = 16 - (input.size() % 16);
    vector<uint8_t> paddedInput = input;
    paddedInput.insert(paddedInput.end(), padLength, padLength);
    return paddedInput;
}

// Удаление выравнивания после расшифрования
vector<uint8_t> unpad(const vector<uint8_t>& input) {
    size_t padLength = input.back();
    return vector<uint8_t>(input.begin(), input.end() - padLength);
}

uint8_t key[16] = {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x4d, 0xa3, 0x88, 0x88, 0x88, 0x88
};


QString encryptMessage(const QString& message, const uint8_t* keyFromClient) {
    if (!keyFromClient) {
        keyFromClient = key;
    }
    QByteArray input = message.toUtf8();
    vector<uint8_t> inputVec(input.begin(), input.end());
    inputVec = pad(inputVec);

    for (size_t i = 0; i < inputVec.size(); i += 16) {
        AESEncrypt(&inputVec[i], keyFromClient);
    }

    QByteArray encryptedMessage(reinterpret_cast<char*>(inputVec.data()), inputVec.size());
    return QString::fromLatin1(encryptedMessage.toBase64());
}

QString decryptMessage(const QString& encryptedMessage, const uint8_t* keyFromClient) {
    if (!keyFromClient) {
        keyFromClient = key;
    }
    QByteArray encryptedBytes = QByteArray::fromBase64(encryptedMessage.toLatin1());
    vector<uint8_t> input(encryptedBytes.begin(), encryptedBytes.end());

    for (size_t i = 0; i < input.size(); i += 16) {
        AESDecrypt(&input[i], keyFromClient);
    }

    input = unpad(input);
    QByteArray decryptedMessage(reinterpret_cast<char*>(input.data()), input.size());
    return QString::fromUtf8(decryptedMessage);
}
