#ifndef __C_BLOCK_INCLUDED__
#define __C_BLOCK_INCLUDED__
#include <openssl/sha.h>
#include <string>
//#include <ctime> //?


namespace blockchain
{
    class CBlock
    {
    private:
        uint8_t mHash[SHA224_DIGEST_LENGTH];
        uint8_t mPrevHash[SHA256_DIGEST_LENGTH];
        CBlock* mPrevBlock;
        uint8_t* mData;
        uint32_t mDataSize;
        time_t mCreatedTs;
        uint32_t mNonce;
    public:
        CBlock(CBlock* prevBlock);
        void calculateHash();
        uint8_t* getHash();
        std::string getHashStr();
        CBlock* getPrevBlock();
        void appendData(uint8_t* data,uint32_t size);
        bool isDifficulty(int difficulty);
        void mine(int difficulty);
        uint32_t getNonce();
        
    };
}








#endif