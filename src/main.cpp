#include <cstdio>
#include "BackwardChecker.h"
#include "AigerModel.h"
#include "Settings.h"
#include <string.h>
using namespace car;
using namespace std;

void PrintUsage ();
Settings GetArgv(int argc, char **argv);

    
    





int main(int argc, char** argv)
{
    Settings settings = GetArgv(argc, argv);
    AigerModel* aigerModel = new AigerModel(settings.aigFilePath);
    
    BaseChecker* checker = new BackwardChecker(settings, aigerModel);
    checker->Run();
    delete aigerModel;
    delete checker;
    return 0;
}

void PrintUsage()
{
    printf ("Usage: simplecar <-f|-b> [-e|-v|-h] <-begin|-end> <-interation|-rotation|-interation -rotation> <aiger file> <output directory>\n");
    printf ("       -f              forward checking (Default = backward checking)\n");
    printf ("       -b              backward checking \n");
    printf ("       -begin          state numeration from begin of the sequence\n");
    printf ("       -end            state numeration from end of the sequence\n");
    printf ("       -interaion      enable intersection heuristic\n");
    printf ("       -rotation       enable rotation heurisitc\n");
    printf ("       -e              print witness (Default = off)\n");
    printf ("       -v              print verbose information (Default = off)\n");
    printf ("       -h              print help information\n");
    printf ("NOTE: -f and -b cannot be used together!\n");
    printf ("NOTE: -begin and -end cannot be used together!\n");
    exit (0);
}

Settings GetArgv(int argc, char** argv)
{
    bool hasSetInputDir = false;
    bool hasSetOutputDir = false;
    Settings settings;
    for (int i = 1; i < argc; i ++)
    {
        if (strcmp (argv[i], "-f") == 0)
        {
            settings.forward = true;
        }
        else if (strcmp (argv[i], "-b") == 0)
        {
            settings.forward = false;
        }
        else if (strcmp (argv[i], "-v") == 0)
        {
            settings.verbose = true;
        }
        else if (strcmp (argv[i], "-e") == 0)
        {
            settings.evidence = true;
        }
        else if (!hasSetInputDir)
        {
            settings.aigFilePath = string (argv[i]);
            hasSetInputDir = true;
        }
        else if (!hasSetOutputDir)
        {
            settings.outputDir = string (argv[i]);
            if (settings.outputDir[settings.outputDir.length()-1] != '/')
            {
                settings.outputDir += "/";
            }
            hasSetOutputDir = true;
        }
        else
        {
            PrintUsage ();
        }
    }
    return settings;
}