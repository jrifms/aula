#pragma once
#include "models.h"

void storage_init_file();

/* Campus */
int add_campus_file(const Campus *c);
void list_campuses_file();

/* Curso */
int add_curso_file(const Curso *c);
void list_cursos_file();

/* Aluno */
int add_aluno_file(const Aluno *a);
void list_alunos_file();

/* Professor */
int add_professor_file(const Professor *p);
void list_professores_file();
