/** @file
 * @brief Implementation of the SHA512 Algorithm
 */

#include "SHA512.h"
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <iomanip>
//#include <cstdint>
#include <sstream>

typedef unsigned long long uint64;

/**
 * Конструктор класса SHA512
 */
SHA512::SHA512(){
}

/**
 * Деструктор класса SHA512
 */
SHA512::~SHA512(){
}

/**
 * Возвращает дайджест сообщения с использованием алгоритма SHA512
 * @param строка входного сообщения, используемая в качестве
 * входных данных для алгоритма SHA512, должна быть размером < t бит
 */
std::string SHA512::hash(const std::string input){
    size_t nBuffer; // количество блоков сообщений
    uint64** buffer; // буферы блоков сообщений (каждое 1024-битное = 16 64-битных слов)
    uint64* h = new uint64[HASH_LEN]; // буфер, содержащий дайджест сообщения (512 бит = 8 64-битных слов)
    buffer = preprocess((unsigned char*) input.c_str(), nBuffer);
    process(buffer, nBuffer, h);

    freeBuffer(buffer, nBuffer);
    return digest(h);
}

/**
 * Предварительная обработка алгоритма SHA512
 * @param входное сообщение в байтовом представлении
 * @param Количество блоков сообщений в буфере nBuffer
 */
uint64** SHA512::preprocess(const unsigned char* input, size_t &nBuffer){
    // Заполнение: ввод || 1 || 0*k || l (в 128-битном представлении)
    size_t mLen = strlen((const char*) input);
    size_t l = mLen * CHAR_LEN_BITS; // длина входных данных в битах
    size_t k = (896-1-l) % MESSAGE_BLOCK_SIZE; // длина заполнения нулевого бита (l + 1 + k = 896 по модулю 1024)
    nBuffer = (l+1+k+128) / MESSAGE_BLOCK_SIZE;

    uint64** buffer = new uint64*[nBuffer];

    for(size_t i=0; i<nBuffer; i++){
        buffer[i] = new uint64[SEQUENCE_LEN];
    }

    uint64 in;
    size_t index;

    // Либо скопируйте существующее сообщение, добавьте 1 бит, либо добавьте 0 бит
    for(size_t i=0; i<nBuffer; i++){
        for(size_t j=0; j<SEQUENCE_LEN; j++){
            in = 0x0ULL;
            for(size_t k=0; k<WORD_LEN; k++){
                index = i*128+j*8+k;
                if(index < mLen){
                    in = in<<8 | (uint64)input[index];
                }else if(index == mLen){
                    in = in<<8 | 0x80ULL;
                }else{
                    in = in<<8 | 0x0ULL;
                }
            }
            buffer[i][j] = in;
        }
    }

    // Добавьте длину к двум последним 64-разрядным блокам
    appendLen(l, buffer[nBuffer-1][SEQUENCE_LEN-1], buffer[nBuffer-1][SEQUENCE_LEN-2]);
    return buffer;
}

/**
 * Обработка по алгоритму SHA512
 * @param буферный массив, содержащий предварительно обработанные
 * @param Количество блоков сообщений в буфере nBuffer
 * @param h массив дайджеста выходных сообщений
 */
void SHA512::process(uint64** buffer, size_t nBuffer, uint64* h){
    uint64 s[WORKING_VAR_LEN];
    uint64 w[MESSAGE_SCHEDULE_LEN];

    memcpy(h, hPrime, WORKING_VAR_LEN*sizeof(uint64));

    for(size_t i=0; i<nBuffer; i++){
        // скопировать в расписание сообщений
        memcpy(w, buffer[i], SEQUENCE_LEN*sizeof(uint64));

        // Подготовьте расписание рассылок
        for(size_t j=16; j<MESSAGE_SCHEDULE_LEN; j++){
            w[j] = w[j-16] + sig0(w[j-15]) + w[j-7] + sig1(w[j-2]);
        }
        // Инициализируйте рабочие переменные
        memcpy(s, h, WORKING_VAR_LEN*sizeof(uint64));

        // Компрессия
        for(size_t j=0; j<MESSAGE_SCHEDULE_LEN; j++){
            uint64 temp1 = s[7] + Sig1(s[4]) + Ch(s[4], s[5], s[6]) + k[j] + w[j];
            uint64 temp2 = Sig0(s[0]) + Maj(s[0], s[1], s[2]);

            s[7] = s[6];
            s[6] = s[5];
            s[5] = s[4];
            s[4] = s[3] + temp1;
            s[3] = s[2];
            s[2] = s[1];
            s[1] = s[0];
            s[0] = temp1 + temp2;
        }

        // Вычислите промежуточные значения хэша
        for(size_t j=0; j<WORKING_VAR_LEN; j++){
            h[j] += s[j];
        }
    }

}

/**
 * Добавляет длину сообщения в последние два блока сообщений
 * @param l размер сообщения в битах
 * @param выводит указатель на предпоследний блок сообщений
 * @param hi, указатель на последний блок сообщений
 */
void SHA512::appendLen(size_t l, uint64& lo, uint64& hi){
    lo = l;
    hi = 0x00ULL;
}

/**
 * Выводит окончательный обзор сообщения в шестнадцатеричном виде
 * @param h массив digest выходных сообщений
 */
std::string SHA512::digest(uint64* h){
    std::stringstream ss;
    for(size_t i=0; i<OUTPUT_LEN; i++){
        ss << std::hex << std::setw(16) << std::setfill('0') << h[i];
    }
    delete[] h;
    return ss.str();
}

/**
 * Правильно освободите буфер
 * @param буферный массив, содержащий предварительно обработанные
 * @param Количество блоков сообщений в буфере nBuffer
 */
void SHA512::freeBuffer(uint64** buffer, size_t nBuffer){
    for(size_t i=0; i<nBuffer; i++){
        delete[] buffer[i];
    }

    delete[] buffer;
}
