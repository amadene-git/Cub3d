#ifndef FILE_CONFIG_H
# define FILE_CONFIG_H

typedef struct  s_fileConfig {
    const char      *_filename;
    char            **_fileDuplicate;
    unsigned int    _resolutionWidth;
    unsigned int    _resolutionHeight;
}               t_fileConfig;

#endif