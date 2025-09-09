#pragma once

#ifdef _WIN32
#ifdef MLCPPPY_EXPORTS
#define MLCPPPY_API __declspec(dllexport)
#else
#define MLCPPPY_API __declspec(dllimport)
#endif
#else
#define MLCPPPY_API
#endif
