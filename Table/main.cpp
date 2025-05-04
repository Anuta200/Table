#include <iostream>
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "ArrayHashTable.h"
#include "ListHashTable.h"
#include <string>
#include <ctime>
using namespace std;


//template <typename TKey, typename TVal>
//void PrintTable(Table<TKey, TVal>& table, const string& tableName) {
//    cout << "\n" << tableName << " contents:" << endl;
//    table.Reset();
//    while (!table.IsEnd()) {
//        cout << "Key: " << table.getCurrKey() << ", Value: " << table.getCurrVal() << endl;
//        table.GoNext();
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//    const int tableSize = 11;
//    const int keyRange = 100;
//    Record<int, string> commonRecord = { 1, "Common Value" };
//    
//    ScanTable<int, string> scanTable(tableSize+1);
//    scanTable.fillTab(tableSize, keyRange);
//    try {
//        scanTable.Insert(commonRecord);
//    }
//    catch (const runtime_error& e) {
//        cerr << "Ошибка при вставке в scanTable: " << e.what() << endl;
//    }
//    scanTable.Delete(1);
//    
//    
//    SortTable<int, string> sortTable(tableSize+1);
//    sortTable.fillTab(tableSize, keyRange);
//    try {
//        sortTable.Insert(commonRecord);
//    }
//    catch (const runtime_error& e) {
//        cerr << "Ошибка вставки в SortTable: " << e.what() << endl;
//    }
//    sortTable.QSort();
//    sortTable.Delete(1);
//
//
//    ArrayHashTable<int, string> arrayHashTable(tableSize+1); 
//    arrayHashTable.fillTab(tableSize, keyRange);
//    try {
//        arrayHashTable.Insert(commonRecord);
//    }
//    catch (const runtime_error& e) {
//        cerr << "Ошибка вставки в ArrayHashTable: " << e.what() << endl;
//    }
//    arrayHashTable.Delete(1);
//
//    
//    ListHashTable<int, string> listHashTable(tableSize * 2);
//    listHashTable.fillTab(tableSize, keyRange);
//    try {
//        listHashTable.Insert(commonRecord);
//    }
//    catch (const runtime_error& e) {
//        cerr << "Ошибка вставки в ListHashTable: " << e.what() << endl;
//    }
//    listHashTable.Delete(1);
//
//    
//
//    
//    std::cout << "\nTable sizes:" << std::endl;
//    std::cout << "ScanTable: " << scanTable.getDataCount() << std::endl;
//    std::cout << "SortTable: " << sortTable.getDataCount() << std::endl;
//    std::cout << "ArrayHashTable: " << arrayHashTable.getDataCount() << std::endl;
//    std::cout << "ListHashTable: " << listHashTable.getDataCount() << std::endl;
//
//    PrintTable(scanTable, "ScanTable");
//    PrintTable(sortTable, "SortTable");
//    PrintTable(arrayHashTable, "ArrayHashTable");
//    PrintTable(listHashTable, "ListHashTable");
//    return 0;
//}


enum TTabMode { SCAN_TABLE = 1, SORT_TABLE = 2, HASH_TABLE1 = 3, HASH_TABLE2 = 4, };

Table<int, string>* pTab = nullptr;
int* pKeys = nullptr;
string* pVals = nullptr;
int DataCount = 0, MemSize = 0;

void CreateTable(TTabMode mode) {
    int MaxKey;
    cout << "Введите количество записей: ";
    cin >> DataCount;
    cout << "Введите максимальный ключ: ";
    cin >> MaxKey;

    MemSize = DataCount+1;  

    
    switch (mode) {
    case SCAN_TABLE:
        pTab = new ScanTable<int, string>(MemSize);
        break;
    case SORT_TABLE:
        pTab = new SortTable<int, string>(MemSize);
        break;
    /*case TREE_TABLE:
        pTab = new TTreeTable();
        break;*/
    case HASH_TABLE1:
        pTab = new ArrayHashTable<int, string>(MemSize);
        break;
    case HASH_TABLE2:
        pTab = new ListHashTable<int, string>(MemSize);
        break;
}

    pKeys = new int[MemSize];
    pVals = new string[MemSize];

    pTab->fillTab(DataCount, MaxKey);

    pTab->ClearEff();
}

bool ProcessTable(TTabMode mode) {
    while (true) {
        int cmd, key;
        string rec;

        cout << "\n0 - Новая таблица, 1 - Поиск, 2 - Вставка, 3 - Удаление, 4 - Печать, 5 - Выход\n";
        cout << "Выберите команду: ";
        cin >> cmd;

        switch (cmd) {
        case 0:
            return false;

        case 1: // Поиск
            cout << "Введите ключ: ";
            cin >> key;
            pTab->ClearEff();
            cout << "Найдено: " << pTab->Find(key) << endl;
            cout << "Эффективность: " << pTab->getEff() << endl;
            break;

        case 2: // Вставка
            cout << "Введите ключ: ";
            cin >> key;
            cout << "Введите значение: ";
            cin >> rec;
            pTab->ClearEff();
            
            
            try {
                pTab->Insert(Record<int, string>(key, rec));
                if (mode == HASH_TABLE2) {
                    if (DataCount >= MemSize) {
                        int newSize = MemSize * 2 + 1;
                        int* newKeys = new int[newSize];
                        string* newVals = new string[newSize];
                        for (int i = 0; i < MemSize; i++) {
                            newKeys[i] = pKeys[i];
                            newVals[i] = pVals[i];
                        }
                        delete[] pKeys;
                        delete[] pVals;
                        pKeys = newKeys;
                        pVals = newVals;
                        MemSize = newSize;
                    }
                }

                pKeys[DataCount] = key;
                pVals[DataCount] = rec;
             
                
            }
            catch (const runtime_error& e) {
                cerr << "Ошибка вставки: " << e.what() << endl; 
            }
            cout << "Эффективность: " << pTab->getEff() << endl;
            break;

        case 3: // Удаление
            cout << "Введите ключ: ";
            cin >> key;
            pTab->ClearEff();
            try {
                pTab->Delete(key);
                            }
            catch (const runtime_error& e) {
                cerr << "Ошибка удвления: " << e.what() << endl;
            }
           // pTab->Delete(key);
            cout << "Эффективность: " << pTab->getEff() << endl;
            break;

        case 4: // Печать
            pTab->ClearEff();
            if (mode == HASH_TABLE2) {
                auto* hashTab = dynamic_cast<ListHashTable<int, string>*>(pTab);
                if (hashTab) {
                    hashTab->PrintTable(); 
                }
                else {
                    cout << "Ошибка: Таблица не является ListHashTable\n";
                }
            }
            else {
                cout << *pTab;
            }
            break;


        case 5: // Выход
            return true;

        default:
            cout << "Неверная команда!" << endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Тест таблиц\n";

    while (true) {
        int type;
        cout << "\nВыберите тип таблицы:\n";
        cout << "1 - Последовательный поиск\n";
        cout << "2 - Отсортированная таблица\n";
        cout << "3 - Хэш-таблица\n";
        cout << "4 - Хэш-таблица с цепочками\n";
        cout << "Тип: ";
        cin >> type;

        CreateTable((TTabMode)type);

        if (ProcessTable((TTabMode)type))
            break;
    }

    delete[] pKeys;
    delete[] pVals;

    return 0;
}

