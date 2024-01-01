#include "CBlock.h"
#include "stdio.h"
#include <string.h>
#include <sstream>
#include <iomanip>

using namespace blockchain;

CBlock::CBlock(CBlock* prevBlock)
{
    mPrevBlock = prevBlock;
    memset(mHash,SHA256_DIGEST_LENGTH,0);
    if(mPrevBlock)
        memcpy(mPrevHash,mPrevBlock->getHash(),SHA256_DIGEST_LENGTH);
    else
        memset(mPrevHash,SHA256_DIGEST_LENGTH,0);
    
    mCreatedTs = time(0);
    mNonce = 0;
    mDataSize = 0;
    mData = 0;
    calculateHash();
}

void CBlock::calculateHash() 
{
    uint32_t sz =(SHA256_DIGEST_LENGTH * sizeof(uint8_t))   +   sizeof(time_t)  +   mDataSize   +   sizeof(uint32_t);
    uint8_t* buf = new uint8_t[sz];
    uint8_t* ptr = buf;

    memcpy(ptr,mPrevHash,SHA256_DIGEST_LENGTH * sizeof(uint8_t));
    ptr += SHA256_DIGEST_LENGTH * sizeof(uint8_t);

    memcpy(ptr, &mCreatedTs,sizeof(time_t));
    ptr += sizeof(time_t);

    if(mDataSize != 0)
    {
        memcpy(ptr,mData,mDataSize);
        ptr += mDataSize;
    }
    memcpy(ptr,&mNonce,sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256,buf,sz);
    SHA256_Final(mHash,&sha256);
    delete[] buf;
}

uint8_t* CBlock::getHash()
{
    return mHash;
}

std::string CBlock::getHashStr()
{
    std::stringstream ss;
    for (uint32_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(mHash[i]);
    }
    return ss.str();
}

CBlock* CBlock::getPrevBlock()
{
    return mPrevBlock;
}

void CBlock::appendData(uint8_t* data,uint32_t size)
{
    uint8_t* newData = new uint8_t[mDataSize +size];
    uint8_t* ptr = newData;
    if(mDataSize != 0)
    {
        memcpy(ptr,mData,mDataSize);
        mData = newData;
        mDataSize +=size;
    }
    memcpy(ptr,data,size);
    mData = newData;
    mDataSize +=size;
}

bool CBlock::isDifficulty(int difficulty)
{
    for (uint32_t i = 0; i < difficulty; i++)
    {
        /* code */
        if(mHash[i] != 0)
            return false;
    }
    return true;
    
}

void CBlock::mine(int difficulty)
{
    while (!isDifficulty(difficulty))
    {
        /* code */
        mNonce++;
        calculateHash();
    }
    
}

uint32_t CBlock::getNonce()
{
    return mNonce;
}