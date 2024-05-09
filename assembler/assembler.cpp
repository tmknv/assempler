#include <iostream>
int IsPrime(int us_num) {
    int num = 10;
    int answ = 1;
    __asm {
        ; сохранить данные в стек
        push eax
        push ebx
        push esi
        push edx

        ; обнулить значения, если были
        xor eax, eax
        xor ebx, ebx
        xor esi, esi

        ; присваивание значений
        mov esi, 1
        mov eax,us_num

        ; цикл
        LOOP1:
        xor edx, edx;избавляемся от остатка от деления на прошлом шаге цикла
            inc esi 
            push eax; кладе значение в стек,чтобы не испортить
            idiv esi; делим eax-> целая часть от деления, edx->остаток
            pop eax; достаем из стека
        cmp eax,esi; если дошли до num == num и не вышли, то просто выходим без изменения answ
            je LOOP_TRUE_EXIT
        cmp edx,0; если остаток от деления == 0, изменяем answ
            je LOOP_EXIT
        cmp esi,num; базовый цикл, скачем, уыеличивая каунт
            jng LOOP1

        LOOP_EXIT:
            mov answ, 0
        LOOP_TRUE_EXIT:

        ; вернуть значения из стека
        pop edx
        pop esi
        pop ebx
        pop eax
    }
    return answ;
}
int main()
{
    int M, N,ct=0;
    std::cin >> M >> N;

    if (N > 2) {
        for (int i = M; i < N; i++) {
            if (i == 1) {
                continue;
            }
            else {
                if (IsPrime(i) and IsPrime(i+2)) {
                    std::cout << i << " " << i+2 << "\n";
                    ct++;
                }
            }
        }
        std::cout << "count : " << ct << "\n";
    }

    else {
        std::cout << "no value";
    }
}
