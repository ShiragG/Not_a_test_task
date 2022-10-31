#include <iostream>
#include <ctime>

using namespace std;

bool is_exception(int value)
{
    int array_exception[] = {37, 38, 39, 40, 41, 42, 44, 46, 47, 58, 59, 60,
                             61, 62, 63, 64, 67, 80, 83, 88, 91, 92, 93, 94, 96, 123, 124, 125};

    for (int i : array_exception)
    {
        if (value == i)
        {
            return true;
        }
    }
    return false;
}

bool is_symbol(int value)
{
    if ((value >= 65) && (value <= 90) || (value >= 97) && (value <= 122))
    {
        return true;
    }
    return false;
}

bool is_number(int value)
{
    if ((value >= 48) && (value <= 57))
    {
        return true;
    }
    return false;
}

int *generate_array(int array_size, int *array)
{
    int random_value;
    bool success_generate;
    array = new int[array_size];
    
    for (int i = 0; i <= array_size; i++)
    {
        success_generate = false;
        while (!success_generate)
        {
            //Генерируем значение с 36 по 126 символ ASCII
            //При этом исключаем ненужные символы
            random_value = 36 + rand() % 90;

            if (!is_exception(random_value))
            {
                array[i] = random_value;
                success_generate = true;
            }
        }
    }
    return array;
}

void replace_symbol(int array_size, int *array, int symbol, int mode)
{

    for (int i = 0; i < array_size; i++)
    {
        if ((mode == 1) && (is_symbol(array[i])))
        {
            array[i] = symbol;
        }
        if ((mode == 2) && (is_number(array[i])))
        {
            array[i] = symbol;
        }
    }

}

int *count_repeat_symbols(int array_size, const int *array, int *result, int first_symbol, int second_symbol)
{
    result = new int[3]{};

    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == first_symbol)
        {
            result[0] += 1;
        }

        if (array[i] == second_symbol)
        {
            result[1] += 1;
        }

        if ((array[i] != first_symbol) && (array[i] != second_symbol))
        {
            result[2] += 1; //Незаменённые
        }
    }
    return result;
}

void print_array(int array_size, const int *array)
{
    for (int i = 0; i < array_size; i++)
    {
        cout << (char)array[i];
    }
    cout << endl;
}

int main()
{
    srand(time(0));
    int array_size = 0;
    int *array;
    int *result;
    char first_symbol;
    char second_symbol;

    //Запрашиваем строку
    cout << "Введите размер массива: ";
    cin >> array_size;
    cout << endl;

    //Генерируем массив
    array = generate_array(array_size, array);

    cout << "Сгенерированая строка: \n";
    print_array(array_size, array);

    //Заменяем буквы на символ
    cout << "Введите символ: " << endl;
    cin >> first_symbol;
    cout << "Заменяем все буквы на " << first_symbol << endl;
    replace_symbol(array_size, array, (int)first_symbol, 1);
    print_array(array_size, array);

    //Заменяем цифры
    cout << "Введите символ: " << endl;
    cin >> second_symbol;
    cout << "Заменяем все цифры на " << second_symbol << endl;
    replace_symbol(array_size, array, (int)second_symbol, 2);
    print_array(array_size, array);

    //Считаем повторения символов
    result = count_repeat_symbols(array_size, array, result,(int)first_symbol, (int)second_symbol);

    cout << "Символов " << first_symbol << " :" << result[0] << endl;
    cout << "Символов " << second_symbol << " :" << result[1] << endl;
    cout << "Незаменённые символы:" << result[2] << endl;

    delete[] array;
    delete[] result;

    return 0;
}