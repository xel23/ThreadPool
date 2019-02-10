#pragma once

class Wrapper {
private:
	struct implBase {
		virtual void call() = 0;
		virtual ~implBase() {}
	};

	std::unique_ptr<implBase> impl;

	template<class F>
	struct implType : implBase {
		F f;
		implType(F&& f_) : f(std::move(f_)) {}
		void call() { f(); }
	};
public:
	template<class F>
	Wrapper(F&& f) : impl(new implType<F>(std::move(f))) {}
	
	void operator() () {
		impl->call();
	}

	Wrapper() = default;

	Wrapper(Wrapper&& other) : impl(std::move(other.impl)) {}

	Wrapper & operator=(Wrapper&& other) {
		impl = std::move(other.impl);
		return *this;
	}

	Wrapper(const Wrapper&) = delete;
	Wrapper(Wrapper&) = delete;
	Wrapper & operator=(const Wrapper &) = delete;
};
