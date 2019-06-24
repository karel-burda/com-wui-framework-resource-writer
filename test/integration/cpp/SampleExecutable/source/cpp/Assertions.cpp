#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Assertions.hpp"

namespace Assertions {
    const int foo = 0;
    const std::string baz = "baz";

    static void Assert(bool condition) {
        if (!condition) {
            std::cerr << "Assertion failed, exiting" << std::endl;

            std::exit(1);
        }
    }

    static void Dummy(int i, int j) {
        Assert(i == j);

        if (i > 1024) {
            return;
        }

        Dummy(++i, ++j);
    }

    static void TestStack() {
        std::clog << "Testing stack" << std::endl;

        Dummy(0, 0);
    }

    static void TestHeap() {
        std::clog << "Testing heap" << std::endl;

        struct Structure {
            std::string id;
        };

        constexpr size_t numberOfElements = 2048;
        std::vector<std::unique_ptr<Structure>> collection;
        collection.reserve(numberOfElements);
        for (size_t i = 0; i < numberOfElements; ++i) {
            collection.emplace_back(std::make_unique<Structure>(Structure{"Structure" + std::to_string(i)}));
        }
        for (size_t i = 0; i < numberOfElements; ++i) {
            Assert(collection[i]->id == "Structure" + std::to_string(i));
        }
    }

    static void TestData(int boo) {
        std::clog << "Testing data sections" << std::endl;

        Assert(foo == 0);
        Assert(baz == "baz");
        Assert(boo == -99);
    }

    void Test() {
        TestStack();
        TestHeap();

        int boo = -99;
        TestData(boo);
    }
}