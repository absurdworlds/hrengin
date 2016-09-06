#include <aw/utility/string/join.h>
#include <aw/utility/string/split.h>
#include <aw/utility/test.h>

TestFile("Combined tests");

namespace aw {
Test(split_and_join) {
	std::string s = "word1 word2 word3";
	std::vector<std::string> v;
	std::string r;

	Setup {
		v = string::split(s, " ");
	}

	Preconditions {
		std::vector<std::string> e{"word1", "word2", "word3"};
		test::check<test::equal>(v, e);
	}

	Checks {
		r = string::join(v, " ");
	}

	Postconditions {
		test::check<test::equal>(r, s);
	}
}

Test(join_and_split) {
	std::string s;
	std::vector<std::string> v{"word1", "word2", "word3"};
	std::vector<std::string> r;

	Setup {
		s = string::join(v, ", ");
	}

	Preconditions {
		test::check<test::equal>(s, "word1, word2, word3");
	}

	Checks {
		r = string::split(s, ", ");
	}

	Postconditions {
		test::check<test::equal>(r, v);
	}
}

Test(join_and_split2) {
	std::string s;
	std::vector<std::string> v{"word1", "word2", "word3"};
	std::vector<std::string> r;

	Setup {
		s = string::join(v, ", ");
	}

	Preconditions {
		test::check<test::equal>(s, "word1, word2, word3");
	}

	Checks {
		r = string::explode(s, ", ");
	}

	Postconditions {
		test::check<test::equal>(r, v);
	}
}
} // namespace aw

RunTests();
