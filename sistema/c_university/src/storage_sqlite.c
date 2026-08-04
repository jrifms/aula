#include "storage_sqlite.h"
#include <stdio.h>

#ifdef HAVE_SQLITE
#include <sqlite3.h>

static sqlite3 *db = NULL;

int sqlite_init_db(const char *filename) {
    if (sqlite3_open(filename, &db) != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir DB: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    char *err = NULL;
    const char *schema =
        "CREATE TABLE IF NOT EXISTS campus (id INTEGER PRIMARY KEY, nome TEXT);"
        "CREATE TABLE IF NOT EXISTS curso (id INTEGER PRIMARY KEY, nome TEXT, campus_id INTEGER);"
        "CREATE TABLE IF NOT EXISTS aluno (id INTEGER PRIMARY KEY, nome TEXT, curso_id INTEGER);"
        "CREATE TABLE IF NOT EXISTS professor (id INTEGER PRIMARY KEY, nome TEXT, curso_id INTEGER);";
    if (sqlite3_exec(db, schema, 0, 0, &err) != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabelas: %s\n", err);
        sqlite3_free(err);
        return -1;
    }
    return 0;
}

int add_campus_sqlite(const Campus *c) {
    if (!db) return -1;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO campus (nome) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return -1;
    sqlite3_bind_text(stmt, 1, c->nome, -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) { sqlite3_finalize(stmt); return -1; }
    sqlite3_finalize(stmt);
    return (int)sqlite3_last_insert_rowid(db);
}

void list_campuses_sqlite() {
    if (!db) { printf("DB não inicializado.\n"); return; }
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, nome FROM campus;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return;
    printf("ID | Nome\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        printf("%d | %s\n", id, nome);
    }
    sqlite3_finalize(stmt);
}

/* Implementação para curso/aluno/professor segue padrão semelhante */
int add_curso_sqlite(const Curso *c) {
    if (!db) return -1;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO curso (nome, campus_id) VALUES (?,?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return -1;
    sqlite3_bind_text(stmt, 1, c->nome, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, c->campus_id);
    if (sqlite3_step(stmt) != SQLITE_DONE) { sqlite3_finalize(stmt); return -1; }
    sqlite3_finalize(stmt);
    return (int)sqlite3_last_insert_rowid(db);
}

void list_cursos_sqlite() {
    if (!db) { printf("DB não inicializado.\n"); return; }
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, nome, campus_id FROM curso;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return;
    printf("ID | Nome | CampusID\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        int campus = sqlite3_column_int(stmt, 2);
        printf("%d | %s | %d\n", id, nome, campus);
    }
    sqlite3_finalize(stmt);
}

int add_aluno_sqlite(const Aluno *a) {
    if (!db) return -1;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO aluno (nome, curso_id) VALUES (?,?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return -1;
    sqlite3_bind_text(stmt, 1, a->nome, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, a->curso_id);
    if (sqlite3_step(stmt) != SQLITE_DONE) { sqlite3_finalize(stmt); return -1; }
    sqlite3_finalize(stmt);
    return (int)sqlite3_last_insert_rowid(db);
}

void list_alunos_sqlite() {
    if (!db) { printf("DB não inicializado.\n"); return; }
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, nome, curso_id FROM aluno;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return;
    printf("ID | Nome | CursoID\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        int curso = sqlite3_column_int(stmt, 2);
        printf("%d | %s | %d\n", id, nome, curso);
    }
    sqlite3_finalize(stmt);
}

int add_professor_sqlite(const Professor *p) {
    if (!db) return -1;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO professor (nome, curso_id) VALUES (?,?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return -1;
    sqlite3_bind_text(stmt, 1, p->nome, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, p->curso_id);
    if (sqlite3_step(stmt) != SQLITE_DONE) { sqlite3_finalize(stmt); return -1; }
    sqlite3_finalize(stmt);
    return (int)sqlite3_last_insert_rowid(db);
}

void list_professores_sqlite() {
    if (!db) { printf("DB não inicializado.\n"); return; }
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, nome, curso_id FROM professor;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return;
    printf("ID | Nome | CursoID\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        int curso = sqlite3_column_int(stmt, 2);
        printf("%d | %s | %d\n", id, nome, curso);
    }
    sqlite3_finalize(stmt);
}

#else

int sqlite_init_db(const char *filename) {
    (void)filename;
    fprintf(stderr, "Compilar com -DHAVE_SQLITE e linkar -lsqlite3 para usar SQLite.\n");
    return -1;
}
int add_campus_sqlite(const Campus *c) { (void)c; return -1; }
void list_campuses_sqlite() { printf("SQLite não habilitado.\n"); }
int add_curso_sqlite(const Curso *c) { (void)c; return -1; }
void list_cursos_sqlite() { printf("SQLite não habilitado.\n"); }
int add_aluno_sqlite(const Aluno *a) { (void)a; return -1; }
void list_alunos_sqlite() { printf("SQLite não habilitado.\n"); }
int add_professor_sqlite(const Professor *p) { (void)p; return -1; }
void list_professores_sqlite() { printf("SQLite não habilitado.\n"); }

#endif
