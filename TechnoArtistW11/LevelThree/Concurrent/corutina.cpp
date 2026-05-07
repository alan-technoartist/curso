#include <coroutine>
#include <iostream>
#include <boost/asio.hpp>

// std::generator (C++23)
struct Generador {
	struct promise_type {
		int valor;

		Generador get_return_object() {
			return Generador{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		std::suspend_always initial_suspend() {
			return {};
		}
		std::suspend_always final_suspend() noexcept {
			return {};
		}
		std::suspend_always yield_value(int i) {
			valor = i;
			return {};
		}
		void unhandled_exception() {
			std::terminate();
		}

		void return_void() {
		}
	};

	std::coroutine_handle<promise_type> handle;

	Generador(std::coroutine_handle<promise_type> h) : handle(h) {}
	~Generador() {
		if (handle)
			handle.destroy();
	}

	int siguiente() {
		handle.resume();
		return handle.promise().valor;
	}
};

// Corutina
Generador generar(int max) {
	int i = 0;

	while(true)
		co_yield i++;
}

void testCorutina() {
	auto generador = generar(6);

	for (int i = 0; i < 6; i++)
		std::cout << generador.siguiente() << std::endl;


}