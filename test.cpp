#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "gasHeader.hpp"

TEST_CASE("processText() Testing", "[processtext]") {
	REQUIRE(processText("The Adventure of the Speckled Band", 1) == true);
}


TEST_CASE("newFolder() Testing", "[newfolder]") {
	REQUIRE(newFolder() == true);
	REQUIRE(newFolder(" ") == false);
}

TEST_CASE("makeHeader1() Testing", "[makeheader]") {
	REQUIRE(makeHeader1("hello") == "<h1>hello</h1>");
}

TEST_CASE("hzRule() Testing", "[hzrule]") {
	REQUIRE(makeHeader1("---") == "<hr>");
}

TEST_CASE("isText() Testing", "[istext]") {
	REQUIRE(isText("The Adventure of the Speckled Band.txt") == true);
}

TEST_CASE("isText() Testing (not .txt file)", "[istext]") {
	REQUIRE(isText("The Adventure of the Speckled Band.md") == false);
	REQUIRE(isText("The Adventure of the Speckled Band") == false);
}

TEST_CASE("isMarkDown() Testing", "[ismarkdown]") {
	REQUIRE(isMarkDown("readme.md") == true);
}

TEST_CASE("isMarkDown() Testing (not .md file)", "[ismarkdown]") {
	REQUIRE(isMarkDown("The Adventure of the Speckled Band.txt") == false);
	REQUIRE(isMarkDown("The Adventure of the Speckled Band") == false);
}

TEST_CASE("isFolder() Testing", "[isfolder]") {
	REQUIRE(isFolder("./dist") == true);
}

TEST_CASE("isFolder() Testing (not folder)", "[isfolder]") {
	REQUIRE(isFolder("The Adventure of the Speckled Band.txt") == false);
	REQUIRE(isFolder("The Adventure of the Speckled Band.json") == false);
}

TEST_CASE("isJson() Testing", "[isjson]") {
	REQUIRE(isJson("ssg-config.json") == true);
}

TEST_CASE("isJson() Testing (not .json file)", "[isjson]") {
	REQUIRE(isJson("The Adventure of the Speckled Band.txt") == false);
	REQUIRE(isJson("The Adventure of the Speckled Band") == false);
}

TEST_CASE("getJsonValue() Testing", "[getjsonvalue]") {
	REQUIRE(getJsonValue("\"input:\" \"README.md\"") == "README.md");
}

TEST_CASE("processJsonFormat() Testing", "[processjsonformat]") {
	REQUIRE(processJsonFormat("ssg-config.json") == true);
}