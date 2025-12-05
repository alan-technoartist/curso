#include <iostream>
#include <memory>
#include <string>
#include <vector>


class PlannerException : public std::exception {
public:
    PlannerException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
private:
    std::string message;
};

// Excepciones específicas
class InvalidTaskTypeException : public PlannerException {
public:
    InvalidTaskTypeException(const std::string& msg) : PlannerException(msg) {}
};

class TaskNotFoundException : public PlannerException {
public:
    TaskNotFoundException(const std::string& msg) : PlannerException(msg) {}
};

// Clase Abstracta y clases concretas (solo la declaración de la interfaz)
class Task {
public:
    virtual void MarkAsCompleted() = 0;
    virtual void DisplayDetails() const = 0;
    virtual std::string GetRecurrenceType() const = 0;
    virtual std::string GetTitle() const = 0; // Se añade para búsqueda
    virtual ~Task() = default;
};

class OneTimeTask : public Task {};
class RecurringTask : public Task {};
class PriorityTask : public Task {};

// Patrón Factory
class TaskFactory {
public:
    std::unique_ptr<Task> CreateTask(const std::string& type, const std::string& title, const std::string& deadline, const std::string& recurrence = "");
};

// Patrón Singleton
class TaskManager {
private:
    TaskManager() = default;
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

public:
    static TaskManager& GetInstance();
    void AddTask(std::unique_ptr<Task> task);
    Task* GetTask(const std::string& title);
    void ListAllTasks() const;
    void GenerateReport() const;

private:
    std::vector<std::unique_ptr<Task>> tasks;
};

template <typename T>
void SortTasks(T& taskContainer) {
    // Aquí se implementaría la lógica de ordenamiento genérica
    // std::sort(taskContainer.begin(), taskContainer.end(), [](const auto& a, const auto& b) { /* lógica de ordenamiento */ });
}


int main() {
    // 1. Uso del Patrón Singleton (TaskManager)
    // Se obtiene la única instancia del TaskManager
    TaskManager& planner = TaskManager::GetInstance();
    TaskFactory factory;

    // 2. Uso del Patrón Factory y Polimorfismo
    try {
        // Tarea Única
        std::unique_ptr<Task> task1 = factory.CreateTask("OneTime", "Proyecto Final C++", "2025-12-01");
        planner.AddTask(std::move(task1)); // Añadir polimórficamente

        // Tarea Recurrente
        std::unique_ptr<Task> task2 = factory.CreateTask("Recurring", "Reunión de Equipo", "2025-10-31", "Semanal");
        planner.AddTask(std::move(task2));

        // Tarea Prioritaria
        std::unique_ptr<Task> task3 = factory.CreateTask("Priority", "Preparar Presentación", "2025-11-15");
        planner.AddTask(std::move(task3));

        std::cout << "Tareas creadas y añadidas exitosamente.\n";
    }
    catch (const PlannerException& e) {
        std::cerr << "Excepción de Factory: " << e.what() << "\n";
    }

    // 3. Demostración de Polimorfismo

    // Listar tareas (Usa polimorfismo al llamar a DisplayDetails() en cada Task)
    planner.ListAllTasks();

    // Marcar una tarea como completada
    try {
        Task* t = planner.GetTask("Reunión de Equipo");
        if (t) {
            std::cout << "-> Marcando 'Reunión de Equipo' como completada...\n";
            t->MarkAsCompleted(); // Llamada polimórfica (podría reajustar la fecha si es recurrente)
            std::cout << "   Tipo de recurrencia: " << t->GetRecurrenceType() << "\n";
        }
    }
    catch (const TaskNotFoundException& e) {
        std::cerr << "Error de búsqueda: " << e.what() << "\n";
    }

    // Generar reporte final
    planner.GenerateReport();

    // 4. Demostración de Excepciones Personalizadas
    try {
        // Prueba 4a: InvalidTaskTypeException (lanzada por el Factory)
        std::cout << "-> Intentando crear un tipo de tarea inválido...\n";
        std::unique_ptr<Task> invalidTask = factory.CreateTask("NonExistent", "Tarea Falsa", "2025-01-01");
        // Si el factory estuviera implementado, esta línea fallaría y no se ejecutaría la siguiente
        planner.AddTask(std::move(invalidTask)); // Esta línea no debería ejecutarse

    }
    catch (const InvalidTaskTypeException& e) {
        std::cout << "   EXCEPCIÓN CAPTURADA: " << e.what() << "\n";
    }
    catch (const PlannerException& e) {
        std::cerr << "Excepción Genérica: " << e.what() << "\n";
    }

    try {
        // Prueba 4b: TaskNotFoundException (lanzada por el TaskManager::GetTask)
        std::cout << "-> Intentando obtener una tarea que no existe...\n";
        Task* nonExisting = planner.GetTask("Tarea Que No Existe");
        if (!nonExisting) { // Esto es necesario si GetTask devuelve nullptr en la implementación de prueba
            throw TaskNotFoundException("Tarea con título 'Tarea Que No Existe' no encontrada.");
        }
    }
    catch (const TaskNotFoundException& e) {
        std::cout << "   EXCEPCIÓN CAPTURADA: " << e.what() << "\n";
    }


    // 5. Uso de Plantillas
    // La plantilla SortTasks debe funcionar con el contenedor interno del TaskManager (simulado)
    // Asumimos que podemos obtener una referencia al contenedor para este ejemplo de prueba.

    // Nota: En la implementación real, SortTasks podría ser un método del TaskManager, 
    // o el TaskManager podría exponer una forma segura de acceder al contenedor.

    std::vector<std::string> dummyContainer = { "Z", "A", "M" };
    SortTasks(dummyContainer); // La plantilla funciona con std::vector<std::string>
    // En la implementación real, llamaría a SortTasks(planner.getTasks());

    std::cout << "Finalización del código de prueba.\n";

    return 0;
}