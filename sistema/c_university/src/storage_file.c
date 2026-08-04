#include "storage_file.h"
#include <stdio.h>
#include <string.h>

static const char *CAMPUS_FILE = "campus.csv";
static const char *CURSO_FILE = "curso.csv";
static const char *ALUNO_FILE = "aluno.csv";
static const char *PROF_FILE = "professor.csv";

void storage_init_file() {
    /* cria arquivos se não existirem */
    FILE *f;
    f = fopen(CAMPUS_FILE, "a+"); if (f) fclose(f);
    f = fopen(CURSO_FILE, "a+"); if (f) fclose(f);
    f = fopen(ALUNO_FILE, "a+"); if (f) fclose(f);
    f = fopen(PROF_FILE, "a+"); if (f) fclose(f);
}

static int next_id(FILE *f) {
    int id = 0;
    char line[512];
    rewind(f);
    while (fgets(line, sizeof(line), f)) {
        int cur;
        if (sscanf(line, "%d", &cur) == 1) id = cur;
    }
    return id + 1;
}

int add_campus_file(const Campus *c) {
    FILE *f = fopen(CAMPUS_FILE, "a+");
    if (!f) return -1;
    int id = next_id(f);
    fprintf(f, "%d,%s\n", id, c->nome);
    fclose(f);
    return id;
}

void list_campuses_file() {
    FILE *f = fopen(CAMPUS_FILE, "r");
    if (!f) { printf("Nenhum campus cadastrado.\n"); return; }
    char line[512];
    printf("ID | Nome\n");
    while (fgets(line, sizeof(line), f)) {
        int id; char nome[NAME_MAX];
        if (sscanf(line, "%d,%127[^"]", &id, nome) >= 1) {
            printf("%d | %s\n", id, nome);
        }
    }
    fclose(f);
}

int add_curso_file(const Curso *c) {
    FILE *f = fopen(CURSO_FILE, "a+");
    if (!f) return -1;
    int id = next_id(f);
    fprintf(f, "%d,%s,%d\n", id, c->nome, c->campus_id);
    fclose(f);
    return id;
}

void list_cursos_file() {
    FILE *f = fopen(CURSO_FILE, "r");
    if (!f) { printf("Nenhum curso cadastrado.\n"); return; }
    char line[512];
    printf("ID | Nome | CampusID\n");
    while (fgets(line, sizeof(line), f)) {
        int id; char nome[NAME_MAX]; int campus_id;
        if (sscanf(line, "%d,%127[^,],%d", &id, nome, &campus_id) >= 1) {
            printf("%d | %s | %d\n", id, nome, campus_id);
        }
    }
    fclose(f);
}

int add_aluno_file(const Aluno *a) {
    FILE *f = fopen(ALUNO_FILE, "a+");
    if (!f) return -1;
    int id = next_id(f);
    fprintf(f, "%d,%s,%d\n", id, a->nome, a->curso_id);
    fclose(f);
    return id;
}

void list_alunos_file() {
    FILE *f = fopen(ALUNO_FILE, "r");
    if (!f) { printf("Nenhum aluno cadastrado.\n"); return; }
    char line[512];
    printf("ID | Nome | CursoID\n");
    while (fgets(line, sizeof(line), f)) {
        int id; char nome[NAME_MAX]; int curso_id;
        if (sscanf(line, "%d,%127[^,],%d", &id, nome, &curso_id) >= 1) {
            printf("%d | %s | %d\n", id, nome, curso_id);
        }
    }
    fclose(f);
}

int add_professor_file(const Professor *p) {
    FILE *f = fopen(PROF_FILE, "a+");
    if (!f) return -1;
    int id = next_id(f);
    fprintf(f, "%d,%s,%d\n", id, p->nome, p->curso_id);
    fclose(f);
    return id;
}

void list_professores_file() {
    FILE *f = fopen(PROF_FILE, "r");
    if (!f) { printf("Nenhum professor cadastrado.\n"); return; }
    char line[512];
    printf("ID | Nome | CursoID\n");
    while (fgets(line, sizeof(line), f)) {
        int id; char nome[NAME_MAX]; int curso_id;
        if (sscanf(line, "%d,%127[^,],%d", &id, nome, &curso_id) >= 1) {
            printf("%d | %s | %d\n", id, nome, curso_id);
        }
    }
    fclose(f);
}
