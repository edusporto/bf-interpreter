#include <iostream>
#include <fstream>
#include <stack>
#include <cstdint>

int main(int argc, char *argv[])
{
    unsigned int mem_alloc_size = 0;

    if (argc == 2) {
        mem_alloc_size = 30000;
        // if no memory size is specified,
        // sets the default to 30000 bytes
    } else if (argc == 3) {
        mem_alloc_size = atoi(argv[2]);
        // amount of memory specified
    } else {
        std::cerr << "Usage: ";
        std::cerr << argv[0] << " [file name] " << "[OPTIONAL: amount of memory to allocate]" << std::endl;
        return EXIT_FAILURE;
    }

    // Trying to open the file containing the code
    std::ifstream file;
    file.open(argv[1]);
    if (!file) {
        std::cerr << "Unable to open " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // Writing the BF code to a string that the program can read
    std::string currLine = "";
    std::string code     = "";
    while (getline(file, currLine)) {
        code.append(currLine);
    }
    file.close();

    uint8_t* mem = (uint8_t*)calloc(mem_alloc_size, sizeof(uint8_t));
    // 1 byte * amount of mem to alloc
    uint8_t* currMem = mem;

    if (mem == NULL) {
        std::cerr << "Unable to allocate memory." << std::endl;
        return EXIT_FAILURE;
    }

    unsigned int currCommandPos = 0;
    std::stack<unsigned int> loopStack; // contains position for last [

    while (currCommandPos < code.length())
    {
        switch (code[currCommandPos])
        {
            case '>':
                currMem++;
                break;

            case '<':
                currMem--;
                break;

            case '+':
                (*currMem)++;
                break;

            case '-':
                (*currMem)--;
                break;

            case '[':
                if (!*currMem) {
                    unsigned int loopStartCount = 1;
                    currCommandPos++;
                    while (loopStartCount != 0) {
                        if (code[currCommandPos] == '[')
                            loopStartCount++;
                        if (code[currCommandPos] == ']')
                            loopStartCount--;
                        currCommandPos++;
                    }
                    currCommandPos--;
                } else {
                    loopStack.push(currCommandPos);
                }
                break;

            case ']':
                if (*currMem) {
                    currCommandPos = loopStack.top();
                } else {
                    loopStack.pop();
                }
                break;

            case ',':
                (*currMem) = getchar();
                break;

            case '.':
                putchar(*currMem);
                break;
        }

        currCommandPos++;
    }

    free(mem);

    return EXIT_SUCCESS;
}
