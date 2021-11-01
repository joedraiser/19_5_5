#include <iostream>
#include <fstream>

int main()
{
    std::ifstream file;
    std::string answer, input;
    bool played[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int yourPoints=0, theirPoints=0;
    char buffer[100];
    int offset, currentPos = 0;

    std::string questionsPath="c:\\qstns\\";

    while(yourPoints<6&&theirPoints<6)
    {
        std::cout << "Input offset: ";

        std::cin >> offset;
        currentPos = (currentPos + offset) % 13;
        std::cout << "Current question is " << currentPos+1 << std::endl;

        while(played[currentPos])
        {
            std::cout << currentPos+1 << " was already played, playing " << currentPos+2 << " question\n";
            currentPos=(currentPos+1)%13;
        }

        file.open(questionsPath+std::to_string(currentPos+1)+".txt", std::ios::binary);
        if(!file.is_open())
        {
            std::cout << "File is not opened, check questionsPath variable";
            exit(EXIT_FAILURE);
        }

        do
        {
            file.read(buffer, sizeof(buffer)-1);
            buffer[file.gcount()]=0;

            std::cout << buffer;
        }
        while(!file.eof());

        std::cout << std::endl;

        file.close();
        played[currentPos]=true;

        file.open(questionsPath+std::to_string(currentPos+1)+"_ans.txt");
        file >> answer;
        std::cin >> input;
        if(answer==input)
        {
            std::cout << "correct\n";
            yourPoints++;
        }
        else
        {
            std::cout << "incorrect\n";
            theirPoints++;
        }
        file.close();
    }

    if(yourPoints>=6)
        std::cout << "You won";
    else
        std::cout << "You lose";

    return 0;
}
