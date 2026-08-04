#pragma once
#include "models.h"

int sqlite_init_db(const char *filename);

/* Campus */
int add_campus_sqlite(const Campus *c);
void list_campuses_sqlite();

/* Curso */
int add_curso_sqlite(const Curso *c);
void list_cursos_sqlite();

/* Aluno */
int add_aluno_sqlite(const Aluno *a);
void list_alunos_sqlite();

/* Professor */
int add_professor_sqlite(const Professor *p);
void list_professores_sqlite();
