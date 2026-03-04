#include <iostream>
#include "../../include/sqlite3.h"

void crearTabla(sqlite3* db) {
	char* zErrMsg = 0;

	std::string query = "CREATE TABLE alumnos ("
		" id INTEGER PRIMARY KEY AUTOINCREMENT,"
		" nombre TEXT,"
		" apellido TEXT)";

	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cout << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Consulta ejecutada con éxito" << std::endl;
	}
}

void queryVariable(sqlite3* db) {
    sqlite3_stmt* stmt;

    const char* sql_insert = "INSERT INTO alumnos (nombre, apellido) VALUES (?, ?)";
    sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);

	std::string nombre = "";
	std::string apellido = "";

    // Vincular variables
    sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, apellido.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt); // Ejecutar
    sqlite3_finalize(stmt); // Destruir el statement para liberar memoria

    // Obtener el ID que SQLite le asignó automáticamente
    long long id_creado = sqlite3_last_insert_rowid(db);

	// ====================================================================================

    const char* sql_select = "SELECT id, nombre, apellido FROM alumnos WHERE id = ?";
    sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr);

	// Vincular variables
    sqlite3_bind_int64(stmt, 1, id_creado);

    // Equivalente a res->next() en MySQL
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0); // La columna 0 es 'id'
        const unsigned char* nombre = sqlite3_column_text(stmt, 1); // La columna 1 es 'nombre'

        std::cout << "Alumno leido: ID " << id << " - " << nombre << std::endl;
    }
    sqlite3_finalize(stmt);

	// ===========================================================================================

    const char* sql_update = "UPDATE alumnos SET nombre = ? WHERE id = ?";
    sqlite3_prepare_v2(db, sql_update, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, "NuevoNombre", -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, id_creado);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

	// =====================================================================

    const char* sql_delete = "DELETE FROM alumnos WHERE id = ?";
    sqlite3_prepare_v2(db, sql_delete, -1, &stmt, nullptr);
    sqlite3_bind_int64(stmt, 1, id_creado);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

}

void insertarAlumno(sqlite3* db, const std::string& nombre) {
	char* zErrMsg = 0;

	std::string query = "INSERT INTO alumnos ("
		" nombre , apellido)"
		" VALUES ('Alan', 'Bautista')";

	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cout << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
	}
	else {
		std::cout << "Consulta ejecutada con éxito" << std::endl;
	}
}

void testSQLite() {
	sqlite3* db;
	char* zErrMsg = 0;

	int rc = sqlite3_open("escuela.db", &db);

	if (rc) {
		std::cout << "Error al abrir el archivo de base de datos" << std::endl;
		sqlite3_close(db);
		return;
	}


	sqlite3_close(db);
}

