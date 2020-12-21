// Laba4.cpp : Defines the entry point for the console application.
//

#include <windows.h>        // for SetConsoleCursorPosition(...)
#include <conio.h>          // for getch()

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

short int mainmenu();

int       TextFromFile(string &text);
string    TextCorrection(string text);

void      Task1_printWordsNoNumbers(string word);
void      Task2_printWordsWithCaps(string word);
void      Task2_printTextWithCaps(string text);

void      LinearSearch(string text, string key);
void      BMSearch(string text, string key);

void      SplitString(string text, string seps, vector<string> &words);

//globals



int main() // меню
{
   setlocale(LC_ALL, "Russian");
   string text;

   short int choose_menu, exit = 0;

   while (1)
   {
      choose_menu = mainmenu();
      switch (choose_menu)
      {
      case 1:
         goto KeyboardExec;
      case 2:
         TextFromFile(text);
         goto ContinueExec;
      case 0:
         return -1;
         break;

      }
      cout << endl;
   }
KeyboardExec:
   {
   const int N = 100;
   char Str[N];

   cin.ignore();

   cin.getline(Str, N);
   text = Str;
   }

ContinueExec:

   cout << endl;
   cout << text << endl << endl;

   string newtext = TextCorrection(text);
   cout << endl;

   vector<string> words;

   SplitString(newtext, " ,?!\"", words);

   size_t i, i0 = words.size();
   /*
   for (i = 0; i < i0; i++)
   {
      cout << words[i];
      cout << endl;
   }
   */

   // Вывести на экран слова последовательности, не содержащие цифр.
   cout << endl;
   cout << "Задача 1: Вывести на экран слова последовательности, не содержащие цифр." << endl;
   for (i = 0; i < i0; i++)
      Task1_printWordsNoNumbers(words[i]);

   // Вывести все слова с первой заглавной буквой
   cout << endl;
   cout << "Задача 2.1: Вывести все слова с первой заглавной буквой" << endl;
   for (i = 0; i < i0; i++)
      Task2_printWordsWithCaps(words[i]);

   cout << endl;
   cout << "Задача 2.2: Вывести текст, все слова в котором с первой заглавной буквой" << endl;
   cout << "Нормальный текст: " << newtext << endl;
   cout << "Текст с капсами: ";
   Task2_printTextWithCaps(newtext);

   // Линейный поиск подстроки в строке
   string key;

   cout << endl;
   cout << "Задача 3: Линейный поиск" << endl;
   cout << "Введите строку для поиска: ";
   cin >> key;

   LinearSearch(newtext, key);


   // Поиск подстроки методом Бойера-Мура
   cout << endl;
   cout << "Задача 4: Алгоритм Бойера-Мура" << endl;
   cout << "Введите строку для поиска: ";
   cin >> key;

   BMSearch(newtext, key);


   cout << endl << endl << endl;
   cout << "Нажмите любую клавишу, чтобы выйти.";
   _getch();
   return 0;
}


short int mainmenu() // меню, выбор задания
{
   setlocale(LC_ALL, "Russian");
   short int i;
   cout << "Лабораторная работа №4 \n\n";
   cout << "Выберите пункт 1 или 2, чтобы продолжить, или 0, чтобы выйти. \n";
   cout << "1) Ввод текста с клавиатуры. \n";
   cout << "2) Ввод текста из текстового документа. \n";
   cout << "0) Выход\n" << endl;

   cout << "Выбор: ";

   while (1)
   {
      cin >> i;
      if ((i >= 0) & (i <= 2))
         break;
      else
         cout << "Некорректный ввод, повторите попытку.\n";
   }
   cout << "\n";
   return i;
}

/*
void TextFromKeyboard(string text)
{
   cout << "Попал в функцию" << endl;
   const int N = 500;
   char keytext[N];
   cin.getline (keytext, N);
   text = keytext;
   cout << text << endl;
   cout << "Функция закончилась" << endl;
}
*/

int TextFromFile(string &text)
{
   
   ifstream File;
   File.open("input.txt");

   if (!File.is_open())  //  Проверили, удалось ли открыть файл
   {
      cout << "Открыть файл не удалось! \n";
      return -1;
   }

   getline(File, text, '.');

   File.close();
   return 1;
}

bool IsValidSeq(char prev, char ch)
{
   bool bOk = true;

   string seq(" ,?!@");

   size_t i, iSize = seq.length();
   for (i = 0; i < iSize; i++)
   {
        if (ch == seq[i] && prev == ch) 
         return false;
   }

   return true;
}

string TextCorrection(string text)
{
   string out;
   char prev='\0';

   size_t i, iSize = text.length();
   for (i = 0; i < iSize; i++)
   {
      char ch = text[i];

      if (!IsValidSeq(prev, ch)) continue;

      if (out.length()) ch = tolower(ch);

      out += ch;
      prev = ch;
   }

   cout << out << endl;
   return out;
}

void SplitString(string text, string seps, vector<string>& words)
{
   words.clear();

   size_t start = text.find_first_not_of(seps);
   size_t end = start;

   while (start != std::string::npos)
   {
      // найдем следующее вхождение одного из разделителей
      end = text.find_first_of(seps, start);

      // добавим слово в вектор
      words.push_back(text.substr(start, end-start));
        
      // пропустим найденный разделитель, 
      // чтобы найти следующее начало
      start = text.find_first_not_of(seps, end);
   }
}

void Task1_printWordsNoNumbers(string word)
{
   size_t start = word.find_first_of("0123456789");
   if(start != std::string::npos)   // есть вхождение
      return;                       // выходим

   // 'нормальное' слово, выведем его в консоль
   cout << word << endl;
}

void Task2_printWordsWithCaps(string word)
{
   word[0] = toupper( word[0] );
   cout << word << endl;
}


void Task2_printTextWithCaps(string text)
{
   // создадим вектор из лексем, используя в качестве разделителей только пробелы
   // все знаки препинания попадут в набор (вектор)
   vector<string> results;
   SplitString(text, " ", results);

   string capsed;
   size_t i, i0 = results.size();
   for(i=0; i< i0; i++) 
   {
       string word = results[i];
       word[0] = toupper( word[0] );

       if( capsed.size()>0 ) capsed += ' ';
       capsed += word;
   }

   cout << capsed << endl;
};
 

void LinearSearch(string text, string key)
{
    bool   bFound = false;
    size_t start = text.find(key);
    size_t len   = key.length();

    while (start != std::string::npos)
    {
        cout << "Подстрока '" << key << "' найдена на позиции: " << start << "." << endl;
        bFound =  true;

        start = text.find(key, start + len);
    }

    if(!bFound)
        cout << "Подстрока '" << key << "' не найдена." << endl;
}

///////////////////////////////////////////////////////////////////////////////
//
# define NO_OF_CHARS 1024
 
// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(const char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
 
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}
 
void bmsearch(const char *txt, const char *pat)
{
    bool   bFound = false;
    int m = strlen(pat);
    int n = strlen(txt);
 
    int badchar[NO_OF_CHARS];
 
    badCharHeuristic(pat, m, badchar);
 
    int s = 0; // s is shift of the pattern with respect to text
    while (s <= (n - m))
    {
        int j = m - 1;
 
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
 
        if (j < 0)
        {
            cout << "Подстрока '" << pat << "' найдена на позиции: " << s << "." << endl;

            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
            bFound = true;
         }
 
        else
            s += max(1, j - badchar[txt[s + j]]);
    }

    if(!bFound)
        cout << "Подстрока '" << pat << "' не найдена." << endl;

}

void BMSearch(string text, string key)
{
    bmsearch(text.c_str(), key.c_str());
}

