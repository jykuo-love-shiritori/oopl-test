build = cmakeBuild
buildCache = $(build)/Makefile

test: $(buildCache)
	@echo "[CMake] make"
	@cmake --build $(build)
	@echo "[Google Test]"
	@$(build)/hello_test --gtest_color=yes
	@#ctest --test-dir $(build)

$(buildCache):
	@echo "[CMake] build"
	@mkdir -p $(build)
	@cmake -S . -B $(build)

clean:
	rm -rf $(build)

