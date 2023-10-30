#ifndef PASTEQUEARENA_OS_H
#define PASTEQUEARENA_OS_H

// All supported operating systems in Pasteque ARENA:
// - GNU/Linux (it's actually important to specify "GNU" because we have Android)
// - Other UNIX-based systems (approximative support)
// - Windows (7+)
// - Android (API 21+)

// All of those macros are defined by CMake.

#ifndef PA_OS_LINUX
#define PA_OS_LINUX 0
#endif

#ifndef PA_OS_UNIX
#define PA_OS_UNIX PA_OS_LINUX
#endif

#ifndef PA_OS_WINDOWS
#define PA_OS_WINDOWS 0
#endif

#ifndef PA_OS_ANDROID
#define PA_OS_ANDROID 0
#endif

#endif //PASTEQUEARENA_OS_H
