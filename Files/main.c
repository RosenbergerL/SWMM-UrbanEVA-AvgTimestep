//-----------------------------------------------------------------------------
//   main.c
//
//   Project:  EPA SWMM5
//   Version:  5.1
//   Date:     05/10/2018 (5.1.013)
//             03/20/2020 (Build UrbanEva ue)
//   Author:   L. Rossman
//             M. Henrichs (IWARU)
//
//  Build UrbanEva (ue):
//  - adding procedure for testing, version info

//   Main stub for the command line version of EPA SWMM 5.1
//   to be run with swmm5.dll.

#include <stdio.h>
#include <time.h>
#include "swmm5.h"

int  main(int argc, char *argv[])
//
//  Input:   argc = number of command line arguments
//           argv = array of command line arguments
//  Output:  returns error status
//  Purpose: runs the command line version of EPA SWMM 5.1.
//
//  Command line is: swmm5 f1  f2  f3
//  where f1 = name of input file, f2 = name of report file, and
//  f3 = name of binary output file if saved (or blank if not saved).
//
{
    char *inputFile;
    char *reportFile;
    char *binaryFile;
    char *arg1;
    char blank[] = "";
    int  version, vMajor, vMinor, vRelease;
    char errMsg[128];
    int  msgLen = 127;
    time_t start;
    double runTime;
    
    version = swmm_getVersion();
    vMajor = version / 10000;
    vMinor = (version - 10000 * vMajor) / 1000;
    vRelease = (version - 10000 * vMajor - 1000 * vMinor);
    start = time(0);

    ////(ue) section for testing, delete for final version
    //int testue = 0;
    //if (testue == 1)
    //{
    //    argc = 4;
    //    //argv[2] = "C:/10_AG-Uhl/06_Software/UrbanEva/source5_1_014/testdata/StArnold_Gruen_develop.rpt"; //argv[2];
    //    //argv[1] = "C:/10_AG-Uhl/06_Software/UrbanEva/source5_1_014/testdata/StArnold_Gruen_develop.inp"; //argv[1];
    //    //argv[3] = "C:/10_AG-Uhl/06_Software/UrbanEva/source5_1_014/testdata/StArnold_Gruen_develop.out";

    //    argv[2] = "C:/Daten/testdata/swmm_inp.rpt"; //argv[2];
    //    argv[1] = "C:/Daten/testdata/swmm_inp.inp"; //argv[1];
    //    argv[3] = "C:/Daten/testdata/swmm_inp.out";

    //    //argv[2] = "C:/10_AG-Uhl/06_Software/UrbanEva/source5_1_014/testdata/urbaneva.rpt"; //argv[2];
    //    //argv[1] = "C:/10_AG-Uhl/06_Software/UrbanEva/source5_1_014/testdata/urbaneva.inp"; //argv[1];
    //    //argv[3] = "C:/10_AG-Uhl/06_Software/UrbanEva/source5_1_014/testdata/urbaneva.out";


    //}
    ////end test section /*


    // --- check for proper number of command line arguments
    if (argc == 1)
    {
        printf("\nNot Enough Arguments (See Help --help)\n\n");
    }
    else if (argc == 2)
    {
        // --- extract first argument
        arg1 = argv[1];

        if (strcmp(arg1, "--help") == 0 || strcmp(arg1, "-h") == 0)
        {
            // Help
            printf("\n\nSTORMWATER MANAGEMENT MODEL (SWMM5) HELP\n\n");
            printf("COMMANDS:\n");
            printf("\t--help (-h)       Help Docs\n");
            printf("\t--version (-v)    Build Version\n");
            printf("\nRUNNING A SIMULATION:\n");
            printf("\t swmm5 <input file> <report file> <output file>\n\n");
        }
        else if (strcmp(arg1, "--version") == 0 || strcmp(arg1, "-v") == 0)
        {
            // Output version number
            printf("\n%d.%d.%0d\n\n", vMajor, vMinor, vRelease);
        }
        else
        {
            printf("\nUnknown Argument (See Help --help)\n\n");
        }
    }
    else
    {
        // --- extract file names from command line arguments
        inputFile = argv[1];
        reportFile = argv[2];
        if (argc > 3) binaryFile = argv[3];
        else          binaryFile = blank;

        printf("\n... EPA-SWMM %d.%d (Build %d.%d.%0d)\n", vMajor, vMinor,
            vMajor, vMinor, vRelease);

        // --- modified Version from IWARU by MH
        printf("    modified Version UrbanEva on basis of swmm 5.1.014 from IWARU by MH...\n");    // (ue)
        printf(argv[2]);                                                                         // (ue)

        // --- run SWMM
        swmm_run(inputFile, reportFile, binaryFile);

        // Display closing status on console
        runTime = difftime(time(0), start);
        printf("\n\n... EPA-SWMM completed in %.2f seconds.", runTime);
        if      ( swmm_getError(errMsg, msgLen) > 0 ) printf(" There are errors.\n");
        else if ( swmm_getWarnings() > 0 ) printf(" There are warnings.\n");
        else printf("\n");
    }

// --- Use the code below if you need to keep the console window visible
 
    //printf("    press enter to continue...");
    //getchar();


    return 0;
}