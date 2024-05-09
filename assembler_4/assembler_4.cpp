#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
int lenStr(const char * str) {
    int answ = 0;
    __asm {
        push esi
        push ecx

        mov esi,str
        xor ecx,ecx

        MAIN_LOOP:
            cmp byte ptr[esi], 0 ; достаем значение типа byte по адресу esi и сравниваем с 0, 0 конец строки
                je EXIT
            inc ecx
            lodsb
                jne MAiN_LOOP
        EXIT:
            mov answ,ecx

        pop ecx
        pop esi
    }
    return answ;
}

void find_substring(const char* main_str, const char* slice_str) {

     int length_slice_str= lenStr(slice_str);

    __asm {
        ; 1 способ(не сделал)
        ; возьму длину куска, которого ищем и буду идти с шагом 1 в главной строке
        ; пример: 
        ; ищем world в строке hello world
        ; 1 шаг |Hello| world 
        ; 2 шаг H|ello |world
        ; n шаг Hellp |world|
        ; условие выхода если abs(len(main_str) - esi) < len(slice_str) или нашлось, тогда указатель на начало

        ; 2 способ (сделал)
        ; всегда увеличиваю ecx, если текуща буква из esi (al) не равна букве [edi-ecx+1], то зануляем ecx
        ; ecx должен в итоге равняться длине слова, которое мы ищем
        ;message: db "Hello, World"

        xor ecx, ecx
        xor eax,eax
        xor edx,edx 

        mov edx, length_slice_str
        mov esi, main_str
        mov edi, slice_str
        ; сбросил флаг направления => чтение из регистра esi будет происходить слева направо
        cld 
        
        MAIN_LOOP:
        xor eax, eax
            cmp byte ptr[esi], 0; выходим если конец
            je EXIT
            inc ecx; всегда увеличиваю, если что заксорю(есил дорастет до строки, которую ищем - побеа)

            lodsb

            cmp ecx, edx; длина равна, на выход
                je GOOD_EXIT
            

            cmp byte ptr[edi+ecx-1],al  ; сравниваю букву из edi с текущей из esi(al)
                je MAIN_LOOP
                xor ecx, ecx
                jmp MAIN_LOOP

        GOOD_EXIT:
            xor eax,eax
            sub esi,edx;сделал чтобы по плоской памяти обратно шагнуть на длину найденного слова, т.к оно съелось
            lea eax, [esi]
            mov slice_str,eax
        EXIT:
            
    }       
    std::cout << slice_str << '\n';

    //return -1;
}

int main() {
    char main_str[10] = "112233";
    char slice_str[10] = "22";

    int len_main_str = lenStr(main_str);
    int len_slice_str = lenStr(slice_str);
    if (len_main_str < len_slice_str) {
        std::cout << "None";
    }
    else {
        find_substring(main_str, slice_str);
    }

}