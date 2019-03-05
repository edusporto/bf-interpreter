#include <iostream>
#include <fstream>
#include <stack>

int main(int argc, char *argv[])
{
    // This program requires 2 arguments
    if (argc != 3) {
        std::cerr << "Please specify (in this order):" << std::endl;
        std::cerr << " - amount of memory to be allocated" << std::endl;
        std::cerr << " - file containing BF code" << std::endl;
        return EXIT_FAILURE;
    }

    // Trying to open the file containing the code
    std::ifstream file;
    file.open(argv[2]);
    if (!file) {
        std::cerr << "Unable to open " << argv[2] << std::endl;
        return EXIT_FAILURE;
    }

    // Writing the BF code to a string that the program can read
    std::string currLine = "";
    std::string code     = "";
    while (getline(file, currLine)) {
        code.append(currLine);
    }
    file.close();

    unsigned int mem_alloc_size = atoi(argv[1]);
    u_int8_t* mem = (u_int8_t*)calloc(mem_alloc_size, 1);
    // 1 byte * amount of mem to alloc
    u_int8_t* currMem = mem;

    if (mem == NULL) {
        std::cerr << "Unable to alocate memory." << std::endl;
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
