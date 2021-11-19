#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "gasHeader.hpp"

TEST_CASE("processText() Testing", "[processtext]") {
	REQUIRE(processText("The Adventure of the Speckled Band.txt", 1) == true);
}


TEST_CASE("newFolder() Testing", "[newfolder]") {
	REQUIRE(newFolder() == true);
}

TEST_CASE("makeHeader1() Testing", "[makeheader]") {
	REQUIRE(makeHeader1("# hello") == "<h1>hello</h1>");
}

TEST_CASE("hzRule() Testing", "[hzrule]") {
	REQUIRE(hzRule("---") == "<hr>");
}

TEST_CASE("isText() Testing", "[istext]") {
	REQUIRE(isText("The Adventure of the Speckled Band.txt") == true);
}

TEST_CASE("isMarkDown() Testing", "[ismarkdown]") {
	REQUIRE(isMarkDown("readme.md") == true);
}

TEST_CASE("isFolder() Testing", "[isfolder]") {
	REQUIRE(isFolder("./dist") == true);
}

TEST_CASE("isJson() Testing", "[isjson]") {
	REQUIRE(isJson("ssg-config.json") == true);
}

TEST_CASE("getJsonValue() Testing", "[getjsonvalue]") {
	REQUIRE(getJsonValue("input: \"README.md\"") == "README.md");
}

TEST_CASE("processJsonFormat() Testing", "[processjsonformat]") {
	REQUIRE(processJsonFormat("ssg-config.json") == true);
}