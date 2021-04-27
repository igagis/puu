#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../src/treeml/tree.hpp"

namespace{
tst::set set1("parser_correctness", [](auto& suite){
	suite.template add<std::pair<const char*, const char*>>(
			"single_slash_is_parsed_as_node",
			// the test checks start 5th element is as expected
			{
				{"a b c d e f g", "f"},
				{"a b c d e / g", "/"},
				{"a b c d e /\rg", "/"},
				{"a b c d e /\tg", "/"},
				{"a b c d e /\ng", "/"},
				{"a b c d e / /g", "/"},
				{"a b c d e /f g", "/f"},
				{"a b c d e /{z} g", "/"},
				{"a b c d e //{z} g\nf g", "f"},
			},
			[](auto& p){
				auto r = treeml::read(p.first);

				tst::check_ge(r.size(), size_t(5), SL);

				tst::check_eq(r[5].value.to_string(), std::string(p.second), SL);
			}
		);
});
}