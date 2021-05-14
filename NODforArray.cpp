/* Первая лабораторная (Л2), задание 7. 
   Найти  наибольший  общий  делитель  всех  элементов массива (на который они все делятся без остатка). */

#include <stdio.h>
#include <clocale>   // для кириллицы
#include <stdlib.h>  // для генерации случайных чисел
#include <time.h>    // для генерации случайных чисел

// псевдоним типа натуральное число = unsigned int:
typedef unsigned natural;

// ОБЪЯВЛЕНИЕ ВСПОМОГАТЕЛЬНЫХ ФУНКЦИЙ:
natural get_positive_number(const char* text_to_user = "", int max = 65'534);
void get_array_from_user(natural* array, const natural size, const natural max = 100);
void get_array_by_random(natural* array, const natural size, const natural max = 100);
void print_array(const natural* array, const natural size);
enum Bool { False = 0, True = 1 };
natural find_NOD(const natural* array, const natural size);

// ГЛАВНАЯ ФУНКЦИЯ
int main()
{
    setlocale(LC_CTYPE, "Russian");  // для кириллицы

    printf("Данная программа находит Наибольший Общий Делитель (НОД) для массива чисел.\n\n");

    natural length = get_positive_number("Введите количество чисел в массиве", 30);
    natural* array = new natural[length];
    
    // получаем элементы массива от пользователя или случайным образом (раскомментировать нужное):
    get_array_from_user(array, length);
    //srand(time(NULL));                 // типа randomize, чтобы с каждым запуском программы генерировались разные числа
    //get_array_by_random(array, length);

    print_array(array, length);

    printf("НОД для данного массива: %d\n\n", find_NOD(array, length));

    delete[] array;
    return 0;
}

// ОПРЕДЕЛЕНИЕ ВСПОМОГАТЕЛЬНЫХ ФУНКЦИЙ:

// получаем целое положительное число от пользователя в рамках диапазона 0, max
natural get_positive_number(const char* text_to_user, int max)
{
    char text_number[256];
    int number = 0;
    do
    {
        printf("%s (целое положительное число не больше %d): ", text_to_user, max);
        scanf("%s", text_number);
        number = atoi(text_number);
    } while (number <= 0 || number > max);
    return (natural)number;
}

// получаем от пользователя заданное количество элементов массива
void get_array_from_user(natural* array, const natural size, const natural max)
{
    printf("Введите %d элементов массива:\n", size);
    for (natural i = 0; i < size; ++i)
        array[i] = get_positive_number("", max);
}

// получаем заданное количество элементов массива с помощью генератора псевдослучайных чисел
void get_array_by_random(natural* array, const natural size, const natural max)
{
    for (natural i = 0; i < size; ++i)
        array[i] = rand() % max + 1;
}

// выводим на экран все элементы переданного массива
void print_array(const natural* array, const natural size)
{
    printf("\nВсе элементы массива:\n");
    for (natural i = 0; i < size; )
    {
        printf("%4i ", array[i++]);
        if (i % 10 == 0)            // не больше 10 чисел в строке
            printf("\n");
    }
    printf("\n\n");
}

// находим наименьший элемент массива
natural find_min_element(const natural* array, const natural size)
{
    natural min = array[0];
    for (natural i = 1; i < size; ++i)
        if (array[i] < min)
            min = array[i];
    return min;
}

// проверяем, делит ли переданный делитель все элементы массива
Bool check_divider_for_array(const natural* array, const natural size, const natural divider)
{
    natural index = 0;
    while (index < size)
        if (array[index++] % divider != 0)
            return False;
    return True;
}

// находим наибольший общий делитель всех элементов массива
natural find_NOD(const natural* array, const natural size)
{
    // т.к. НОД не может быть больше минимального элемента, отталкиваться будем от него
    natural min = find_min_element(array, size);
    if (check_divider_for_array(array, size, min))
        return min;
    
    for (natural max_divider = min/2; max_divider > 1; --max_divider)
        if (check_divider_for_array(array, size, max_divider))
            return max_divider;
    
    return 1;
}