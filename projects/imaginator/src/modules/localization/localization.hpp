#include <string>

namespace LOCALIZATION {
const std::string MESSAGE_WELCOME = "--IMAGINATOR--\n\nPress ENTER to continue...\n";

const std::string MESSAGE_HELP =
    "Use the arguments below:\n"
    "--help                                                             - an instruction.\n"
    "--negative                                                         - reverse colors.\n"
    "--replace {which} {replace}                                        - replace color.\n"
    "--sepia                                                            - sepia effect.\n"
    "--grayscale                                                        - grayscale effect.\n"
    "--improve-quality                                                  - improve quality.\n"
    "--gaussian-blur                                                    - blur.\n"
    "--edge-selection                                                   - select edges.\n"
    "--noise-remove                                                     - remove noise.\n"
    "--cut {x} {y} {height} {width}                                     - cut.\n"
    "\nExamples:\n"
    "• img --negaive --edge-selection image.bmp result.bmp              - apply negative and edge filters.\n"
    "• img --gaussian-blur --cut 0 0 128 128 image.bmp result.bmp       - apply blur and cut filters.\n"
    "• img --noise-remove --improve-quality image.bmp result.bmp        - apply noise removal and quality improval "
    "filters.\n";

const std::string MESSAGE_HELP_INTERACTIVE =
    "Use the commands below to navigate:\n"
    "ls                                                                 - display files in current folder.\n"
    "cd {path}                                                          - change the current directory.\n"
    "open {file}                                                        - open bitmap.\n"
    "save {file}                                                        - save bitmap.\n"
    "exit                                                               - exit.\n"
    "undo                                                               - undo.\n"
    "redo                                                               - redo.\n"
    "apply                                                              - apply filters.\n";

const std::string MESSAGE_IMAGE_SAVED = "Image was successfully saved.";

const std::string MESSAGE_EXCEPTION_INVALID_ARGUMENT = "Exception! Invalid parameters were provided by user!";
const std::string MESSAGE_EXCEPTION_NOTHING_TO_UNDO = "Exception! Nothing to undo!",
                  MESSAGE_EXCEPTION_NOTHING_TO_REDO = "Exception! Nothing to redo!";

const std::string MESSAGE_EXCEPTION_CANNOT_OPEN_BITMAP = "Exception! Cannot open!",
                  MESSAGE_EXCEPTION_CANNOT_SAVE_BITMAP = "Exception! Cannot save!";

const std::string ARGUMENT_HELP = "--help", ARGUMENT_NEGATIVE = "--negative", ARGUMENT_REPLACE_COLOR = "--replace",
                  ARGUMENT_SEPIA = "--sepia", ARGUMENT_IMPROVE_QUALITY = "--improve-quality",
                  ARGUMENT_GAUSSIAN_BLUR = "--gaussian-blur", ARGUMENT_EDGE_SELECTION = "--edge-selection",
                  ARGUMENT_NOISE_REMOVE = "--noise-remove", ARGUMENT_CUT = "--cut", ARGUMENT_GRAYSCALE = "--grayscale";
}  // namespace LOCALIZATION