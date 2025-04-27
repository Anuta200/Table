#include <iostream>
#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "ArrayHashTable.h"
#include "ListHashTable.h"
using namespace std;


template <typename TKey, typename TVal>
void PrintTable(Table<TKey, TVal>& table, const string& tableName) {
    cout << "\n" << tableName << " contents:" << endl;
    table.Reset();
    while (!table.IsEnd()) {
        cout << "Key: " << table.getCurrKey() << ", Value: " << table.getCurrVal() << endl;
        table.GoNext();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    const int tableSize = 11;
    const int keyRange = 100;
    Record<int, string> commonRecord = { 1, "Common Value" };
    
    ScanTable<int, string> scanTable(tableSize+1);
    scanTable.fillTab(tableSize, keyRange);
    try {
        scanTable.Insert(commonRecord);
    }
    catch (const runtime_error& e) {
        cerr << "Ошибка при вставке в scanTable: " << e.what() << endl;
    }
    scanTable.Delete(1);
    
    
    SortTable<int, string> sortTable(tableSize+1);
    sortTable.fillTab(tableSize, keyRange);
    try {
        sortTable.Insert(commonRecord);
    }
    catch (const runtime_error& e) {
        cerr << "Ошибка вставки в SortTable: " << e.what() << endl;
    }
    sortTable.QSort();
    sortTable.Delete(1);


    ArrayHashTable<int, string> arrayHashTable(tableSize+1); 
    arrayHashTable.fillTab(tableSize, keyRange);
    try {
        arrayHashTable.Insert(commonRecord);
    }
    catch (const runtime_error& e) {
        cerr << "Ошибка вставки в ArrayHashTable: " << e.what() << endl;
    }
    arrayHashTable.Delete(1);

    
    ListHashTable<int, string> listHashTable(tableSize * 2);
    listHashTable.fillTab(tableSize, keyRange);
    try {
        listHashTable.Insert(commonRecord);
    }
    catch (const runtime_error& e) {
        cerr << "Ошибка вставки в ListHashTable: " << e.what() << endl;
    }
    listHashTable.Delete(1);

    

    
    std::cout << "\nTable sizes:" << std::endl;
    std::cout << "ScanTable: " << scanTable.getDataCount() << std::endl;
    std::cout << "SortTable: " << sortTable.getDataCount() << std::endl;
    std::cout << "ArrayHashTable: " << arrayHashTable.getDataCount() << std::endl;
    std::cout << "ListHashTable: " << listHashTable.getDataCount() << std::endl;

    PrintTable(scanTable, "ScanTable");
    PrintTable(sortTable, "SortTable");
    PrintTable(arrayHashTable, "ArrayHashTable");
    PrintTable(listHashTable, "ListHashTable");
    return 0;
}
