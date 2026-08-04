#pragma once

#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX 128

typedef struct {
    int id;
    char nome[NAME_MAX];
} Campus;

typedef struct {
    int id;
    char nome[NAME_MAX];
    int campus_id;
} Curso;

typedef struct {
    int id;
    char nome[NAME_MAX];
    int curso_id;
} Aluno;

typedef struct {
    int id;
    char nome[NAME_MAX];
    int curso_id;
} Professor;
