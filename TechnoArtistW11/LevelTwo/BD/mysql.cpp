#include <mysql/jdbc.h>

void mostrarCursos(const std::unique_ptr<sql::Connection>& con) {
	// Crear objeto Statement
	std::unique_ptr< sql::Statement > stmt (con->createStatement());

	// Ejecutar query y asignar a ResultSet
	std::unique_ptr< sql::ResultSet >
		res(stmt->executeQuery("SELECT * FROM CURSOS"));

	// Leer resultado
	while (res->next()) {
		std::cout << res->getString("nombre_curso") << std::endl;
	}
}

void buscarCurso(const std::unique_ptr<sql::Connection>& con, const std::string& curso) {
	std::string nombreCurso = "%" + curso + "%";

	std::string query = "SELECT * FROM CURSOS WHERE nombre_curso LIKE ?";

	// Crear objeto PreparedStatement
	std::unique_ptr<sql::PreparedStatement> pst(con->prepareStatement(query));
	// Asociar ? con variable
	pst->setString(1, nombreCurso);

	// Ejecutar query y asignar a ResultSet
	std::unique_ptr<sql::ResultSet> res (pst->executeQuery());

	//if (res->isNull(1)) {
	//	std::cout << "No se encontraron registros" << std::endl;
	//}

	// Leer resultado
	while (res->next()) {

		std::cout << res->getString("nombre_curso") << std::endl;
	}

}

void testMySQL() {
	try {
		// Obtener singleton
		sql::Driver* driver = sql::mysql::get_driver_instance();

		// Conectar al servidor
		std::unique_ptr<sql::Connection> con(driver->connect("localhost", "alan", "technoartist"));

		// Equivalente a "USE escuela"
		con->setSchema("escuela");

		std::string curso;
		std::cin >> curso;
		buscarCurso(con, curso);

	}
	catch (const sql::SQLException& e) {
		std::cout << e.what() << std::endl;

	}
}