#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <fstream>

using namespace std;

vector<string> getFiles(string cate_dir)
{
    vector<string> files;//存放文件名

    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if ((dir = opendir(cate_dir.c_str())) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
            continue;
        else if (ptr->d_type == 8)    ///file
            files.push_back(ptr->d_name);
        else if (ptr->d_type == 10)    ///link file
            continue;
        else if (ptr->d_type == 4)    ///dir
        {
            files.push_back(ptr->d_name);
        }
    }
    closedir(dir);

    //排序，按从小到大排序
    sort(files.begin(), files.end());
    return files;
}

int main(int argc, char *argv[])
{
    ofstream f;
    f.open("../data.csv");
    f << fixed;

    vector<string> files = getFiles(argv[1]);
    for (int i = 0; i < files.size(); i++)
    {
        f<<files[i]<<endl;
        cout << files[i] << endl;
    }
    f.close();

    cout << endl << "File Saved!" << endl;

    return 0;
}