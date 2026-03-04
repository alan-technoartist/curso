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

	if (res->rowsCount() == 0) {
		std::cout << "No se encontraron registros" << std::endl;
		return;
	}

	// Leer resultado
	while (res->next()) {
		std::cout << res->getString("nombre_curso") << std::endl;
	}

}

void insertarAlumno(const std::unique_ptr<sql::Connection>& con) {
	std::string query = "INSERT INTO alumnos (nombre, apellido, edad) VALUES(?, ? ,?)";

	std::string nombreAlumno;
	std::string apellidoAlumno;
	int edadAlumno;

	std::cout << "Nombre: ";
	std::cin >> nombreAlumno;
	std::cout << "Apellido: ";
	std::cin >> apellidoAlumno;
	std::cout << "Edad: ";
	std::cin >> edadAlumno;

	// Crear objeto PreparedStatement
	std::unique_ptr<sql::PreparedStatement> pst(con->prepareStatement(query));

	// Asociar ??? con variable
	pst->setString(1, nombreAlumno);
	pst->setString(2, apellidoAlumno);
	pst->setInt(3, edadAlumno);

	// Ejecutar query
	pst->executeUpdate();
}

void mostrarAlumnos(const std::unique_ptr<sql::Connection>& con) {
	std::string query = "SELECT alumnos.nombre AS nombre, alumnos.apellido AS apellido, cursos.nombre_curso AS curso"
						" FROM alumnos"
						" LEFT JOIN inscripciones ON alumnos.id = inscripciones.alumno_id"
						" LEFT JOIN cursos ON cursos.id = inscripciones.curso_id";

	// Crear objeto Statement
	std::unique_ptr< sql::Statement > stmt(con->createStatement());

	// Ejecutar query y asignar a ResultSet
	std::unique_ptr< sql::ResultSet > res(stmt->executeQuery(query));

	if (res->rowsCount() == 0) {
		std::cout << "No se encontraron registros" << std::endl;
		return;
	}

	// Leer resultado
	while (res->next()) {
		std::cout << res->getString("nombre") << " | ";
		std::cout << res->getString("apellido") << " | ";

		if (! res->isNull("curso"))
			std::cout << res->getString("curso") << std::endl;
		else
			std::cout << "Sin curso asignado" << std::endl;
	}
}

void eliminarAlumno(const std::unique_ptr<sql::Connection>& con) {
	std::string query = "INSERT INTO alumnos (nombre, apellido, edad) VALUES(?, ? ,?)";

	std::string nombreAlumno;
	std::string apellidoAlumno;
	int edadAlumno;

	std::cout << "Nombre: ";
	std::cin >> nombreAlumno;
	std::cout << "Apellido: ";
	std::cin >> apellidoAlumno;
	std::cout << "Edad: ";
	std::cin >> edadAlumno;

	// Crear objeto PreparedStatement
	std::unique_ptr<sql::PreparedStatement> pst(con->prepareStatement(query));

	// Asociar ??? con variable
	pst->setString(1, nombreAlumno);
	pst->setString(2, apellidoAlumno);
	pst->setInt(3, edadAlumno);

	// Ejecutar query
	pst->executeUpdate();
}

void testMySQL() {
	try {
		// Obtener singleton
		sql::Driver* driver = sql::mysql::get_driver_instance();

		// Conectar al servidor
		std::unique_ptr<sql::Connection> con(driver->connect("localhost", "alan", "technoartist"));

		// Equivalente a "USE escuela"
		con->setSchema("escuela");

		//std::string curso;
		//std::cin >> curso;
		//buscarCurso(con, curso);

		//insertarAlumno(con);

		mostrarAlumnos(con);
	}
	catch (const sql::SQLException& e) {
		std::cout << e.what() << std::endl;

	}
}