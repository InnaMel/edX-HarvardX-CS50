#include "Metods.h"

int main()
{
    //  create of array all pointers of files
    filesList files;

    //  create of array of arrays pointers of files
    vector<filesList *> duplicates;

    // variable for user path (next way we use it for change it into pointer)
    wstring userPath;
    bool resultAnswer = true;
    do
    {
        // checking the correct entered path
        resultAnswer = recordPath(&userPath);
        if (resultAnswer)
        {
            if (!dirExists(userPath))
            {
                wcout << L"Invalid path" << endl;
            }
            else
            {
                // check if user do`t enter \ in the end, we add it
                WCHAR last = userPath.at(userPath.length() - 1);
                if (last != L'\\')
                {
                    userPath += L"\\";
                }

                // for correct display various language
                setlocale(LC_ALL, "");

                // finding each file from userPath, add and save in files
                listContent(userPath, &files);

                // searching all duplicates in files, save them in an individual array
                findDuplicates(&files, &duplicates);

                // print all duplicates on the console
                printDuplicatesLists(&duplicates);

                // after all delete all items and clear memory
                clearSearchResult(&files);
                clearDuplicateLists(&duplicates);
            }
        }
        else
        {
            break;
        }
    }
    while (true);

    system("pause");
    return 0;
}
