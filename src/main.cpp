#include "blockchain/Chain.h"
#include <iostream>
#include <memory>
#include <random>

using namespace blockchain;

// Function to generate random garbage
void generateGarbage(uint8_t* garbage, size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);

    for (size_t i = 0; i < size; ++i) {
        garbage[i] = dis(gen);
    }
}

int main(int argc, char const* argv[]) {
    std::cout << "Start \n";

    Chain chain(1);

    // Generate and append garbage to the current block
    uint8_t garbage1[32];
    generateGarbage(garbage1, sizeof(garbage1));
    chain.appendToCurrentBlock(garbage1, sizeof(garbage1));

    std::cout << "Garbage appended to current block. \n";

    chain.nextBlock();

    std::cout << "Next block mined. \n";

    // Display information about the genesis block
    std::cout << "Genesis Hash: " << chain.getCurrentBlock()->getPrevBlock()->getHashStr()
              << "\nNonce: " << chain.getCurrentBlock()->getNonce() << "\n";

    // Generate and append another set of garbage to the current block
    uint8_t garbage2[32];
    generateGarbage(garbage2, sizeof(garbage2));
    chain.appendToCurrentBlock(garbage2, sizeof(garbage2));

    std::cout << "Garbage appended to current block. \n";

    chain.nextBlock();

    std::cout << "Next block mined. \n";

    // Display information about the latest block
    std::cout << "Previous Hash: " << chain.getCurrentBlock()->getPrevBlock()->getHashStr()
              << "\nNonce: " << chain.getCurrentBlock()->getNonce() << "\n";

    return 0;
}
