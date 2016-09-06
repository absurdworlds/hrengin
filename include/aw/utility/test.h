/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_test_h
#define aw_test_test_h
#include <utility>
#include <functional>
#include <exception>
#include <vector>
#include <iostream>
#include <aw/config.h>
#include <aw/utility/static_object.h>
#if AW_PLATFORM < AW_PLATFORM_WIN32
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <cstdio>
#endif

/*!
 * This header is made for awlib internal tests.
 * It is so simple and crude, that it doesn't even
 * deserve separate directory.
 */

int main(int,char**);

namespace aw {
#if AW_PLATFORM < AW_PLATFORM_WIN32
char const bold[]  = "\033[1m";
char const red[]   = "\033[31m";
char const green[] = "\033[32m";
char const white[] = "\033[37m";
char const reset[] = "\033[0m";
#else
char const bold[]  = "";
char const red[]   = "";
char const green[] = "";
char const white[] = "";
char const reset[] = "";
#endif

namespace test {
enum class stage : size_t {
	start,
	setup,
	preconditions,
	checks,
	postconditions,
	end
};

static char const* stage_name[] {
	"start",
	"setup",
	"preconditions",
	"checks",
	"postconditions",
	"end"
};

struct test {
	using test_function = void();
	test(char const* name, test_function* func)
		: name{name}, func{func}
	{ }

	char const*    const name;

private:
	friend struct context;

	test_function* const func;

	stage st = stage::start;

	size_t failed   = 0;
	size_t succeded = 0;
};

struct test_failed : std::exception {};

template<typename... Args>
void print(Args&&...args)
{
	( std::cerr << ... << std::forward<Args>(args) );
}

namespace {
class context_check;
class context_block;
class register_test;
}

class registry {
	friend int ::main(int, char**);
	friend struct context;
	class _ctxs {
		friend class registry;
		std::vector<struct context*> ctxs;
	public:
		_ctxs() = default;
	};

	static void add(context& ctx)
	{
		auto& vec = static_object<_ctxs>::instance().ctxs;
		vec.push_back(&ctx);
	}

	inline static int run();
};

struct context {
	context(char const* filename)
		: filename(filename)
	{
		registry::add(*this);
	}

	test& current() { return *cur; }
	char const* const filename;

	int run()
	{
		install_handler();

		print(bold, '[', filename, ']', ' ', reset);
		print("running tests\n");

		for (size_t i = 0, e = tests.size(); i < e; ++i) {
			print(bold, '[', i+1, '/', e, ']', ' ', reset);
			run_test(tests[i]);
		}

		size_t succeded = tests.size() - failed;

		print(bold, '[', filename, ']', ' ', reset);
		print("tests done, failed: ");
		print(bold, (failed > 0 ? red : white), failed, reset);
		print(", succeeded: ");
		print(bold, (succeded > 0 ? green : white), succeded, reset);
		print(reset, '\n');

		return failed;
	}

private:
	friend class aw::test::context_check;
	friend class aw::test::context_block;
	friend class aw::test::register_test;

	inline static void segvhandler(int signum);

	void install_handler()
	{
#if AW_PLATFORM < AW_PLATFORM_WIN32
		signal(SIGSEGV, segvhandler);
#endif
	}

	inline void run_test(test& tst);

	void enter(stage st)
	{
		if (cur->failed > 0)
			throw test_failed{};
		cur->st = st;
	}

	void leave()
	{
	}

	void add_test(test&& tst)
	{
		tests.push_back(std::move(tst));
	}

	void check_fail()
	{
		++cur->failed;
	}

	void check_succeed()
	{
		++cur->succeded;
	}

private:
	test* cur;
	std::vector<test> tests;
	unsigned failed = 0;
};

int registry::run()
{
	auto& vec = static_object<_ctxs>::instance().ctxs;

	int res = 0;
	for (auto& ctx : vec)
		res += ctx->run();

	return res > 0xFF ? 0xFF : res;
}

void context::run_test(test& tst)
{
	cur = &tst;
	print("test \"", bold, cur->name, reset, '"');
	try {
		enter(stage::start);
		cur->func();
		enter(stage::end);
		print(bold, green, " succeded, checks: ", cur->succeded, reset, '\n');
	} catch (test_failed& ex) {
		++failed;
		print(bold, red, " failed: (", stage_name[size_t(cur->st)], ") ", reset);
		print(red, "failed checks: ", bold, cur->failed, reset);
		print(green, ", succeded checks: ", bold, cur->succeded, reset, '\n');
	}
}

namespace {
extern context file_context;
}

void context::segvhandler(int signum)
{
#if AW_PLATFORM < AW_PLATFORM_WIN32
	static constexpr char desc[] = "\nCaught SIGSEGV, aborting tests.\n";
	std::fwrite(desc, sizeof(desc), 1, stderr);
	signal(signum, SIG_DFL);
	kill(getpid(), signum);
#endif
}

namespace {
class context_check {
	template<template <typename...> class Checker, typename... Args>
	friend void check(Args&&... args);

	static void check_fail()
	{
		file_context.check_fail();
	}
	static void check_succeed()
	{
		file_context.check_succeed();
	}
};

class context_block {
	friend bool setup();
	friend bool preconditions();
	friend bool checks();
	friend bool postconditions();

	static void enter(stage st)
	{
		file_context.enter(st);
	}
	static void leave()
	{
		file_context.leave();
	}
};

class register_test {
protected:
	void add_test(test&& tst)
	{
		file_context.add_test(std::move(tst));
	}
};

bool setup()          { context_block::enter(stage::setup); return true; }
bool preconditions()  { context_block::enter(stage::preconditions); return true; }
bool checks()         { context_block::enter(stage::checks); return true; }
bool postconditions() { context_block::enter(stage::postconditions); return true; }

template<template <typename...> class Checker, typename... Args>
void check(Args&&... args)
{
	Checker<Args...> check;
	check(std::forward<Args>(args)...) ?
		context_check::check_succeed() :
		context_check::check_fail();
}
} // namespace

template<typename A, typename B>
struct equal {
	bool operator()(A const& a, B const& b)
	{
		return a == b;
	}
};
} // namespace test
} // namespace aw

#define TestFile(name) namespace aw { namespace test { namespace { context file_context{name}; } } }
#define Test(name)     \
	void run_test_##name(); \
	struct Add_test_##name : aw::test::register_test { \
		Add_test_##name() { \
			add_test(aw::test::test{#name, run_test_##name}); \
		} \
	} add_test_##name; \
	void run_test_##name()
#define Setup          if (aw::test::setup())
#define Preconditions  if (aw::test::preconditions())
#define Checks         if (aw::test::checks())
#define Postconditions if (aw::test::postconditions())
#define RunTests()     int main(int,char**) { return aw::test::registry::run(); }

#endif//aw_test_test_h
