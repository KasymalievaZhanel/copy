#include <stdio.h>
#include <stdint.h>

const uint8_t AMOUNT = 62;

void Function_to_main(uint64_t, uint64_t);
int Convert_to_int(char);
void Print_set(uint64_t *);
char Encrypt_symbol(const int);

void MAKE_CURRENT_SET(uint64_t *set, int number){
    *set |= 1ULL << number;
}


int main() {
    uint64_t result_set = 0;
    uint64_t current_set = 0;
    Function_to_main(result_set, current_set);
    return 0;
}

void Function_to_main(uint64_t result_set, uint64_t current_set) {
    for (char current_symbol = getchar(); current_symbol != EOF; current_symbol = getchar()) {
        //ищем символ
        switch (current_symbol) {
            case '&':
                result_set &= current_set;
                break;
            case '~':
                result_set = ~result_set;
                //continue чтобы current_set != 0;
                continue;
            case '|':
                result_set |= current_set;
                break;
            case '^':
                result_set ^= current_set;
                break;
                //если ничего не нашли
            default : {
                int current_int_symbol = Convert_to_int(current_symbol);
                if (current_int_symbol < AMOUNT && current_int_symbol >= 0) {
                    MAKE_CURRENT_SET(&current_set, current_int_symbol);
                    continue;
                }
            }
        }
        current_set = 0;
    }
    Print_set(&result_set);
}

int Convert_to_int(char char_symbol){
    if (char_symbol >= 'a'){
        return 10 + 26 + (int)(char_symbol - 'a');
    }
    else if(char_symbol >= 'A'){
        return 10  + (int)(char_symbol - 'A');
    }
    else
        return (int)(char_symbol - '0');

}

void Print_set(uint64_t *set){
    for (uint8_t i = 0; i < AMOUNT; ++i) {
        char ch;
        if ((*set >> i) & 1ULL) {
            ch = Encrypt_symbol(i);
        } else {
            ch = 0;
        }
        if (ch != 0) {
            putchar(ch);
        }
    }
    putchar('\n');
}

char Encrypt_symbol(const int symbol) {
    //>= 'a'
    if (symbol >= 36) {
        return (char) ((symbol - 36) + 'a');
    //>= 'A'
    } else if (symbol >= 10) {
        return (char) ((symbol - 10) + 'A');
    } else {
    //>= '0'
        return (char) (symbol + '0');
    }
}
