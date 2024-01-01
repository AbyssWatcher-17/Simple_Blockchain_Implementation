#include "Chain.h"

using namespace blockchain;

Chain::Chain(int difficulty)
{
    mDifficulty = difficulty;
    mChain.push_back(CBlock(0));
    mCurrentBlock = &mChain[0];

}

void  Chain::appendToCurrentBlock(uint8_t* data, uint32_t size)
{
    mCurrentBlock->appendData(data,size);
}

void Chain::nextBlock()
{
    CBlock block(mCurrentBlock);
    block.mine(mDifficulty);
    mChain.push_back(block);
    mCurrentBlock = &mChain.back();
}

CBlock* Chain::getCurrentBlock()
{
    return mCurrentBlock;
}