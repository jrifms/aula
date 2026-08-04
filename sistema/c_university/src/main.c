#include <stdio.h>
#include <string.h>
#include "models.h"
#include "storage_file.h"
#include "storage_sqlite.h"

static void ler_texto(const char *prompt, char *buf, size_t n) {
    printf("%s", prompt);
    if (!fgets(buf, n, stdin)) { buf[0] = '\0'; return; }
    size_t l = strlen(buf); if (l && buf[l-1]=='\n') buf[l-1]='\0';
}

int main() {
    storage_init_file();
    printf("Sistema de cadastro - arquivos CSV / SQLite\n");
    int use_sqlite = 0;
#ifdef HAVE_SQLITE
    if (sqlite_init_db("university.db") == 0) use_sqlite = 1;
#endif
    while (1) {
        printf("\nMenu:\n1) Adicionar campus\n2) Listar campus\n3) Adicionar curso\n4) Listar cursos\n5) Adicionar aluno\n6) Listar alunos\n7) Adicionar professor\n8) Listar professores\n0) Sair\nEscolha: ");
        int op = 0;
        if (scanf("%d", &op) != 1) break;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (op == 0) break;
        if (op == 1) {
            Campus cam = {0};
            ler_texto("Nome do campus: ", cam.nome, NAME_MAX);
            if (use_sqlite) {
                int id = add_campus_sqlite(&cam);
                printf("Inserido (sqlite) id=%d\n", id);
            } else {
                int id = add_campus_file(&cam);
                printf("Inserido (arquivo) id=%d\n", id);
            }
        } else if (op == 2) {
            if (use_sqlite) list_campuses_sqlite(); else list_campuses_file();
        } else if (op == 3) {
            Curso cur = {0}; char buf[32];
            ler_texto("Nome do curso: ", cur.nome, NAME_MAX);
            ler_texto("Campus ID: ", buf, sizeof(buf)); cur.campus_id = atoi(buf);
            if (use_sqlite) printf("Inserido (sqlite) id=%d\n", add_curso_sqlite(&cur)); else printf("Inserido (arquivo) id=%d\n", add_curso_file(&cur));
        } else if (op == 4) {
            if (use_sqlite) list_cursos_sqlite(); else list_cursos_file();
        } else if (op == 5) {
            Aluno a = {0}; char buf[32];
            ler_texto("Nome do aluno: ", a.nome, NAME_MAX);
            ler_texto("Curso ID: ", buf, sizeof(buf)); a.curso_id = atoi(buf);
            if (use_sqlite) printf("Inserido (sqlite) id=%d\n", add_aluno_sqlite(&a)); else printf("Inserido (arquivo) id=%d\n", add_aluno_file(&a));
        } else if (op == 6) {
            if (use_sqlite) list_alunos_sqlite(); else list_alunos_file();
        } else if (op == 7) {
            Professor p = {0}; char buf[32];
            ler_texto("Nome do professor: ", p.nome, NAME_MAX);
            ler_texto("Curso ID: ", buf, sizeof(buf)); p.curso_id = atoi(buf);
            if (use_sqlite) printf("Inserido (sqlite) id=%d\n", add_professor_sqlite(&p)); else printf("Inserido (arquivo) id=%d\n", add_professor_file(&p));
        } else if (op == 8) {
            if (use_sqlite) list_professores_sqlite(); else list_professores_file();
        } else {
            printf("Opção inválida\n");
        }
    }
    printf("Tchau\n");
    return 0;
}
