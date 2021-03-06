// This program reads a unicharset file, puts the result in a UNICHARSET
// object, fills it with properties about the unichars it contains and writes
// the result back to a file.

#include <stdlib.h>
#include <string.h>
#include <string>

#include "commandlineflags.h"
#include BLIK_TESSERACT_U_tprintf_h //original-code:"tprintf.h"
#include "unicharset_training_utils.h"

// The directory that is searched for universal script unicharsets.
STRING_PARAM_FLAG(script_dir, "",
                  "Directory name for input script unicharsets/xheights");

// Flags from commontraining.cpp
DECLARE_STRING_PARAM_FLAG(U);
DECLARE_STRING_PARAM_FLAG(O);
DECLARE_STRING_PARAM_FLAG(X);

int main(int argc, char** argv) {
  tesseract::ParseCommandLineFlags(argv[0], &argc, &argv, true);

  // Check validity of input flags.
  if (FLAGS_U.empty() || FLAGS_O.empty()) {
    tprintf("Specify both input and output unicharsets!\n");
    exit(1);
  }
  if (FLAGS_script_dir.empty()) {
    tprintf("Must specify a script_dir!\n");
    exit(1);
  }

  tesseract::SetPropertiesForInputFile(FLAGS_script_dir.c_str(),
                                       FLAGS_U.c_str(), FLAGS_O.c_str(),
                                       FLAGS_X.c_str());
  return 0;
}
