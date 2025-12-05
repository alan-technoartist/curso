#include <exception>
#include <string>
namespace InventarioNuevo {

	class NoEncontradoExcp : public std::exception {
	private:
		std::string mensaje;

	public:
		NoEncontradoExcp(std::string m);

		const char* what() const noexcept override;
	};
}