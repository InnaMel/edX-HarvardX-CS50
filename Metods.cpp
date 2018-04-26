#include "Metods.h"

// asking user path
bool recordPath(wstring *result)
{
    WCHAR userAnswer[MAX_PATH];
    wcout << L"Enter path for scanning or press \"Q\" for exit: ";
    wcin >> userAnswer;
    wcout << endl;

    // *result - dereferensing variable (for access into value variable)
    *result = userAnswer;

    if ((*result == L"q") || (*result == L"Q"))
    {
        return false;
    }
    else
    {
        return true;
    }
}

// checking user path in correct
bool dirExists(const wstring &userPath)
{
    DWORD ftyp = GetFileAttributes(userPath.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
    {
        return false;  //something is wrong with your path!
    }

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;   // this is a directory!
    }

    return false;    // this is not a directory!
}

// creating list, searching all files from users directory
void listContent(wstring firstPath, filesList *foundFiles)
{
    wstring astra = _T("*");
    wstring yourPath = firstPath + astra;

    WIN32_FIND_DATAW wfd;
    HANDLE const hFind = FindFirstFile(yourPath.c_str(), &wfd);
    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            wstring fileName = wfd.cFileName;
            if ((fileName != L".") && (fileName != L".."))
            {
                wstring f;
                wstring fullPath = firstPath + fileName;
                if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    //f = L"Folder ";
                    listContent(fullPath + L"\\", foundFiles);
                }
                else
                {
                    FileItem *foundItem = new FileItem();
                    foundFiles->push_back(foundItem);
                    foundItem->name = fileName;
                    foundItem->path = firstPath;
                }
            }
        }
        while (NULL != FindNextFile(hFind, &wfd));

        FindClose(hFind);
    }
}

// searching all duplicates files from general list
void findDuplicates(filesList *files, vector<filesList *> *duplicates)
{
    int lengthfiles = files->size();
    for (int i = 0; i < lengthfiles; i++)
    {
        FileItem *item1 = files->at(i);
        if (item1->marked == false)
        {
            filesList *list = NULL;
            for (int j = i + 1; j < lengthfiles; j++)
            {
                FileItem *item2 = files->at(j);
                if ((item2->marked == false) && (lstrcmpi(item1->name.c_str(), item2->name.c_str()) == 0))
                {
                    if (list == NULL)
                    {
                        list = new filesList();
                        duplicates->push_back(list);
                        list->push_back(item1);
                    }
                    list->push_back(item2);
                    item2->marked = true;
                }
            }
        }
    }
}

// print on the console all duplicates lists
void printDuplicatesLists(vector<filesList *> *duplicates)
{
    for (size_t i = 0; i < duplicates->size(); i++)
    {
        wcout << L"Duplicate:" << endl;
        filesList *item = duplicates->at(i);
        for (size_t j = 0; j < item->size(); j++)
        {
            FileItem *fileItem = item->at(j);
            wcout << L"\t" << fileItem->fullPath().c_str() << endl;
        }
        wcout << endl;
    }
}

// clear general search result
void clearSearchResult(filesList *foundFiles)
{
    for (size_t i = 0; i < foundFiles->size(); i++)
    {
        FileItem *item = foundFiles->at(i);
        delete item;
    }
    foundFiles->clear();
}

void clearDuplicateLists(vector<filesList *> *duplicates)
{
    for (size_t i = 0; i < duplicates->size(); i++)
    {
        // "delete" - clear memory by pointer (when we allocate memory with "new")
        delete duplicates->at(i);
    }

    // "clear()" - clear memory which we use for variable (in this case clear 8b for each pointer in list)
    duplicates->clear();
}
