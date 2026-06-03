#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Operators
{
    Add,
    Sub,
    Mul,
    Div,
};

char OpSym[] = {'+', '-', 'x', '/'};

//Random Ra = new Random();
int NR = 0;
int NW = 0;
int Q[] = { 0, 0 };
int R[] = { 2, 10 };
enum Operators Op = Add;
bool RandomOp = true;

void SetOptions(char argv[])
{
    RandomOp = false;
    switch (argv[0]) {
        case 'a':
            Op = Add;
        break;
        case 's':
            Op = Sub;
        break;
        case 'm':
            Op = Mul;
        break;
        case 'd':
            Op = Div;
        break;
        case 'r':
        default:
            RandomOp = true;
        break;
    }
}

void SetRange(int re)
{
    R[1] = re;
}

void NextQuestion() {
    unsigned int rs = time(NULL);
    if (RandomOp) {
        int tnum = rand_r(&rs) % 4;
        Op = tnum;
    }

    Q[0] = (rand_r(&rs) % R[1]) + R[0];
    Q[1] = (rand_r(&rs) % 10) + 2;

    if (Op == Sub) {
        Q[0] += Q[1];
    } else if (Op == Div) {
        Q[0] = Q[1] * Q[0];
    }

}

void DisplayQuestion() {
    printf("%d %c %d\n", Q[0], OpSym[Op], Q[1]);
}

 bool CheckAnswer(int ans) {

    bool correct = false;

    switch (Op) {
        case Add:
            correct = (Q[0] + Q[1] == ans);
            break;
        case Sub:
            correct = ((Q[0] - Q[1]) == ans);
            break;
        case Mul:
            correct = ((Q[0] * Q[1]) == ans);
            break;
        case Div:
            correct = ((Q[0] / Q[1]) == ans);
            break;
            default:
            break;
    }

    return correct;
}

void DisplayAnswerResult(bool result, int a) {
    if (result) {
        NR++;
        printf("Correct! %d %c %d = %d!\n", Q[0], OpSym[Op], Q[1], a);
    } else {
        NW++;
        printf("Wrong! %d %c %d is not %d!\n", Q[0], OpSym[Op], Q[1], a);
    }
    printf("Number Correct: %d\n", NR);
    printf("Number Wrong: %d\n", NW);
}

int main(int argc, char *argv[]) {
    printf("Welcome to MathFlash for %c. \nType 'q' to quit. \n", OpSym[Op]);

    if (argc > 1)
    {
        SetOptions(argv[1]);
    }
    if (argc > 2 )
    {
        int cvrt = atoi(argv[2]);
        if (cvrt > 0)
        {
            SetRange(cvrt);
        }
    }

    bool q = false;
    bool repeat = false;

    while (!q)
    {

        if (!repeat)
        {
            NextQuestion();
        }

        DisplayQuestion();

        char uin[30];

        scanf("%s", &uin);

        //printf("%s\n", uin);

        if (uin[0] == 'q')
        {
            q = true;
            continue;
        }

        int cvrta = atoi(uin);

        if (cvrta > 0) {
            bool result = CheckAnswer(cvrta);
            DisplayAnswerResult(result, cvrta);
            repeat = false;
        } else {
            repeat = true;
        }
        //repeat = (uin != nullptr && cvrta > 0)? CheckAnswer(cvrta): true;

    }

    printf("Bye!\n");
    return 0;
}




