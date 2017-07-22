//
// Created by nespl on 22/7/17.
//
#include <iostream>
#include <thread>

class Board {
protected:
    char *Design;
    int count;

public:
    Board() {
        Design = new char[9];
        for (int i = 0; i < 9; ++i) {
            Design[i] = '*';
        }
        count = 1;
    }

    void Display() const;

    void CheckHorizontal() const;

    void CheckVertical() const;

    void CheckDiagonal() const;

    void Player();


};

void Board::Display() const {
    for (int i = 0; i < 9; ++i) {
        std::cout << Design[i] << ' ';
        if (i == 2 || i == 5 || i == 8)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::CheckHorizontal() const {
    while (true) {
        if (Design[0] == Design[1] && Design[0] == Design[2]
            && Design[0] != '*'
            && Design[1] != '*'
            && Design[2] != '*') {
            break;
        }

        if (Design[3] == Design[4] && Design[3] == Design[5]
            && Design[3] != '*'
            && Design[4] != '*'
            && Design[5] != '*') {
            break;
        }

        if (Design[6] == Design[7] && Design[6] == Design[8]
            && Design[6] != '*'
            && Design[7] != '*'
            && Design[8] != '*') {
            break;
        }
    }

    pthread_mutex_lock((pthread_mutex_t *) this);
    std::cout << "Player " << count <<" has Won ! " << std::endl;
    exit(1);
}

void Board::CheckVertical() const {
    while (true) {
        if (Design[0] == Design[3] && Design[0] == Design[6]
            && Design[0] != '*'
            && Design[3] != '*'
            && Design[6] != '*') {
            break;
        }

        if (Design[1] == Design[4] && Design[1] == Design[7]
            && Design[1] != '*'
            && Design[4] != '*'
            && Design[7] != '*') {
            break;
        }

        if (Design[2] == Design[5] && Design[2] == Design[8]
            && Design[2] != '*'
            && Design[5] != '*'
            && Design[8] != '*') {
            break;
        }
    }

    pthread_mutex_lock((pthread_mutex_t *) this);
    std::cout << "Player " << count <<" has Won ! " << std::endl;
    exit(1);
}

void Board::CheckDiagonal() const {
    while (true) {
        if (Design[0] == Design[4] && Design[0] == Design[8]
            && Design[0] != '*'
            && Design[4] != '*'
            && Design[8] != '*') {
            break;
        }

        if (Design[2] == Design[4] && Design[2] == Design[6]
            && Design[2] != '*'
            && Design[4] != '*'
            && Design[6] != '*') {
            break;
        }
    }
    pthread_mutex_lock((pthread_mutex_t *) this);
    std::cout << "Player " << count <<" has Won ! " << std::endl;
    exit(1);
}

void Board::Player() {
    int position = -1;
    int fillvalue = 0;
    again:
    std::cout << "Enter the position !:  ";
    std::cin >> position;

    if (Design[position] == 'O'
        || Design[position] == 'X') {
        std::cerr << "Player entered wrong position ! TRY AGAIN !!";
        std::cout << std::endl;
        goto again;
    }

    switch (count) {
        case 1:
            Design[position] = 'O';
            count++;
            fillvalue++;
            break;
        case 2:
            Design[position] = 'X';
            count--;
            fillvalue++;
            break;
        default:
            break;
    }

    Display();
    if (fillvalue < 9)
        goto again;
}

int main(int argc, char *const argv[]) {
    Board board;
    board.Display();

    std::thread player(&Board::Player, &board);
    std::thread checkHorizontal(&Board::CheckHorizontal, &board);
    std::thread checkVertical(&Board::CheckVertical, &board);
    std::thread checkDiagonal(&Board::CheckDiagonal, &board);

    checkHorizontal.join();
    checkDiagonal.join();
    checkVertical.join();
    player.join();
    board.Display();

    return 0;
}